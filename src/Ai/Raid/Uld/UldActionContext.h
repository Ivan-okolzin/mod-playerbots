/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#ifndef PLAYERBOTS_ULDACTIONCONTEXT_H
#define PLAYERBOTS_ULDACTIONCONTEXT_H

#include "Action.h"
#include "BossAuraActions.h"
#include "NamedObjectContext.h"
#include "UldActions.h"
#include "UldHelpers.h"
#include <vector>

class RaidUlduarActionContext : public NamedObjectContext<Action>
{
public:
    RaidUlduarActionContext()
    {
        creators["vezax attack saronite animus"] =
            &RaidUlduarActionContext::attack_vezax_saronite_animus;
        creators["freya attack strengthened iron roots"] =
            &RaidUlduarActionContext::attack_freya_strengthened_iron_roots;
        creators["hodir attack player ice"] =
            &RaidUlduarActionContext::attack_hodir_player_ice;
        creators["flame leviathan vehicle"] = &RaidUlduarActionContext::flame_leviathan_vehicle;
        creators["flame leviathan enter vehicle"] = &RaidUlduarActionContext::flame_leviathan_enter_vehicle;
        creators["razorscale avoid devouring flames"] = &RaidUlduarActionContext::razorscale_avoid_devouring_flames;
        creators["razorscale avoid sentinel"] = &RaidUlduarActionContext::razorscale_avoid_sentinel;
        creators["razorscale ignore flying alone"] = &RaidUlduarActionContext::razorscale_ignore_flying_alone;
        creators["razorscale avoid whirlwind"] = &RaidUlduarActionContext::razorscale_avoid_whirlwind;
        creators["razorscale grounded"] = &RaidUlduarActionContext::razorscale_grounded;
        creators["razorscale harpoon action"] = &RaidUlduarActionContext::razorscale_harpoon_action;
        creators["razorscale fuse armor action"] = &RaidUlduarActionContext::razorscale_fuse_armor_action;
        creators["razorscale fire resistance action"] = &RaidUlduarActionContext::razorscale_fire_resistance_action;
        creators["ignis fire resistance action"] = &RaidUlduarActionContext::ignis_fire_resistance_action;
        creators["iron assembly lightning tendrils action"] = &RaidUlduarActionContext::iron_assembly_lightning_tendrils_action;
        creators["iron assembly overload action"] = &RaidUlduarActionContext::iron_assembly_overload_action;
        creators["iron assembly rune of power action"] = &RaidUlduarActionContext::iron_assembly_rune_of_power_action;
        creators["kologarn mark dps target action"] = &RaidUlduarActionContext::kologarn_mark_dps_target_action;
        creators["kologarn fall from floor action"] = &RaidUlduarActionContext::kologarn_fall_from_floor_action;
        creators["kologarn nature resistance action"] = &RaidUlduarActionContext::kologarn_nature_resistance_action;
        creators["kologarn rubble slowdown action"] = &RaidUlduarActionContext::kologarn_rubble_slowdown_action;
        creators["kologarn eyebeam action"] = &RaidUlduarActionContext::kologarn_eyebeam_action;
        creators["kologarn rti target action"] = &RaidUlduarActionContext::kologarn_rti_target_action;
        creators["kologarn crunch armor action"] = &RaidUlduarActionContext::kologarn_crunch_armor_action;
        creators["auriaya fall from floor action"] = &RaidUlduarActionContext::auriaya_fall_from_floor_action;
        creators["hodir move snowpacked icicle"] = &RaidUlduarActionContext::hodir_move_snowpacked_icicle;
        creators["hodir biting cold jump"] = &RaidUlduarActionContext::hodir_biting_cold_jump;
        creators["hodir frost resistance action"] = &RaidUlduarActionContext::hodir_frost_resistance_action;
        creators["freya move away nature bomb"] = &RaidUlduarActionContext::freya_move_away_nature_bomb;
        creators["freya fire resistance action"] = &RaidUlduarActionContext::freya_fire_resistance_action;
        creators["freya nature resistance action"] = &RaidUlduarActionContext::freya_nature_resistance_action;
        creators["freya mark dps target action"] = &RaidUlduarActionContext::freya_mark_dps_target_action;
        creators["freya move to healing spore action"] = &RaidUlduarActionContext::freya_move_to_healing_spore_action;
        creators["thorim frost resistance action"] = &RaidUlduarActionContext::thorim_frost_resistance_action;
        creators["thorim nature resistance action"] = &RaidUlduarActionContext::thorim_nature_resistance_action;
        creators["thorim unbalancing strike action"] = &RaidUlduarActionContext::thorim_unbalancing_strike_action;
        creators["thorim mark dps target action"] = &RaidUlduarActionContext::thorim_mark_dps_target_action;
        creators["thorim arena positioning action"] = &RaidUlduarActionContext::thorim_arena_positioning_action;
        creators["thorim gauntlet positioning action"] = &RaidUlduarActionContext::thorim_gauntlet_positioning_action;
        creators["thorim phase 2 positioning action"] = &RaidUlduarActionContext::thorim_phase2_positioning_action;
        creators["mimiron fire resistance action"] = &RaidUlduarActionContext::mimiron_fire_resistance_action;
        creators["mimiron shock blast action"] = &RaidUlduarActionContext::mimiron_shock_blast_action;
        creators["mimiron phase 1 positioning action"] = &RaidUlduarActionContext::mimiron_phase_1_positioning_action;
        creators["mimiron p3wx2 laser barrage action"] = &RaidUlduarActionContext::mimiron_p3wx2_laser_barrage_action;
        creators["mimiron rapid burst action"] = &RaidUlduarActionContext::mimiron_rapid_burst_action;
        creators["mimiron aerial command unit action"] = &RaidUlduarActionContext::mimiron_aerial_command_unit_action;
        creators["mimiron rocket strike action"] = &RaidUlduarActionContext::mimiron_rocket_strike_action;
        creators["mimiron phase 4 mark dps action"] = &RaidUlduarActionContext::mimiron_phase_4_mark_dps_action;
        creators["mimiron cheat action"] = &RaidUlduarActionContext::mimiron_cheat_action;
        creators["vezax cheat action"] = &RaidUlduarActionContext::vezax_cheat_action;
        creators["vezax shadow crash action"] = &RaidUlduarActionContext::vezax_shadow_crash_action;
        creators["vezax mark of the faceless action"] = &RaidUlduarActionContext::vezax_mark_of_the_faceless_action;
        creators["vezax shadow resistance action"] = &RaidUlduarActionContext::vezax_shadow_resistance_action;
        creators["sara shadow resistance action"] = &RaidUlduarActionContext::sara_shadow_resistance_action;
        creators["yogg-saron shadow resistance action"] = &RaidUlduarActionContext::yogg_saron_shadow_resistance_action;
        creators["yogg-saron ominous cloud cheat action"] = &RaidUlduarActionContext::yogg_saron_ominous_cloud_cheat_action;
        creators["yogg-saron guardian positioning action"] = &RaidUlduarActionContext::yogg_saron_guardian_positioning_action;
        creators["yogg-saron sanity action"] = &RaidUlduarActionContext::yogg_saron_sanity_action;
        creators["yogg-saron death orb action"] = &RaidUlduarActionContext::yogg_saron_death_orb_action;
        creators["yogg-saron malady of the mind action"] = &RaidUlduarActionContext::yogg_saron_malady_of_the_mind_action;
        creators["yogg-saron mark target action"] = &RaidUlduarActionContext::yogg_saron_mark_target_action;
        creators["yogg-saron brain link action"] = &RaidUlduarActionContext::yogg_saron_brain_link_action;
        creators["yogg-saron move to enter portal action"] = &RaidUlduarActionContext::yogg_saron_move_to_enter_portal_action;
        creators["yogg-saron use portal action"] = &RaidUlduarActionContext::yogg_saron_use_portal_action;
        creators["yogg-saron fall from floor action"] = &RaidUlduarActionContext::yogg_saron_fall_from_floor_action;
        creators["yogg-saron boss room movement cheat action"] = &RaidUlduarActionContext::yogg_saron_boss_room_movement_cheat_action;
        creators["yogg-saron illusion room action"] = &RaidUlduarActionContext::yogg_saron_illusion_room_action;
        creators["yogg-saron move to exit portal action"] = &RaidUlduarActionContext::yogg_saron_move_to_exit_portal_action;
        creators["yogg-saron lunatic gaze action"] = &RaidUlduarActionContext::yogg_saron_lunatic_gaze_action;
        creators["yogg-saron phase 3 positioning action"] = &RaidUlduarActionContext::yogg_saron_phase_3_positioning_action;

        // XT-002 Deconstructor
        creators["xt-002 main tank attack boss"] =
            &RaidUlduarActionContext::xt002_main_tank_attack_boss;
        creators["xt-002 attack exposed heart"] =
            &RaidUlduarActionContext::xt002_attack_exposed_heart;
        creators["xt-002 move away from raid"] = &RaidUlduarActionContext::xt002_move_away_from_raid;
        creators["xt-002 move away from void zone"] =
            &RaidUlduarActionContext::xt002_move_away_from_void_zone;
        creators["xt-002 attack nearest life spark"] =
            &RaidUlduarActionContext::xt002_attack_nearest_life_spark;
        creators["xt-002 attack nearest scrapbot"] =
            &RaidUlduarActionContext::xt002_attack_nearest_scrapbot;
        creators["xt-002 tank attack nearest pummeller"] =
            &RaidUlduarActionContext::xt002_tank_attack_nearest_pummeller;
        creators["xt-002 attack nearest boombot"] =
            &RaidUlduarActionContext::xt002_attack_nearest_boombot;
        creators["xt-002 move away from boombot"] =
            &RaidUlduarActionContext::xt002_move_away_from_boombot;
        creators["xt-002 spread ranged"] = &RaidUlduarActionContext::xt002_spread_ranged;

        // Ignis the Furnace Master
        creators["ignis main tank attack boss"] =
            &RaidUlduarActionContext::ignis_main_tank_attack_boss;
        creators["ignis tank attack nearest construct"] =
            &RaidUlduarActionContext::ignis_tank_attack_nearest_construct;
        creators["ignis drag molten construct to water"] =
            &RaidUlduarActionContext::ignis_drag_molten_construct_to_water;
        creators["ignis attack brittle construct"] =
            &RaidUlduarActionContext::ignis_attack_brittle_construct;
        creators["ignis move away from scorched ground"] =
            &RaidUlduarActionContext::ignis_move_away_from_scorched_ground;

        // Auriaya
        creators["auriaya main tank attack boss"] =
            &RaidUlduarActionContext::auriaya_main_tank_attack_boss;
        creators["auriaya tank attack nearest sentry"] =
            &RaidUlduarActionContext::auriaya_tank_attack_nearest_sentry;
        creators["auriaya attack sanctum sentry"] =
            &RaidUlduarActionContext::auriaya_attack_sanctum_sentry;
        creators["auriaya attack nearest feral defender"] =
            &RaidUlduarActionContext::auriaya_attack_nearest_feral_defender;
        creators["auriaya move away from seeping essence"] =
            &RaidUlduarActionContext::auriaya_move_away_from_seeping_essence;

        // Algalon the Observer
        creators["algalon main tank attack boss"] =
            &RaidUlduarActionContext::algalon_main_tank_attack_boss;
        creators["algalon tank swap"] = &RaidUlduarActionContext::algalon_tank_swap;
        creators["algalon hide in black hole"] = &RaidUlduarActionContext::algalon_hide_in_black_hole;
        creators["algalon move away from cosmic smash"] =
            &RaidUlduarActionContext::algalon_move_away_from_cosmic_smash;
        creators["algalon attack nearest collapsing star"] =
            &RaidUlduarActionContext::algalon_attack_nearest_collapsing_star;
        creators["algalon lead constellation to black hole"] =
            &RaidUlduarActionContext::algalon_lead_constellation_to_black_hole;
        creators["algalon attack nearest dark matter"] =
            &RaidUlduarActionContext::algalon_attack_nearest_dark_matter;
    }

private:
    static Action* attack_vezax_saronite_animus(PlayerbotAI* botAI)
    {
        return new UldAttackNearestAddAction(
            botAI, "vezax attack saronite animus",
            UldHelpers::VEZAX_SARONITE_ANIMUS_VALUE);
    }
    static Action* attack_freya_strengthened_iron_roots(PlayerbotAI* botAI)
    {
        return new UldAttackNearestAddAction(
            botAI, "freya attack strengthened iron roots",
            UldHelpers::FREYA_STRENGTHENED_IRON_ROOTS_VALUE);
    }
    static Action* attack_hodir_player_ice(PlayerbotAI* botAI)
    {
        return new UldAttackNearestAddAction(
            botAI, "hodir attack player ice",
            UldHelpers::HODIR_PLAYER_ICE_VALUE);
    }
    static Action* flame_leviathan_vehicle(PlayerbotAI* botAI) { return new FlameLeviathanVehicleAction(botAI); }
    static Action* flame_leviathan_enter_vehicle(PlayerbotAI* botAI) { return new FlameLeviathanEnterVehicleAction(botAI); }
    static Action* razorscale_avoid_devouring_flames(PlayerbotAI* botAI) { return new RazorscaleAvoidDevouringFlameAction(botAI); }
    static Action* razorscale_avoid_sentinel(PlayerbotAI* botAI) { return new RazorscaleAvoidSentinelAction(botAI); }
    static Action* razorscale_ignore_flying_alone(PlayerbotAI* botAI) { return new RazorscaleIgnoreBossAction(botAI); }
    static Action* razorscale_avoid_whirlwind(PlayerbotAI* botAI) { return new RazorscaleAvoidWhirlwindAction(botAI); }
    static Action* razorscale_grounded(PlayerbotAI* botAI) { return new RazorscaleGroundedAction(botAI); }
    static Action* razorscale_harpoon_action(PlayerbotAI* botAI) { return new RazorscaleHarpoonAction(botAI); }
    static Action* razorscale_fuse_armor_action(PlayerbotAI* botAI) { return new RazorscaleFuseArmorAction(botAI); }
    static Action* razorscale_fire_resistance_action(PlayerbotAI* botAI) { return new BossFireResistanceAction(botAI, "razorscale"); }
    static Action* ignis_fire_resistance_action(PlayerbotAI* botAI) { return new BossFireResistanceAction(botAI, "ignis the furnace master"); }
    static Action* iron_assembly_lightning_tendrils_action(PlayerbotAI* botAI) { return new IronAssemblyLightningTendrilsAction(botAI); }
    static Action* iron_assembly_overload_action(PlayerbotAI* botAI) { return new IronAssemblyOverloadAction(botAI); }
    static Action* iron_assembly_rune_of_power_action(PlayerbotAI* botAI) { return new IronAssemblyRuneOfPowerAction(botAI); }
    static Action* kologarn_mark_dps_target_action(PlayerbotAI* botAI) { return new KologarnMarkDpsTargetAction(botAI); }
    static Action* kologarn_fall_from_floor_action(PlayerbotAI* botAI) { return new KologarnFallFromFloorAction(botAI); }
    static Action* kologarn_nature_resistance_action(PlayerbotAI* botAI) { return new BossNatureResistanceAction(botAI, "kologarn"); }
    static Action* kologarn_rubble_slowdown_action(PlayerbotAI* botAI) { return new KologarnRubbleSlowdownAction(botAI); }
    static Action* kologarn_eyebeam_action(PlayerbotAI* botAI) { return new KologarnEyebeamAction(botAI); }
    static Action* kologarn_rti_target_action(PlayerbotAI* botAI) { return new KologarnRtiTargetAction(botAI); }
    static Action* kologarn_crunch_armor_action(PlayerbotAI* botAI) { return new KologarnCrunchArmorAction(botAI); }
    static Action* auriaya_fall_from_floor_action(PlayerbotAI* botAI) { return new AuriayaFallFromFloorAction(botAI); }
    static Action* hodir_move_snowpacked_icicle(PlayerbotAI* botAI) { return new HodirMoveSnowpackedIcicleAction(botAI); }
    static Action* hodir_biting_cold_jump(PlayerbotAI* botAI) { return new HodirBitingColdJumpAction(botAI); }
    static Action* hodir_frost_resistance_action(PlayerbotAI* botAI) { return new BossFrostResistanceAction(botAI, "hodir"); }
    static Action* freya_move_away_nature_bomb(PlayerbotAI* botAI) { return new FreyaMoveAwayNatureBombAction(botAI); }
    static Action* freya_fire_resistance_action(PlayerbotAI* botAI) { return new BossFireResistanceAction(botAI, "freya"); }
    static Action* freya_nature_resistance_action(PlayerbotAI* botAI) { return new BossNatureResistanceAction(botAI, "freya"); }
    static Action* freya_mark_dps_target_action(PlayerbotAI* botAI) { return new FreyaMarkDpsTargetAction(botAI); }
    static Action* freya_move_to_healing_spore_action(PlayerbotAI* botAI) { return new FreyaMoveToHealingSporeAction(botAI); }
    static Action* thorim_frost_resistance_action(PlayerbotAI* botAI) { return new BossFrostResistanceAction(botAI, "thorim"); }
    static Action* thorim_nature_resistance_action(PlayerbotAI* botAI) { return new BossNatureResistanceAction(botAI, "thorim"); }
    static Action* thorim_unbalancing_strike_action(PlayerbotAI* botAI) { return new ThorimUnbalancingStrikeAction(botAI); }
    static Action* thorim_mark_dps_target_action(PlayerbotAI* botAI) { return new ThorimMarkDpsTargetAction(botAI); }
    static Action* thorim_arena_positioning_action(PlayerbotAI* botAI) { return new ThorimArenaPositioningAction(botAI); }
    static Action* thorim_gauntlet_positioning_action(PlayerbotAI* botAI) { return new ThorimGauntletPositioningAction(botAI); }
    static Action* thorim_phase2_positioning_action(PlayerbotAI* botAI) { return new ThorimPhase2PositioningAction(botAI); }
    static Action* mimiron_fire_resistance_action(PlayerbotAI* botAI) { return new BossFireResistanceAction(botAI, "mimiron"); }
    static Action* mimiron_shock_blast_action(PlayerbotAI* botAI) { return new MimironShockBlastAction(botAI); }
    static Action* mimiron_phase_1_positioning_action(PlayerbotAI* botAI) { return new MimironPhase1PositioningAction(botAI); }
    static Action* mimiron_p3wx2_laser_barrage_action(PlayerbotAI* botAI) { return new MimironP3Wx2LaserBarrageAction(botAI); }
    static Action* mimiron_rapid_burst_action(PlayerbotAI* botAI) { return new MimironRapidBurstAction(botAI); }
    static Action* mimiron_aerial_command_unit_action(PlayerbotAI* botAI) { return new MimironAerialCommandUnitAction(botAI); }
    static Action* mimiron_rocket_strike_action(PlayerbotAI* botAI) { return new MimironRocketStrikeAction(botAI); }
    static Action* mimiron_phase_4_mark_dps_action(PlayerbotAI* botAI) { return new MimironPhase4MarkDpsAction(botAI); }
    static Action* mimiron_cheat_action(PlayerbotAI* botAI) { return new MimironCheatAction(botAI); }
    static Action* vezax_cheat_action(PlayerbotAI* botAI) { return new VezaxCheatAction(botAI); }
    static Action* vezax_shadow_crash_action(PlayerbotAI* botAI) { return new VezaxShadowCrashAction(botAI); }
    static Action* vezax_mark_of_the_faceless_action(PlayerbotAI* botAI) { return new VezaxMarkOfTheFacelessAction(botAI); }
    static Action* vezax_shadow_resistance_action(PlayerbotAI* botAI) { return new BossShadowResistanceAction(botAI, "general vezax"); }
    static Action* sara_shadow_resistance_action(PlayerbotAI* botAI) { return new BossShadowResistanceAction(botAI, "sara"); }
    static Action* yogg_saron_shadow_resistance_action(PlayerbotAI* botAI) { return new BossShadowResistanceAction(botAI, "yogg-saron"); }
    static Action* yogg_saron_ominous_cloud_cheat_action(PlayerbotAI* botAI) { return new YoggSaronOminousCloudCheatAction(botAI); }
    static Action* yogg_saron_guardian_positioning_action(PlayerbotAI* botAI) { return new YoggSaronGuardianPositioningAction(botAI); }
    static Action* yogg_saron_sanity_action(PlayerbotAI* botAI) { return new YoggSaronSanityAction(botAI); }
    static Action* yogg_saron_death_orb_action(PlayerbotAI* botAI) { return new YoggSaronDeathOrbAction(botAI); }
    static Action* yogg_saron_malady_of_the_mind_action(PlayerbotAI* botAI) { return new YoggSaronMaladyOfTheMindAction(botAI); }
    static Action* yogg_saron_mark_target_action(PlayerbotAI* botAI) { return new YoggSaronMarkTargetAction(botAI); }
    static Action* yogg_saron_brain_link_action(PlayerbotAI* botAI) { return new YoggSaronBrainLinkAction(botAI); }
    static Action* yogg_saron_move_to_enter_portal_action(PlayerbotAI* botAI) { return new YoggSaronMoveToEnterPortalAction(botAI); }
    static Action* yogg_saron_use_portal_action(PlayerbotAI* botAI) { return new YoggSaronUsePortalAction(botAI); }
    static Action* yogg_saron_fall_from_floor_action(PlayerbotAI* botAI) { return new YoggSaronFallFromFloorAction(botAI); }
    static Action* yogg_saron_boss_room_movement_cheat_action(PlayerbotAI* botAI) { return new YoggSaronBossRoomMovementCheatAction(botAI); }
    static Action* yogg_saron_illusion_room_action(PlayerbotAI* botAI) { return new YoggSaronIllusionRoomAction(botAI); }
    static Action* yogg_saron_move_to_exit_portal_action(PlayerbotAI* botAI) { return new YoggSaronMoveToExitPortalAction(botAI); }
    static Action* yogg_saron_lunatic_gaze_action(PlayerbotAI* botAI) { return new YoggSaronLunaticGazeAction(botAI); }
    static Action* yogg_saron_phase_3_positioning_action(PlayerbotAI* botAI) { return new YoggSaronPhase3PositioningAction(botAI); }

    // XT-002 Deconstructor
    static Action* xt002_main_tank_attack_boss(PlayerbotAI* botAI)
    {
        return new UldAttackCreatureAction(botAI, "xt-002 main tank attack boss", Xt002Entries());
    }
    static Action* xt002_attack_exposed_heart(PlayerbotAI* botAI)
    {
        return new Xt002AttackExposedHeartAction(botAI);
    }
    static Action* xt002_move_away_from_raid(PlayerbotAI* botAI)
    {
        return new Xt002MoveAwayFromRaidAction(botAI);
    }
    static Action* xt002_move_away_from_void_zone(PlayerbotAI* botAI)
    {
        return new UldMoveAwayFromHazardAction(
            botAI, "xt-002 move away from void zone", UldHelpers::XT002_VOID_ZONES_VALUE,
            UldHelpers::VOID_ZONE_RADIUS);
    }
    static Action* xt002_attack_nearest_life_spark(PlayerbotAI* botAI)
    {
        return new UldAttackNearestAddAction(
            botAI, "xt-002 attack nearest life spark", UldHelpers::XT002_LIFE_SPARKS_VALUE);
    }
    static Action* xt002_attack_nearest_scrapbot(PlayerbotAI* botAI)
    {
        return new UldAttackNearestAddAction(
            botAI, "xt-002 attack nearest scrapbot", UldHelpers::XT002_SCRAPBOTS_VALUE);
    }
    static Action* xt002_tank_attack_nearest_pummeller(PlayerbotAI* botAI)
    {
        return new UldTankAttackNearestAddAction(
            botAI, "xt-002 tank attack nearest pummeller", UldHelpers::XT002_PUMMELLERS_VALUE);
    }
    static Action* xt002_attack_nearest_boombot(PlayerbotAI* botAI)
    {
        return new UldAttackNearestAddAction(
            botAI, "xt-002 attack nearest boombot", UldHelpers::XT002_BOOMBOTS_VALUE);
    }
    static Action* xt002_move_away_from_boombot(PlayerbotAI* botAI)
    {
        return new UldMoveAwayFromHazardAction(
            botAI, "xt-002 move away from boombot", UldHelpers::XT002_BOOMBOTS_VALUE,
            UldHelpers::BOOMBOT_BLAST_RADIUS);
    }
    static Action* xt002_spread_ranged(PlayerbotAI* botAI)
    {
        return new UldSpreadRangedAction(botAI, "xt-002 spread ranged", Xt002Entries());
    }

    // Ignis the Furnace Master
    static Action* ignis_main_tank_attack_boss(PlayerbotAI* botAI)
    {
        return new UldAttackCreatureAction(botAI, "ignis main tank attack boss", IgnisEntries());
    }
    static Action* ignis_tank_attack_nearest_construct(PlayerbotAI* botAI)
    {
        return new UldTankAttackNearestAddAction(
            botAI, "ignis tank attack nearest construct", UldHelpers::IGNIS_CONSTRUCTS_VALUE);
    }
    static Action* ignis_drag_molten_construct_to_water(PlayerbotAI* botAI)
    {
        return new IgnisDragMoltenConstructToWaterAction(botAI);
    }
    static Action* ignis_attack_brittle_construct(PlayerbotAI* botAI)
    {
        return new IgnisAttackBrittleConstructAction(botAI);
    }
    static Action* ignis_move_away_from_scorched_ground(PlayerbotAI* botAI)
    {
        return new UldMoveAwayFromHazardAction(
            botAI, "ignis move away from scorched ground", UldHelpers::IGNIS_SCORCHED_GROUND_VALUE,
            UldHelpers::SCORCHED_GROUND_RADIUS);
    }

    // Auriaya
    static Action* auriaya_main_tank_attack_boss(PlayerbotAI* botAI)
    {
        return new UldAttackCreatureAction(botAI, "auriaya main tank attack boss", AuriayaEntries());
    }
    static Action* auriaya_tank_attack_nearest_sentry(PlayerbotAI* botAI)
    {
        return new UldTankAttackNearestAddAction(
            botAI, "auriaya tank attack nearest sentry", UldHelpers::AURIAYA_SENTRIES_VALUE);
    }
    static Action* auriaya_attack_sanctum_sentry(PlayerbotAI* botAI)
    {
        return new AuriayaAttackSanctumSentryAction(botAI);
    }
    static Action* auriaya_attack_nearest_feral_defender(PlayerbotAI* botAI)
    {
        return new UldAttackNearestAddAction(
            botAI, "auriaya attack nearest feral defender",
            UldHelpers::AURIAYA_FERAL_DEFENDERS_VALUE);
    }
    static Action* auriaya_move_away_from_seeping_essence(PlayerbotAI* botAI)
    {
        return new UldMoveAwayFromHazardAction(
            botAI, "auriaya move away from seeping essence",
            UldHelpers::AURIAYA_SEEPING_ESSENCES_VALUE, UldHelpers::SEEPING_ESSENCE_RADIUS);
    }

    // Algalon the Observer
    static Action* algalon_main_tank_attack_boss(PlayerbotAI* botAI)
    {
        return new UldAttackCreatureAction(botAI, "algalon main tank attack boss", AlgalonEntries());
    }
    static Action* algalon_tank_swap(PlayerbotAI* botAI) { return new AlgalonTankSwapAction(botAI); }
    static Action* algalon_hide_in_black_hole(PlayerbotAI* botAI)
    {
        return new AlgalonHideInBlackHoleAction(botAI);
    }
    static Action* algalon_move_away_from_cosmic_smash(PlayerbotAI* botAI)
    {
        return new UldMoveAwayFromHazardAction(
            botAI, "algalon move away from cosmic smash", UldHelpers::ALGALON_COSMIC_SMASH_VALUE,
            UldHelpers::COSMIC_SMASH_RADIUS);
    }
    static Action* algalon_attack_nearest_collapsing_star(PlayerbotAI* botAI)
    {
        return new UldAttackNearestAddAction(
            botAI, "algalon attack nearest collapsing star",
            UldHelpers::ALGALON_COLLAPSING_STARS_VALUE);
    }
    static Action* algalon_lead_constellation_to_black_hole(PlayerbotAI* botAI)
    {
        return new AlgalonLeadConstellationToBlackHoleAction(botAI);
    }
    static Action* algalon_attack_nearest_dark_matter(PlayerbotAI* botAI)
    {
        return new UldAttackNearestAddAction(
            botAI, "algalon attack nearest dark matter", UldHelpers::ALGALON_DARK_MATTER_VALUE);
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
