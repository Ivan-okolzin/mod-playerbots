/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#include "VoAActions.h"
#include "Define.h"
#include "EncounterHelpers.h"
#include "Event.h"
#include "Group.h"
#include "ObjectGuid.h"
#include "Player.h"
#include "Playerbots.h"
#include "Unit.h"
#include "VoAHelpers.h"
#include "VoATriggers.h"
#include <cmath>

using namespace EncounterHelpers;
using namespace VoAHelpers;

const Position VOA_EMALON_RESTORE_POSITION = Position(-221.8f, -243.8f, 96.8f, 4.7f);

bool EmalonMarkBossAction::Execute(Event /*event*/)
{
    Unit* boss = AI_VALUE2(Unit*, "find target", "emalon the storm watcher");
    if (!boss || !boss->IsAlive())
    {
        return false;
    }

    bool isMainTank = PlayerbotAI::IsMainTank(bot);
    Unit* mainTankUnit = AI_VALUE(Unit*, "main tank");
    Player* mainTank = mainTankUnit ? mainTankUnit->ToPlayer() : nullptr;

    if (mainTank && !GET_PLAYERBOT_AI(mainTank))  // Main tank is a real player
    {
        // Iterate through the first 3 bot tanks to assign the Skull marker
        for (int i = 0; i < 3; ++i)
        {
            if (PlayerbotAI::IsAssistTankOfIndex(bot, i) && GET_PLAYERBOT_AI(bot))  // Bot is a valid tank
            {
                Group* group = bot->GetGroup();
                if (group && boss)
                {
                    int8 skullIndex = 7;  // Skull
                    ObjectGuid currentSkullTarget = group->GetTargetIcon(skullIndex);

                    // If there's no skull set yet, or the skull is on a different target, set boss
                    if (!currentSkullTarget || (boss->GetGUID() != currentSkullTarget))
                    {
                        group->SetTargetIcon(skullIndex, bot->GetGUID(), boss->GetGUID());
                        return true;
                    }
                }
                break;  // Stop after finding the first valid bot tank
            }
        }
    }
    else if (isMainTank)  // Bot is the main tank
    {
        Group* group = bot->GetGroup();
        if (group)
        {
            int8 skullIndex = 7;  // Skull
            ObjectGuid currentSkullTarget = group->GetTargetIcon(skullIndex);

            // If there's no skull set yet, or the skull is on a different target, set the Eonar's Gift
            if (!currentSkullTarget || (boss->GetGUID() != currentSkullTarget))
            {
                group->SetTargetIcon(skullIndex, bot->GetGUID(), boss->GetGUID());
                return true;
            }
        }
    }

    return false;
}

bool EmalonMarkBossAction::isUseful()
{
    EmalonMarkBossTrigger emalonMarkBossTrigger(botAI);
    return emalonMarkBossTrigger.IsActive();
}

bool EmalonLightingNovaAction::Execute(Event /*event*/)
{
    const float radius = 25.0f;  // 20 yards + 5 yard for safety for 10 man. For 25man there is no maximum range but 25 yards should be ok

    Unit* boss = AI_VALUE2(Unit*, "find target", "emalon the storm watcher");
    if (!boss)
        return false;

    float currentDistance = bot->GetDistance2d(boss);

    if (currentDistance < radius)
    {
        return MoveAway(boss, radius - currentDistance);
    }

    return false;
}

bool EmalonLightingNovaAction::isUseful()
{
    EmalonLightingNovaTrigger emalonLightingNovaTrigger(botAI);
    return emalonLightingNovaTrigger.IsActive();
}

bool EmalonOverchargeAction::Execute(Event /*event*/)
{
    Unit* minion = GetOverchargedMinion(botAI);
    if (!minion)
    {
        return false;
    }

    bool isMainTank = PlayerbotAI::IsMainTank(bot);
    Unit* mainTankUnit = AI_VALUE(Unit*, "main tank");
    Player* mainTank = mainTankUnit ? mainTankUnit->ToPlayer() : nullptr;

    if (mainTank && !GET_PLAYERBOT_AI(mainTank))  // Main tank is a real player
    {
        // Iterate through the first 3 bot tanks to assign the Skull marker
        for (int i = 0; i < 3; ++i)
        {
            if (PlayerbotAI::IsAssistTankOfIndex(bot, i) && GET_PLAYERBOT_AI(bot))  // Bot is a valid tank
            {
                Group* group = bot->GetGroup();
                if (group && minion)
                {
                    int8 skullIndex = 7;  // Skull
                    ObjectGuid currentSkullTarget = group->GetTargetIcon(skullIndex);

                    // If there's no skull set yet, or the skull is on a different target, set Tempest Minion
                    if (!currentSkullTarget || (minion->GetGUID() != currentSkullTarget))
                    {
                        group->SetTargetIcon(skullIndex, bot->GetGUID(), minion->GetGUID());
                        return true;
                    }
                }
                break;  // Stop after finding the first valid bot tank
            }
        }
    }
    else if (isMainTank)  // Bot is the main tank
    {
        Group* group = bot->GetGroup();
        if (group)
        {
            int8 skullIndex = 7;  // Skull
            ObjectGuid currentSkullTarget = group->GetTargetIcon(skullIndex);

            // If there's no skull set yet, or the skull is on a different target, set the Eonar's Gift
            if (!currentSkullTarget || (minion->GetGUID() != currentSkullTarget))
            {
                group->SetTargetIcon(skullIndex, bot->GetGUID(), minion->GetGUID());
                return true;
            }
        }
    }

    return false;
}

bool EmalonOverchargeAction::isUseful()
{
    EmalonOverchargeTrigger emalonOverchargeTrigger(botAI);
    return emalonOverchargeTrigger.IsActive();
}

bool EmalonFallFromFloorAction::Execute(Event /*event*/)
{
    return bot->TeleportTo(bot->GetMapId(), VOA_EMALON_RESTORE_POSITION.GetPositionX(),
                           VOA_EMALON_RESTORE_POSITION.GetPositionY(), VOA_EMALON_RESTORE_POSITION.GetPositionZ(),
                           VOA_EMALON_RESTORE_POSITION.GetOrientation());
}

bool EmalonFallFromFloorAction::isUseful()
{
    EmalonFallFromFloorTrigger emalonFallFromFloorTrigger(botAI);
    return emalonFallFromFloorTrigger.IsActive();
}

// Shared

bool VoAAttackCreatureAction::Execute(Event /*event*/)
{
    Unit* target = FindThreatCreature(bot, _entry);
    if (!target)
        return false;

    return AI_VALUE(Unit*, "current target") != target && Attack(target);
}

bool VoATankAttackNearestAddAction::Execute(Event /*event*/)
{
    Unit* add = GetNearestAttackableCachedUnit(botAI, _addsValue);
    if (!add)
        return false;

    if (AI_VALUE(Unit*, "current target") != add)
        return Attack(add);

    return add->GetVictim() != bot && CastTankTaunt(botAI, add);
}

bool VoAAttackNearestAddAction::Execute(Event /*event*/)
{
    Unit* add = GetNearestAttackableCachedUnit(botAI, _addsValue);
    if (!add)
        return false;

    return AI_VALUE(Unit*, "current target") != add && Attack(add);
}

bool VoASpreadRangedAction::Execute(Event /*event*/)
{
    if (!FindThreatCreature(bot, _bossEntry))
        return false;

    Player* nearestPlayer = GetNearestPlayerInRadius(bot, SPREAD_DISTANCE);
    return nearestPlayer && FleePosition(nearestPlayer->GetPosition(), SPREAD_DISTANCE);
}

bool VoAMoveAwayFromAddAction::Execute(Event /*event*/)
{
    Position safePos;
    if (!FindPositionAwayFromCachedUnits(botAI, _addsValue, _radius, safePos))
        return false;

    bot->CastStop();
    return MoveTo(
        VOA_MAP_ID, safePos.GetPositionX(), safePos.GetPositionY(), bot->GetPositionZ(), false,
        false, false, false, MovementPriority::MOVEMENT_FORCED, true, false);
}

// Emalon the Storm Watcher

bool EmalonAttackOverchargedMinionAction::Execute(Event /*event*/)
{
    Unit* minion = GetOverchargedMinion(botAI);
    if (!minion)
        return false;

    return AI_VALUE(Unit*, "current target") != minion && Attack(minion);
}

// Koralon the Flame Watcher

bool KoralonMoveBehindBossAction::Execute(Event /*event*/)
{
    Unit* koralon = FindThreatCreature(bot, Id(VoANpcs::NPC_KORALON));
    if (!IsBreathingFire(koralon))
        return false;

    float const behind = koralon->GetOrientation() + static_cast<float>(M_PI);
    float const x = koralon->GetPositionX() + BURNING_BREATH_REAR_DISTANCE * std::cos(behind);
    float const y = koralon->GetPositionY() + BURNING_BREATH_REAR_DISTANCE * std::sin(behind);

    bot->CastStop();
    return MoveTo(
        VOA_MAP_ID, x, y, koralon->GetPositionZ(), false, false, false, false,
        MovementPriority::MOVEMENT_FORCED, true, false);
}

// Toravon the Ice Watcher

bool ToravonFleeFromOrbAction::Execute(Event /*event*/)
{
    Unit* orb = GetPursuingFrozenOrb(botAI);
    if (!orb)
        return false;

    bot->CastStop();
    return FleePosition(orb->GetPosition(), FROZEN_ORB_ESCAPE_DISTANCE);
}

bool ToravonMoveOutOfFreezingGroundAction::Execute(Event /*event*/)
{
    Position safePos;
    if (!FindPositionOutsideHazards(
            botAI, TORAVON_FREEZING_GROUND_VALUE, FREEZING_GROUND_RADIUS, safePos))
    {
        return false;
    }

    bot->CastStop();
    return MoveTo(
        VOA_MAP_ID, safePos.GetPositionX(), safePos.GetPositionY(), bot->GetPositionZ(), false,
        false, false, false, MovementPriority::MOVEMENT_FORCED, true, false);
}
