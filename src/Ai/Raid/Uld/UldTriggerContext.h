/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#ifndef PLAYERBOTS_ULDTRIGGERCONTEXT_H
#define PLAYERBOTS_ULDTRIGGERCONTEXT_H

#include "BossAuraTriggers.h"
#include "NamedObjectContext.h"
#include "UldHelpers.h"
#include "UldTriggers.h"
#include <vector>

class RaidUlduarTriggerContext : public NamedObjectContext<Trigger>
{
public:
    RaidUlduarTriggerContext()
    {
        creators["vezax saronite animus spawned"] =
            &RaidUlduarTriggerContext::vezax_saronite_animus_spawned;
        creators["freya strengthened iron roots spawned"] =
            &RaidUlduarTriggerContext::freya_strengthened_iron_roots_spawned;
        creators["hodir player ice spawned"] =
            &RaidUlduarTriggerContext::hodir_player_ice_spawned;
        creators["flame leviathan on vehicle"] = &RaidUlduarTriggerContext::flame_leviathan_on_vehicle;
        creators["flame leviathan vehicle near"] = &RaidUlduarTriggerContext::flame_leviathan_vehicle_near;
        creators["razorscale flying alone"] = &RaidUlduarTriggerContext::razorscale_flying_alone;
        creators["razorscale avoid devouring flames"] = &RaidUlduarTriggerContext::razorscale_avoid_devouring_flames;
        creators["razorscale avoid sentinel"] = &RaidUlduarTriggerContext::razorscale_avoid_sentinel;
        creators["razorscale avoid whirlwind"] = &RaidUlduarTriggerContext::razorscale_avoid_whirlwind;
        creators["razorscale grounded"] = &RaidUlduarTriggerContext::razorscale_grounded;
        creators["razorscale harpoon trigger"] = &RaidUlduarTriggerContext::razorscale_harpoon_trigger;
        creators["razorscale fuse armor trigger"] = &RaidUlduarTriggerContext::razorscale_fuse_armor_trigger;
        creators["razorscale fire resistance trigger"] = &RaidUlduarTriggerContext::razorscale_fire_resistance_trigger;
        creators["ignis fire resistance trigger"] = &RaidUlduarTriggerContext::ignis_fire_resistance_trigger;
        creators["iron assembly lightning tendrils trigger"] = &RaidUlduarTriggerContext::iron_assembly_lightning_tendrils_trigger;
        creators["iron assembly overload trigger"] = &RaidUlduarTriggerContext::iron_assembly_overload_trigger;
        creators["iron assembly rune of power trigger"] = &RaidUlduarTriggerContext::iron_assembly_rune_of_power_trigger;
        creators["kologarn mark dps target trigger"] = &RaidUlduarTriggerContext::kologarn_mark_dps_target_trigger;
        creators["kologarn fall from floor trigger"] = &RaidUlduarTriggerContext::kologarn_fall_from_floor_trigger;
        creators["kologarn nature resistance trigger"] = &RaidUlduarTriggerContext::kologarn_nature_resistance_trigger;
        creators["kologarn rubble slowdown trigger"] = &RaidUlduarTriggerContext::kologarn_rubble_slowdown_trigger;
        creators["kologarn eyebeam trigger"] = &RaidUlduarTriggerContext::kologarn_eyebeam_trigger;
        creators["kologarn rti target trigger"] = &RaidUlduarTriggerContext::kologarn_rti_target_trigger;
        creators["kologarn crunch armor trigger"] = &RaidUlduarTriggerContext::kologarn_crunch_armor_trigger;
        creators["kologarn attack dps target trigger"] = &RaidUlduarTriggerContext::kologarn_attack_dps_target_trigger;
        creators["auriaya fall from floor trigger"] = &RaidUlduarTriggerContext::auriaya_fall_from_floor_trigger;
        creators["hodir biting cold"] = &RaidUlduarTriggerContext::hodir_biting_cold;
        creators["hodir near snowpacked icicle"] = &RaidUlduarTriggerContext::hodir_near_snowpacked_icicle;
        creators["hodir frost resistance trigger"] = &RaidUlduarTriggerContext::hodir_frost_resistance_trigger;
        creators["freya near nature bomb"] = &RaidUlduarTriggerContext::freya_near_nature_bomb;
        creators["freya fire resistance trigger"] = &RaidUlduarTriggerContext::freya_fire_resistance_trigger;
        creators["freya nature resistance trigger"] = &RaidUlduarTriggerContext::freya_nature_resistance_trigger;
        creators["freya mark dps target trigger"] = &RaidUlduarTriggerContext::freya_mark_dps_target_trigger;
        creators["freya move to healing spore trigger"] = &RaidUlduarTriggerContext::freya_move_to_healing_spore_trigger;
        creators["thorim frost resistance trigger"] = &RaidUlduarTriggerContext::thorim_frost_resistance_trigger;
        creators["thorim nature resistance trigger"] = &RaidUlduarTriggerContext::thorim_nature_resistance_trigger;
        creators["thorim unbalancing strike trigger"] = &RaidUlduarTriggerContext::thorim_unbalancing_strike_trigger;
        creators["thorim mark dps target trigger"] = &RaidUlduarTriggerContext::thorim_mark_dps_target_trigger;
        creators["thorim arena positioning trigger"] = &RaidUlduarTriggerContext::thorim_arena_positioning_trigger;
        creators["thorim gauntlet positioning trigger"] = &RaidUlduarTriggerContext::thorim_gauntlet_positioning_trigger;
        creators["thorim fall from floor trigger"] = &RaidUlduarTriggerContext::thorim_fall_from_floor_trigger;
        creators["thorim phase 2 positioning trigger"] = &RaidUlduarTriggerContext::thorim_phase2_positioning_trigger;
        creators["mimiron fire resistance trigger"] = &RaidUlduarTriggerContext::mimiron_fire_resistance_trigger;
        creators["mimiron shock blast trigger"] = &RaidUlduarTriggerContext::mimiron_shock_blast_trigger;
        creators["mimiron phase 1 positioning trigger"] = &RaidUlduarTriggerContext::mimiron_phase_1_positioning_trigger;
        creators["mimiron p3wx2 laser barrage trigger"] = &RaidUlduarTriggerContext::mimiron_p3wx2_laser_barrage_trigger;
        creators["mimiron rapid burst trigger"] = &RaidUlduarTriggerContext::mimiron_rapid_burst_trigger;
        creators["mimiron aerial command unit trigger"] = &RaidUlduarTriggerContext::mimiron_aerial_command_unit_trigger;
        creators["mimiron rocket strike trigger"] = &RaidUlduarTriggerContext::mimiron_rocket_strike_trigger;
        creators["mimiron phase 4 mark dps trigger"] = &RaidUlduarTriggerContext::mimiron_phase_4_mark_dps_trigger;
        creators["mimiron cheat trigger"] = &RaidUlduarTriggerContext::mimiron_cheat_trigger;
        creators["vezax cheat trigger"] = &RaidUlduarTriggerContext::vezax_cheat_trigger;
        creators["vezax shadow crash trigger"] = &RaidUlduarTriggerContext::vezax_shadow_crash_trigger;
        creators["vezax mark of the faceless trigger"] = &RaidUlduarTriggerContext::vezax_mark_of_the_faceless_trigger;
        creators["vezax shadow resistance trigger"] = &RaidUlduarTriggerContext::vezax_shadow_resistance_trigger;
        creators["sara shadow resistance trigger"] = &RaidUlduarTriggerContext::sara_shadow_resistance_trigger;
        creators["yogg-saron shadow resistance trigger"] =
            &RaidUlduarTriggerContext::yogg_saron_shadow_resistance_trigger;
        creators["yogg-saron ominous cloud cheat trigger"] = &RaidUlduarTriggerContext::yogg_saron_ominous_cloud_cheat_trigger;
        creators["yogg-saron guardian positioning trigger"] = &RaidUlduarTriggerContext::yogg_saron_guardian_positioning_trigger;
        creators["yogg-saron sanity trigger"] = &RaidUlduarTriggerContext::yogg_saron_sanity_trigger;
        creators["yogg-saron death orb trigger"] = &RaidUlduarTriggerContext::yogg_saron_death_orb_trigger;
        creators["yogg-saron malady of the mind trigger"] = &RaidUlduarTriggerContext::yogg_saron_malady_of_the_mind_trigger;
        creators["yogg-saron mark target trigger"] = &RaidUlduarTriggerContext::yogg_saron_mark_target_trigger;
        creators["yogg-saron brain link trigger"] = &RaidUlduarTriggerContext::yogg_saron_brain_link_trigger;
        creators["yogg-saron move to enter portal trigger"] = &RaidUlduarTriggerContext::yogg_saron_move_to_enter_portal_trigger;
        creators["yogg-saron use portal trigger"] = &RaidUlduarTriggerContext::yogg_saron_use_portal_trigger;
        creators["yogg-saron fall from floor trigger"] = &RaidUlduarTriggerContext::yogg_saron_fall_from_floor_trigger;
        creators["yogg-saron boss room movement cheat trigger"] = &RaidUlduarTriggerContext::yogg_saron_boss_room_movement_cheat_trigger;
        creators["yogg-saron illusion room trigger"] = &RaidUlduarTriggerContext::yogg_saron_illusion_room_trigger;
        creators["yogg-saron move to exit portal trigger"] = &RaidUlduarTriggerContext::yogg_saron_move_to_exit_portal_trigger;
        creators["yogg-saron lunatic gaze trigger"] = &RaidUlduarTriggerContext::yogg_saron_lunatic_gaze_trigger;
        creators["yogg-saron phase 3 positioning trigger"] = &RaidUlduarTriggerContext::yogg_saron_phase_3_positioning_trigger;

        // XT-002 Deconstructor
        creators["xt-002 should be tanked"] = &RaidUlduarTriggerContext::xt002_should_be_tanked;
        creators["xt-002 heart exposed"] = &RaidUlduarTriggerContext::xt002_heart_exposed;
        creators["xt-002 bot has gravity bomb"] =
            &RaidUlduarTriggerContext::xt002_bot_has_gravity_bomb;
        creators["xt-002 bot in void zone"] = &RaidUlduarTriggerContext::xt002_bot_in_void_zone;
        creators["xt-002 life spark spawned"] = &RaidUlduarTriggerContext::xt002_life_spark_spawned;
        creators["xt-002 scrapbot spawned"] = &RaidUlduarTriggerContext::xt002_scrapbot_spawned;
        creators["xt-002 pummeller spawned"] = &RaidUlduarTriggerContext::xt002_pummeller_spawned;
        creators["xt-002 boombot spawned"] = &RaidUlduarTriggerContext::xt002_boombot_spawned;
        creators["xt-002 bot near boombot"] = &RaidUlduarTriggerContext::xt002_bot_near_boombot;
        creators["xt-002 ranged should spread"] =
            &RaidUlduarTriggerContext::xt002_ranged_should_spread;

        // Ignis the Furnace Master
        creators["ignis should be tanked"] = &RaidUlduarTriggerContext::ignis_should_be_tanked;
        creators["ignis iron construct should be tanked"] =
            &RaidUlduarTriggerContext::ignis_construct_should_be_tanked;
        creators["ignis molten construct should be doused"] =
            &RaidUlduarTriggerContext::ignis_molten_construct_should_be_doused;
        creators["ignis brittle construct should be killed"] =
            &RaidUlduarTriggerContext::ignis_brittle_construct_should_be_killed;
        creators["ignis bot in scorched ground"] =
            &RaidUlduarTriggerContext::ignis_bot_in_scorched_ground;

        // Auriaya
        creators["auriaya should be tanked"] = &RaidUlduarTriggerContext::auriaya_should_be_tanked;
        creators["auriaya sentries spawned"] = &RaidUlduarTriggerContext::auriaya_sentries_spawned;
        creators["auriaya sanctum sentry should be killed"] =
            &RaidUlduarTriggerContext::auriaya_sentry_should_be_killed;
        creators["auriaya feral defender spawned"] =
            &RaidUlduarTriggerContext::auriaya_feral_defender_spawned;
        creators["auriaya bot in seeping essence"] =
            &RaidUlduarTriggerContext::auriaya_bot_in_seeping_essence;

        // Algalon the Observer
        creators["algalon should be tanked"] = &RaidUlduarTriggerContext::algalon_should_be_tanked;
        creators["algalon main tank has phase punch stacks"] =
            &RaidUlduarTriggerContext::algalon_main_tank_has_phase_punch_stacks;
        creators["algalon big bang incoming"] = &RaidUlduarTriggerContext::algalon_big_bang_incoming;
        creators["algalon bot near cosmic smash"] =
            &RaidUlduarTriggerContext::algalon_bot_near_cosmic_smash;
        creators["algalon collapsing star should be killed"] =
            &RaidUlduarTriggerContext::algalon_collapsing_star_should_be_killed;
        creators["algalon constellation chasing bot"] =
            &RaidUlduarTriggerContext::algalon_constellation_chasing_bot;
        creators["algalon dark matter spawned"] =
            &RaidUlduarTriggerContext::algalon_dark_matter_spawned;
    }

private:
    static Trigger* vezax_saronite_animus_spawned(PlayerbotAI* botAI)
    {
        return new UldAddsSpawnedTrigger(
            botAI, "vezax saronite animus spawned",
            UldHelpers::VEZAX_SARONITE_ANIMUS_VALUE, UldAddRole::Dps);
    }
    static Trigger* freya_strengthened_iron_roots_spawned(PlayerbotAI* botAI)
    {
        return new UldAddsSpawnedTrigger(
            botAI, "freya strengthened iron roots spawned",
            UldHelpers::FREYA_STRENGTHENED_IRON_ROOTS_VALUE, UldAddRole::Dps);
    }
    static Trigger* hodir_player_ice_spawned(PlayerbotAI* botAI)
    {
        return new UldAddsSpawnedTrigger(
            botAI, "hodir player ice spawned",
            UldHelpers::HODIR_PLAYER_ICE_VALUE, UldAddRole::Dps);
    }
    static Trigger* flame_leviathan_on_vehicle(PlayerbotAI* botAI) { return new FlameLeviathanOnVehicleTrigger(botAI); }
    static Trigger* flame_leviathan_vehicle_near(PlayerbotAI* botAI) { return new FlameLeviathanVehicleNearTrigger(botAI); }
    static Trigger* razorscale_flying_alone(PlayerbotAI* botAI) { return new RazorscaleFlyingAloneTrigger(botAI); }
    static Trigger* razorscale_avoid_devouring_flames(PlayerbotAI* botAI) { return new RazorscaleDevouringFlamesTrigger(botAI); }
    static Trigger* razorscale_avoid_sentinel(PlayerbotAI* botAI) { return new RazorscaleAvoidSentinelTrigger(botAI); }
    static Trigger* razorscale_avoid_whirlwind(PlayerbotAI* botAI) { return new RazorscaleAvoidWhirlwindTrigger(botAI); }
    static Trigger* razorscale_grounded(PlayerbotAI* botAI) { return new RazorscaleGroundedTrigger(botAI); }
    static Trigger* razorscale_harpoon_trigger(PlayerbotAI* botAI) { return new RazorscaleHarpoonAvailableTrigger(botAI); }
    static Trigger* razorscale_fuse_armor_trigger(PlayerbotAI* botAI) { return new RazorscaleFuseArmorTrigger(botAI); }
    static Trigger* razorscale_fire_resistance_trigger(PlayerbotAI* botAI) { return new BossFireResistanceTrigger(botAI, "razorscale"); }
    static Trigger* ignis_fire_resistance_trigger(PlayerbotAI* botAI) { return new BossFireResistanceTrigger(botAI, "ignis the furnace master"); }
    static Trigger* iron_assembly_lightning_tendrils_trigger(PlayerbotAI* botAI) { return new IronAssemblyLightningTendrilsTrigger(botAI); }
    static Trigger* iron_assembly_overload_trigger(PlayerbotAI* botAI) { return new IronAssemblyOverloadTrigger(botAI); }
    static Trigger* iron_assembly_rune_of_power_trigger(PlayerbotAI* botAI) { return new IronAssemblyRuneOfPowerTrigger(botAI); }
    static Trigger* kologarn_mark_dps_target_trigger(PlayerbotAI* botAI) { return new KologarnMarkDpsTargetTrigger(botAI); }
    static Trigger* kologarn_fall_from_floor_trigger(PlayerbotAI* botAI) { return new KologarnFallFromFloorTrigger(botAI); }
    static Trigger* kologarn_nature_resistance_trigger(PlayerbotAI* botAI) { return new BossNatureResistanceTrigger(botAI, "kologarn"); }
    static Trigger* kologarn_rubble_slowdown_trigger(PlayerbotAI* botAI) { return new KologarnRubbleSlowdownTrigger(botAI); }
    static Trigger* kologarn_eyebeam_trigger(PlayerbotAI* botAI) { return new KologarnEyebeamTrigger(botAI); }
    static Trigger* kologarn_rti_target_trigger(PlayerbotAI* botAI) { return new KologarnRtiTargetTrigger(botAI); }
    static Trigger* kologarn_crunch_armor_trigger(PlayerbotAI* botAI) { return new KologarnCrunchArmorTrigger(botAI); }
    static Trigger* kologarn_attack_dps_target_trigger(PlayerbotAI* botAI) { return new KologarnAttackDpsTargetTrigger(botAI); }
    static Trigger* auriaya_fall_from_floor_trigger(PlayerbotAI* botAI) { return new AuriayaFallFromFloorTrigger(botAI); }
    static Trigger* hodir_biting_cold(PlayerbotAI* botAI) { return new HodirBitingColdTrigger(botAI); }
    static Trigger* hodir_near_snowpacked_icicle(PlayerbotAI* botAI) { return new HodirNearSnowpackedIcicleTrigger(botAI); }
    static Trigger* hodir_frost_resistance_trigger(PlayerbotAI* botAI) { return new BossFrostResistanceTrigger(botAI, "hodir"); }
    static Trigger* freya_near_nature_bomb(PlayerbotAI* botAI) { return new FreyaNearNatureBombTrigger(botAI); }
    static Trigger* freya_fire_resistance_trigger(PlayerbotAI* botAI) { return new BossFireResistanceTrigger(botAI, "freya"); }
    static Trigger* freya_nature_resistance_trigger(PlayerbotAI* botAI) { return new BossNatureResistanceTrigger(botAI, "freya"); }
    static Trigger* freya_mark_dps_target_trigger(PlayerbotAI* botAI) { return new FreyaMarkDpsTargetTrigger(botAI); }
    static Trigger* freya_move_to_healing_spore_trigger(PlayerbotAI* botAI) { return new FreyaMoveToHealingSporeTrigger(botAI); }
    static Trigger* thorim_frost_resistance_trigger(PlayerbotAI* botAI) { return new BossFrostResistanceTrigger(botAI, "thorim"); }
    static Trigger* thorim_nature_resistance_trigger(PlayerbotAI* botAI) { return new BossNatureResistanceTrigger(botAI, "thorim"); }
    static Trigger* thorim_unbalancing_strike_trigger(PlayerbotAI* botAI) { return new ThorimUnbalancingStrikeTrigger(botAI); }
    static Trigger* thorim_mark_dps_target_trigger(PlayerbotAI* botAI) { return new ThorimMarkDpsTargetTrigger(botAI); }
    static Trigger* thorim_arena_positioning_trigger(PlayerbotAI* botAI) { return new ThorimArenaPositioningTrigger(botAI); }
    static Trigger* thorim_gauntlet_positioning_trigger(PlayerbotAI* botAI) { return new ThorimGauntletPositioningTrigger(botAI); }
    static Trigger* thorim_fall_from_floor_trigger(PlayerbotAI* botAI) { return new ThorimFallFromFloorTrigger(botAI); }
    static Trigger* thorim_phase2_positioning_trigger(PlayerbotAI* botAI) { return new ThorimPhase2PositioningTrigger(botAI); }
    static Trigger* mimiron_fire_resistance_trigger(PlayerbotAI* botAI) { return new BossFireResistanceTrigger(botAI, "mimiron"); }
    static Trigger* mimiron_shock_blast_trigger(PlayerbotAI* botAI) { return new MimironShockBlastTrigger(botAI); }
    static Trigger* mimiron_phase_1_positioning_trigger(PlayerbotAI* botAI) { return new MimironPhase1PositioningTrigger(botAI); }
    static Trigger* mimiron_p3wx2_laser_barrage_trigger(PlayerbotAI* botAI) { return new MimironP3Wx2LaserBarrageTrigger(botAI); }
    static Trigger* mimiron_rapid_burst_trigger(PlayerbotAI* botAI) { return new MimironRapidBurstTrigger(botAI); }
    static Trigger* mimiron_aerial_command_unit_trigger(PlayerbotAI* botAI) { return new MimironAerialCommandUnitTrigger(botAI); }
    static Trigger* mimiron_rocket_strike_trigger(PlayerbotAI* botAI) { return new MimironRocketStrikeTrigger(botAI); }
    static Trigger* mimiron_phase_4_mark_dps_trigger(PlayerbotAI* botAI) { return new MimironPhase4MarkDpsTrigger(botAI); }
    static Trigger* mimiron_cheat_trigger(PlayerbotAI* botAI) { return new MimironCheatTrigger(botAI); }
    static Trigger* vezax_cheat_trigger(PlayerbotAI* botAI) { return new VezaxCheatTrigger(botAI); }
    static Trigger* vezax_shadow_crash_trigger(PlayerbotAI* botAI) { return new VezaxShadowCrashTrigger(botAI); }
    static Trigger* vezax_shadow_resistance_trigger(PlayerbotAI* botAI) { return new BossShadowResistanceTrigger(botAI, "general vezax"); }
    static Trigger* sara_shadow_resistance_trigger(PlayerbotAI* botAI) { return new BossShadowResistanceTrigger(botAI, "sara"); }
    static Trigger* yogg_saron_shadow_resistance_trigger(PlayerbotAI* botAI) { return new BossShadowResistanceTrigger(botAI, "yogg-saron"); }
    static Trigger* vezax_mark_of_the_faceless_trigger(PlayerbotAI* botAI) { return new VezaxMarkOfTheFacelessTrigger(botAI); }
    static Trigger* yogg_saron_ominous_cloud_cheat_trigger(PlayerbotAI* botAI) { return new YoggSaronOminousCloudCheatTrigger(botAI); }
    static Trigger* yogg_saron_guardian_positioning_trigger(PlayerbotAI* botAI) { return new YoggSaronGuardianPositioningTrigger(botAI); }
    static Trigger* yogg_saron_sanity_trigger(PlayerbotAI* botAI) { return new YoggSaronSanityTrigger(botAI); }
    static Trigger* yogg_saron_death_orb_trigger(PlayerbotAI* botAI) { return new YoggSaronDeathOrbTrigger(botAI); }
    static Trigger* yogg_saron_malady_of_the_mind_trigger(PlayerbotAI* botAI) { return new YoggSaronMaladyOfTheMindTrigger(botAI); }
    static Trigger* yogg_saron_mark_target_trigger(PlayerbotAI* botAI) { return new YoggSaronMarkTargetTrigger(botAI); }
    static Trigger* yogg_saron_brain_link_trigger(PlayerbotAI* botAI) { return new YoggSaronBrainLinkTrigger(botAI); }
    static Trigger* yogg_saron_move_to_enter_portal_trigger(PlayerbotAI* botAI) { return new YoggSaronMoveToEnterPortalTrigger(botAI); }
    static Trigger* yogg_saron_use_portal_trigger(PlayerbotAI* botAI) { return new YoggSaronUsePortalTrigger(botAI); }
    static Trigger* yogg_saron_fall_from_floor_trigger(PlayerbotAI* botAI) { return new YoggSaronFallFromFloorTrigger(botAI); }
    static Trigger* yogg_saron_boss_room_movement_cheat_trigger(PlayerbotAI* botAI) { return new YoggSaronBossRoomMovementCheatTrigger(botAI); }
    static Trigger* yogg_saron_illusion_room_trigger(PlayerbotAI* botAI) { return new YoggSaronIllusionRoomTrigger(botAI); }
    static Trigger* yogg_saron_move_to_exit_portal_trigger(PlayerbotAI* botAI) { return new YoggSaronMoveToExitPortalTrigger(botAI); }
    static Trigger* yogg_saron_lunatic_gaze_trigger(PlayerbotAI* botAI) { return new YoggSaronLunaticGazeTrigger(botAI); }
    static Trigger* yogg_saron_phase_3_positioning_trigger(PlayerbotAI* botAI) { return new YoggSaronPhase3PositioningTrigger(botAI); }

    // XT-002 Deconstructor
    static Trigger* xt002_should_be_tanked(PlayerbotAI* botAI)
    {
        return new UldBossShouldBeTankedTrigger(botAI, "xt-002 should be tanked", Xt002Entries());
    }
    static Trigger* xt002_heart_exposed(PlayerbotAI* botAI)
    {
        return new Xt002HeartExposedTrigger(botAI);
    }
    static Trigger* xt002_bot_has_gravity_bomb(PlayerbotAI* botAI)
    {
        return new Xt002BotHasGravityBombTrigger(botAI);
    }
    static Trigger* xt002_bot_in_void_zone(PlayerbotAI* botAI)
    {
        return new UldBotNearHazardTrigger(
            botAI, "xt-002 bot in void zone", UldHelpers::XT002_VOID_ZONES_VALUE,
            UldHelpers::VOID_ZONE_RADIUS);
    }
    // The spark hits whoever Searing Light was on (BXT:748-755) and shocks anyone casting next to
    // it (BXT:671), so the melee take it off rather than the casters.
    static Trigger* xt002_life_spark_spawned(PlayerbotAI* botAI)
    {
        return new UldAddsSpawnedTrigger(
            botAI, "xt-002 life spark spawned", UldHelpers::XT002_LIFE_SPARKS_VALUE,
            UldAddRole::MeleeAndTanks);
    }
    // A Scrapbot that reaches XT-002 repairs him (BXT:508-513), so it is shot on the way in.
    static Trigger* xt002_scrapbot_spawned(PlayerbotAI* botAI)
    {
        return new UldAddsSpawnedTrigger(
            botAI, "xt-002 scrapbot spawned", UldHelpers::XT002_SCRAPBOTS_VALUE,
            UldAddRole::RangedDps);
    }
    static Trigger* xt002_pummeller_spawned(PlayerbotAI* botAI)
    {
        return new UldAddsSpawnedTrigger(
            botAI, "xt-002 pummeller spawned", UldHelpers::XT002_PUMMELLERS_VALUE,
            UldAddRole::Tanks);
    }
    static Trigger* xt002_boombot_spawned(PlayerbotAI* botAI)
    {
        return new UldAddsSpawnedTrigger(
            botAI, "xt-002 boombot spawned", UldHelpers::XT002_BOOMBOTS_VALUE,
            UldAddRole::RangedDps);
    }
    static Trigger* xt002_bot_near_boombot(PlayerbotAI* botAI)
    {
        return new Xt002BotNearBoombotTrigger(botAI);
    }
    static Trigger* xt002_ranged_should_spread(PlayerbotAI* botAI)
    {
        return new UldRangedShouldSpreadTrigger(
            botAI, "xt-002 ranged should spread", Xt002Entries());
    }

    // Ignis the Furnace Master
    static Trigger* ignis_should_be_tanked(PlayerbotAI* botAI)
    {
        return new UldBossShouldBeTankedTrigger(botAI, "ignis should be tanked", IgnisEntries());
    }
    static Trigger* ignis_construct_should_be_tanked(PlayerbotAI* botAI)
    {
        return new IgnisConstructShouldBeTankedTrigger(botAI);
    }
    static Trigger* ignis_molten_construct_should_be_doused(PlayerbotAI* botAI)
    {
        return new IgnisMoltenConstructShouldBeDousedTrigger(botAI);
    }
    static Trigger* ignis_brittle_construct_should_be_killed(PlayerbotAI* botAI)
    {
        return new IgnisBrittleConstructShouldBeKilledTrigger(botAI);
    }
    static Trigger* ignis_bot_in_scorched_ground(PlayerbotAI* botAI)
    {
        return new UldBotNearHazardTrigger(
            botAI, "ignis bot in scorched ground", UldHelpers::IGNIS_SCORCHED_GROUND_VALUE,
            UldHelpers::SCORCHED_GROUND_RADIUS);
    }

    // Auriaya
    static Trigger* auriaya_should_be_tanked(PlayerbotAI* botAI)
    {
        return new UldBossShouldBeTankedTrigger(botAI, "auriaya should be tanked", AuriayaEntries());
    }
    static Trigger* auriaya_sentries_spawned(PlayerbotAI* botAI)
    {
        return new UldAddsSpawnedTrigger(
            botAI, "auriaya sentries spawned", UldHelpers::AURIAYA_SENTRIES_VALUE,
            UldAddRole::Tanks);
    }
    static Trigger* auriaya_sentry_should_be_killed(PlayerbotAI* botAI)
    {
        return new AuriayaSentryShouldBeKilledTrigger(botAI);
    }
    // The Defender picks a new player out of thin air every few seconds (BAU:323, :428), so there
    // is no holding it: the melee kill it and the ranged stay on Auriaya.
    static Trigger* auriaya_feral_defender_spawned(PlayerbotAI* botAI)
    {
        return new UldAddsSpawnedTrigger(
            botAI, "auriaya feral defender spawned", UldHelpers::AURIAYA_FERAL_DEFENDERS_VALUE,
            UldAddRole::MeleeAndTanks);
    }
    static Trigger* auriaya_bot_in_seeping_essence(PlayerbotAI* botAI)
    {
        return new UldBotNearHazardTrigger(
            botAI, "auriaya bot in seeping essence", UldHelpers::AURIAYA_SEEPING_ESSENCES_VALUE,
            UldHelpers::SEEPING_ESSENCE_RADIUS);
    }

    // Algalon the Observer
    static Trigger* algalon_should_be_tanked(PlayerbotAI* botAI)
    {
        return new UldBossShouldBeTankedTrigger(botAI, "algalon should be tanked", AlgalonEntries());
    }
    static Trigger* algalon_main_tank_has_phase_punch_stacks(PlayerbotAI* botAI)
    {
        return new AlgalonMainTankPhasePunchStacksTrigger(botAI);
    }
    static Trigger* algalon_big_bang_incoming(PlayerbotAI* botAI)
    {
        return new AlgalonBigBangIncomingTrigger(botAI);
    }
    static Trigger* algalon_bot_near_cosmic_smash(PlayerbotAI* botAI)
    {
        return new UldBotNearHazardTrigger(
            botAI, "algalon bot near cosmic smash", UldHelpers::ALGALON_COSMIC_SMASH_VALUE,
            UldHelpers::COSMIC_SMASH_RADIUS);
    }
    // A Collapsing Star turns into the Black Hole the raid needs when it dies (BAL:1004-1010), and
    // it wanders the room out of melee reach (BAL:995).
    static Trigger* algalon_collapsing_star_should_be_killed(PlayerbotAI* botAI)
    {
        return new UldAddsSpawnedTrigger(
            botAI, "algalon collapsing star should be killed",
            UldHelpers::ALGALON_COLLAPSING_STARS_VALUE, UldAddRole::RangedDps);
    }
    static Trigger* algalon_constellation_chasing_bot(PlayerbotAI* botAI)
    {
        return new AlgalonConstellationChasingBotTrigger(botAI);
    }
    // Phase two leaves nothing but Algalon and these, and they chase a random player (BAL:591).
    static Trigger* algalon_dark_matter_spawned(PlayerbotAI* botAI)
    {
        return new UldAddsSpawnedTrigger(
            botAI, "algalon dark matter spawned", UldHelpers::ALGALON_DARK_MATTER_VALUE,
            UldAddRole::Everyone);
    }

    // Both creature templates of each boss: the 25-man raid spawns difficulty_entry_1 instead.
    static std::vector<uint32> Xt002Entries()
    {
        return { UldHelpers::Id(UldHelpers::UldNpcs::NPC_XT002),
                 UldHelpers::Id(UldHelpers::UldNpcs::NPC_XT002_25) };
    }
    static std::vector<uint32> IgnisEntries()
    {
        return { UldHelpers::Id(UldHelpers::UldNpcs::NPC_IGNIS),
                 UldHelpers::Id(UldHelpers::UldNpcs::NPC_IGNIS_25) };
    }
    static std::vector<uint32> AuriayaEntries()
    {
        return { UldHelpers::Id(UldHelpers::UldNpcs::NPC_AURIAYA),
                 UldHelpers::Id(UldHelpers::UldNpcs::NPC_AURIAYA_25) };
    }
    static std::vector<uint32> AlgalonEntries()
    {
        return { UldHelpers::Id(UldHelpers::UldNpcs::NPC_ALGALON),
                 UldHelpers::Id(UldHelpers::UldNpcs::NPC_ALGALON_25) };
    }
};

#endif
