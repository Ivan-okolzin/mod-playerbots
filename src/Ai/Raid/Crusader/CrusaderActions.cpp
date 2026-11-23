/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#include "CrusaderActions.h"
#include "CrusaderHelpers.h"
#include "EncounterHelpers.h"
#include "Playerbots.h"
#include "WorldPacket.h"
#include "WorldSession.h"
#include <algorithm>
#include <cmath>

using namespace CrusaderHelpers;
using namespace EncounterHelpers;

// Shared

bool CrusaderAttackCreatureAction::Execute(Event /*event*/)
{
    Unit* target = FindThreatCreature(bot, _entry);
    if (!target)
        return false;

    return AI_VALUE(Unit*, "current target") != target && Attack(target);
}

bool CrusaderAttackNearestAddAction::Execute(Event /*event*/)
{
    Unit* add = GetNearestAttackableCachedUnit(botAI, _addsValue);
    if (!add)
        return false;

    return AI_VALUE(Unit*, "current target") != add && Attack(add);
}

bool CrusaderSpreadRangedAction::Execute(Event /*event*/)
{
    Unit* boss = FindThreatCreature(bot, _bossEntry);
    if (!boss)
        return false;

    constexpr uint32 minInterval = 0;
    if (bot->GetExactDist(boss) < _distanceFromBoss &&
        FleePosition(boss->GetPosition(), _distanceFromBoss, minInterval))
    {
        return true;
    }

    Player* nearestPlayer = GetNearestPlayerInRadius(bot, SPREAD_DISTANCE);
    return nearestPlayer && FleePosition(nearestPlayer->GetPosition(), SPREAD_DISTANCE);
}

bool CrusaderMoveAwayFromHazardAction::Execute(Event /*event*/)
{
    Position safePos;
    if (!FindPositionAwayFromCachedUnits(botAI, _hazardValue, _radius, safePos))
        return false;

    bot->CastStop();
    return MoveTo(
        CRUSADER_MAP_ID, safePos.GetPositionX(), safePos.GetPositionY(), bot->GetPositionZ(), false,
        false, false, false, MovementPriority::MOVEMENT_FORCED, true, false);
}

// Gormok the Impaler

bool GormokAttackNearestSnoboldAction::Execute(Event /*event*/)
{
    Unit* snobold = GetNearestLatchedSnobold(botAI);
    if (!snobold)
        return false;

    return AI_VALUE(Unit*, "current target") != snobold && Attack(snobold);
}

bool GormokTankSwapAction::Execute(Event /*event*/)
{
    Unit* gormok = FindThreatCreature(bot, Id(CrusaderNpcs::NPC_GORMOK));
    if (!gormok)
        return false;

    if (AI_VALUE(Unit*, "current target") != gormok && !Attack(gormok))
        return false;

    return CastTankTaunt(botAI, gormok);
}

// Acidmaw and Dreadscale

bool JormungarAssignTanksAction::Execute(Event /*event*/)
{
    Unit* worm = GetAssignedWorm(botAI);
    if (!worm)
        return false;

    if (AI_VALUE(Unit*, "current target") != worm)
        return Attack(worm);

    return worm->GetVictim() != bot && CastTankTaunt(botAI, worm);
}

// Icehowl

bool IcehowlMoveOutOfChargePathAction::Execute(Event /*event*/)
{
    Unit* icehowl = FindThreatCreature(bot, Id(CrusaderNpcs::NPC_ICEHOWL));
    if (!IsIcehowlCharging(icehowl))
        return false;

    // GetRelativeAngle is normalized to [0, 2pi), so a bot left of the lane reads below pi. It
    // keeps going to the side it is already on, which is the shorter way out of the lane.
    constexpr float quarterTurn = static_cast<float>(M_PI) / 2.0f;
    bool const leftOfLane = icehowl->GetRelativeAngle(bot) < static_cast<float>(M_PI);
    float const sideways = leftOfLane ? icehowl->GetOrientation() + quarterTurn :
        icehowl->GetOrientation() - quarterTurn;

    float const safeX = bot->GetPositionX() + TRAMPLE_DODGE_DISTANCE * std::cos(sideways);
    float const safeY = bot->GetPositionY() + TRAMPLE_DODGE_DISTANCE * std::sin(sideways);

    constexpr float stepDistance = 10.0f;
    float stepX;
    float stepY;
    float stepZ;
    if (!CanTakeStepTowards(bot, safeX, safeY, stepDistance, stepX, stepY, stepZ))
        return false;

    bot->CastStop();
    return MoveTo(
        CRUSADER_MAP_ID, stepX, stepY, stepZ, false, false, false, false,
        MovementPriority::MOVEMENT_FORCED, true, false);
}

bool IcehowlMoveAwayFromArenaWallAction::Execute(Event /*event*/)
{
    Position const center(ARENA_CENTER_X, ARENA_CENTER_Y, bot->GetPositionZ());

    float stepX;
    float stepY;
    if (!GetPathStepTowardPoint(bot, center, ARENA_SAFE_DISTANCE, PATH_STEP_DISTANCE, stepX, stepY))
        return false;

    return MoveTo(
        CRUSADER_MAP_ID, stepX, stepY, bot->GetPositionZ(), false, false, false, false,
        MovementPriority::MOVEMENT_COMBAT, true, false);
}

// Faction Champions

bool FactionChampionsAttackFocusTargetAction::Execute(Event /*event*/)
{
    Unit* focus = FindFactionChampionFocus(bot);
    if (!focus)
        return false;

    if (AI_VALUE(Unit*, "current target") != focus)
        return Attack(focus);

    return MarkTargetWithSkull(bot, focus);
}

// Twin Val'kyr

bool ValkyrTakeEssenceAction::Execute(Event /*event*/)
{
    uint32 const entry = GetAssignedEssence(bot) == CrusaderEssence::Light ?
        Id(CrusaderNpcs::NPC_LIGHT_ESSENCE) : Id(CrusaderNpcs::NPC_DARK_ESSENCE);

    Unit* essence = GetNearestCachedUnitOfEntry(botAI, VALKYR_ESSENCES_VALUE, entry);
    if (!essence)
        return false;

    if (bot->GetExactDist(essence) > ESSENCE_INTERACT_DISTANCE)
    {
        float stepX;
        float stepY;
        if (!GetPathStepTowardUnit(
                bot, essence, ESSENCE_INTERACT_DISTANCE, PATH_STEP_DISTANCE, stepX, stepY))
        {
            return false;
        }

        return MoveTo(
            CRUSADER_MAP_ID, stepX, stepY, bot->GetPositionZ(), false, false, false, false,
            MovementPriority::MOVEMENT_COMBAT, true, false);
    }

    if (!bot->GetSession())
        return false;

    // The Essences carry no gossip options of their own: the aura swap happens in the encounter
    // script's gossip hello hook (BTV:574), so sending the hello is the whole click.
    WorldPacket packet;
    packet << essence->GetGUID();
    bot->GetSession()->HandleGossipHelloOpcode(packet);

    return GetEssence(bot) != CrusaderEssence::None;
}

bool ValkyrAssignTanksAction::Execute(Event /*event*/)
{
    uint32 twinEntry = 0;
    if (PlayerbotAI::IsMainTank(bot))
        twinEntry = Id(CrusaderNpcs::NPC_FJOLA_LIGHTBANE);
    else if (PlayerbotAI::IsAssistTankOfIndex(bot, 0, true))
        twinEntry = Id(CrusaderNpcs::NPC_EYDIS_DARKBANE);

    if (!twinEntry)
        return false;

    Unit* twin = FindThreatCreature(bot, twinEntry);
    if (!twin)
        return false;

    return AI_VALUE(Unit*, "current target") != twin && Attack(twin);
}

bool ValkyrAttackPactingTwinAction::Execute(Event /*event*/)
{
    Unit* twin = GetPactingTwin(botAI);
    if (!twin)
        return false;

    return AI_VALUE(Unit*, "current target") != twin && Attack(twin);
}

bool ValkyrMoveAwayFromBallAction::Execute(Event /*event*/)
{
    constexpr bool matching = false;
    char const* value = GetBallValue(bot, matching);
    if (!value)
        return false;

    Position safePos;
    if (!FindPositionAwayFromCachedUnits(botAI, value, BALL_BURST_RADIUS, safePos))
        return false;

    bot->CastStop();
    return MoveTo(
        CRUSADER_MAP_ID, safePos.GetPositionX(), safePos.GetPositionY(), bot->GetPositionZ(), false,
        false, false, false, MovementPriority::MOVEMENT_FORCED, true, false);
}

bool ValkyrCollectMatchingBallAction::Execute(Event /*event*/)
{
    constexpr bool matching = true;
    char const* value = GetBallValue(bot, matching);
    if (!value)
        return false;

    Unit* ball = GetNearestCachedUnit(botAI, value);
    if (!ball)
        return false;

    // The ball bursts on its own as soon as the bot is next to it (BTV:880), so walking onto it
    // is all there is to do.
    constexpr float stopDistance = 0.0f;
    float stepX;
    float stepY;
    if (!GetPathStepTowardUnit(bot, ball, stopDistance, PATH_STEP_DISTANCE, stepX, stepY))
        return false;

    return MoveTo(
        CRUSADER_MAP_ID, stepX, stepY, bot->GetPositionZ(), false, false, false, false,
        MovementPriority::MOVEMENT_COMBAT, true, false);
}

// Anub'arak

bool AnubarakFleeToPermafrostAction::Execute(Event /*event*/)
{
    Unit* permafrost = GetNearestPermafrost(botAI);
    if (!permafrost)
        return false;

    // The spike dies when it comes within 8 yards of the patch, and it is right behind the bot,
    // so the bot only has to reach the edge of it.
    constexpr float stopDistance = 2.0f;
    float stepX;
    float stepY;
    if (!GetPathStepTowardUnit(bot, permafrost, stopDistance, PATH_STEP_DISTANCE, stepX, stepY))
        return false;

    bot->CastStop();
    return MoveTo(
        CRUSADER_MAP_ID, stepX, stepY, bot->GetPositionZ(), false, false, false, false,
        MovementPriority::MOVEMENT_FORCED, true, false);
}

bool AnubarakFleeFromSpikeAction::Execute(Event /*event*/)
{
    Unit* spike = GetNearestCachedUnit(botAI, ANUBARAK_SPIKES_VALUE);
    if (!spike)
        return false;

    bot->CastStop();
    constexpr uint32 minInterval = 0;
    return FleePosition(spike->GetPosition(), SPIKE_ESCAPE_DISTANCE, minInterval);
}

bool AnubarakShootDownFrostSphereAction::Execute(Event /*event*/)
{
    Unit* sphere = GetNearestHoveringFrostSphere(botAI);
    if (!sphere)
        return false;

    return AI_VALUE(Unit*, "current target") != sphere && Attack(sphere);
}
