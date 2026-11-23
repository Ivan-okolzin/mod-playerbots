/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#ifndef PLAYERBOTS_CRUSADERACTIONCONTEXT_H
#define PLAYERBOTS_CRUSADERACTIONCONTEXT_H

#include "CrusaderActions.h"
#include "CrusaderHelpers.h"
#include "NamedObjectContext.h"

class RaidCrusaderActionContext : public NamedObjectContext<Action>
{
public:
    RaidCrusaderActionContext()
    {
        // Northrend Beasts
        creators["gormok the impaler main tank attack boss"] =
            &RaidCrusaderActionContext::gormok_main_tank_attack_boss;
        creators["gormok the impaler attack nearest snobold"] =
            &RaidCrusaderActionContext::gormok_attack_nearest_snobold;
        creators["gormok the impaler tank swap"] = &RaidCrusaderActionContext::gormok_tank_swap;
        creators["acidmaw and dreadscale assign tanks"] =
            &RaidCrusaderActionContext::jormungar_assign_tanks;
        creators["acidmaw and dreadscale move away from slime pool"] =
            &RaidCrusaderActionContext::jormungar_move_away_from_slime_pool;
        creators["icehowl main tank attack boss"] =
            &RaidCrusaderActionContext::icehowl_main_tank_attack_boss;
        creators["icehowl move out of charge path"] =
            &RaidCrusaderActionContext::icehowl_move_out_of_charge_path;
        creators["icehowl move away from arena wall"] =
            &RaidCrusaderActionContext::icehowl_move_away_from_arena_wall;
        creators["icehowl spread ranged"] = &RaidCrusaderActionContext::icehowl_spread_ranged;

        // Lord Jaraxxus
        creators["lord jaraxxus main tank attack boss"] =
            &RaidCrusaderActionContext::jaraxxus_main_tank_attack_boss;
        creators["lord jaraxxus move away from legion flame"] =
            &RaidCrusaderActionContext::jaraxxus_move_away_from_legion_flame;
        creators["lord jaraxxus tank attack nearest demon"] =
            &RaidCrusaderActionContext::jaraxxus_tank_attack_nearest_demon;
        creators["lord jaraxxus spread ranged"] =
            &RaidCrusaderActionContext::jaraxxus_spread_ranged;

        // Faction Champions
        creators["faction champions attack focus target"] =
            &RaidCrusaderActionContext::faction_champions_attack_focus_target;

        // Twin Val'kyr
        creators["twin val'kyr take essence"] = &RaidCrusaderActionContext::valkyr_take_essence;
        creators["twin val'kyr assign tanks"] = &RaidCrusaderActionContext::valkyr_assign_tanks;
        creators["twin val'kyr attack pacting twin"] =
            &RaidCrusaderActionContext::valkyr_attack_pacting_twin;
        creators["twin val'kyr move away from ball"] =
            &RaidCrusaderActionContext::valkyr_move_away_from_ball;
        creators["twin val'kyr collect matching ball"] =
            &RaidCrusaderActionContext::valkyr_collect_matching_ball;

        // Anub'arak
        creators["anub'arak main tank attack boss"] =
            &RaidCrusaderActionContext::anubarak_main_tank_attack_boss;
        creators["anub'arak flee to permafrost"] =
            &RaidCrusaderActionContext::anubarak_flee_to_permafrost;
        creators["anub'arak flee from spike"] = &RaidCrusaderActionContext::anubarak_flee_from_spike;
        creators["anub'arak move away from spike"] =
            &RaidCrusaderActionContext::anubarak_move_away_from_spike;
        creators["anub'arak shoot down frost sphere"] =
            &RaidCrusaderActionContext::anubarak_shoot_down_frost_sphere;
        creators["anub'arak attack nearest burrower"] =
            &RaidCrusaderActionContext::anubarak_attack_nearest_burrower;
        creators["anub'arak attack nearest scarab"] =
            &RaidCrusaderActionContext::anubarak_attack_nearest_scarab;
    }

private:
    static Action* gormok_main_tank_attack_boss(PlayerbotAI* botAI)
    {
        return new CrusaderAttackCreatureAction(
            botAI, "gormok the impaler main tank attack boss",
            CrusaderHelpers::Id(CrusaderHelpers::CrusaderNpcs::NPC_GORMOK));
    }
    static Action* gormok_attack_nearest_snobold(PlayerbotAI* botAI)
    {
        return new GormokAttackNearestSnoboldAction(botAI);
    }
    static Action* gormok_tank_swap(PlayerbotAI* botAI) { return new GormokTankSwapAction(botAI); }
    static Action* jormungar_assign_tanks(PlayerbotAI* botAI)
    {
        return new JormungarAssignTanksAction(botAI);
    }
    static Action* jormungar_move_away_from_slime_pool(PlayerbotAI* botAI)
    {
        return new CrusaderMoveAwayFromHazardAction(
            botAI, "acidmaw and dreadscale move away from slime pool",
            CrusaderHelpers::JORMUNGAR_SLIME_POOLS_VALUE, CrusaderHelpers::SLIME_POOL_RADIUS);
    }
    static Action* icehowl_main_tank_attack_boss(PlayerbotAI* botAI)
    {
        return new CrusaderAttackCreatureAction(
            botAI, "icehowl main tank attack boss",
            CrusaderHelpers::Id(CrusaderHelpers::CrusaderNpcs::NPC_ICEHOWL));
    }
    static Action* icehowl_move_out_of_charge_path(PlayerbotAI* botAI)
    {
        return new IcehowlMoveOutOfChargePathAction(botAI);
    }
    static Action* icehowl_move_away_from_arena_wall(PlayerbotAI* botAI)
    {
        return new IcehowlMoveAwayFromArenaWallAction(botAI);
    }
    static Action* icehowl_spread_ranged(PlayerbotAI* botAI)
    {
        constexpr float noDistanceFromBoss = 0.0f;
        return new CrusaderSpreadRangedAction(
            botAI, "icehowl spread ranged",
            CrusaderHelpers::Id(CrusaderHelpers::CrusaderNpcs::NPC_ICEHOWL), noDistanceFromBoss);
    }

    static Action* jaraxxus_main_tank_attack_boss(PlayerbotAI* botAI)
    {
        return new CrusaderAttackCreatureAction(
            botAI, "lord jaraxxus main tank attack boss",
            CrusaderHelpers::Id(CrusaderHelpers::CrusaderNpcs::NPC_JARAXXUS));
    }
    static Action* jaraxxus_move_away_from_legion_flame(PlayerbotAI* botAI)
    {
        return new CrusaderMoveAwayFromHazardAction(
            botAI, "lord jaraxxus move away from legion flame",
            CrusaderHelpers::JARAXXUS_LEGION_FLAMES_VALUE, CrusaderHelpers::LEGION_FLAME_RADIUS);
    }
    static Action* jaraxxus_tank_attack_nearest_demon(PlayerbotAI* botAI)
    {
        return new CrusaderAttackNearestAddAction(
            botAI, "lord jaraxxus tank attack nearest demon",
            CrusaderHelpers::JARAXXUS_DEMONS_VALUE);
    }
    static Action* jaraxxus_spread_ranged(PlayerbotAI* botAI)
    {
        constexpr float noDistanceFromBoss = 0.0f;
        return new CrusaderSpreadRangedAction(
            botAI, "lord jaraxxus spread ranged",
            CrusaderHelpers::Id(CrusaderHelpers::CrusaderNpcs::NPC_JARAXXUS), noDistanceFromBoss);
    }

    static Action* faction_champions_attack_focus_target(PlayerbotAI* botAI)
    {
        return new FactionChampionsAttackFocusTargetAction(botAI);
    }

    static Action* valkyr_take_essence(PlayerbotAI* botAI)
    {
        return new ValkyrTakeEssenceAction(botAI);
    }
    static Action* valkyr_assign_tanks(PlayerbotAI* botAI)
    {
        return new ValkyrAssignTanksAction(botAI);
    }
    static Action* valkyr_attack_pacting_twin(PlayerbotAI* botAI)
    {
        return new ValkyrAttackPactingTwinAction(botAI);
    }
    static Action* valkyr_move_away_from_ball(PlayerbotAI* botAI)
    {
        return new ValkyrMoveAwayFromBallAction(botAI);
    }
    static Action* valkyr_collect_matching_ball(PlayerbotAI* botAI)
    {
        return new ValkyrCollectMatchingBallAction(botAI);
    }

    static Action* anubarak_main_tank_attack_boss(PlayerbotAI* botAI)
    {
        return new CrusaderAttackCreatureAction(
            botAI, "anub'arak main tank attack boss",
            CrusaderHelpers::Id(CrusaderHelpers::CrusaderNpcs::NPC_ANUBARAK));
    }
    static Action* anubarak_flee_to_permafrost(PlayerbotAI* botAI)
    {
        return new AnubarakFleeToPermafrostAction(botAI);
    }
    static Action* anubarak_flee_from_spike(PlayerbotAI* botAI)
    {
        return new AnubarakFleeFromSpikeAction(botAI);
    }
    static Action* anubarak_move_away_from_spike(PlayerbotAI* botAI)
    {
        return new CrusaderMoveAwayFromHazardAction(
            botAI, "anub'arak move away from spike", CrusaderHelpers::ANUBARAK_SPIKES_VALUE,
            CrusaderHelpers::SPIKE_HAZARD_RADIUS);
    }
    static Action* anubarak_shoot_down_frost_sphere(PlayerbotAI* botAI)
    {
        return new AnubarakShootDownFrostSphereAction(botAI);
    }
    static Action* anubarak_attack_nearest_burrower(PlayerbotAI* botAI)
    {
        return new CrusaderAttackNearestAddAction(
            botAI, "anub'arak attack nearest burrower", CrusaderHelpers::ANUBARAK_BURROWERS_VALUE);
    }
    static Action* anubarak_attack_nearest_scarab(PlayerbotAI* botAI)
    {
        return new CrusaderAttackNearestAddAction(
            botAI, "anub'arak attack nearest scarab", CrusaderHelpers::ANUBARAK_SCARABS_VALUE);
    }
};

#endif
