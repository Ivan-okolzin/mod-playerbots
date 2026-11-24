/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#ifndef PLAYERBOTS_VOATRIGGERCONTEXT_H
#define PLAYERBOTS_VOATRIGGERCONTEXT_H

#include "BossAuraTriggers.h"
#include "NamedObjectContext.h"
#include "VoAHelpers.h"
#include "VoATriggers.h"

class RaidVoATriggerContext : public NamedObjectContext<Trigger>
{
public:
    RaidVoATriggerContext()
    {
        creators["emalon mark boss trigger"] = &RaidVoATriggerContext::emalon_mark_boss_trigger;
        creators["emalon lighting nova trigger"] = &RaidVoATriggerContext::emalon_lighting_nova_trigger;
        creators["emalon overcharge trigger"] = &RaidVoATriggerContext::emalon_overcharge_trigger;
        creators["emalon fall from floor trigger"] = &RaidVoATriggerContext::emalon_fall_from_floor_trigger;
        creators["emalon nature resistance trigger"] = &RaidVoATriggerContext::emalon_nature_resistance_trigger;
        creators["koralon fire resistance trigger"] = &RaidVoATriggerContext::koralon_fire_resistance_trigger;

        // Archavon the Stone Watcher
        creators["archavon attacking non tank"] = &RaidVoATriggerContext::archavon_attacking_non_tank;
        creators["archavon should be tanked"] = &RaidVoATriggerContext::archavon_should_be_tanked;
        creators["archavon ranged should spread"] =
            &RaidVoATriggerContext::archavon_ranged_should_spread;

        // Emalon the Storm Watcher
        creators["emalon should be tanked"] = &RaidVoATriggerContext::emalon_should_be_tanked;
        creators["emalon ranged should spread"] =
            &RaidVoATriggerContext::emalon_ranged_should_spread;
        creators["emalon tempest minions spawned"] =
            &RaidVoATriggerContext::emalon_tempest_minions_spawned;
        creators["emalon overcharged minion should be killed"] =
            &RaidVoATriggerContext::emalon_overcharged_minion_should_be_killed;

        // Koralon the Flame Watcher
        creators["koralon should be tanked"] = &RaidVoATriggerContext::koralon_should_be_tanked;
        creators["koralon ranged should spread"] =
            &RaidVoATriggerContext::koralon_ranged_should_spread;
        creators["koralon burning breath incoming"] =
            &RaidVoATriggerContext::koralon_burning_breath_incoming;

        // Toravon the Ice Watcher
        creators["toravon should be tanked"] = &RaidVoATriggerContext::toravon_should_be_tanked;
        creators["toravon frozen orbs spawned"] =
            &RaidVoATriggerContext::toravon_frozen_orbs_spawned;
        creators["toravon bot pursued by frozen orb"] =
            &RaidVoATriggerContext::toravon_bot_pursued_by_frozen_orb;
        creators["toravon bot near frozen orb"] =
            &RaidVoATriggerContext::toravon_bot_near_frozen_orb;
        creators["toravon bot in freezing ground"] =
            &RaidVoATriggerContext::toravon_bot_in_freezing_ground;
    }

private:
    static Trigger* archavon_attacking_non_tank(PlayerbotAI* botAI)
    {
        return new ArchavonLostAggroTrigger(botAI);
    }

    static Trigger* emalon_mark_boss_trigger(PlayerbotAI* botAI) { return new EmalonMarkBossTrigger(botAI); }
    static Trigger* emalon_lighting_nova_trigger(PlayerbotAI* botAI) { return new EmalonLightingNovaTrigger(botAI); }
    static Trigger* emalon_overcharge_trigger(PlayerbotAI* botAI) { return new EmalonOverchargeTrigger(botAI); }
    static Trigger* emalon_fall_from_floor_trigger(PlayerbotAI* botAI) { return new EmalonFallFromFloorTrigger(botAI); }
    static Trigger* emalon_nature_resistance_trigger(PlayerbotAI* botAI) { return new BossNatureResistanceTrigger(botAI, "emalon the storm watcher"); }
    static Trigger* koralon_fire_resistance_trigger(PlayerbotAI* botAI) { return new BossFireResistanceTrigger(botAI, "koralon the flame watcher"); }

    static Trigger* archavon_should_be_tanked(PlayerbotAI* botAI)
    {
        return new VoABossShouldBeTankedTrigger(
            botAI, "archavon should be tanked",
            VoAHelpers::Id(VoAHelpers::VoANpcs::NPC_ARCHAVON));
    }
    // Rock Shards and Crushing Leap both pick one random player (BA:134, :142).
    static Trigger* archavon_ranged_should_spread(PlayerbotAI* botAI)
    {
        return new VoARangedShouldSpreadTrigger(
            botAI, "archavon ranged should spread",
            VoAHelpers::Id(VoAHelpers::VoANpcs::NPC_ARCHAVON));
    }
    static Trigger* emalon_should_be_tanked(PlayerbotAI* botAI)
    {
        return new VoABossShouldBeTankedTrigger(
            botAI, "emalon should be tanked", VoAHelpers::Id(VoAHelpers::VoANpcs::NPC_EMALON));
    }
    // Chain Lightning is cast at one random player and jumps from there (BE:182).
    static Trigger* emalon_ranged_should_spread(PlayerbotAI* botAI)
    {
        return new VoARangedShouldSpreadTrigger(
            botAI, "emalon ranged should spread", VoAHelpers::Id(VoAHelpers::VoANpcs::NPC_EMALON));
    }
    static Trigger* emalon_tempest_minions_spawned(PlayerbotAI* botAI)
    {
        return new EmalonTempestMinionsTrigger(botAI);
    }
    static Trigger* emalon_overcharged_minion_should_be_killed(PlayerbotAI* botAI)
    {
        return new EmalonOverchargedMinionTrigger(botAI);
    }
    static Trigger* koralon_should_be_tanked(PlayerbotAI* botAI)
    {
        return new VoABossShouldBeTankedTrigger(
            botAI, "koralon should be tanked", VoAHelpers::Id(VoAHelpers::VoANpcs::NPC_KORALON));
    }
    // Flaming Cinder lands on one player within 100 yards (BK:151, corrections of 66690).
    static Trigger* koralon_ranged_should_spread(PlayerbotAI* botAI)
    {
        return new VoARangedShouldSpreadTrigger(
            botAI, "koralon ranged should spread",
            VoAHelpers::Id(VoAHelpers::VoANpcs::NPC_KORALON));
    }
    static Trigger* koralon_burning_breath_incoming(PlayerbotAI* botAI)
    {
        return new KoralonBurningBreathTrigger(botAI);
    }
    static Trigger* toravon_should_be_tanked(PlayerbotAI* botAI)
    {
        return new VoABossShouldBeTankedTrigger(
            botAI, "toravon should be tanked", VoAHelpers::Id(VoAHelpers::VoANpcs::NPC_TORAVON));
    }
    // The orbs chase players through the room, so the melee stay on the boss and the ranged take
    // them down from where they are.
    static Trigger* toravon_frozen_orbs_spawned(PlayerbotAI* botAI)
    {
        return new VoAAddsSpawnedTrigger(
            botAI, "toravon frozen orbs spawned", VoAHelpers::TORAVON_FROZEN_ORBS_VALUE,
            VoAAddRole::RangedDps);
    }
    static Trigger* toravon_bot_pursued_by_frozen_orb(PlayerbotAI* botAI)
    {
        return new ToravonBotPursuedByOrbTrigger(botAI);
    }
    static Trigger* toravon_bot_near_frozen_orb(PlayerbotAI* botAI)
    {
        return new VoABotNearAddTrigger(
            botAI, "toravon bot near frozen orb", VoAHelpers::TORAVON_FROZEN_ORBS_VALUE,
            VoAHelpers::FROZEN_ORB_RADIUS);
    }
    static Trigger* toravon_bot_in_freezing_ground(PlayerbotAI* botAI)
    {
        return new ToravonBotInFreezingGroundTrigger(botAI);
    }
};

#endif
