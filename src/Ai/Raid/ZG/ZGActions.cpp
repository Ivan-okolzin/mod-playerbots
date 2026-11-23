/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#include "ZGActions.h"
#include "EncounterHelpers.h"
#include "Playerbots.h"
#include "RtiTargetValue.h"
#include "ZGHelpers.h"

using namespace EncounterHelpers;
using namespace ZulGurubHelpers;

// Shared

bool ZulGurubResetEncounterStatesAction::Execute(Event /*event*/)
{
    return ClearStrategyTargetIcon(
        bot, RtiTargetValue::skullIndex,
        { Id(ZulGurubNpcs::NPC_THEKAL), Id(ZulGurubNpcs::NPC_ZEALOT_LORKHAN),
          Id(ZulGurubNpcs::NPC_ZEALOT_ZATH) });
}

bool ZulGurubMainTankAttackBossAction::Execute(Event /*event*/)
{
    Unit* boss = FindThreatCreature(bot, _bossEntry);
    if (!boss || IsUnassailable(boss))
        return false;

    return AI_VALUE(Unit*, "current target") != boss && Attack(boss);
}

bool ZulGurubTankTauntBossAction::Execute(Event /*event*/)
{
    Unit* boss = FindThreatCreature(bot, _bossEntry);
    if (!boss || IsUnassailable(boss))
        return false;

    if (AI_VALUE(Unit*, "current target") != boss && !Attack(boss))
        return false;

    return CastTankTaunt(botAI, boss);
}

bool ZulGurubAttackNearestAddAction::Execute(Event /*event*/)
{
    Unit* add = GetNearestCachedUnit(botAI, _addsValue);
    if (!add || IsUnassailable(add))
        return false;

    return AI_VALUE(Unit*, "current target") != add && Attack(add);
}

bool ZulGurubMoveOutOfHazardAction::Execute(Event /*event*/)
{
    Position safePos;
    if (!FindPositionOutsideHazards(botAI, _hazardValue, _radius, safePos))
        return false;

    bot->CastStop();
    return MoveTo(
        ZG_MAP_ID, safePos.GetPositionX(), safePos.GetPositionY(), bot->GetPositionZ(), false,
        false, false, false, MovementPriority::MOVEMENT_FORCED, true, false);
}

bool ZulGurubSpreadRangedAction::Execute(Event /*event*/)
{
    Player* nearestPlayer = GetNearestPlayerInRadius(bot, SPREAD_DISTANCE);
    return nearestPlayer && FleePosition(nearestPlayer->GetPosition(), SPREAD_DISTANCE);
}

bool ZulGurubFleeFromCreatureAction::Execute(Event /*event*/)
{
    Unit* creature = FindThreatCreature(bot, _creatureEntry);
    if (!creature)
        return false;

    constexpr uint32 minInterval = 0;
    return FleePosition(creature->GetPosition(), _distance, minInterval);
}

bool ZulGurubStopAttackingCharmedAllyAction::Execute(Event /*event*/)
{
    Unit* target = AI_VALUE(Unit*, "current target");
    if (!target)
        return false;

    bool acted = StopAttackingTarget(bot, *target);

    if (Unit* boss = FindThreatCreature(bot, _bossEntry))
        acted = SelectTarget(botAI, boss) || acted;

    return acted;
}

bool ZulGurubMoveIntoPoisonousCloudAction::Execute(Event /*event*/)
{
    Unit* cloud = GetNearestCachedUnit(botAI, POISONOUS_CLOUDS_VALUE);
    if (!cloud)
        return false;

    float stepX;
    float stepY;
    if (!GetPathStepTowardUnit(
            bot, cloud, POISON_PICKUP_STAND_DISTANCE, PATH_STEP_DISTANCE, stepX, stepY))
    {
        return false;
    }

    return MoveTo(
        ZG_MAP_ID, stepX, stepY, bot->GetPositionZ(), false, false, false, false,
        MovementPriority::MOVEMENT_COMBAT, true, false);
}

// Bloodlord Mandokir

bool MandokirStopAttackingWhileWatchedAction::Execute(Event /*event*/)
{
    return StopAttackingAndChanneling(bot);
}

// High Priest Thekal

bool ThekalAssistTankAttackZealotAction::Execute(Event /*event*/)
{
    uint32 entry = 0;
    if (PlayerbotAI::IsAssistTankOfIndex(bot, 0, true))
        entry = Id(ZulGurubNpcs::NPC_ZEALOT_LORKHAN);
    else if (PlayerbotAI::IsAssistTankOfIndex(bot, 1, true))
        entry = Id(ZulGurubNpcs::NPC_ZEALOT_ZATH);

    if (!entry)
        return false;

    Unit* target = GetCachedUnitOfEntry(botAI, THEKAL_TRIO_VALUE, entry);
    if (!target || IsUnassailable(target))
        return false;

    return AI_VALUE(Unit*, "current target") != target && Attack(target);
}

bool ThekalAttackTrioFocusAction::Execute(Event /*event*/)
{
    Unit* focus = GetThekalTrioFocus(botAI);
    if (!focus)
        return false;

    if (AI_VALUE(Unit*, "current target") != focus)
        return Attack(focus);

    return MarkTargetWithSkull(bot, focus);
}
