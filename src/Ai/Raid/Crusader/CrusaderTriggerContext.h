/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#ifndef PLAYERBOTS_CRUSADERTRIGGERCONTEXT_H
#define PLAYERBOTS_CRUSADERTRIGGERCONTEXT_H

#include "CrusaderHelpers.h"
#include "CrusaderTriggers.h"
#include "NamedObjectContext.h"

class RaidCrusaderTriggerContext : public NamedObjectContext<Trigger>
{
public:
    RaidCrusaderTriggerContext() : NamedObjectContext<Trigger>()
    {
        // Northrend Beasts
        creators["gormok the impaler should be tanked"] =
            &RaidCrusaderTriggerContext::gormok_should_be_tanked;
        creators["gormok the impaler snobold on raid member"] =
            &RaidCrusaderTriggerContext::gormok_snobold_on_raid_member;
        creators["gormok the impaler bot is snobolled"] =
            &RaidCrusaderTriggerContext::gormok_bot_is_snobolled;
        creators["gormok the impaler main tank has impale stacks"] =
            &RaidCrusaderTriggerContext::gormok_main_tank_has_impale_stacks;
        creators["acidmaw and dreadscale should be tanked"] =
            &RaidCrusaderTriggerContext::jormungar_should_be_tanked;
        creators["acidmaw and dreadscale bot in slime pool"] =
            &RaidCrusaderTriggerContext::jormungar_bot_in_slime_pool;
        creators["icehowl should be tanked"] = &RaidCrusaderTriggerContext::icehowl_should_be_tanked;
        creators["icehowl charge incoming"] = &RaidCrusaderTriggerContext::icehowl_charge_incoming;
        creators["icehowl bot near arena wall"] =
            &RaidCrusaderTriggerContext::icehowl_bot_near_arena_wall;
        creators["icehowl ranged should spread"] =
            &RaidCrusaderTriggerContext::icehowl_ranged_should_spread;

        // Lord Jaraxxus
        creators["lord jaraxxus should be tanked"] =
            &RaidCrusaderTriggerContext::jaraxxus_should_be_tanked;
        creators["lord jaraxxus bot in legion flame"] =
            &RaidCrusaderTriggerContext::jaraxxus_bot_in_legion_flame;
        creators["lord jaraxxus demon spawned"] =
            &RaidCrusaderTriggerContext::jaraxxus_demon_spawned;
        creators["lord jaraxxus ranged should spread"] =
            &RaidCrusaderTriggerContext::jaraxxus_ranged_should_spread;

        // Faction Champions
        creators["faction champions should focus target"] =
            &RaidCrusaderTriggerContext::faction_champions_should_focus_target;

        // Twin Val'kyr
        creators["twin val'kyr bot has no essence"] =
            &RaidCrusaderTriggerContext::valkyr_bot_has_no_essence;
        creators["twin val'kyr should be tanked"] =
            &RaidCrusaderTriggerContext::valkyr_should_be_tanked;
        creators["twin val'kyr pact incoming"] = &RaidCrusaderTriggerContext::valkyr_pact_incoming;
        creators["twin val'kyr bot near opposite ball"] =
            &RaidCrusaderTriggerContext::valkyr_bot_near_opposite_ball;
        creators["twin val'kyr matching ball nearby"] =
            &RaidCrusaderTriggerContext::valkyr_matching_ball_nearby;

        // Anub'arak
        creators["anub'arak should be tanked"] =
            &RaidCrusaderTriggerContext::anubarak_should_be_tanked;
        creators["anub'arak bot pursued by spike"] =
            &RaidCrusaderTriggerContext::anubarak_bot_pursued_by_spike;
        creators["anub'arak bot near pursuing spike"] =
            &RaidCrusaderTriggerContext::anubarak_bot_near_pursuing_spike;
        creators["anub'arak frost sphere should be dropped"] =
            &RaidCrusaderTriggerContext::anubarak_frost_sphere_should_be_dropped;
        creators["anub'arak burrowers spawned"] =
            &RaidCrusaderTriggerContext::anubarak_burrowers_spawned;
        creators["anub'arak scarabs spawned"] = &RaidCrusaderTriggerContext::anubarak_scarabs_spawned;
    }

private:
    static Trigger* gormok_should_be_tanked(PlayerbotAI* botAI)
    {
        return new CrusaderBossShouldBeTankedTrigger(
            botAI, "gormok the impaler should be tanked",
            CrusaderHelpers::Id(CrusaderHelpers::CrusaderNpcs::NPC_GORMOK));
    }
    static Trigger* gormok_snobold_on_raid_member(PlayerbotAI* botAI)
    {
        return new GormokSnoboldOnRaidMemberTrigger(botAI);
    }
    static Trigger* gormok_bot_is_snobolled(PlayerbotAI* botAI)
    {
        return new GormokBotIsSnobolledTrigger(botAI);
    }
    static Trigger* gormok_main_tank_has_impale_stacks(PlayerbotAI* botAI)
    {
        return new GormokMainTankImpaleStacksTrigger(botAI);
    }
    static Trigger* jormungar_should_be_tanked(PlayerbotAI* botAI)
    {
        return new JormungarShouldBeTankedTrigger(botAI);
    }
    static Trigger* jormungar_bot_in_slime_pool(PlayerbotAI* botAI)
    {
        return new CrusaderBotNearHazardTrigger(
            botAI, "acidmaw and dreadscale bot in slime pool",
            CrusaderHelpers::JORMUNGAR_SLIME_POOLS_VALUE, CrusaderHelpers::SLIME_POOL_RADIUS);
    }
    static Trigger* icehowl_should_be_tanked(PlayerbotAI* botAI)
    {
        return new CrusaderBossShouldBeTankedTrigger(
            botAI, "icehowl should be tanked",
            CrusaderHelpers::Id(CrusaderHelpers::CrusaderNpcs::NPC_ICEHOWL));
    }
    static Trigger* icehowl_charge_incoming(PlayerbotAI* botAI)
    {
        return new IcehowlChargeIncomingTrigger(botAI);
    }
    static Trigger* icehowl_bot_near_arena_wall(PlayerbotAI* botAI)
    {
        return new IcehowlBotNearArenaWallTrigger(botAI);
    }
    static Trigger* icehowl_ranged_should_spread(PlayerbotAI* botAI)
    {
        // Arctic Breath picks a random player (BNB:1134) and Whirl only reaches melee, so this is
        // spacing between the ranged, not distance from the boss.
        constexpr float noDistanceFromBoss = 0.0f;
        return new CrusaderRangedShouldSpreadTrigger(
            botAI, "icehowl ranged should spread",
            CrusaderHelpers::Id(CrusaderHelpers::CrusaderNpcs::NPC_ICEHOWL), noDistanceFromBoss);
    }

    static Trigger* jaraxxus_should_be_tanked(PlayerbotAI* botAI)
    {
        return new CrusaderBossShouldBeTankedTrigger(
            botAI, "lord jaraxxus should be tanked",
            CrusaderHelpers::Id(CrusaderHelpers::CrusaderNpcs::NPC_JARAXXUS));
    }
    static Trigger* jaraxxus_bot_in_legion_flame(PlayerbotAI* botAI)
    {
        return new CrusaderBotNearHazardTrigger(
            botAI, "lord jaraxxus bot in legion flame",
            CrusaderHelpers::JARAXXUS_LEGION_FLAMES_VALUE, CrusaderHelpers::LEGION_FLAME_RADIUS);
    }
    static Trigger* jaraxxus_demon_spawned(PlayerbotAI* botAI)
    {
        return new CrusaderAddsSpawnedTrigger(
            botAI, "lord jaraxxus demon spawned", CrusaderHelpers::JARAXXUS_DEMONS_VALUE,
            CrusaderAddRole::Tanks);
    }
    static Trigger* jaraxxus_ranged_should_spread(PlayerbotAI* botAI)
    {
        // Legion Flame drops under a random player and Fel Lightning picks one too (BLJ:185, :166).
        constexpr float noDistanceFromBoss = 0.0f;
        return new CrusaderRangedShouldSpreadTrigger(
            botAI, "lord jaraxxus ranged should spread",
            CrusaderHelpers::Id(CrusaderHelpers::CrusaderNpcs::NPC_JARAXXUS), noDistanceFromBoss);
    }

    static Trigger* faction_champions_should_focus_target(PlayerbotAI* botAI)
    {
        return new FactionChampionsShouldFocusTargetTrigger(botAI);
    }

    static Trigger* valkyr_bot_has_no_essence(PlayerbotAI* botAI)
    {
        return new ValkyrBotHasNoEssenceTrigger(botAI);
    }
    static Trigger* valkyr_should_be_tanked(PlayerbotAI* botAI)
    {
        return new ValkyrShouldBeTankedTrigger(botAI);
    }
    static Trigger* valkyr_pact_incoming(PlayerbotAI* botAI)
    {
        return new ValkyrPactIncomingTrigger(botAI);
    }
    static Trigger* valkyr_bot_near_opposite_ball(PlayerbotAI* botAI)
    {
        constexpr bool matching = false;
        return new ValkyrBallNearbyTrigger(
            botAI, "twin val'kyr bot near opposite ball", matching,
            CrusaderHelpers::BALL_BURST_RADIUS);
    }
    static Trigger* valkyr_matching_ball_nearby(PlayerbotAI* botAI)
    {
        constexpr bool matching = true;
        return new ValkyrBallNearbyTrigger(
            botAI, "twin val'kyr matching ball nearby", matching,
            CrusaderHelpers::BALL_COLLECT_RADIUS);
    }

    static Trigger* anubarak_should_be_tanked(PlayerbotAI* botAI)
    {
        return new CrusaderBossShouldBeTankedTrigger(
            botAI, "anub'arak should be tanked",
            CrusaderHelpers::Id(CrusaderHelpers::CrusaderNpcs::NPC_ANUBARAK));
    }
    static Trigger* anubarak_bot_pursued_by_spike(PlayerbotAI* botAI)
    {
        return new AnubarakBotPursuedBySpikeTrigger(botAI);
    }
    static Trigger* anubarak_bot_near_pursuing_spike(PlayerbotAI* botAI)
    {
        return new AnubarakBotNearSpikeTrigger(botAI);
    }
    static Trigger* anubarak_frost_sphere_should_be_dropped(PlayerbotAI* botAI)
    {
        return new AnubarakFrostSphereShouldBeDroppedTrigger(botAI);
    }
    static Trigger* anubarak_burrowers_spawned(PlayerbotAI* botAI)
    {
        return new CrusaderAddsSpawnedTrigger(
            botAI, "anub'arak burrowers spawned", CrusaderHelpers::ANUBARAK_BURROWERS_VALUE,
            CrusaderAddRole::MeleeAndTanks);
    }
    static Trigger* anubarak_scarabs_spawned(PlayerbotAI* botAI)
    {
        return new CrusaderAddsSpawnedTrigger(
            botAI, "anub'arak scarabs spawned", CrusaderHelpers::ANUBARAK_SCARABS_VALUE,
            CrusaderAddRole::Everyone);
    }
};

#endif
