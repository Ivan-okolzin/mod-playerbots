/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#include "NaxxActions.h"
#include "EncounterHelpers.h"
#include "NaxxHelpers.h"

using namespace NaxxHelpers;

uint32 RotateAroundTheCenterPointAction::FindNearestWaypoint()
{
    float minDistance = 0;
    int ret = -1;
    for (uint32 i = 0; i < intervals; i++)
    {
        float w_x = waypoints[i].first, w_y = waypoints[i].second;
        float dis = bot->GetDistance2d(w_x, w_y);
        if (ret == -1 || dis < minDistance)
        {
            ret = i;
            minDistance = dis;
        }
    }
    return ret;
}

bool NaxxAttackBossAction::Execute(Event /*event*/)
{
    Unit* boss = FindThreatCreature(bot, _bossEntry);
    if (!boss || !IsBossEngageable(botAI, boss))
        return false;

    return AI_VALUE(Unit*, "current target") != boss && Attack(boss);
}

bool NaxxAttackNearestAddAction::Execute(Event /*event*/)
{
    Unit* add = FindAdd();
    if (!add)
        return false;

    return AI_VALUE(Unit*, "current target") != add && Attack(add);
}

Unit* NaxxAttackNearestAddAction::FindAdd()
{
    Unit* add = GetNearestCachedUnit(botAI, _addsValue);
    return add && !IsUnassailable(add) ? add : nullptr;
}

Unit* NaxxDpsAttackAddAction::FindAdd()
{
    if (!HasRole(bot, NaxxRole::Dps) || !EncounterHelpers::IsEncounterInProgress(bot, NAXX_MAP_ID) ||
        !FindThreatCreature(bot, _bossEntry))
        return nullptr;

    return NaxxAttackNearestAddAction::FindAdd();
}
