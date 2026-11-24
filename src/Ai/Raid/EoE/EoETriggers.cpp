/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#include "EoETriggers.h"
#include "SharedDefines.h"

uint8 MalygosTrigger::getPhase(Player* bot, Unit* boss)
{
    uint8 phase = 0;
    Unit* vehicle = bot->GetVehicleBase();
    if (bot->GetMapId() != EOE_MAP_ID) { return phase; }

    if (vehicle && vehicle->GetEntry() == NPC_WYRMREST_SKYTALON)
    {
        phase = 3;
    }
    else if (boss && boss->HealthAbovePct(50))
    {
        phase = 1;
    }
    else if (boss)
    {
        phase = 2;
    }

    return phase;
}

bool MalygosTrigger::IsActive()
{
    return bool(AI_VALUE2(Unit*, "find target", "malygos"));
}

Unit* PowerSparkTrigger::FindTarget(PlayerbotAI* botAI, Unit* boss)
{
    Player* bot = botAI->GetBot();
    if (!PlayerbotAI::IsRangedDps(bot) || MalygosTrigger::getPhase(bot, boss) != 1)
        return nullptr;

    auto* context = botAI->GetAiObjectContext();
    Unit* closest = nullptr;
    for (ObjectGuid const& guid : AI_VALUE(GuidVector, "possible targets"))
    {
        Unit* unit = botAI->GetUnit(guid);
        if (unit && unit->GetEntry() == NPC_POWER_SPARK && bot->IsValidAttackTarget(unit) &&
            (!closest || unit->GetDistance(boss) < closest->GetDistance(boss)))
            closest = unit;
    }

    return closest;
}

bool PowerSparkTrigger::IsActive()
{
    Unit* spark = FindTarget(botAI, AI_VALUE2(Unit*, "find target", "malygos"));
    return spark && spark != AI_VALUE(Unit*, "current target");
}
