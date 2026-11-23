/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#include "Aq20Actions.h"
#include "Aq20Helpers.h"
#include "EncounterHelpers.h"
#include "GameObject.h"
#include "Playerbots.h"
#include "WorldPacket.h"
#include "WorldSession.h"

using namespace Aq20Helpers;
using namespace EncounterHelpers;

// Shared

bool Aq20TankBossAction::Execute(Event /*event*/)
{
    Unit* boss = FindThreatCreature(bot, _bossEntry);
    if (!boss)
        return false;

    if (AI_VALUE(Unit*, "current target") != boss)
        return Attack(boss);

    return _taunt && boss->GetVictim() != bot && CastTankTaunt(botAI, boss);
}

bool Aq20AttackNearestAddAction::Execute(Event /*event*/)
{
    Unit* add = GetNearestAttackableCachedUnit(botAI, _addsValue);
    if (!add)
        return false;

    return AI_VALUE(Unit*, "current target") != add && Attack(add);
}

bool Aq20MoveAwayFromCreatureHazardAction::Execute(Event /*event*/)
{
    Position safePos;
    if (!FindPositionAwayFromCachedUnits(botAI, _hazardValue, _radius, safePos))
        return false;

    bot->CastStop();
    return MoveTo(
        AQ20_MAP_ID, safePos.GetPositionX(), safePos.GetPositionY(), bot->GetPositionZ(), false,
        false, false, false, MovementPriority::MOVEMENT_FORCED, true, false);
}

bool Aq20MoveAwayFromGameObjectHazardAction::Execute(Event /*event*/)
{
    Position safePos;
    if (!FindPositionAwayFromCachedGameObjects(botAI, _hazardValue, _radius, safePos))
        return false;

    bot->CastStop();
    return MoveTo(
        AQ20_MAP_ID, safePos.GetPositionX(), safePos.GetPositionY(), bot->GetPositionZ(), false,
        false, false, false, MovementPriority::MOVEMENT_FORCED, true, false);
}

// Buru the Gorger

bool BuruLureBossToEggAction::Execute(Event /*event*/)
{
    Unit* egg = GetNearestBuruEgg(botAI);
    if (!egg)
        return false;

    // Buru has to be standing in the explosion, so the bot goes all the way onto the egg.
    constexpr float stopDistance = 0.0f;
    float stepX;
    float stepY;
    if (!GetPathStepTowardUnit(bot, egg, stopDistance, PATH_STEP_DISTANCE, stepX, stepY))
        return false;

    return MoveTo(
        AQ20_MAP_ID, stepX, stepY, bot->GetPositionZ(), false, false, false, false,
        MovementPriority::MOVEMENT_COMBAT, true, false);
}

bool BuruAttackTargetEggAction::Execute(Event /*event*/)
{
    Unit* egg = GetBuruTargetEgg(botAI);
    if (!egg)
        return false;

    if (AI_VALUE(Unit*, "current target") != egg)
        return Attack(egg);

    return MarkTargetWithSkull(bot, egg);
}

// Ossirian the Unscarred

bool OssirianTankMoveToCrystalAction::Execute(Event /*event*/)
{
    GameObject* crystal = GetUsableOssirianCrystal(botAI);
    if (!crystal)
        return false;

    float stepX;
    float stepY;
    if (!GetPathStepTowardPoint(
            bot, crystal->GetPosition(), CRYSTAL_INTERACT_DISTANCE, PATH_STEP_DISTANCE, stepX,
            stepY))
    {
        return false;
    }

    return MoveTo(
        AQ20_MAP_ID, stepX, stepY, bot->GetPositionZ(), false, false, false, false,
        MovementPriority::MOVEMENT_COMBAT, true, false);
}

bool OssirianUseCrystalAction::Execute(Event /*event*/)
{
    GameObject* crystal = GetUsableOssirianCrystal(botAI);
    if (!crystal || !bot->GetSession())
        return false;

    if (bot->GetExactDist(crystal) > CRYSTAL_INTERACT_DISTANCE)
        return false;

    // Two packets, because the crystal's gossip hook only rolls the weakness when the core marks
    // the click as a report use (OSS:330). The plain use is what plays the crystal's animation.
    WorldPacket use(CMSG_GAMEOBJ_USE);
    use << crystal->GetGUID();
    bot->GetSession()->HandleGameObjectUseOpcode(use);

    WorldPacket reportUse(CMSG_GAMEOBJ_REPORT_USE);
    reportUse << crystal->GetGUID();
    bot->GetSession()->HandleGameobjectReportUse(reportUse);

    return true;
}
