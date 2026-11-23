/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#ifndef PLAYERBOTS_ZGACTIONCONTEXT_H
#define PLAYERBOTS_ZGACTIONCONTEXT_H

#include "NamedObjectContext.h"
#include "ZGActions.h"
#include "ZGHelpers.h"

class RaidZulGurubActionContext : public NamedObjectContext<Action>
{
public:
    RaidZulGurubActionContext()
    {
        creators["zg reset encounter states"] =
            &RaidZulGurubActionContext::zg_reset_encounter_states;
        creators["zg move into poisonous cloud"] =
            &RaidZulGurubActionContext::zg_move_into_poisonous_cloud;

        // High Priest Venoxis
        creators["high priest venoxis main tank attack boss"] =
            &RaidZulGurubActionContext::venoxis_main_tank_attack_boss;
        creators["high priest venoxis tank taunt boss"] =
            &RaidZulGurubActionContext::venoxis_tank_taunt_boss;
        creators["high priest venoxis attack nearest serpent"] =
            &RaidZulGurubActionContext::venoxis_attack_nearest_serpent;
        creators["high priest venoxis move out of poison cloud"] =
            &RaidZulGurubActionContext::venoxis_move_out_of_poison_cloud;

        // High Priestess Jeklik
        creators["high priestess jeklik main tank attack boss"] =
            &RaidZulGurubActionContext::jeklik_main_tank_attack_boss;
        creators["high priestess jeklik tank taunt boss"] =
            &RaidZulGurubActionContext::jeklik_tank_taunt_boss;
        creators["high priestess jeklik attack nearest bat"] =
            &RaidZulGurubActionContext::jeklik_attack_nearest_bat;
        creators["high priestess jeklik move out of liquid fire"] =
            &RaidZulGurubActionContext::jeklik_move_out_of_liquid_fire;

        // High Priestess Mar'li
        creators["high priestess mar'li main tank attack boss"] =
            &RaidZulGurubActionContext::marli_main_tank_attack_boss;
        creators["high priestess mar'li tank taunt boss"] =
            &RaidZulGurubActionContext::marli_tank_taunt_boss;
        creators["high priestess mar'li attack nearest spawn"] =
            &RaidZulGurubActionContext::marli_attack_nearest_spawn;

        // Bloodlord Mandokir
        creators["bloodlord mandokir main tank attack boss"] =
            &RaidZulGurubActionContext::mandokir_main_tank_attack_boss;
        creators["bloodlord mandokir tank taunt boss"] =
            &RaidZulGurubActionContext::mandokir_tank_taunt_boss;
        creators["bloodlord mandokir stop attacking while watched"] =
            &RaidZulGurubActionContext::mandokir_stop_attacking_while_watched;
        creators["bloodlord mandokir assist tank attack ohgan"] =
            &RaidZulGurubActionContext::mandokir_assist_tank_attack_ohgan;
        creators["bloodlord mandokir attack ohgan"] =
            &RaidZulGurubActionContext::mandokir_attack_ohgan;
        creators["bloodlord mandokir melee back off"] =
            &RaidZulGurubActionContext::mandokir_melee_back_off;

        // High Priest Thekal
        creators["high priest thekal main tank attack boss"] =
            &RaidZulGurubActionContext::thekal_main_tank_attack_boss;
        creators["high priest thekal assist tank attack zealot"] =
            &RaidZulGurubActionContext::thekal_assist_tank_attack_zealot;
        creators["high priest thekal attack healthiest trio target"] =
            &RaidZulGurubActionContext::thekal_attack_healthiest_trio_target;
        creators["high priest thekal tank taunt boss"] =
            &RaidZulGurubActionContext::thekal_tank_taunt_boss;
        creators["high priest thekal attack nearest tiger"] =
            &RaidZulGurubActionContext::thekal_attack_nearest_tiger;

        // High Priestess Arlokk
        creators["high priestess arlokk main tank attack boss"] =
            &RaidZulGurubActionContext::arlokk_main_tank_attack_boss;
        creators["high priestess arlokk tank taunt boss"] =
            &RaidZulGurubActionContext::arlokk_tank_taunt_boss;
        creators["high priestess arlokk attack nearest prowler"] =
            &RaidZulGurubActionContext::arlokk_attack_nearest_prowler;

        // Jin'do the Hexxer
        creators["jin'do the hexxer main tank attack boss"] =
            &RaidZulGurubActionContext::jindo_main_tank_attack_boss;
        creators["jin'do the hexxer attack healing ward"] =
            &RaidZulGurubActionContext::jindo_attack_healing_ward;
        creators["jin'do the hexxer attack brain wash totem"] =
            &RaidZulGurubActionContext::jindo_attack_brain_wash_totem;
        creators["jin'do the hexxer attack nearest shade"] =
            &RaidZulGurubActionContext::jindo_attack_nearest_shade;
        creators["jin'do the hexxer assist tank taunt boss"] =
            &RaidZulGurubActionContext::jindo_assist_tank_taunt_boss;

        // Hakkar
        creators["hakkar main tank attack boss"] =
            &RaidZulGurubActionContext::hakkar_main_tank_attack_boss;
        creators["hakkar tank taunt boss"] = &RaidZulGurubActionContext::hakkar_tank_taunt_boss;
        creators["hakkar stop attacking insane ally"] =
            &RaidZulGurubActionContext::hakkar_stop_attacking_insane_ally;

        // Gahz'ranka
        creators["gahz'ranka main tank attack boss"] =
            &RaidZulGurubActionContext::gahzranka_main_tank_attack_boss;
        creators["gahz'ranka tank taunt boss"] =
            &RaidZulGurubActionContext::gahzranka_tank_taunt_boss;

        // Edge of Madness
        creators["gri'lek main tank attack boss"] =
            &RaidZulGurubActionContext::grilek_main_tank_attack_boss;
        creators["gri'lek tank taunt boss"] = &RaidZulGurubActionContext::grilek_tank_taunt_boss;
        creators["gri'lek run from boss"] = &RaidZulGurubActionContext::grilek_run_from_boss;
        creators["hazza'rah main tank attack boss"] =
            &RaidZulGurubActionContext::hazzarah_main_tank_attack_boss;
        creators["hazza'rah attack nearest illusion"] =
            &RaidZulGurubActionContext::hazzarah_attack_nearest_illusion;
        creators["hazza'rah spread ranged"] = &RaidZulGurubActionContext::hazzarah_spread_ranged;
        creators["renataki main tank attack boss"] =
            &RaidZulGurubActionContext::renataki_main_tank_attack_boss;
        creators["renataki tank taunt boss"] =
            &RaidZulGurubActionContext::renataki_tank_taunt_boss;
        creators["wushoolay main tank attack boss"] =
            &RaidZulGurubActionContext::wushoolay_main_tank_attack_boss;
        creators["wushoolay move out of lightning cloud"] =
            &RaidZulGurubActionContext::wushoolay_move_out_of_lightning_cloud;
        creators["wushoolay spread ranged"] = &RaidZulGurubActionContext::wushoolay_spread_ranged;
    }

private:
    static Action* zg_reset_encounter_states(PlayerbotAI* botAI)
    {
        return new ZulGurubResetEncounterStatesAction(botAI);
    }
    static Action* zg_move_into_poisonous_cloud(PlayerbotAI* botAI)
    {
        return new ZulGurubMoveIntoPoisonousCloudAction(botAI);
    }

    static Action* venoxis_main_tank_attack_boss(PlayerbotAI* botAI)
    {
        return new ZulGurubMainTankAttackBossAction(
            botAI, "high priest venoxis main tank attack boss",
            ZulGurubHelpers::Id(ZulGurubHelpers::ZulGurubNpcs::NPC_VENOXIS));
    }
    static Action* venoxis_tank_taunt_boss(PlayerbotAI* botAI)
    {
        return new ZulGurubTankTauntBossAction(
            botAI, "high priest venoxis tank taunt boss",
            ZulGurubHelpers::Id(ZulGurubHelpers::ZulGurubNpcs::NPC_VENOXIS));
    }
    static Action* venoxis_attack_nearest_serpent(PlayerbotAI* botAI)
    {
        return new ZulGurubAttackNearestAddAction(
            botAI, "high priest venoxis attack nearest serpent",
            ZulGurubHelpers::VENOXIS_SERPENTS_VALUE);
    }
    static Action* venoxis_move_out_of_poison_cloud(PlayerbotAI* botAI)
    {
        return new ZulGurubMoveOutOfHazardAction(
            botAI, "high priest venoxis move out of poison cloud",
            ZulGurubHelpers::VENOXIS_POISON_CLOUD_VALUE, ZulGurubHelpers::POISON_CLOUD_RADIUS);
    }

    static Action* jeklik_main_tank_attack_boss(PlayerbotAI* botAI)
    {
        return new ZulGurubMainTankAttackBossAction(
            botAI, "high priestess jeklik main tank attack boss",
            ZulGurubHelpers::Id(ZulGurubHelpers::ZulGurubNpcs::NPC_JEKLIK));
    }
    static Action* jeklik_tank_taunt_boss(PlayerbotAI* botAI)
    {
        return new ZulGurubTankTauntBossAction(
            botAI, "high priestess jeklik tank taunt boss",
            ZulGurubHelpers::Id(ZulGurubHelpers::ZulGurubNpcs::NPC_JEKLIK));
    }
    static Action* jeklik_attack_nearest_bat(PlayerbotAI* botAI)
    {
        return new ZulGurubAttackNearestAddAction(
            botAI, "high priestess jeklik attack nearest bat", ZulGurubHelpers::JEKLIK_BATS_VALUE);
    }
    static Action* jeklik_move_out_of_liquid_fire(PlayerbotAI* botAI)
    {
        return new ZulGurubMoveOutOfHazardAction(
            botAI, "high priestess jeklik move out of liquid fire",
            ZulGurubHelpers::JEKLIK_LIQUID_FIRE_VALUE, ZulGurubHelpers::LIQUID_FIRE_RADIUS);
    }

    static Action* marli_main_tank_attack_boss(PlayerbotAI* botAI)
    {
        return new ZulGurubMainTankAttackBossAction(
            botAI, "high priestess mar'li main tank attack boss",
            ZulGurubHelpers::Id(ZulGurubHelpers::ZulGurubNpcs::NPC_MARLI));
    }
    static Action* marli_tank_taunt_boss(PlayerbotAI* botAI)
    {
        return new ZulGurubTankTauntBossAction(
            botAI, "high priestess mar'li tank taunt boss",
            ZulGurubHelpers::Id(ZulGurubHelpers::ZulGurubNpcs::NPC_MARLI));
    }
    static Action* marli_attack_nearest_spawn(PlayerbotAI* botAI)
    {
        return new ZulGurubAttackNearestAddAction(
            botAI, "high priestess mar'li attack nearest spawn",
            ZulGurubHelpers::MARLI_SPAWNS_VALUE);
    }

    static Action* mandokir_main_tank_attack_boss(PlayerbotAI* botAI)
    {
        return new ZulGurubMainTankAttackBossAction(
            botAI, "bloodlord mandokir main tank attack boss",
            ZulGurubHelpers::Id(ZulGurubHelpers::ZulGurubNpcs::NPC_MANDOKIR));
    }
    static Action* mandokir_tank_taunt_boss(PlayerbotAI* botAI)
    {
        return new ZulGurubTankTauntBossAction(
            botAI, "bloodlord mandokir tank taunt boss",
            ZulGurubHelpers::Id(ZulGurubHelpers::ZulGurubNpcs::NPC_MANDOKIR));
    }
    static Action* mandokir_stop_attacking_while_watched(PlayerbotAI* botAI)
    {
        return new MandokirStopAttackingWhileWatchedAction(botAI);
    }
    static Action* mandokir_assist_tank_attack_ohgan(PlayerbotAI* botAI)
    {
        return new ZulGurubAttackNearestAddAction(
            botAI, "bloodlord mandokir assist tank attack ohgan",
            ZulGurubHelpers::MANDOKIR_OHGAN_VALUE);
    }
    static Action* mandokir_attack_ohgan(PlayerbotAI* botAI)
    {
        return new ZulGurubAttackNearestAddAction(
            botAI, "bloodlord mandokir attack ohgan", ZulGurubHelpers::MANDOKIR_OHGAN_VALUE);
    }
    static Action* mandokir_melee_back_off(PlayerbotAI* botAI)
    {
        return new ZulGurubFleeFromCreatureAction(
            botAI, "bloodlord mandokir melee back off",
            ZulGurubHelpers::Id(ZulGurubHelpers::ZulGurubNpcs::NPC_MANDOKIR),
            ZulGurubHelpers::WHIRLWIND_ESCAPE_DISTANCE);
    }

    static Action* thekal_main_tank_attack_boss(PlayerbotAI* botAI)
    {
        return new ZulGurubMainTankAttackBossAction(
            botAI, "high priest thekal main tank attack boss",
            ZulGurubHelpers::Id(ZulGurubHelpers::ZulGurubNpcs::NPC_THEKAL));
    }
    static Action* thekal_assist_tank_attack_zealot(PlayerbotAI* botAI)
    {
        return new ThekalAssistTankAttackZealotAction(botAI);
    }
    static Action* thekal_attack_healthiest_trio_target(PlayerbotAI* botAI)
    {
        return new ThekalAttackTrioFocusAction(botAI);
    }
    static Action* thekal_tank_taunt_boss(PlayerbotAI* botAI)
    {
        return new ZulGurubTankTauntBossAction(
            botAI, "high priest thekal tank taunt boss",
            ZulGurubHelpers::Id(ZulGurubHelpers::ZulGurubNpcs::NPC_THEKAL));
    }
    static Action* thekal_attack_nearest_tiger(PlayerbotAI* botAI)
    {
        return new ZulGurubAttackNearestAddAction(
            botAI, "high priest thekal attack nearest tiger", ZulGurubHelpers::THEKAL_TIGERS_VALUE);
    }

    static Action* arlokk_main_tank_attack_boss(PlayerbotAI* botAI)
    {
        return new ZulGurubMainTankAttackBossAction(
            botAI, "high priestess arlokk main tank attack boss",
            ZulGurubHelpers::Id(ZulGurubHelpers::ZulGurubNpcs::NPC_ARLOKK));
    }
    static Action* arlokk_tank_taunt_boss(PlayerbotAI* botAI)
    {
        return new ZulGurubTankTauntBossAction(
            botAI, "high priestess arlokk tank taunt boss",
            ZulGurubHelpers::Id(ZulGurubHelpers::ZulGurubNpcs::NPC_ARLOKK));
    }
    static Action* arlokk_attack_nearest_prowler(PlayerbotAI* botAI)
    {
        return new ZulGurubAttackNearestAddAction(
            botAI, "high priestess arlokk attack nearest prowler",
            ZulGurubHelpers::ARLOKK_PROWLERS_VALUE);
    }

    static Action* jindo_main_tank_attack_boss(PlayerbotAI* botAI)
    {
        return new ZulGurubMainTankAttackBossAction(
            botAI, "jin'do the hexxer main tank attack boss",
            ZulGurubHelpers::Id(ZulGurubHelpers::ZulGurubNpcs::NPC_JINDO));
    }
    static Action* jindo_attack_healing_ward(PlayerbotAI* botAI)
    {
        return new ZulGurubAttackNearestAddAction(
            botAI, "jin'do the hexxer attack healing ward",
            ZulGurubHelpers::JINDO_HEALING_WARDS_VALUE);
    }
    static Action* jindo_attack_brain_wash_totem(PlayerbotAI* botAI)
    {
        return new ZulGurubAttackNearestAddAction(
            botAI, "jin'do the hexxer attack brain wash totem",
            ZulGurubHelpers::JINDO_BRAIN_WASH_TOTEMS_VALUE);
    }
    static Action* jindo_attack_nearest_shade(PlayerbotAI* botAI)
    {
        return new ZulGurubAttackNearestAddAction(
            botAI, "jin'do the hexxer attack nearest shade", ZulGurubHelpers::JINDO_SHADES_VALUE);
    }
    static Action* jindo_assist_tank_taunt_boss(PlayerbotAI* botAI)
    {
        return new ZulGurubTankTauntBossAction(
            botAI, "jin'do the hexxer assist tank taunt boss",
            ZulGurubHelpers::Id(ZulGurubHelpers::ZulGurubNpcs::NPC_JINDO));
    }

    static Action* hakkar_main_tank_attack_boss(PlayerbotAI* botAI)
    {
        return new ZulGurubMainTankAttackBossAction(
            botAI, "hakkar main tank attack boss",
            ZulGurubHelpers::Id(ZulGurubHelpers::ZulGurubNpcs::NPC_HAKKAR));
    }
    static Action* hakkar_tank_taunt_boss(PlayerbotAI* botAI)
    {
        return new ZulGurubTankTauntBossAction(
            botAI, "hakkar tank taunt boss",
            ZulGurubHelpers::Id(ZulGurubHelpers::ZulGurubNpcs::NPC_HAKKAR));
    }
    static Action* hakkar_stop_attacking_insane_ally(PlayerbotAI* botAI)
    {
        return new ZulGurubStopAttackingCharmedAllyAction(
            botAI, "hakkar stop attacking insane ally",
            ZulGurubHelpers::Id(ZulGurubHelpers::ZulGurubNpcs::NPC_HAKKAR));
    }

    static Action* gahzranka_main_tank_attack_boss(PlayerbotAI* botAI)
    {
        return new ZulGurubMainTankAttackBossAction(
            botAI, "gahz'ranka main tank attack boss",
            ZulGurubHelpers::Id(ZulGurubHelpers::ZulGurubNpcs::NPC_GAHZRANKA));
    }
    static Action* gahzranka_tank_taunt_boss(PlayerbotAI* botAI)
    {
        return new ZulGurubTankTauntBossAction(
            botAI, "gahz'ranka tank taunt boss",
            ZulGurubHelpers::Id(ZulGurubHelpers::ZulGurubNpcs::NPC_GAHZRANKA));
    }

    static Action* grilek_main_tank_attack_boss(PlayerbotAI* botAI)
    {
        return new ZulGurubMainTankAttackBossAction(
            botAI, "gri'lek main tank attack boss",
            ZulGurubHelpers::Id(ZulGurubHelpers::ZulGurubNpcs::NPC_GRILEK));
    }
    static Action* grilek_tank_taunt_boss(PlayerbotAI* botAI)
    {
        return new ZulGurubTankTauntBossAction(
            botAI, "gri'lek tank taunt boss",
            ZulGurubHelpers::Id(ZulGurubHelpers::ZulGurubNpcs::NPC_GRILEK));
    }
    static Action* grilek_run_from_boss(PlayerbotAI* botAI)
    {
        return new ZulGurubFleeFromCreatureAction(
            botAI, "gri'lek run from boss",
            ZulGurubHelpers::Id(ZulGurubHelpers::ZulGurubNpcs::NPC_GRILEK),
            ZulGurubHelpers::AVATAR_FLEE_DISTANCE);
    }
    static Action* hazzarah_main_tank_attack_boss(PlayerbotAI* botAI)
    {
        return new ZulGurubMainTankAttackBossAction(
            botAI, "hazza'rah main tank attack boss",
            ZulGurubHelpers::Id(ZulGurubHelpers::ZulGurubNpcs::NPC_HAZZARAH));
    }
    static Action* hazzarah_attack_nearest_illusion(PlayerbotAI* botAI)
    {
        return new ZulGurubAttackNearestAddAction(
            botAI, "hazza'rah attack nearest illusion",
            ZulGurubHelpers::HAZZARAH_ILLUSIONS_VALUE);
    }
    static Action* hazzarah_spread_ranged(PlayerbotAI* botAI)
    {
        return new ZulGurubSpreadRangedAction(botAI, "hazza'rah spread ranged");
    }
    static Action* renataki_main_tank_attack_boss(PlayerbotAI* botAI)
    {
        return new ZulGurubMainTankAttackBossAction(
            botAI, "renataki main tank attack boss",
            ZulGurubHelpers::Id(ZulGurubHelpers::ZulGurubNpcs::NPC_RENATAKI));
    }
    static Action* renataki_tank_taunt_boss(PlayerbotAI* botAI)
    {
        return new ZulGurubTankTauntBossAction(
            botAI, "renataki tank taunt boss",
            ZulGurubHelpers::Id(ZulGurubHelpers::ZulGurubNpcs::NPC_RENATAKI));
    }
    static Action* wushoolay_main_tank_attack_boss(PlayerbotAI* botAI)
    {
        return new ZulGurubMainTankAttackBossAction(
            botAI, "wushoolay main tank attack boss",
            ZulGurubHelpers::Id(ZulGurubHelpers::ZulGurubNpcs::NPC_WUSHOOLAY));
    }
    static Action* wushoolay_move_out_of_lightning_cloud(PlayerbotAI* botAI)
    {
        return new ZulGurubMoveOutOfHazardAction(
            botAI, "wushoolay move out of lightning cloud",
            ZulGurubHelpers::WUSHOOLAY_LIGHTNING_CLOUD_VALUE,
            ZulGurubHelpers::LIGHTNING_CLOUD_RADIUS);
    }
    static Action* wushoolay_spread_ranged(PlayerbotAI* botAI)
    {
        return new ZulGurubSpreadRangedAction(botAI, "wushoolay spread ranged");
    }
};

#endif
