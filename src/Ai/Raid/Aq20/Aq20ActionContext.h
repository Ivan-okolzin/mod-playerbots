/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#ifndef PLAYERBOTS_AQ20ACTIONCONTEXT_H
#define PLAYERBOTS_AQ20ACTIONCONTEXT_H

#include "Action.h"
#include "Aq20Actions.h"
#include "Aq20Helpers.h"
#include "NamedObjectContext.h"

class RaidAq20ActionContext : public NamedObjectContext<Action>
{
public:
    RaidAq20ActionContext()
    {
        // Kurinnaxx
        creators["kurinnaxx main tank attack boss"] =
            &RaidAq20ActionContext::kurinnaxx_main_tank_attack_boss;
        creators["kurinnaxx tank swap"] = &RaidAq20ActionContext::kurinnaxx_tank_swap;
        creators["kurinnaxx move away from sand trap"] =
            &RaidAq20ActionContext::kurinnaxx_move_away_from_sand_trap;

        // General Rajaxx
        creators["general rajaxx main tank attack boss"] =
            &RaidAq20ActionContext::rajaxx_main_tank_attack_boss;

        // Moam
        creators["moam main tank attack boss"] = &RaidAq20ActionContext::moam_main_tank_attack_boss;
        creators["moam attack nearest mana fiend"] =
            &RaidAq20ActionContext::moam_attack_nearest_mana_fiend;

        // Buru the Gorger
        creators["buru the gorger main tank attack boss"] =
            &RaidAq20ActionContext::buru_main_tank_attack_boss;
        creators["buru the gorger lure boss to egg"] =
            &RaidAq20ActionContext::buru_lure_boss_to_egg;
        creators["buru the gorger attack target egg"] =
            &RaidAq20ActionContext::buru_attack_target_egg;
        creators["buru the gorger attack nearest hatchling"] =
            &RaidAq20ActionContext::buru_attack_nearest_hatchling;

        // Ayamiss the Hunter
        creators["ayamiss the hunter main tank attack boss"] =
            &RaidAq20ActionContext::ayamiss_main_tank_attack_boss;
        creators["ayamiss the hunter attack nearest larva"] =
            &RaidAq20ActionContext::ayamiss_attack_nearest_larva;
        creators["ayamiss the hunter attack nearest swarmer"] =
            &RaidAq20ActionContext::ayamiss_attack_nearest_swarmer;

        // Ossirian the Unscarred
        creators["ossirian the unscarred main tank attack boss"] =
            &RaidAq20ActionContext::ossirian_main_tank_attack_boss;
        creators["ossirian the unscarred tank move to crystal"] =
            &RaidAq20ActionContext::ossirian_tank_move_to_crystal;
        creators["ossirian the unscarred use crystal"] =
            &RaidAq20ActionContext::ossirian_use_crystal;
        creators["ossirian the unscarred move away from sand vortex"] =
            &RaidAq20ActionContext::ossirian_move_away_from_sand_vortex;
    }

private:
    static Action* kurinnaxx_main_tank_attack_boss(PlayerbotAI* botAI)
    {
        constexpr bool taunt = false;
        return new Aq20TankBossAction(
            botAI, "kurinnaxx main tank attack boss",
            Aq20Helpers::Id(Aq20Helpers::Aq20Npcs::NPC_KURINNAXX), taunt);
    }
    static Action* kurinnaxx_tank_swap(PlayerbotAI* botAI)
    {
        constexpr bool taunt = true;
        return new Aq20TankBossAction(
            botAI, "kurinnaxx tank swap", Aq20Helpers::Id(Aq20Helpers::Aq20Npcs::NPC_KURINNAXX),
            taunt);
    }
    static Action* kurinnaxx_move_away_from_sand_trap(PlayerbotAI* botAI)
    {
        return new Aq20MoveAwayFromGameObjectHazardAction(
            botAI, "kurinnaxx move away from sand trap", Aq20Helpers::KURINNAXX_SAND_TRAPS_VALUE,
            Aq20Helpers::SAND_TRAP_RADIUS);
    }

    static Action* rajaxx_main_tank_attack_boss(PlayerbotAI* botAI)
    {
        constexpr bool taunt = true;
        return new Aq20TankBossAction(
            botAI, "general rajaxx main tank attack boss",
            Aq20Helpers::Id(Aq20Helpers::Aq20Npcs::NPC_RAJAXX), taunt);
    }

    static Action* moam_main_tank_attack_boss(PlayerbotAI* botAI)
    {
        constexpr bool taunt = false;
        return new Aq20TankBossAction(
            botAI, "moam main tank attack boss", Aq20Helpers::Id(Aq20Helpers::Aq20Npcs::NPC_MOAM),
            taunt);
    }
    static Action* moam_attack_nearest_mana_fiend(PlayerbotAI* botAI)
    {
        return new Aq20AttackNearestAddAction(
            botAI, "moam attack nearest mana fiend", Aq20Helpers::MOAM_MANA_FIENDS_VALUE);
    }

    static Action* buru_main_tank_attack_boss(PlayerbotAI* botAI)
    {
        constexpr bool taunt = true;
        return new Aq20TankBossAction(
            botAI, "buru the gorger main tank attack boss",
            Aq20Helpers::Id(Aq20Helpers::Aq20Npcs::NPC_BURU), taunt);
    }
    static Action* buru_lure_boss_to_egg(PlayerbotAI* botAI)
    {
        return new BuruLureBossToEggAction(botAI);
    }
    static Action* buru_attack_target_egg(PlayerbotAI* botAI)
    {
        return new BuruAttackTargetEggAction(botAI);
    }
    static Action* buru_attack_nearest_hatchling(PlayerbotAI* botAI)
    {
        return new Aq20AttackNearestAddAction(
            botAI, "buru the gorger attack nearest hatchling", Aq20Helpers::BURU_HATCHLINGS_VALUE);
    }

    static Action* ayamiss_main_tank_attack_boss(PlayerbotAI* botAI)
    {
        constexpr bool taunt = true;
        return new Aq20TankBossAction(
            botAI, "ayamiss the hunter main tank attack boss",
            Aq20Helpers::Id(Aq20Helpers::Aq20Npcs::NPC_AYAMISS), taunt);
    }
    static Action* ayamiss_attack_nearest_larva(PlayerbotAI* botAI)
    {
        return new Aq20AttackNearestAddAction(
            botAI, "ayamiss the hunter attack nearest larva", Aq20Helpers::AYAMISS_LARVAE_VALUE);
    }
    static Action* ayamiss_attack_nearest_swarmer(PlayerbotAI* botAI)
    {
        return new Aq20AttackNearestAddAction(
            botAI, "ayamiss the hunter attack nearest swarmer",
            Aq20Helpers::AYAMISS_SWARMERS_VALUE);
    }

    static Action* ossirian_main_tank_attack_boss(PlayerbotAI* botAI)
    {
        constexpr bool taunt = true;
        return new Aq20TankBossAction(
            botAI, "ossirian the unscarred main tank attack boss",
            Aq20Helpers::Id(Aq20Helpers::Aq20Npcs::NPC_OSSIRIAN), taunt);
    }
    static Action* ossirian_tank_move_to_crystal(PlayerbotAI* botAI)
    {
        return new OssirianTankMoveToCrystalAction(botAI);
    }
    static Action* ossirian_use_crystal(PlayerbotAI* botAI)
    {
        return new OssirianUseCrystalAction(botAI);
    }
    static Action* ossirian_move_away_from_sand_vortex(PlayerbotAI* botAI)
    {
        return new Aq20MoveAwayFromCreatureHazardAction(
            botAI, "ossirian the unscarred move away from sand vortex",
            Aq20Helpers::OSSIRIAN_SAND_VORTEXES_VALUE, Aq20Helpers::SAND_VORTEX_RADIUS);
    }
};

#endif
