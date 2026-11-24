/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#ifndef PLAYERBOTS_AQ20TRIGGERCONTEXT_H
#define PLAYERBOTS_AQ20TRIGGERCONTEXT_H

#include "Aq20Helpers.h"
#include "Aq20Triggers.h"
#include "NamedObjectContext.h"

class RaidAq20TriggerContext : public NamedObjectContext<Trigger>
{
public:
    RaidAq20TriggerContext() : NamedObjectContext<Trigger>()
    {
        // Kurinnaxx
        creators["kurinnaxx should be tanked"] = &RaidAq20TriggerContext::kurinnaxx_should_be_tanked;
        creators["kurinnaxx main tank has mortal wound stacks"] =
            &RaidAq20TriggerContext::kurinnaxx_main_tank_has_mortal_wound_stacks;
        creators["kurinnaxx bot in sand trap"] = &RaidAq20TriggerContext::kurinnaxx_bot_in_sand_trap;

        // General Rajaxx
        creators["general rajaxx should be tanked"] =
            &RaidAq20TriggerContext::rajaxx_should_be_tanked;

        // Moam
        creators["moam should be tanked"] = &RaidAq20TriggerContext::moam_should_be_tanked;
        creators["moam mana fiends spawned"] = &RaidAq20TriggerContext::moam_mana_fiends_spawned;

        // Buru the Gorger
        creators["buru the gorger should be tanked"] =
            &RaidAq20TriggerContext::buru_should_be_tanked;
        creators["buru the gorger bot is fixated"] = &RaidAq20TriggerContext::buru_bot_is_fixated;
        creators["buru the gorger egg should be killed"] =
            &RaidAq20TriggerContext::buru_egg_should_be_killed;
        creators["buru the gorger hatchlings spawned"] =
            &RaidAq20TriggerContext::buru_hatchlings_spawned;

        // Ayamiss the Hunter
        creators["ayamiss the hunter should be tanked"] =
            &RaidAq20TriggerContext::ayamiss_should_be_tanked;
        creators["ayamiss the hunter larvae spawned"] =
            &RaidAq20TriggerContext::ayamiss_larvae_spawned;
        creators["ayamiss the hunter swarmers spawned"] =
            &RaidAq20TriggerContext::ayamiss_swarmers_spawned;

        // Ossirian the Unscarred
        creators["ossirian the unscarred should be tanked"] =
            &RaidAq20TriggerContext::ossirian_should_be_tanked;
        creators["ossirian the unscarred tank should move to crystal"] =
            &RaidAq20TriggerContext::ossirian_tank_should_move_to_crystal;
        creators["ossirian the unscarred crystal should be used"] =
            &RaidAq20TriggerContext::ossirian_crystal_should_be_used;
        creators["ossirian the unscarred bot near sand vortex"] =
            &RaidAq20TriggerContext::ossirian_bot_near_sand_vortex;
    }

private:
    static Trigger* kurinnaxx_should_be_tanked(PlayerbotAI* botAI)
    {
        // Kurinnaxx keeps his threat list: only Mortal Wound moves him off the main tank, and
        // that has its own object.
        constexpr bool requireVictim = false;
        return new Aq20BossShouldBeTankedTrigger(
            botAI, "kurinnaxx should be tanked",
            Aq20Helpers::Id(Aq20Helpers::Aq20Npcs::NPC_KURINNAXX), requireVictim);
    }
    static Trigger* kurinnaxx_main_tank_has_mortal_wound_stacks(PlayerbotAI* botAI)
    {
        return new Aq20MainTankAuraStacksTrigger(
            botAI, "kurinnaxx main tank has mortal wound stacks",
            Aq20Helpers::Id(Aq20Helpers::Aq20Npcs::NPC_KURINNAXX),
            Aq20Helpers::Id(Aq20Helpers::Aq20Spells::SPELL_MORTAL_WOUND),
            Aq20Helpers::MORTAL_WOUND_SWAP_STACKS);
    }
    static Trigger* kurinnaxx_bot_in_sand_trap(PlayerbotAI* botAI)
    {
        return new Aq20BotNearGameObjectHazardTrigger(
            botAI, "kurinnaxx bot in sand trap", Aq20Helpers::KURINNAXX_SAND_TRAPS_VALUE,
            Aq20Helpers::SAND_TRAP_RADIUS);
    }

    static Trigger* rajaxx_should_be_tanked(PlayerbotAI* botAI)
    {
        // Thundercrash resets all threat every 21 seconds (RAJ:117), so the tank has to take him
        // back rather than just keep him selected.
        constexpr bool requireVictim = true;
        return new Aq20BossShouldBeTankedTrigger(
            botAI, "general rajaxx should be tanked",
            Aq20Helpers::Id(Aq20Helpers::Aq20Npcs::NPC_RAJAXX), requireVictim);
    }

    static Trigger* moam_should_be_tanked(PlayerbotAI* botAI)
    {
        constexpr bool requireVictim = false;
        return new Aq20BossShouldBeTankedTrigger(
            botAI, "moam should be tanked", Aq20Helpers::Id(Aq20Helpers::Aq20Npcs::NPC_MOAM),
            requireVictim);
    }
    static Trigger* moam_mana_fiends_spawned(PlayerbotAI* botAI)
    {
        return new Aq20AddsSpawnedTrigger(
            botAI, "moam mana fiends spawned", Aq20Helpers::MOAM_MANA_FIENDS_VALUE,
            Aq20AddRole::DamageAndOffTanks);
    }

    static Trigger* buru_should_be_tanked(PlayerbotAI* botAI)
    {
        return new BuruShouldBeTankedTrigger(botAI);
    }
    static Trigger* buru_bot_is_fixated(PlayerbotAI* botAI)
    {
        return new BuruBotFixatedTrigger(botAI);
    }
    static Trigger* buru_egg_should_be_killed(PlayerbotAI* botAI)
    {
        return new BuruEggShouldBeKilledTrigger(botAI);
    }
    static Trigger* buru_hatchlings_spawned(PlayerbotAI* botAI)
    {
        return new Aq20AddsSpawnedTrigger(
            botAI, "buru the gorger hatchlings spawned", Aq20Helpers::BURU_HATCHLINGS_VALUE,
            Aq20AddRole::MeleeAndTanks);
    }

    static Trigger* ayamiss_should_be_tanked(PlayerbotAI* botAI)
    {
        return new AyamissShouldBeTankedTrigger(botAI);
    }
    static Trigger* ayamiss_larvae_spawned(PlayerbotAI* botAI)
    {
        // A Larva walks to the altar and feeds on the player Paralyze pinned there (AYA:224), so
        // it goes before anything else the fight puts on the floor.
        return new Aq20AddsSpawnedTrigger(
            botAI, "ayamiss the hunter larvae spawned", Aq20Helpers::AYAMISS_LARVAE_VALUE,
            Aq20AddRole::Everyone);
    }
    static Trigger* ayamiss_swarmers_spawned(PlayerbotAI* botAI)
    {
        // Swarmers pile up at one every three seconds and all twenty-eight come at the raid at
        // once (AYA:156-160); the melee have nothing else to do while she is in the air.
        return new Aq20AddsSpawnedTrigger(
            botAI, "ayamiss the hunter swarmers spawned", Aq20Helpers::AYAMISS_SWARMERS_VALUE,
            Aq20AddRole::MeleeAndTanks);
    }

    static Trigger* ossirian_should_be_tanked(PlayerbotAI* botAI)
    {
        // The tank walks him from crystal to crystal, so it has to be the one he is hitting.
        constexpr bool requireVictim = true;
        return new Aq20BossShouldBeTankedTrigger(
            botAI, "ossirian the unscarred should be tanked",
            Aq20Helpers::Id(Aq20Helpers::Aq20Npcs::NPC_OSSIRIAN), requireVictim);
    }
    static Trigger* ossirian_tank_should_move_to_crystal(PlayerbotAI* botAI)
    {
        return new OssirianTankShouldMoveToCrystalTrigger(botAI);
    }
    static Trigger* ossirian_crystal_should_be_used(PlayerbotAI* botAI)
    {
        return new OssirianCrystalShouldBeUsedTrigger(botAI);
    }
    static Trigger* ossirian_bot_near_sand_vortex(PlayerbotAI* botAI)
    {
        return new Aq20BotNearCreatureHazardTrigger(
            botAI, "ossirian the unscarred bot near sand vortex",
            Aq20Helpers::OSSIRIAN_SAND_VORTEXES_VALUE, Aq20Helpers::SAND_VORTEX_RADIUS);
    }
};

#endif
