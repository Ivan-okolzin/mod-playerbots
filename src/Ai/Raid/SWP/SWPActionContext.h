/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#ifndef PLAYERBOTS_SWPACTIONCONTEXT_H
#define PLAYERBOTS_SWPACTIONCONTEXT_H

#include "NamedObjectContext.h"
#include "SWPActions.h"
#include "SWPHelpers.h"

class RaidSwpActionContext : public NamedObjectContext<Action>
{
public:
    RaidSwpActionContext()
    {
        // Kalecgos
        creators["kalecgos attack boss"] = &RaidSwpActionContext::kalecgos_attack_boss;
        creators["kalecgos attack sathrovarr"] = &RaidSwpActionContext::kalecgos_attack_sathrovarr;

        // Brutallus
        creators["brutallus main tank attack boss"] =
            &RaidSwpActionContext::brutallus_main_tank_attack_boss;
        creators["brutallus break off from burn"] =
            &RaidSwpActionContext::brutallus_break_off_from_burn;
        creators["brutallus move behind boss"] = &RaidSwpActionContext::brutallus_move_behind_boss;

        // Felmyst
        creators["felmyst main tank attack boss"] =
            &RaidSwpActionContext::felmyst_main_tank_attack_boss;
        creators["felmyst move out of breath path"] =
            &RaidSwpActionContext::felmyst_move_out_of_breath_path;
        creators["felmyst move away from vapor trail"] =
            &RaidSwpActionContext::felmyst_move_away_from_vapor_trail;
        creators["felmyst attack unyielding dead"] =
            &RaidSwpActionContext::felmyst_attack_unyielding_dead;
        creators["felmyst stop attacking charmed ally"] =
            &RaidSwpActionContext::felmyst_stop_attacking_charmed_ally;
        creators["felmyst spread ranged"] = &RaidSwpActionContext::felmyst_spread_ranged;

        // Eredar Twins
        creators["eredar twins assign tanks"] = &RaidSwpActionContext::eredar_twins_assign_tanks;
        creators["eredar twins melee attack lady sacrolash"] =
            &RaidSwpActionContext::eredar_twins_melee_attack_sacrolash;
        creators["eredar twins caster attack alythess"] =
            &RaidSwpActionContext::eredar_twins_caster_attack_alythess;
        creators["eredar twins spread ranged"] = &RaidSwpActionContext::eredar_twins_spread_ranged;

        // M'uru and Entropius
        creators["m'uru main tank attack boss"] = &RaidSwpActionContext::muru_main_tank_attack_boss;
        creators["m'uru attack nearest dark fiend"] =
            &RaidSwpActionContext::muru_attack_nearest_dark_fiend;
        creators["m'uru tank attack void sentinel"] =
            &RaidSwpActionContext::muru_tank_attack_void_sentinel;
        creators["m'uru attack nearest add"] = &RaidSwpActionContext::muru_attack_nearest_add;
        creators["m'uru move away from darkness"] =
            &RaidSwpActionContext::muru_move_away_from_darkness;
        creators["entropius main tank attack boss"] =
            &RaidSwpActionContext::entropius_main_tank_attack_boss;
        creators["entropius move away from singularity"] =
            &RaidSwpActionContext::entropius_move_away_from_singularity;

        // Kil'jaeden
        creators["kil'jaeden main tank attack boss"] =
            &RaidSwpActionContext::kiljaeden_main_tank_attack_boss;
        creators["kil'jaeden move away from armageddon"] =
            &RaidSwpActionContext::kiljaeden_move_away_from_armageddon;
        creators["kil'jaeden attack shield orb"] =
            &RaidSwpActionContext::kiljaeden_attack_shield_orb;
        creators["kil'jaeden attack sinister reflection"] =
            &RaidSwpActionContext::kiljaeden_attack_sinister_reflection;
        creators["kil'jaeden attack hand of the deceiver"] =
            &RaidSwpActionContext::kiljaeden_attack_hand_of_the_deceiver;
        creators["kil'jaeden spread ranged"] = &RaidSwpActionContext::kiljaeden_spread_ranged;
    }

private:
    static Action* kalecgos_attack_boss(PlayerbotAI* botAI)
    {
        return new KalecgosAttackRealmBossAction(botAI, false);
    }
    static Action* kalecgos_attack_sathrovarr(PlayerbotAI* botAI)
    {
        return new KalecgosAttackRealmBossAction(botAI, true);
    }

    static Action* brutallus_main_tank_attack_boss(PlayerbotAI* botAI)
    {
        return new SwpAttackCreatureAction(
            botAI, "brutallus main tank attack boss",
            SwpHelpers::Id(SwpHelpers::SwpNpcs::NPC_BRUTALLUS));
    }
    static Action* brutallus_break_off_from_burn(PlayerbotAI* botAI)
    {
        return new SwpFleeNearestPlayerAction(
            botAI, "brutallus break off from burn", SwpHelpers::BURN_ESCAPE_DISTANCE);
    }
    static Action* brutallus_move_behind_boss(PlayerbotAI* botAI)
    {
        return new SwpMoveBehindBossAction(
            botAI, "brutallus move behind boss",
            SwpHelpers::Id(SwpHelpers::SwpNpcs::NPC_BRUTALLUS));
    }

    static Action* felmyst_main_tank_attack_boss(PlayerbotAI* botAI)
    {
        return new SwpAttackCreatureAction(
            botAI, "felmyst main tank attack boss",
            SwpHelpers::Id(SwpHelpers::SwpNpcs::NPC_FELMYST));
    }
    static Action* felmyst_move_out_of_breath_path(PlayerbotAI* botAI)
    {
        return new FelmystMoveOutOfBreathPathAction(botAI);
    }
    static Action* felmyst_move_away_from_vapor_trail(PlayerbotAI* botAI)
    {
        return new SwpMoveAwayFromHazardAction(
            botAI, "felmyst move away from vapor trail", SwpHelpers::FELMYST_VAPOR_TRAILS_VALUE,
            SwpHelpers::VAPOR_TRAIL_RADIUS);
    }
    static Action* felmyst_attack_unyielding_dead(PlayerbotAI* botAI)
    {
        return new SwpAttackNearestAddAction(
            botAI, "felmyst attack unyielding dead",
            SwpHelpers::FELMYST_UNYIELDING_DEAD_VALUE);
    }
    static Action* felmyst_stop_attacking_charmed_ally(PlayerbotAI* botAI)
    {
        return new SwpStopAttackingCharmedAllyAction(
            botAI, "felmyst stop attacking charmed ally",
            SwpHelpers::Id(SwpHelpers::SwpNpcs::NPC_FELMYST));
    }
    static Action* felmyst_spread_ranged(PlayerbotAI* botAI)
    {
        constexpr float noDistanceFromBoss = 0.0f;
        return new SwpSpreadRangedAction(
            botAI, "felmyst spread ranged", SwpHelpers::Id(SwpHelpers::SwpNpcs::NPC_FELMYST),
            noDistanceFromBoss);
    }

    static Action* eredar_twins_assign_tanks(PlayerbotAI* botAI)
    {
        return new EredarTwinsAssignTanksAction(botAI);
    }
    static Action* eredar_twins_melee_attack_sacrolash(PlayerbotAI* botAI)
    {
        return new SwpAttackCreatureAction(
            botAI, "eredar twins melee attack lady sacrolash",
            SwpHelpers::Id(SwpHelpers::SwpNpcs::NPC_LADY_SACROLASH));
    }
    static Action* eredar_twins_caster_attack_alythess(PlayerbotAI* botAI)
    {
        return new SwpAttackCreatureAction(
            botAI, "eredar twins caster attack alythess",
            SwpHelpers::Id(SwpHelpers::SwpNpcs::NPC_GRAND_WARLOCK_ALYTHESS));
    }
    static Action* eredar_twins_spread_ranged(PlayerbotAI* botAI)
    {
        return new SwpSpreadRangedAction(
            botAI, "eredar twins spread ranged",
            SwpHelpers::Id(SwpHelpers::SwpNpcs::NPC_GRAND_WARLOCK_ALYTHESS),
            SwpHelpers::ALYTHESS_RANGED_DISTANCE);
    }

    static Action* muru_main_tank_attack_boss(PlayerbotAI* botAI)
    {
        return new SwpAttackCreatureAction(
            botAI, "m'uru main tank attack boss", SwpHelpers::Id(SwpHelpers::SwpNpcs::NPC_MURU));
    }
    static Action* muru_attack_nearest_dark_fiend(PlayerbotAI* botAI)
    {
        return new SwpAttackNearestAddAction(
            botAI, "m'uru attack nearest dark fiend", SwpHelpers::MURU_DARK_FIENDS_VALUE);
    }
    static Action* muru_tank_attack_void_sentinel(PlayerbotAI* botAI)
    {
        return new SwpAttackNearestAddAction(
            botAI, "m'uru tank attack void sentinel", SwpHelpers::MURU_VOID_SENTINELS_VALUE);
    }
    static Action* muru_attack_nearest_add(PlayerbotAI* botAI)
    {
        return new SwpAttackNearestAddAction(
            botAI, "m'uru attack nearest add", SwpHelpers::MURU_ADDS_VALUE);
    }
    static Action* muru_move_away_from_darkness(PlayerbotAI* botAI)
    {
        return new SwpMoveAwayFromHazardAction(
            botAI, "m'uru move away from darkness", SwpHelpers::MURU_DARKNESS_VALUE,
            SwpHelpers::DARKNESS_RADIUS);
    }
    static Action* entropius_main_tank_attack_boss(PlayerbotAI* botAI)
    {
        return new SwpAttackCreatureAction(
            botAI, "entropius main tank attack boss",
            SwpHelpers::Id(SwpHelpers::SwpNpcs::NPC_ENTROPIUS));
    }
    static Action* entropius_move_away_from_singularity(PlayerbotAI* botAI)
    {
        return new SwpMoveAwayFromHazardAction(
            botAI, "entropius move away from singularity",
            SwpHelpers::ENTROPIUS_SINGULARITIES_VALUE, SwpHelpers::SINGULARITY_RADIUS);
    }

    static Action* kiljaeden_main_tank_attack_boss(PlayerbotAI* botAI)
    {
        return new SwpAttackCreatureAction(
            botAI, "kil'jaeden main tank attack boss",
            SwpHelpers::Id(SwpHelpers::SwpNpcs::NPC_KILJAEDEN));
    }
    static Action* kiljaeden_move_away_from_armageddon(PlayerbotAI* botAI)
    {
        return new SwpMoveAwayFromHazardAction(
            botAI, "kil'jaeden move away from armageddon",
            SwpHelpers::KILJAEDEN_ARMAGEDDON_VALUE, SwpHelpers::ARMAGEDDON_RADIUS);
    }
    static Action* kiljaeden_attack_shield_orb(PlayerbotAI* botAI)
    {
        return new SwpAttackNearestAddAction(
            botAI, "kil'jaeden attack shield orb", SwpHelpers::KILJAEDEN_SHIELD_ORBS_VALUE);
    }
    static Action* kiljaeden_attack_sinister_reflection(PlayerbotAI* botAI)
    {
        return new SwpAttackNearestAddAction(
            botAI, "kil'jaeden attack sinister reflection",
            SwpHelpers::KILJAEDEN_REFLECTIONS_VALUE);
    }
    static Action* kiljaeden_attack_hand_of_the_deceiver(PlayerbotAI* botAI)
    {
        return new SwpAttackNearestAddAction(
            botAI, "kil'jaeden attack hand of the deceiver", SwpHelpers::KILJAEDEN_HANDS_VALUE);
    }
    static Action* kiljaeden_spread_ranged(PlayerbotAI* botAI)
    {
        constexpr float noDistanceFromBoss = 0.0f;
        return new SwpSpreadRangedAction(
            botAI, "kil'jaeden spread ranged", SwpHelpers::Id(SwpHelpers::SwpNpcs::NPC_KILJAEDEN),
            noDistanceFromBoss);
    }
};

#endif
