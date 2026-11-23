/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#include "SWPTriggers.h"
#include "EncounterHelpers.h"
#include "Playerbots.h"
#include "SWPHelpers.h"

using namespace EncounterHelpers;
using namespace SwpHelpers;

// Shared

bool SwpBossShouldBeTankedTrigger::IsActiveInEncounter()
{
    if (!PlayerbotAI::IsMainTank(bot))
        return false;

    Unit* boss = FindThreatCreature(bot, _bossEntry);
    return boss && AI_VALUE(Unit*, "current target") != boss;
}

bool SwpRangedShouldSpreadTrigger::IsActiveInEncounter()
{
    if (!PlayerbotAI::IsRanged(bot))
        return false;

    Unit* boss = FindThreatCreature(bot, _bossEntry);
    if (!boss || boss->GetVictim() == bot)
        return false;

    if (bot->GetExactDist(boss) < _distanceFromBoss)
        return true;

    return GetNearestPlayerInRadius(bot, SPREAD_DISTANCE) != nullptr;
}

bool SwpAddsSpawnedTrigger::IsActiveInEncounter()
{
    switch (_role)
    {
        case SwpAddRole::MeleeAndTanks:
            if (!PlayerbotAI::IsMelee(bot) && !PlayerbotAI::IsTank(bot))
                return false;
            break;
        case SwpAddRole::Tanks:
            if (!PlayerbotAI::IsTank(bot))
                return false;
            break;
        case SwpAddRole::RangedDps:
            if (!PlayerbotAI::IsRangedDps(bot))
                return false;
            break;
        case SwpAddRole::Everyone:
            if (PlayerbotAI::IsHeal(bot))
                return false;
            break;
    }

    Unit* add = GetNearestCachedUnit(botAI, _addsValue);
    return add && AI_VALUE(Unit*, "current target") != add;
}

bool SwpBotNearHazardTrigger::IsActiveInEncounter()
{
    return IsNearCachedUnit(botAI, _hazardValue, _radius);
}

// Kalecgos

// Healers keep healing: picking a target for them would only cut a cast short.
bool KalecgosBotInSpectralRealmTrigger::IsActiveInEncounter()
{
    if (PlayerbotAI::IsHeal(bot))
        return false;

    if (!FindThreatCreature(bot, Id(SwpNpcs::NPC_KALECGOS)) &&
        !FindThreatCreature(bot, Id(SwpNpcs::NPC_SATHROVARR)))
    {
        return false;
    }

    if (!IsInSpectralRealm(bot))
        return false;

    Unit* sathrovarr = FindThreatCreature(bot, Id(SwpNpcs::NPC_SATHROVARR));
    return sathrovarr && AI_VALUE(Unit*, "current target") != sathrovarr;
}

bool KalecgosBotInDragonRealmTrigger::IsActiveInEncounter()
{
    if (PlayerbotAI::IsHeal(bot))
        return false;

    if (IsInSpectralRealm(bot))
        return false;

    Unit* kalecgos = FindThreatCreature(bot, Id(SwpNpcs::NPC_KALECGOS));
    return kalecgos && AI_VALUE(Unit*, "current target") != kalecgos;
}

// Brutallus

bool BrutallusBotIsBurningTrigger::IsActiveInEncounter()
{
    if (!FindThreatCreature(bot, Id(SwpNpcs::NPC_BRUTALLUS)))
        return false;

    return IsBurning(bot) && GetNearestPlayerInRadius(bot, BURN_ESCAPE_DISTANCE) != nullptr;
}

bool BrutallusBotNearBurningAllyTrigger::IsActiveInEncounter()
{
    if (IsBurning(bot) || !FindThreatCreature(bot, Id(SwpNpcs::NPC_BRUTALLUS)))
        return false;

    Player* nearest = GetNearestPlayerInRadius(bot, BURN_ESCAPE_DISTANCE);
    return nearest && IsBurning(nearest);
}

bool BrutallusBotHasMeteorSlashTrigger::IsActiveInEncounter()
{
    if (PlayerbotAI::IsMainTank(bot))
        return false;

    if (!bot->HasAura(Id(SwpSpells::SPELL_METEOR_SLASH)))
        return false;

    Unit* brutallus = FindThreatCreature(bot, Id(SwpNpcs::NPC_BRUTALLUS));
    return brutallus && brutallus->HasInArc(METEOR_SLASH_ARC, bot);
}

// Felmyst

bool FelmystBreathIncomingTrigger::IsActiveInEncounter()
{
    Unit* felmyst = FindThreatCreature(bot, Id(SwpNpcs::NPC_FELMYST));
    if (!felmyst || !felmyst->HasAura(Id(SwpSpells::SPELL_FELMYST_SPEED_BURST)))
        return false;

    return felmyst->HasInLine(bot, BREATH_LANE_WIDTH);
}

bool SwpAttackingCharmedAllyTrigger::IsActiveInEncounter()
{
    Unit* target = AI_VALUE(Unit*, "current target");
    if (!target || !target->IsPlayer())
        return false;

    for (uint32 const spellId : _charmSpellIds)
    {
        if (target->HasAura(spellId))
            return true;
    }

    return false;
}

// Eredar Twins

// The main tank takes Lady Sacrolash, whose Shadow Blades and Confounding Blow land on whoever
// holds her, and the first assist tank takes Alythess, whose damage is all fire.
bool EredarTwinsShouldBeTankedTrigger::IsActiveInEncounter()
{
    if (PlayerbotAI::IsMainTank(bot))
        return FindThreatCreature(bot, Id(SwpNpcs::NPC_LADY_SACROLASH)) != nullptr;

    if (PlayerbotAI::IsAssistTankOfIndex(bot, 0, true))
        return FindThreatCreature(bot, Id(SwpNpcs::NPC_GRAND_WARLOCK_ALYTHESS)) != nullptr;

    return false;
}

bool EredarTwinsShouldSwitchTargetTrigger::IsActiveInEncounter()
{
    if (PlayerbotAI::IsTank(bot) || PlayerbotAI::IsHeal(bot))
        return false;

    if (_forMelee ? !PlayerbotAI::IsMelee(bot) : !PlayerbotAI::IsRangedDps(bot))
        return false;

    Unit* boss = FindThreatCreature(bot, _bossEntry);
    return boss && AI_VALUE(Unit*, "current target") != boss;
}
