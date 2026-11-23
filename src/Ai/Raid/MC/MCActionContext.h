/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#ifndef PLAYERBOTS_MCACTIONCONTEXT_H
#define PLAYERBOTS_MCACTIONCONTEXT_H

#include "Action.h"
#include "BossAuraActions.h"
#include "MCActions.h"
#include "MCHelpers.h"
#include "NamedObjectContext.h"

class RaidMcActionContext : public NamedObjectContext<Action>
{
public:
    RaidMcActionContext()
    {
        creators["mc lucifron shadow resistance"] = &RaidMcActionContext::lucifron_shadow_resistance;
        creators["mc lucifron main tank attack boss"] = &RaidMcActionContext::lucifron_main_tank_attack_boss;
        creators["mc lucifron tank attack nearest protector"] =
            &RaidMcActionContext::lucifron_tank_attack_nearest_protector;
        creators["mc magmadar fire resistance"] = &RaidMcActionContext::magmadar_fire_resistance;
        creators["mc magmadar main tank attack boss"] = &RaidMcActionContext::magmadar_main_tank_attack_boss;
        creators["mc magmadar move out of lava bomb"] = &RaidMcActionContext::magmadar_move_out_of_lava_bomb;
        creators["mc gehennas shadow resistance"] = &RaidMcActionContext::gehennas_shadow_resistance;
        creators["mc gehennas main tank attack boss"] = &RaidMcActionContext::gehennas_main_tank_attack_boss;
        creators["mc gehennas tank attack nearest flamewaker"] =
            &RaidMcActionContext::gehennas_tank_attack_nearest_flamewaker;
        creators["mc gehennas move out of rain of fire"] =
            &RaidMcActionContext::gehennas_move_out_of_rain_of_fire;
        creators["mc garr fire resistance"] = &RaidMcActionContext::garr_fire_resistance;
        creators["mc garr main tank attack boss"] = &RaidMcActionContext::garr_main_tank_attack_boss;
        creators["mc garr tank attack nearest firesworn"] =
            &RaidMcActionContext::garr_tank_attack_nearest_firesworn;
        creators["mc baron geddon fire resistance"] = &RaidMcActionContext::baron_geddon_fire_resistance;
        creators["mc move from group"] = &RaidMcActionContext::check_should_move_from_group;
        creators["mc move from baron geddon"] = &RaidMcActionContext::move_from_baron_geddon;
        creators["mc shazzrah move away"] = &RaidMcActionContext::shazzrah_move_away;
        creators["mc shazzrah main tank attack boss"] = &RaidMcActionContext::shazzrah_main_tank_attack_boss;
        creators["mc shazzrah taunt boss"] = &RaidMcActionContext::shazzrah_taunt_boss;
        creators["mc sulfuron harbinger fire resistance"] = &RaidMcActionContext::sulfuron_harbinger_fire_resistance;
        creators["mc sulfuron harbinger main tank attack boss"] =
            &RaidMcActionContext::sulfuron_harbinger_main_tank_attack_boss;
        creators["mc sulfuron harbinger tank attack nearest priest"] =
            &RaidMcActionContext::sulfuron_harbinger_tank_attack_nearest_priest;
        creators["mc golemagg fire resistance"] = &RaidMcActionContext::golemagg_fire_resistance;
        creators["mc golemagg mark boss"] = &RaidMcActionContext::golemagg_mark_boss;
        creators["mc golemagg main tank attack golemagg"] = &RaidMcActionContext::golemagg_main_tank_attack_golemagg;
        creators["mc golemagg assist tank attack core rager"] = &RaidMcActionContext::golemagg_assist_tank_attack_core_rager;
        creators["mc golemagg back off"] = &RaidMcActionContext::golemagg_back_off;
        creators["mc golemagg healer position"] = &RaidMcActionContext::golemagg_healer_position;
        creators["mc majordomo shadow resistance"] = &RaidMcActionContext::majordomo_shadow_resistance;
        creators["mc majordomo stop attack"] = &RaidMcActionContext::majordomo_stop_attack;
        creators["mc majordomo main tank attack boss"] = &RaidMcActionContext::majordomo_main_tank_attack_boss;
        creators["mc majordomo taunt boss"] = &RaidMcActionContext::majordomo_taunt_boss;
        creators["mc majordomo tank attack nearest add"] =
            &RaidMcActionContext::majordomo_tank_attack_nearest_add;
        creators["mc ragnaros fire resistance"] = &RaidMcActionContext::ragnaros_fire_resistance;
        creators["mc ragnaros main tank attack boss"] = &RaidMcActionContext::ragnaros_main_tank_attack_boss;
        creators["mc ragnaros taunt boss"] = &RaidMcActionContext::ragnaros_taunt_boss;
        creators["mc ragnaros attack nearest son of flame"] =
            &RaidMcActionContext::ragnaros_attack_nearest_son_of_flame;
        creators["mc ragnaros move out of lava burst"] = &RaidMcActionContext::ragnaros_move_out_of_lava_burst;
        creators["mc core hound mark"] = &RaidMcActionContext::core_hound_mark;
        creators["mc move from lava"] = &RaidMcActionContext::move_from_lava;
    }

private:
    // Lucifron
    static Action* lucifron_shadow_resistance(PlayerbotAI* botAI) { return new BossShadowResistanceAction(botAI, "lucifron"); }
    static Action* lucifron_main_tank_attack_boss(PlayerbotAI* botAI)
    {
        return new McAttackBossAction(
            botAI, "mc lucifron main tank attack boss", MoltenCoreHelpers::NPC_LUCIFRON);
    }
    static Action* lucifron_tank_attack_nearest_protector(PlayerbotAI* botAI)
    {
        return new McAttackNearestAddAction(
            botAI, "mc lucifron tank attack nearest protector",
            MoltenCoreHelpers::LUCIFRON_PROTECTORS_VALUE);
    }

    // Magmadar
    static Action* magmadar_fire_resistance(PlayerbotAI* botAI) { return new BossFireResistanceAction(botAI, "magmadar"); }
    static Action* magmadar_main_tank_attack_boss(PlayerbotAI* botAI)
    {
        return new McAttackBossAction(
            botAI, "mc magmadar main tank attack boss", MoltenCoreHelpers::NPC_MAGMADAR);
    }
    static Action* magmadar_move_out_of_lava_bomb(PlayerbotAI* botAI)
    {
        return new McMoveOutOfHazardAction(
            botAI, "mc magmadar move out of lava bomb",
            MoltenCoreHelpers::MAGMADAR_LAVA_BOMBS_VALUE, MoltenCoreHelpers::LAVA_BOMB_RADIUS);
    }

    // Gehennas
    static Action* gehennas_shadow_resistance(PlayerbotAI* botAI) { return new BossShadowResistanceAction(botAI, "gehennas"); }
    static Action* gehennas_main_tank_attack_boss(PlayerbotAI* botAI)
    {
        return new McAttackBossAction(
            botAI, "mc gehennas main tank attack boss", MoltenCoreHelpers::NPC_GEHENNAS);
    }
    static Action* gehennas_tank_attack_nearest_flamewaker(PlayerbotAI* botAI)
    {
        return new McAttackNearestAddAction(
            botAI, "mc gehennas tank attack nearest flamewaker",
            MoltenCoreHelpers::GEHENNAS_FLAMEWAKERS_VALUE);
    }
    static Action* gehennas_move_out_of_rain_of_fire(PlayerbotAI* botAI)
    {
        return new McMoveOutOfHazardAction(
            botAI, "mc gehennas move out of rain of fire",
            MoltenCoreHelpers::GEHENNAS_RAIN_OF_FIRE_VALUE, MoltenCoreHelpers::RAIN_OF_FIRE_RADIUS);
    }

    // Garr
    static Action* garr_fire_resistance(PlayerbotAI* botAI) { return new BossFireResistanceAction(botAI, "garr"); }
    static Action* garr_main_tank_attack_boss(PlayerbotAI* botAI)
    {
        return new McAttackBossAction(botAI, "mc garr main tank attack boss", MoltenCoreHelpers::NPC_GARR);
    }
    static Action* garr_tank_attack_nearest_firesworn(PlayerbotAI* botAI)
    {
        return new McAttackNearestAddAction(
            botAI, "mc garr tank attack nearest firesworn", MoltenCoreHelpers::GARR_FIRESWORN_VALUE);
    }

    // Baron Geddon
    static Action* baron_geddon_fire_resistance(PlayerbotAI* botAI) { return new BossFireResistanceAction(botAI, "baron geddon"); }
    static Action* check_should_move_from_group(PlayerbotAI* botAI) { return new McMoveFromGroupAction(botAI); }
    static Action* move_from_baron_geddon(PlayerbotAI* botAI)
    {
        return new McFleeFromBossAction(
            botAI, "mc move from baron geddon", MoltenCoreHelpers::NPC_BARON_GEDDON,
            MoltenCoreHelpers::BARON_GEDDON_VALUE, MoltenCoreHelpers::INFERNO_DISTANCE);
    }

    // Shazzrah
    static Action* shazzrah_move_away(PlayerbotAI* botAI) { return new McShazzrahMoveAwayAction(botAI); }
    static Action* shazzrah_main_tank_attack_boss(PlayerbotAI* botAI)
    {
        return new McAttackBossAction(
            botAI, "mc shazzrah main tank attack boss", MoltenCoreHelpers::NPC_SHAZZRAH,
            MoltenCoreHelpers::SHAZZRAH_VALUE);
    }
    static Action* shazzrah_taunt_boss(PlayerbotAI* botAI)
    {
        return new McTauntBossAction(
            botAI, "mc shazzrah taunt boss", MoltenCoreHelpers::NPC_SHAZZRAH,
            MoltenCoreHelpers::SHAZZRAH_VALUE);
    }

    // Sulfuron Harbinger
    static Action* sulfuron_harbinger_fire_resistance(PlayerbotAI* botAI) { return new BossFireResistanceAction(botAI, "sulfuron harbinger"); }
    static Action* sulfuron_harbinger_main_tank_attack_boss(PlayerbotAI* botAI)
    {
        return new McAttackBossAction(
            botAI, "mc sulfuron harbinger main tank attack boss",
            MoltenCoreHelpers::NPC_SULFURON_HARBINGER);
    }
    static Action* sulfuron_harbinger_tank_attack_nearest_priest(PlayerbotAI* botAI)
    {
        return new McAttackNearestAddAction(
            botAI, "mc sulfuron harbinger tank attack nearest priest",
            MoltenCoreHelpers::SULFURON_PRIESTS_VALUE);
    }

    // Golemagg the Incinerator
    static Action* golemagg_fire_resistance(PlayerbotAI* botAI) { return new BossFireResistanceAction(botAI, "golemagg the incinerator"); }
    static Action* golemagg_mark_boss(PlayerbotAI* botAI) { return new McGolemaggMarkBossAction(botAI); }
    static Action* golemagg_main_tank_attack_golemagg(PlayerbotAI* botAI) { return new McGolemaggMainTankAttackGolemaggAction(botAI); }
    static Action* golemagg_assist_tank_attack_core_rager(PlayerbotAI* botAI) { return new McGolemaggAssistTankAttackCoreRagerAction(botAI); }
    static Action* golemagg_back_off(PlayerbotAI* botAI) { return new McGolemaggBackOffAction(botAI); }
    static Action* golemagg_healer_position(PlayerbotAI* botAI) { return new McGolemaggHealerPositionAction(botAI); }

    // Majordomo Executus
    static Action* majordomo_shadow_resistance(PlayerbotAI* botAI) { return new BossShadowResistanceAction(botAI, "majordomo executus"); }
    static Action* majordomo_stop_attack(PlayerbotAI* botAI) { return new McMajordomoStopAttackAction(botAI); }
    static Action* majordomo_main_tank_attack_boss(PlayerbotAI* botAI)
    {
        return new McAttackBossAction(
            botAI, "mc majordomo main tank attack boss", MoltenCoreHelpers::NPC_MAJORDOMO_EXECUTUS,
            MoltenCoreHelpers::MAJORDOMO_VALUE);
    }
    static Action* majordomo_taunt_boss(PlayerbotAI* botAI)
    {
        return new McTauntBossAction(
            botAI, "mc majordomo taunt boss", MoltenCoreHelpers::NPC_MAJORDOMO_EXECUTUS,
            MoltenCoreHelpers::MAJORDOMO_VALUE);
    }
    static Action* majordomo_tank_attack_nearest_add(PlayerbotAI* botAI)
    {
        return new McAttackNearestAddAction(
            botAI, "mc majordomo tank attack nearest add", MoltenCoreHelpers::MAJORDOMO_ADDS_VALUE);
    }

    // Ragnaros
    static Action* ragnaros_fire_resistance(PlayerbotAI* botAI) { return new BossFireResistanceAction(botAI, "ragnaros"); }
    static Action* ragnaros_main_tank_attack_boss(PlayerbotAI* botAI)
    {
        return new McAttackBossAction(
            botAI, "mc ragnaros main tank attack boss", MoltenCoreHelpers::NPC_RAGNAROS,
            MoltenCoreHelpers::RAGNAROS_VALUE);
    }
    static Action* ragnaros_taunt_boss(PlayerbotAI* botAI)
    {
        return new McTauntBossAction(
            botAI, "mc ragnaros taunt boss", MoltenCoreHelpers::NPC_RAGNAROS,
            MoltenCoreHelpers::RAGNAROS_VALUE);
    }
    static Action* ragnaros_attack_nearest_son_of_flame(PlayerbotAI* botAI)
    {
        return new McAttackNearestAddAction(
            botAI, "mc ragnaros attack nearest son of flame",
            MoltenCoreHelpers::RAGNAROS_SONS_OF_FLAME_VALUE);
    }
    static Action* ragnaros_move_out_of_lava_burst(PlayerbotAI* botAI)
    {
        return new McMoveOutOfHazardAction(
            botAI, "mc ragnaros move out of lava burst",
            MoltenCoreHelpers::RAGNAROS_LAVA_BURSTS_VALUE, MoltenCoreHelpers::LAVA_BURST_RADIUS);
    }

    // Trash and anywhere in the instance
    static Action* core_hound_mark(PlayerbotAI* botAI) { return new McCoreHoundMarkAction(botAI); }
    static Action* move_from_lava(PlayerbotAI* botAI) { return new McMoveFromLavaAction(botAI); }
};

#endif
