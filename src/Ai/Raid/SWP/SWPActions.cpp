/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#include "SWPActions.h"
#include "EncounterHelpers.h"
#include "Playerbots.h"
#include "SWPHelpers.h"
#include <algorithm>
#include <cmath>

using namespace EncounterHelpers;
using namespace SwpHelpers;

// Shared

bool SwpAttackCreatureAction::Execute(Event /*event*/)
{
    Unit* target = FindThreatCreature(bot, _entry);
    if (!target)
        return false;

    return AI_VALUE(Unit*, "current target") != target && Attack(target);
}

bool SwpAttackNearestAddAction::Execute(Event /*event*/)
{
    Unit* add = GetNearestCachedUnit(botAI, _addsValue);
    if (!add)
        return false;

    return AI_VALUE(Unit*, "current target") != add && Attack(add);
}

bool SwpSpreadRangedAction::Execute(Event /*event*/)
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

bool SwpMoveAwayFromHazardAction::Execute(Event /*event*/)
{
    Position safePos;
    if (!FindPositionAwayFromCachedUnits(botAI, _hazardValue, _radius, safePos))
        return false;

    bot->CastStop();
    return MoveTo(
        SWP_MAP_ID, safePos.GetPositionX(), safePos.GetPositionY(), bot->GetPositionZ(), false,
        false, false, false, MovementPriority::MOVEMENT_FORCED, true, false);
}

bool SwpStopAttackingCharmedAllyAction::Execute(Event /*event*/)
{
    Unit* target = AI_VALUE(Unit*, "current target");
    if (!target)
        return false;

    bool acted = StopAttackingTarget(bot, *target);

    if (Unit* boss = FindThreatCreature(bot, _bossEntry))
        acted = SelectTarget(botAI, boss) || acted;

    return acted;
}

// Brutallus

bool SwpFleeNearestPlayerAction::Execute(Event /*event*/)
{
    Player* nearestPlayer = GetNearestPlayerInRadius(bot, _distance);
    if (!nearestPlayer)
        return false;

    constexpr uint32 minInterval = 0;
    return FleePosition(nearestPlayer->GetPosition(), _distance, minInterval);
}

bool SwpMoveBehindBossAction::Execute(Event /*event*/)
{
    Unit* boss = FindThreatCreature(bot, _bossEntry);
    if (!boss)
        return false;

    constexpr float minRadius = 6.0f;
    constexpr float stepDistance = 8.0f;
    float const radius = std::max(boss->GetExactDist2d(bot), minRadius);
    float const behind = boss->GetOrientation() + static_cast<float>(M_PI);
    float const safeX = boss->GetPositionX() + radius * std::cos(behind);
    float const safeY = boss->GetPositionY() + radius * std::sin(behind);

    float stepX;
    float stepY;
    float stepZ;
    if (!CanTakeStepTowards(bot, safeX, safeY, stepDistance, stepX, stepY, stepZ))
        return false;

    return MoveTo(
        SWP_MAP_ID, stepX, stepY, stepZ, false, false, false, false,
        MovementPriority::MOVEMENT_COMBAT, true, false);
}

// Eredar Twins

bool EredarTwinsAssignTanksAction::Execute(Event /*event*/)
{
    uint32 twinEntry = 0;
    if (PlayerbotAI::IsMainTank(bot))
        twinEntry = Id(SwpNpcs::NPC_LADY_SACROLASH);
    else if (PlayerbotAI::IsAssistTankOfIndex(bot, 0, true))
        twinEntry = Id(SwpNpcs::NPC_GRAND_WARLOCK_ALYTHESS);

    if (!twinEntry)
        return false;

    Unit* twin = FindThreatCreature(bot, twinEntry);
    if (!twin)
        return false;

    return AI_VALUE(Unit*, "current target") != twin && Attack(twin);
}

// Felmyst

bool FelmystMoveOutOfBreathPathAction::Execute(Event /*event*/)
{
    Unit* felmyst = FindThreatCreature(bot, Id(SwpNpcs::NPC_FELMYST));
    if (!felmyst)
        return false;

    // GetRelativeAngle is normalized to [0, 2pi), so a bot left of the lane reads below pi. It
    // keeps going to the side it is already on, which is the shorter way out of the lane.
    constexpr float quarterTurn = static_cast<float>(M_PI) / 2.0f;
    bool const leftOfLane = felmyst->GetRelativeAngle(bot) < static_cast<float>(M_PI);
    float const sideways = leftOfLane ? felmyst->GetOrientation() + quarterTurn :
        felmyst->GetOrientation() - quarterTurn;

    float const safeX = bot->GetPositionX() + BREATH_DODGE_DISTANCE * std::cos(sideways);
    float const safeY = bot->GetPositionY() + BREATH_DODGE_DISTANCE * std::sin(sideways);

    constexpr float stepDistance = 10.0f;
    float stepX;
    float stepY;
    float stepZ;
    if (!CanTakeStepTowards(bot, safeX, safeY, stepDistance, stepX, stepY, stepZ))
        return false;

    bot->CastStop();
    return MoveTo(
        SWP_MAP_ID, stepX, stepY, stepZ, false, false, false, false,
        MovementPriority::MOVEMENT_FORCED, true, false);
}
