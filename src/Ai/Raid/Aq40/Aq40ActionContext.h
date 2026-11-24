/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#ifndef PLAYERBOTS_AQ40ACTIONCONTEXT_H
#define PLAYERBOTS_AQ40ACTIONCONTEXT_H

#include "Aq40Actions.h"
#include "Aq40Helpers.h"
#include "NamedObjectContext.h"

class RaidAq40ActionContext : public NamedObjectContext<Action>
{
public:
    RaidAq40ActionContext()
    {
        creators["aq40 reset encounter states"] =
            &RaidAq40ActionContext::aq40_reset_encounter_states;

        // The Prophet Skeram
        creators["the prophet skeram main tank attack boss"] =
            &RaidAq40ActionContext::skeram_main_tank_attack_boss;
        creators["the prophet skeram assist tank attack image"] =
            &RaidAq40ActionContext::skeram_assist_tank_attack_image;
        creators["the prophet skeram assign dps priority"] =
            &RaidAq40ActionContext::skeram_assign_dps_priority;
        creators["the prophet skeram stop attacking mind controlled ally"] =
            &RaidAq40ActionContext::skeram_stop_attacking_mind_controlled_ally;
        creators["the prophet skeram spread ranged"] =
            &RaidAq40ActionContext::skeram_spread_ranged;

        // Silithid Royalty
        creators["bug trio assign tanks"] = &RaidAq40ActionContext::bug_trio_assign_tanks;
        creators["bug trio assign dps priority"] =
            &RaidAq40ActionContext::bug_trio_assign_dps_priority;
        creators["bug trio move out of poison cloud"] =
            &RaidAq40ActionContext::bug_trio_move_out_of_poison_cloud;
        creators["bug trio attack nearest brood"] =
            &RaidAq40ActionContext::bug_trio_attack_nearest_brood;

        // Battleguard Sartura
        creators["battleguard sartura main tank attack boss"] =
            &RaidAq40ActionContext::sartura_main_tank_attack_boss;
        creators["battleguard sartura assist tank attack guard"] =
            &RaidAq40ActionContext::sartura_assist_tank_attack_guard;
        creators["battleguard sartura melee back off"] =
            &RaidAq40ActionContext::sartura_melee_back_off;
        creators["battleguard sartura assign dps priority"] =
            &RaidAq40ActionContext::sartura_assign_dps_priority;

        // Fankriss the Unyielding
        creators["fankriss the unyielding main tank attack boss"] =
            &RaidAq40ActionContext::fankriss_main_tank_attack_boss;
        creators["fankriss the unyielding tank swap"] =
            &RaidAq40ActionContext::fankriss_tank_swap;
        creators["fankriss the unyielding attack worms"] =
            &RaidAq40ActionContext::fankriss_attack_worms;
        creators["fankriss the unyielding attack spawns"] =
            &RaidAq40ActionContext::fankriss_attack_spawns;

        // Viscidus
        creators["viscidus attack frozen boss"] = &RaidAq40ActionContext::viscidus_attack_frozen_boss;
        creators["viscidus cast frost spell"] = &RaidAq40ActionContext::viscidus_cast_frost_spell;
        creators["viscidus attack nearest glob"] =
            &RaidAq40ActionContext::viscidus_attack_nearest_glob;
        creators["viscidus spread ranged"] = &RaidAq40ActionContext::viscidus_spread_ranged;

        // Princess Huhuran
        creators["princess huhuran main tank attack boss"] =
            &RaidAq40ActionContext::huhuran_main_tank_attack_boss;
        creators["princess huhuran move out of noxious poison"] =
            &RaidAq40ActionContext::huhuran_move_out_of_noxious_poison;
        creators["princess huhuran spread ranged"] =
            &RaidAq40ActionContext::huhuran_spread_ranged;

        // Twin Emperors
        creators["twin emperors tank position boss"] =
            &RaidAq40ActionContext::twin_emperors_tank_position_boss;
        creators["twin emperors melee attack vek'nilash"] =
            &RaidAq40ActionContext::twin_emperors_melee_attack_veknilash;
        creators["twin emperors caster attack vek'lor"] =
            &RaidAq40ActionContext::twin_emperors_caster_attack_veklor;
        creators["twin emperors move out of blizzard"] =
            &RaidAq40ActionContext::twin_emperors_move_out_of_blizzard;

        // Ouro
        creators["ouro main tank attack boss"] = &RaidAq40ActionContext::ouro_main_tank_attack_boss;
        creators["ouro spread from dirt mounds"] =
            &RaidAq40ActionContext::ouro_spread_from_dirt_mounds;
        creators["ouro attack nearest scarab"] =
            &RaidAq40ActionContext::ouro_attack_nearest_scarab;
        creators["ouro spread ranged"] = &RaidAq40ActionContext::ouro_spread_ranged;

        // C'Thun
        creators["eye of c'thun move out of dark glare"] =
            &RaidAq40ActionContext::cthun_move_out_of_dark_glare;
        creators["eye of c'thun attack claw tentacle"] =
            &RaidAq40ActionContext::cthun_attack_claw_tentacle;
        creators["eye of c'thun spread ranged"] = &RaidAq40ActionContext::cthun_eye_spread_ranged;
        creators["c'thun attack nearest eye tentacle"] =
            &RaidAq40ActionContext::cthun_attack_nearest_eye_tentacle;
        creators["c'thun tank attack giant claw tentacle"] =
            &RaidAq40ActionContext::cthun_tank_attack_giant_claw_tentacle;
        creators["c'thun attack giant eye tentacle"] =
            &RaidAq40ActionContext::cthun_attack_giant_eye_tentacle;
        creators["c'thun attack body"] = &RaidAq40ActionContext::cthun_attack_body;
        creators["c'thun attack flesh tentacle"] =
            &RaidAq40ActionContext::cthun_attack_flesh_tentacle;
        creators["c'thun leave stomach"] = &RaidAq40ActionContext::cthun_leave_stomach;
        creators["c'thun spread ranged"] = &RaidAq40ActionContext::cthun_spread_ranged;
    }

private:
    static Action* aq40_reset_encounter_states(PlayerbotAI* botAI)
    {
        return new Aq40ResetEncounterStatesAction(botAI);
    }

    static Action* skeram_main_tank_attack_boss(PlayerbotAI* botAI)
    {
        return new SkeramMainTankAttackBossAction(botAI);
    }
    static Action* skeram_assist_tank_attack_image(PlayerbotAI* botAI)
    {
        return new SkeramAssistTankAttackImageAction(botAI);
    }
    static Action* skeram_assign_dps_priority(PlayerbotAI* botAI)
    {
        return new SkeramAssignDpsPriorityAction(botAI);
    }
    static Action* skeram_stop_attacking_mind_controlled_ally(PlayerbotAI* botAI)
    {
        return new SkeramStopAttackingMindControlledAllyAction(botAI);
    }
    static Action* skeram_spread_ranged(PlayerbotAI* botAI)
    {
        return new Aq40SpreadRangedAction(
            botAI, "the prophet skeram spread ranged", Aq40Helpers::SKERAM_NAME,
            Aq40Helpers::SKERAM_RANGED_DISTANCE);
    }

    static Action* bug_trio_assign_tanks(PlayerbotAI* botAI)
    {
        return new BugTrioAssignTanksAction(botAI);
    }
    static Action* bug_trio_assign_dps_priority(PlayerbotAI* botAI)
    {
        return new BugTrioAssignDpsPriorityAction(botAI);
    }
    static Action* bug_trio_move_out_of_poison_cloud(PlayerbotAI* botAI)
    {
        return new Aq40MoveOutOfHazardAction(
            botAI, "bug trio move out of poison cloud", Aq40Helpers::POISON_CLOUD_VALUE,
            Aq40Helpers::POISON_CLOUD_RADIUS);
    }
    static Action* bug_trio_attack_nearest_brood(PlayerbotAI* botAI)
    {
        return new Aq40AttackNearestAddAction(
            botAI, "bug trio attack nearest brood", Aq40Helpers::YAUJ_BROOD_VALUE);
    }

    static Action* sartura_main_tank_attack_boss(PlayerbotAI* botAI)
    {
        return new Aq40MainTankAttackBossAction(
            botAI, "battleguard sartura main tank attack boss", Aq40Helpers::SARTURA_NAME);
    }
    static Action* sartura_assist_tank_attack_guard(PlayerbotAI* botAI)
    {
        return new SarturaAssistTankAttackGuardAction(botAI);
    }
    static Action* sartura_melee_back_off(PlayerbotAI* botAI)
    {
        return new SarturaMeleeBackOffAction(botAI);
    }
    static Action* sartura_assign_dps_priority(PlayerbotAI* botAI)
    {
        return new SarturaAssignDpsPriorityAction(botAI);
    }

    static Action* fankriss_main_tank_attack_boss(PlayerbotAI* botAI)
    {
        return new Aq40MainTankAttackBossAction(
            botAI, "fankriss the unyielding main tank attack boss", Aq40Helpers::FANKRISS_NAME);
    }
    static Action* fankriss_tank_swap(PlayerbotAI* botAI)
    {
        return new FankrissTankSwapAction(botAI);
    }
    static Action* fankriss_attack_worms(PlayerbotAI* botAI)
    {
        return new Aq40AttackNearestAddAction(
            botAI, "fankriss the unyielding attack worms", Aq40Helpers::FANKRISS_WORMS_VALUE);
    }

    static Action* fankriss_attack_spawns(PlayerbotAI* botAI)
    {
        return new Aq40AttackNearestAddAction(
            botAI, "fankriss the unyielding attack spawns", Aq40Helpers::FANKRISS_SPAWNS_VALUE);
    }

    static Action* viscidus_attack_frozen_boss(PlayerbotAI* botAI)
    {
        return new ViscidusAttackFrozenBossAction(botAI);
    }
    static Action* viscidus_cast_frost_spell(PlayerbotAI* botAI)
    {
        return new ViscidusCastFrostSpellAction(botAI);
    }
    static Action* viscidus_attack_nearest_glob(PlayerbotAI* botAI)
    {
        return new Aq40AttackNearestAddAction(
            botAI, "viscidus attack nearest glob", Aq40Helpers::VISCIDUS_GLOBS_VALUE);
    }
    static Action* viscidus_spread_ranged(PlayerbotAI* botAI)
    {
        return new Aq40SpreadRangedAction(
            botAI, "viscidus spread ranged", Aq40Helpers::VISCIDUS_NAME,
            Aq40Helpers::VISCIDUS_RANGED_DISTANCE);
    }

    static Action* huhuran_main_tank_attack_boss(PlayerbotAI* botAI)
    {
        return new Aq40MainTankAttackBossAction(
            botAI, "princess huhuran main tank attack boss", Aq40Helpers::HUHURAN_NAME);
    }
    static Action* huhuran_move_out_of_noxious_poison(PlayerbotAI* botAI)
    {
        return new Aq40MoveOutOfHazardAction(
            botAI, "princess huhuran move out of noxious poison",
            Aq40Helpers::NOXIOUS_POISON_VALUE, Aq40Helpers::NOXIOUS_POISON_RADIUS);
    }
    static Action* huhuran_spread_ranged(PlayerbotAI* botAI)
    {
        constexpr float noDistanceFromBoss = 0.0f;
        return new Aq40SpreadRangedAction(
            botAI, "princess huhuran spread ranged", Aq40Helpers::HUHURAN_NAME,
            noDistanceFromBoss);
    }

    static Action* twin_emperors_tank_position_boss(PlayerbotAI* botAI)
    {
        return new TwinEmperorsTankPositionBossAction(botAI);
    }
    static Action* twin_emperors_melee_attack_veknilash(PlayerbotAI* botAI)
    {
        return new TwinEmperorsSwitchTargetAction(
            botAI, "twin emperors melee attack vek'nilash", Aq40Helpers::VEKNILASH_NAME);
    }
    static Action* twin_emperors_caster_attack_veklor(PlayerbotAI* botAI)
    {
        return new TwinEmperorsSwitchTargetAction(
            botAI, "twin emperors caster attack vek'lor", Aq40Helpers::VEKLOR_NAME);
    }
    static Action* twin_emperors_move_out_of_blizzard(PlayerbotAI* botAI)
    {
        return new Aq40MoveOutOfHazardAction(
            botAI, "twin emperors move out of blizzard", Aq40Helpers::BLIZZARD_VALUE,
            Aq40Helpers::BLIZZARD_RADIUS);
    }

    static Action* ouro_main_tank_attack_boss(PlayerbotAI* botAI)
    {
        return new Aq40MainTankAttackBossAction(
            botAI, "ouro main tank attack boss", Aq40Helpers::OURO_NAME);
    }
    static Action* ouro_spread_from_dirt_mounds(PlayerbotAI* botAI)
    {
        return new OuroSpreadFromDirtMoundsAction(botAI);
    }
    static Action* ouro_attack_nearest_scarab(PlayerbotAI* botAI)
    {
        return new Aq40AttackNearestAddAction(
            botAI, "ouro attack nearest scarab", Aq40Helpers::OURO_SCARABS_VALUE);
    }
    static Action* ouro_spread_ranged(PlayerbotAI* botAI)
    {
        return new Aq40SpreadRangedAction(
            botAI, "ouro spread ranged", Aq40Helpers::OURO_NAME,
            Aq40Helpers::OURO_RANGED_DISTANCE);
    }

    static Action* cthun_move_out_of_dark_glare(PlayerbotAI* botAI)
    {
        return new CthunMoveOutOfDarkGlareAction(botAI);
    }
    static Action* cthun_attack_claw_tentacle(PlayerbotAI* botAI)
    {
        return new Aq40AttackNearestAddAction(
            botAI, "eye of c'thun attack claw tentacle",
            Aq40Helpers::CTHUN_CLAW_TENTACLES_VALUE);
    }
    static Action* cthun_eye_spread_ranged(PlayerbotAI* botAI)
    {
        constexpr float noDistanceFromBoss = 0.0f;
        return new Aq40SpreadRangedAction(
            botAI, "eye of c'thun spread ranged", Aq40Helpers::CTHUN_EYE_NAME,
            noDistanceFromBoss);
    }
    static Action* cthun_attack_nearest_eye_tentacle(PlayerbotAI* botAI)
    {
        return new Aq40AttackNearestAddAction(
            botAI, "c'thun attack nearest eye tentacle",
            Aq40Helpers::CTHUN_EYE_TENTACLES_VALUE);
    }
    static Action* cthun_tank_attack_giant_claw_tentacle(PlayerbotAI* botAI)
    {
        return new Aq40AttackNearestAddAction(
            botAI, "c'thun tank attack giant claw tentacle",
            Aq40Helpers::CTHUN_GIANT_CLAW_TENTACLES_VALUE);
    }
    static Action* cthun_attack_giant_eye_tentacle(PlayerbotAI* botAI)
    {
        return new Aq40AttackNearestAddAction(
            botAI, "c'thun attack giant eye tentacle",
            Aq40Helpers::CTHUN_GIANT_EYE_TENTACLES_VALUE);
    }
    static Action* cthun_attack_body(PlayerbotAI* botAI)
    {
        return new CthunAttackBodyAction(botAI);
    }
    static Action* cthun_attack_flesh_tentacle(PlayerbotAI* botAI)
    {
        return new Aq40AttackNearestAddAction(
            botAI, "c'thun attack flesh tentacle", Aq40Helpers::CTHUN_FLESH_TENTACLES_VALUE);
    }
    static Action* cthun_leave_stomach(PlayerbotAI* botAI)
    {
        return new CthunLeaveStomachAction(botAI);
    }
    static Action* cthun_spread_ranged(PlayerbotAI* botAI)
    {
        constexpr float noDistanceFromBoss = 0.0f;
        return new Aq40SpreadRangedAction(
            botAI, "c'thun spread ranged", Aq40Helpers::CTHUN_NAME, noDistanceFromBoss);
    }
};

#endif
