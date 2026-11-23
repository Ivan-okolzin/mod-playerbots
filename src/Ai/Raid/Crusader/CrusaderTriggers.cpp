/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#include "CrusaderTriggers.h"
#include "CrusaderHelpers.h"
#include "EncounterHelpers.h"
#include "Playerbots.h"

using namespace CrusaderHelpers;
using namespace EncounterHelpers;

// Shared

bool CrusaderBossShouldBeTankedTrigger::IsActiveInEncounter()
{
    if (!PlayerbotAI::IsMainTank(bot))
        return false;

    // Anub'arak spends a minute of every phase under the floor and untargetable (BAT:319), which
    // is what keeps this object out of that phase.
    Unit* boss = FindThreatCreature(bot, _bossEntry);
    return IsAttackableNow(boss) && AI_VALUE(Unit*, "current target") != boss;
}

bool CrusaderRangedShouldSpreadTrigger::IsActiveInEncounter()
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

bool CrusaderAddsSpawnedTrigger::IsActiveInEncounter()
{
    switch (_role)
    {
        case CrusaderAddRole::MeleeAndTanks:
            if (!PlayerbotAI::IsMelee(bot) && !PlayerbotAI::IsTank(bot))
                return false;
            break;
        case CrusaderAddRole::Tanks:
            if (!PlayerbotAI::IsTank(bot))
                return false;
            break;
        case CrusaderAddRole::RangedDps:
            if (!PlayerbotAI::IsRangedDps(bot))
                return false;
            break;
        case CrusaderAddRole::Everyone:
            if (PlayerbotAI::IsHeal(bot))
                return false;
            break;
    }

    Unit* add = GetNearestAttackableCachedUnit(botAI, _addsValue);
    return add && AI_VALUE(Unit*, "current target") != add;
}

bool CrusaderBotNearHazardTrigger::IsActiveInEncounter()
{
    return IsNearCachedUnit(botAI, _hazardValue, _radius);
}

// Gormok the Impaler

bool GormokSnoboldOnRaidMemberTrigger::IsActiveInEncounter()
{
    if (!PlayerbotAI::IsRangedDps(bot))
        return false;

    Unit* snobold = GetNearestLatchedSnobold(botAI);
    return snobold && AI_VALUE(Unit*, "current target") != snobold;
}

// The tank keeps Gormok and healers keep healing: the Snobold rides on somebody, so whoever is
// standing next to its carrier can reach it anyway.
bool GormokBotIsSnobolledTrigger::IsActiveInEncounter()
{
    if (PlayerbotAI::IsTank(bot) || PlayerbotAI::IsHeal(bot))
        return false;

    if (!IsSnobolled(botAI, bot))
        return false;

    Unit* snobold = GetNearestLatchedSnobold(botAI);
    return snobold && AI_VALUE(Unit*, "current target") != snobold;
}

bool GormokMainTankImpaleStacksTrigger::IsActiveInEncounter()
{
    if (!PlayerbotAI::IsAssistTankOfIndex(bot, 0, true))
        return false;

    Unit* gormok = FindThreatCreature(bot, Id(CrusaderNpcs::NPC_GORMOK));
    if (!gormok)
        return false;

    Unit* mainTank = AI_VALUE(Unit*, "main tank");
    if (!mainTank || gormok->GetVictim() != mainTank)
        return false;

    return GetAuraStacks(mainTank, Id(CrusaderSpells::SPELL_IMPALE)) >= IMPALE_SWAP_STACKS;
}

// Acidmaw and Dreadscale

bool JormungarShouldBeTankedTrigger::IsActiveInEncounter()
{
    Unit* worm = GetAssignedWorm(botAI);
    if (!worm)
        return false;

    // Every emerge wipes the worms' threat (BNB:799), so holding the target is not enough.
    return AI_VALUE(Unit*, "current target") != worm || worm->GetVictim() != bot;
}

// Icehowl

bool IcehowlChargeIncomingTrigger::IsActiveInEncounter()
{
    Unit* icehowl = FindThreatCreature(bot, Id(CrusaderNpcs::NPC_ICEHOWL));
    if (!IsIcehowlCharging(icehowl))
        return false;

    if (!GetNearestCachedUnit(botAI, ICEHOWL_CHARGE_STALKERS_VALUE))
        return false;

    return icehowl->HasInLine(bot, TRAMPLE_LANE_WIDTH);
}

bool IcehowlBotNearArenaWallTrigger::IsActiveInEncounter()
{
    Unit* icehowl = FindThreatCreature(bot, Id(CrusaderNpcs::NPC_ICEHOWL));
    if (!IsIcehowlCharging(icehowl))
        return false;

    // Once the stalker is up the lane is known, and leaving it is the better move.
    if (GetNearestCachedUnit(botAI, ICEHOWL_CHARGE_STALKERS_VALUE))
        return false;

    return bot->GetExactDist2d(ARENA_CENTER_X, ARENA_CENTER_Y) > ARENA_WALL_DISTANCE;
}

// Faction Champions

bool FactionChampionsShouldFocusTargetTrigger::IsActiveInEncounter()
{
    if (PlayerbotAI::IsHeal(bot))
        return false;

    Unit* focus = FindFactionChampionFocus(bot);
    return focus && AI_VALUE(Unit*, "current target") != focus;
}

// Twin Val'kyr

bool ValkyrBotHasNoEssenceTrigger::IsActiveInEncounter()
{
    if (GetEssence(bot) != CrusaderEssence::None)
        return false;

    // The Essences are summoned with the twins and despawn with them (BTV:533, :559), so finding
    // one is what says this encounter is the one being fought.
    uint32 const entry = GetAssignedEssence(bot) == CrusaderEssence::Light ?
        Id(CrusaderNpcs::NPC_LIGHT_ESSENCE) : Id(CrusaderNpcs::NPC_DARK_ESSENCE);

    return GetNearestCachedUnitOfEntry(botAI, VALKYR_ESSENCES_VALUE, entry) != nullptr;
}

// Fjola's damage is all light and Eydis's all dark, so each tank holds the twin whose colour its
// essence absorbs.
bool ValkyrShouldBeTankedTrigger::IsActiveInEncounter()
{
    uint32 twinEntry = 0;
    if (PlayerbotAI::IsMainTank(bot))
        twinEntry = Id(CrusaderNpcs::NPC_FJOLA_LIGHTBANE);
    else if (PlayerbotAI::IsAssistTankOfIndex(bot, 0, true))
        twinEntry = Id(CrusaderNpcs::NPC_EYDIS_DARKBANE);

    if (!twinEntry)
        return false;

    Unit* twin = FindThreatCreature(bot, twinEntry);
    return twin && AI_VALUE(Unit*, "current target") != twin;
}

bool ValkyrPactIncomingTrigger::IsActiveInEncounter()
{
    if (PlayerbotAI::IsTank(bot) || PlayerbotAI::IsHeal(bot))
        return false;

    Unit* twin = GetPactingTwin(botAI);
    return twin && AI_VALUE(Unit*, "current target") != twin;
}

bool ValkyrBallNearbyTrigger::IsActiveInEncounter()
{
    // Tanks hold their twin rather than walk off after a ball; getting out of the way of one that
    // would hurt them is another matter.
    if (_matching && PlayerbotAI::IsTank(bot))
        return false;

    char const* value = GetBallValue(bot, _matching);
    return value && IsNearCachedUnit(botAI, value, _radius);
}

// Anub'arak

bool AnubarakBotPursuedBySpikeTrigger::IsActiveInEncounter()
{
    return IsPursuedBySpike(botAI, bot);
}

bool AnubarakBotNearSpikeTrigger::IsActiveInEncounter()
{
    if (IsPursuedBySpike(botAI, bot))
        return false;

    return IsNearCachedUnit(botAI, ANUBARAK_SPIKES_VALUE, SPIKE_HAZARD_RADIUS);
}

bool AnubarakFrostSphereShouldBeDroppedTrigger::IsActiveInEncounter()
{
    if (!PlayerbotAI::IsRangedDps(bot))
        return false;

    Unit* anubarak = FindThreatCreature(bot, Id(CrusaderNpcs::NPC_ANUBARAK));
    if (!IsAnubarakSubmerged(anubarak))
        return false;

    // One patch at a time: while a sphere is already down the raid has somewhere to lead the
    // spike, and the rest of the damage belongs on the Burrowers.
    if (GetNearestPermafrost(botAI))
        return false;

    Unit* sphere = GetNearestHoveringFrostSphere(botAI);
    return sphere && AI_VALUE(Unit*, "current target") != sphere;
}
