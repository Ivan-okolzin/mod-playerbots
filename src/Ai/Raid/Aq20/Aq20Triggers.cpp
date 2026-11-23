/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#include "Aq20Triggers.h"
#include "Aq20Helpers.h"
#include "EncounterHelpers.h"
#include "GameObject.h"
#include "Playerbots.h"

using namespace Aq20Helpers;
using namespace EncounterHelpers;

// Shared

bool Aq20BossShouldBeTankedTrigger::IsActiveInEncounter()
{
    if (!PlayerbotAI::IsMainTank(bot))
        return false;

    Unit* boss = FindThreatCreature(bot, _bossEntry);
    if (!IsAttackableNow(boss))
        return false;

    if (AI_VALUE(Unit*, "current target") != boss)
        return true;

    return _requireVictim && boss->GetVictim() != bot;
}

bool Aq20MainTankAuraStacksTrigger::IsActiveInEncounter()
{
    if (!PlayerbotAI::IsAssistTankOfIndex(bot, 0, true))
        return false;

    Unit* boss = FindThreatCreature(bot, _bossEntry);
    if (!boss)
        return false;

    Unit* mainTank = AI_VALUE(Unit*, "main tank");
    if (!mainTank || boss->GetVictim() != mainTank)
        return false;

    return GetAuraStacks(mainTank, _spellId) >= _stacks;
}

bool Aq20AddsSpawnedTrigger::IsActiveInEncounter()
{
    switch (_role)
    {
        case Aq20AddRole::MeleeAndTanks:
            if (!PlayerbotAI::IsMelee(bot) && !PlayerbotAI::IsTank(bot))
                return false;
            break;
        case Aq20AddRole::Everyone:
            if (PlayerbotAI::IsHeal(bot))
                return false;
            break;
    }

    Unit* add = GetNearestAttackableCachedUnit(botAI, _addsValue);
    return add && AI_VALUE(Unit*, "current target") != add;
}

bool Aq20BotNearCreatureHazardTrigger::IsActiveInEncounter()
{
    return IsNearCachedUnit(botAI, _hazardValue, _radius);
}

bool Aq20BotNearGameObjectHazardTrigger::IsActiveInEncounter()
{
    return IsNearCachedGameObject(botAI, _hazardValue, _radius);
}

// Buru the Gorger

bool BuruBotFixatedTrigger::IsActiveInEncounter()
{
    if (!IsFixatedByBuru(bot))
        return false;

    // Nothing to lead him to once every egg in reach is gone; the raid finishes the phase on his
    // own health instead.
    return GetNearestBuruEgg(botAI) != nullptr;
}

bool BuruEggShouldBeKilledTrigger::IsActiveInEncounter()
{
    if (PlayerbotAI::IsHeal(bot))
        return false;

    // The fixated bot is busy keeping Buru on the egg, and it is standing on the explosion.
    if (IsFixatedByBuru(bot))
        return false;

    Unit* egg = GetBuruTargetEgg(botAI);
    return egg && AI_VALUE(Unit*, "current target") != egg;
}

bool BuruShouldBeTankedTrigger::IsActiveInEncounter()
{
    if (!PlayerbotAI::IsMainTank(bot))
        return false;

    Unit* buru = FindThreatCreature(bot, Id(Aq20Npcs::NPC_BURU));
    if (!IsAttackableNow(buru) || IsBuruInEggPhase(buru))
        return false;

    // The transform resets the threat list (BUR:146), so holding the target is not enough.
    return AI_VALUE(Unit*, "current target") != buru || buru->GetVictim() != bot;
}

// Ayamiss the Hunter

bool AyamissShouldBeTankedTrigger::IsActiveInEncounter()
{
    if (!PlayerbotAI::IsMainTank(bot))
        return false;

    Unit* ayamiss = FindThreatCreature(bot, Id(Aq20Npcs::NPC_AYAMISS));
    if (!IsAttackableNow(ayamiss) || IsAyamissInAirPhase(ayamiss))
        return false;

    return AI_VALUE(Unit*, "current target") != ayamiss || ayamiss->GetVictim() != bot;
}

// Ossirian the Unscarred

bool OssirianTankShouldMoveToCrystalTrigger::IsActiveInEncounter()
{
    if (!PlayerbotAI::IsMainTank(bot))
        return false;

    Unit* ossirian = FindThreatCreature(bot, Id(Aq20Npcs::NPC_OSSIRIAN));
    if (!IsAttackableNow(ossirian) || !IsOssirianCrystalDue(ossirian, CRYSTAL_APPROACH_LEAD_MS))
        return false;

    GameObject* crystal = GetUsableOssirianCrystal(botAI);
    if (!crystal)
        return false;

    return bot->GetExactDist(crystal) > CRYSTAL_INTERACT_DISTANCE ||
        ossirian->GetExactDist(crystal) > CRYSTAL_WEAKNESS_REACH;
}

bool OssirianCrystalShouldBeUsedTrigger::IsActiveInEncounter()
{
    if (!PlayerbotAI::IsMainTank(bot))
        return false;

    Unit* ossirian = FindThreatCreature(bot, Id(Aq20Npcs::NPC_OSSIRIAN));
    if (!IsAttackableNow(ossirian) || !IsOssirianCrystalDue(ossirian, CRYSTAL_ACTIVATION_LEAD_MS))
        return false;

    GameObject* crystal = GetUsableOssirianCrystal(botAI);
    if (!crystal)
        return false;

    return bot->GetExactDist(crystal) <= CRYSTAL_INTERACT_DISTANCE &&
        ossirian->GetExactDist(crystal) <= CRYSTAL_WEAKNESS_REACH;
}
