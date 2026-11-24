/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#ifndef PLAYERBOTS_VOAACTIONCONTEXT_H
#define PLAYERBOTS_VOAACTIONCONTEXT_H

#include "Action.h"
#include "BossAuraActions.h"
#include "NamedObjectContext.h"
#include "PlayerbotAI.h"
#include "VoAActions.h"
#include "VoAHelpers.h"

class RaidVoAActionContext : public NamedObjectContext<Action>
{
public:
    RaidVoAActionContext()
    {
        creators["emalon mark boss action"] = &RaidVoAActionContext::emalon_mark_boss_action;
        creators["emalon lighting nova action"] = &RaidVoAActionContext::emalon_lighting_nova_action;
        creators["emalon overcharge action"] = &RaidVoAActionContext::emalon_overcharge_action;
        creators["emalon fall from floor action"] = &RaidVoAActionContext::emalon_fall_from_floor_action;
        creators["emalon nature resistance action"] = &RaidVoAActionContext::emalon_nature_resistance_action;
        creators["koralon fire resistance action"] = &RaidVoAActionContext::koralon_fire_resistance_action;

        // Archavon the Stone Watcher
        creators["archavon taunt boss"] = &RaidVoAActionContext::archavon_taunt_boss;
        creators["archavon main tank attack boss"] =
            &RaidVoAActionContext::archavon_main_tank_attack_boss;
        creators["archavon spread ranged"] = &RaidVoAActionContext::archavon_spread_ranged;

        // Emalon the Storm Watcher
        creators["emalon main tank attack boss"] =
            &RaidVoAActionContext::emalon_main_tank_attack_boss;
        creators["emalon spread ranged"] = &RaidVoAActionContext::emalon_spread_ranged;
        creators["emalon tank attack nearest minion"] =
            &RaidVoAActionContext::emalon_tank_attack_nearest_minion;
        creators["emalon attack overcharged minion"] =
            &RaidVoAActionContext::emalon_attack_overcharged_minion;

        // Koralon the Flame Watcher
        creators["koralon main tank attack boss"] =
            &RaidVoAActionContext::koralon_main_tank_attack_boss;
        creators["koralon spread ranged"] = &RaidVoAActionContext::koralon_spread_ranged;
        creators["koralon move behind koralon"] =
            &RaidVoAActionContext::koralon_move_behind_koralon;

        // Toravon the Ice Watcher
        creators["toravon main tank attack boss"] =
            &RaidVoAActionContext::toravon_main_tank_attack_boss;
        creators["toravon attack nearest frozen orb"] =
            &RaidVoAActionContext::toravon_attack_nearest_frozen_orb;
        creators["toravon flee from frozen orb"] =
            &RaidVoAActionContext::toravon_flee_from_frozen_orb;
        creators["toravon move away from frozen orb"] =
            &RaidVoAActionContext::toravon_move_away_from_frozen_orb;
        creators["toravon move out of freezing ground"] =
            &RaidVoAActionContext::toravon_move_out_of_freezing_ground;
    }

private:
    static Action* archavon_taunt_boss(PlayerbotAI* botAI)
    {
        return new ArchavonTauntAction(botAI);
    }

    static Action* emalon_mark_boss_action(PlayerbotAI* botAI) { return new EmalonMarkBossAction(botAI); }
    static Action* emalon_lighting_nova_action(PlayerbotAI* botAI) { return new EmalonLightingNovaAction(botAI); }
    static Action* emalon_overcharge_action(PlayerbotAI* botAI) { return new EmalonOverchargeAction(botAI); }
    static Action* emalon_fall_from_floor_action(PlayerbotAI* botAI) { return new EmalonFallFromFloorAction(botAI); }
    static Action* emalon_nature_resistance_action(PlayerbotAI* botAI) { return new BossNatureResistanceAction(botAI, "emalon the storm watcher"); }
    static Action* koralon_fire_resistance_action(PlayerbotAI* botAI) { return new BossFireResistanceAction(botAI, "koralon the flame watcher"); }

    static Action* archavon_main_tank_attack_boss(PlayerbotAI* botAI)
    {
        return new VoAAttackCreatureAction(
            botAI, "archavon main tank attack boss",
            VoAHelpers::Id(VoAHelpers::VoANpcs::NPC_ARCHAVON));
    }
    static Action* archavon_spread_ranged(PlayerbotAI* botAI)
    {
        return new VoASpreadRangedAction(
            botAI, "archavon spread ranged", VoAHelpers::Id(VoAHelpers::VoANpcs::NPC_ARCHAVON));
    }
    static Action* emalon_main_tank_attack_boss(PlayerbotAI* botAI)
    {
        return new VoAAttackCreatureAction(
            botAI, "emalon main tank attack boss",
            VoAHelpers::Id(VoAHelpers::VoANpcs::NPC_EMALON));
    }
    static Action* emalon_spread_ranged(PlayerbotAI* botAI)
    {
        return new VoASpreadRangedAction(
            botAI, "emalon spread ranged", VoAHelpers::Id(VoAHelpers::VoANpcs::NPC_EMALON));
    }
    static Action* emalon_tank_attack_nearest_minion(PlayerbotAI* botAI)
    {
        return new VoATankAttackNearestAddAction(
            botAI, "emalon tank attack nearest minion", VoAHelpers::EMALON_MINIONS_VALUE);
    }
    static Action* emalon_attack_overcharged_minion(PlayerbotAI* botAI)
    {
        return new EmalonAttackOverchargedMinionAction(botAI);
    }
    static Action* koralon_main_tank_attack_boss(PlayerbotAI* botAI)
    {
        return new VoAAttackCreatureAction(
            botAI, "koralon main tank attack boss",
            VoAHelpers::Id(VoAHelpers::VoANpcs::NPC_KORALON));
    }
    static Action* koralon_spread_ranged(PlayerbotAI* botAI)
    {
        return new VoASpreadRangedAction(
            botAI, "koralon spread ranged", VoAHelpers::Id(VoAHelpers::VoANpcs::NPC_KORALON));
    }
    static Action* koralon_move_behind_koralon(PlayerbotAI* botAI)
    {
        return new KoralonMoveBehindBossAction(botAI);
    }
    static Action* toravon_main_tank_attack_boss(PlayerbotAI* botAI)
    {
        return new VoAAttackCreatureAction(
            botAI, "toravon main tank attack boss",
            VoAHelpers::Id(VoAHelpers::VoANpcs::NPC_TORAVON));
    }
    static Action* toravon_attack_nearest_frozen_orb(PlayerbotAI* botAI)
    {
        return new VoAAttackNearestAddAction(
            botAI, "toravon attack nearest frozen orb", VoAHelpers::TORAVON_FROZEN_ORBS_VALUE);
    }
    static Action* toravon_flee_from_frozen_orb(PlayerbotAI* botAI)
    {
        return new ToravonFleeFromOrbAction(botAI);
    }
    static Action* toravon_move_away_from_frozen_orb(PlayerbotAI* botAI)
    {
        return new VoAMoveAwayFromAddAction(
            botAI, "toravon move away from frozen orb", VoAHelpers::TORAVON_FROZEN_ORBS_VALUE,
            VoAHelpers::FROZEN_ORB_RADIUS);
    }
    static Action* toravon_move_out_of_freezing_ground(PlayerbotAI* botAI)
    {
        return new ToravonMoveOutOfFreezingGroundAction(botAI);
    }
};

#endif
