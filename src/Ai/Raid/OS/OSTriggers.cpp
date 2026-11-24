/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#include "OSTriggers.h"
#include "InstanceScript.h"
#include "SharedDefines.h"

bool SartharionTankTrigger::IsActive()
{
    Unit* boss = AI_VALUE2(Unit*, "find target", "sartharion");
    if (!boss) { return false; }

    return PlayerbotAI::IsTank(bot);
}

bool FlameTsunamiTrigger::IsActive()
{
    if (PlayerbotAI::IsTank(bot)) { return false; }

    Unit* boss = AI_VALUE2(Unit*, "find target", "sartharion");
    if (!boss) { return false; }

    GuidVector npcs = AI_VALUE(GuidVector, "nearest hostile npcs");
    for (auto& npc : npcs)
    {
        Unit* unit = botAI->GetUnit(npc);
        if (unit)
        {
            if (unit->GetEntry() == NPC_FLAME_TSUNAMI)
            {
                return true;
            }
        }
    }

    return false;
}

bool TwilightFissureTrigger::IsActive()
{
    GuidVector npcs = AI_VALUE(GuidVector, "nearest hostile npcs");
    for (auto& npc : npcs)
    {
        Unit* unit = botAI->GetUnit(npc);
        if (unit)
        {
            if (unit->GetEntry() == NPC_TWILIGHT_FISSURE)
            {
                return true;
            }
        }
    }

    return false;
}

bool SartharionDpsTrigger::IsActive()
{
    if (bot->HasAura(SPELL_TWILIGHT_SHIFT))
        return PlayerbotAI::IsDps(bot);

    Unit* boss = AI_VALUE2(Unit*, "find target", "sartharion");
    if (!boss) { return false; }

    return PlayerbotAI::IsDps(bot);
}

bool SartharionMeleePositioningTrigger::IsActive()
{
    if (!PlayerbotAI::IsMelee(bot) || !PlayerbotAI::IsDps(bot)) { return false; }

    Unit* target = AI_VALUE(Unit*, "current target");
    if (target && (target->GetEntry() == NPC_TENEBRON || target->GetEntry() == NPC_SHADRON ||
                   target->GetEntry() == NPC_VESPERON))
        return true;

    Unit* boss = AI_VALUE2(Unit*, "find target", "sartharion");
    if (!boss) { return false; }

    Unit* shadron = AI_VALUE2(Unit*, "find target", "shadron");
    Unit* tenebron = AI_VALUE2(Unit*, "find target", "tenebron");
    Unit* vesperon = AI_VALUE2(Unit*, "find target", "vesperon");

    return !(shadron || tenebron || vesperon);
}

bool IsStandaloneTenebronActive(Player* bot)
{
    constexpr uint32 dataTenebron = 1;
    InstanceScript* instance = bot->GetInstanceScript();
    return instance && instance->GetBossState(dataTenebron) == IN_PROGRESS;
}

bool ShouldEnterTwilightPortal(PlayerbotAI* botAI)
{
    Player* bot = botAI->GetBot();
    if (bot->HasAura(SPELL_TWILIGHT_SHIFT) || PlayerbotAI::IsTank(bot) || PlayerbotAI::IsAssistHealOfIndex(bot, 0))
        return false;

    if (IsStandaloneTenebronActive(bot))
        return true;

    AiObjectContext* context = botAI->GetAiObjectContext();
    Unit* sartharion = AI_VALUE2(Unit*, "find target", "sartharion");
    if (sartharion && sartharion->HasAura(SPELL_GIFT_OF_TWILIGHT_FIRE))
        return true;

    Unit* shadron = AI_VALUE2(Unit*, "find target", "shadron");
    Unit* vesperon = AI_VALUE2(Unit*, "find target", "vesperon");
    return (shadron && shadron->HasAura(SPELL_GIFT_OF_TWILIGHT_SHADOW)) ||
           (vesperon && (vesperon->HasAura(SPELL_TWILIGHT_TORMENT_VESPERON) ||
                         vesperon->HasAura(SPELL_TWILIGHT_TORMENT_SARTHARION) ||
                         bot->HasAura(SPELL_TWILIGHT_TORMENT_VESPERON))) ||
           (sartharion && bot->HasAura(SPELL_TWILIGHT_TORMENT_SARTHARION));
}

bool TwilightPortalEnterTrigger::IsActive()
{
    return ShouldEnterTwilightPortal(botAI);
}

bool TwilightPortalExitTrigger::IsActive()
{
    return bot->HasAura(SPELL_TWILIGHT_SHIFT) && !IsStandaloneTenebronActive(bot);
}
