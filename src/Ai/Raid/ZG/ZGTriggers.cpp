/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#include "ZGTriggers.h"
#include "EncounterHelpers.h"
#include "Playerbots.h"
#include "ZGHelpers.h"

using namespace EncounterHelpers;
using namespace ZulGurubHelpers;

// Shared

bool ZulGurubNoEncounterInProgressTrigger::IsActive()
{
    return !IsEncounterInProgress(bot, ZG_MAP_ID);
}

bool ZulGurubBossShouldBeTankedTrigger::IsActiveInEncounter()
{
    if (!PlayerbotAI::IsMainTank(bot))
        return false;

    Unit* boss = FindThreatCreature(bot, _bossEntry);
    if (!boss || IsUnassailable(boss))
        return false;

    return AI_VALUE(Unit*, "current target") != boss;
}

bool ZulGurubBossLostThreatTrigger::IsActiveInEncounter()
{
    if (!PlayerbotAI::IsTank(bot))
        return false;

    Unit* boss = FindThreatCreature(bot, _bossEntry);
    if (!boss || IsUnassailable(boss))
        return false;

    return IsBossOnNonTank(boss);
}

bool ZulGurubAddsSpawnedTrigger::IsActiveInEncounter()
{
    switch (_role)
    {
        case ZulGurubAddRole::Dps:
            // Healers are kept out of every target switch of this raid: a cut heal costs more
            // than an add lives.
            if (!PlayerbotAI::IsDps(bot) || PlayerbotAI::IsTank(bot) || PlayerbotAI::IsHeal(bot))
                return false;
            break;
        case ZulGurubAddRole::AssistTanks:
            if (!PlayerbotAI::IsAssistTank(bot))
                return false;
            break;
    }

    if (_bossEntry && !FindThreatCreature(bot, _bossEntry))
        return false;

    Unit* add = SelectCachedTarget(botAI, _addsValue);
    return add && AI_VALUE(Unit*, "current target") != add;
}

bool ZulGurubBotInHazardTrigger::IsActiveInEncounter()
{
    Unit* boss = FindThreatCreature(bot, _bossEntry);
    if (!boss)
        return false;

    if (_bossAura && !boss->HasAura(_bossAura))
        return false;

    return IsInHazard(botAI, _hazardValue, _radius);
}

bool ZulGurubRangedShouldSpreadTrigger::IsActiveInEncounter()
{
    if (!PlayerbotAI::IsRanged(bot))
        return false;

    Unit* boss = FindThreatCreature(bot, _bossEntry);
    if (!boss || boss->GetVictim() == bot)
        return false;

    return GetNearestPlayerInRadius(bot, SPREAD_DISTANCE) != nullptr;
}

bool ZulGurubAttackingCharmedAllyTrigger::IsActiveInEncounter()
{
    Unit* target = AI_VALUE(Unit*, "current target");
    if (!target || !target->IsPlayer())
        return false;

    return target->HasAura(_charmSpellId);
}

// The clouds stand in the Bloodfire Pit, where the Sons of Hakkar are cleared, so this only ever
// fires on the way to Hakkar and never during a fight.
bool ZulGurubShouldPickUpPoisonousBloodTrigger::IsActive()
{
    if (bot->GetMapId() != ZG_MAP_ID || bot->IsInCombat())
        return false;

    if (bot->HasAura(Id(ZulGurubSpells::SPELL_POISONOUS_BLOOD)))
        return false;

    if (bot->GetHealthPct() < POISON_PICKUP_MIN_HEALTH_PCT)
        return false;

    Unit* cloud = SelectCachedTarget(botAI, POISONOUS_CLOUDS_VALUE);
    return cloud && bot->GetExactDist2d(cloud) > POISON_PICKUP_STAND_DISTANCE;
}

// Bloodlord Mandokir

bool MandokirBotIsWatchedTrigger::IsActiveInEncounter()
{
    if (!FindThreatCreature(bot, Id(ZulGurubNpcs::NPC_MANDOKIR)))
        return false;

    return bot->HasAura(Id(ZulGurubSpells::SPELL_WATCH));
}

bool MandokirMeleeInWhirlwindRangeTrigger::IsActiveInEncounter()
{
    if (!PlayerbotAI::IsMelee(bot) || PlayerbotAI::IsTank(bot))
        return false;

    Unit* mandokir = FindThreatCreature(bot, Id(ZulGurubNpcs::NPC_MANDOKIR));
    if (!mandokir || !mandokir->HasAura(Id(ZulGurubSpells::SPELL_WHIRLWIND)))
        return false;

    return bot->GetExactDist(mandokir) < WHIRLWIND_ESCAPE_DISTANCE;
}

// High Priest Thekal

bool ThekalZealotsShouldBeTankedTrigger::IsActiveInEncounter()
{
    if (!IsThekalTrioFight(botAI))
        return false;

    for (uint8 index = 0; index < 2; ++index)
    {
        if (!PlayerbotAI::IsAssistTankOfIndex(bot, index, true))
            continue;

        uint32 const entry = index == 0 ? Id(ZulGurubNpcs::NPC_ZEALOT_LORKHAN)
                                        : Id(ZulGurubNpcs::NPC_ZEALOT_ZATH);
        Unit* zealot = GetCachedUnitOfEntry(botAI, THEKAL_TRIO_VALUE, entry);
        return zealot && AI_VALUE(Unit*, "current target") != zealot;
    }

    return false;
}

bool ThekalShouldBalanceTrioDamageTrigger::IsActiveInEncounter()
{
    if (PlayerbotAI::IsTank(bot) || PlayerbotAI::IsHeal(bot))
        return false;

    Unit* focus = GetThekalTrioFocus(botAI);
    return focus && AI_VALUE(Unit*, "current target") != focus;
}

// Jin'do the Hexxer

bool JindoHexedTankTrigger::IsActiveInEncounter()
{
    if (!PlayerbotAI::IsAssistTankOfIndex(bot, 0, true))
        return false;

    Unit* jindo = FindThreatCreature(bot, Id(ZulGurubNpcs::NPC_JINDO));
    if (!jindo)
        return false;

    Unit* victim = jindo->GetVictim();
    return victim && victim != bot && victim->HasAura(Id(ZulGurubSpells::SPELL_HEX));
}

// Gri'lek

bool GrilekBotIsPursuedTrigger::IsActiveInEncounter()
{
    if (PlayerbotAI::IsMainTank(bot))
        return false;

    Unit* grilek = FindThreatCreature(bot, Id(ZulGurubNpcs::NPC_GRILEK));
    if (!grilek || !grilek->HasAura(Id(ZulGurubSpells::SPELL_AVATAR)))
        return false;

    return grilek->GetVictim() == bot;
}
