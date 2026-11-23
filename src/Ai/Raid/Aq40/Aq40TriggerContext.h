/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#ifndef PLAYERBOTS_AQ40TRIGGERCONTEXT_H
#define PLAYERBOTS_AQ40TRIGGERCONTEXT_H

#include "Aq40Helpers.h"
#include "Aq40Triggers.h"
#include "NamedObjectContext.h"

class RaidAq40TriggerContext : public NamedObjectContext<Trigger>
{
public:
    RaidAq40TriggerContext() : NamedObjectContext<Trigger>()
    {
        creators["aq40 no encounter in progress"] =
            &RaidAq40TriggerContext::aq40_no_encounter_in_progress;

        // The Prophet Skeram
        creators["the prophet skeram should be tanked"] =
            &RaidAq40TriggerContext::skeram_should_be_tanked;
        creators["the prophet skeram images spawned"] =
            &RaidAq40TriggerContext::skeram_images_spawned;
        creators["the prophet skeram should assign dps priority"] =
            &RaidAq40TriggerContext::skeram_should_assign_dps_priority;
        creators["the prophet skeram attacking mind controlled ally"] =
            &RaidAq40TriggerContext::skeram_attacking_mind_controlled_ally;
        creators["the prophet skeram ranged should spread"] =
            &RaidAq40TriggerContext::skeram_ranged_should_spread;

        // Silithid Royalty
        creators["bug trio targets should be tanked"] =
            &RaidAq40TriggerContext::bug_trio_targets_should_be_tanked;
        creators["bug trio should assign dps priority"] =
            &RaidAq40TriggerContext::bug_trio_should_assign_dps_priority;
        creators["bug trio bot in poison cloud"] =
            &RaidAq40TriggerContext::bug_trio_bot_in_poison_cloud;
        creators["bug trio brood spawned"] = &RaidAq40TriggerContext::bug_trio_brood_spawned;

        // Battleguard Sartura
        creators["battleguard sartura should be tanked"] =
            &RaidAq40TriggerContext::sartura_should_be_tanked;
        creators["battleguard sartura royal guards should be tanked"] =
            &RaidAq40TriggerContext::sartura_royal_guards_should_be_tanked;
        creators["battleguard sartura melee in whirlwind range"] =
            &RaidAq40TriggerContext::sartura_melee_in_whirlwind_range;
        creators["battleguard sartura should assign dps priority"] =
            &RaidAq40TriggerContext::sartura_should_assign_dps_priority;

        // Fankriss the Unyielding
        creators["fankriss the unyielding should be tanked"] =
            &RaidAq40TriggerContext::fankriss_should_be_tanked;
        creators["fankriss the unyielding main tank has mortal wound stacks"] =
            &RaidAq40TriggerContext::fankriss_main_tank_has_mortal_wound_stacks;
        creators["fankriss the unyielding worms spawned"] =
            &RaidAq40TriggerContext::fankriss_worms_spawned;

        // Viscidus
        creators["viscidus in frost phase"] = &RaidAq40TriggerContext::viscidus_in_frost_phase;
        creators["viscidus globs spawned"] = &RaidAq40TriggerContext::viscidus_globs_spawned;
        creators["viscidus ranged should spread"] =
            &RaidAq40TriggerContext::viscidus_ranged_should_spread;

        // Princess Huhuran
        creators["princess huhuran should be tanked"] =
            &RaidAq40TriggerContext::huhuran_should_be_tanked;
        creators["princess huhuran bot in noxious poison"] =
            &RaidAq40TriggerContext::huhuran_bot_in_noxious_poison;
        creators["princess huhuran ranged should spread"] =
            &RaidAq40TriggerContext::huhuran_ranged_should_spread;

        // Twin Emperors
        creators["twin emperors should be tanked apart"] =
            &RaidAq40TriggerContext::twin_emperors_should_be_tanked_apart;
        creators["twin emperors melee should attack vek'nilash"] =
            &RaidAq40TriggerContext::twin_emperors_melee_should_attack_veknilash;
        creators["twin emperors casters should attack vek'lor"] =
            &RaidAq40TriggerContext::twin_emperors_casters_should_attack_veklor;
        creators["twin emperors bot in blizzard"] =
            &RaidAq40TriggerContext::twin_emperors_bot_in_blizzard;

        // Ouro
        creators["ouro should be tanked"] = &RaidAq40TriggerContext::ouro_should_be_tanked;
        creators["ouro melee in front of boss"] =
            &RaidAq40TriggerContext::ouro_melee_in_front_of_boss;
        creators["ouro ranged should spread"] = &RaidAq40TriggerContext::ouro_ranged_should_spread;
        creators["ouro submerged"] = &RaidAq40TriggerContext::ouro_submerged;
        creators["ouro scarabs spawned"] = &RaidAq40TriggerContext::ouro_scarabs_spawned;

        // C'Thun
        creators["eye of c'thun dark glare incoming"] =
            &RaidAq40TriggerContext::cthun_dark_glare_incoming;
        creators["eye of c'thun claw tentacle spawned"] =
            &RaidAq40TriggerContext::cthun_claw_tentacle_spawned;
        creators["eye of c'thun ranged should spread"] =
            &RaidAq40TriggerContext::cthun_eye_ranged_should_spread;
        creators["c'thun eye tentacles spawned"] =
            &RaidAq40TriggerContext::cthun_eye_tentacles_spawned;
        creators["c'thun giant claw tentacle spawned"] =
            &RaidAq40TriggerContext::cthun_giant_claw_tentacle_spawned;
        creators["c'thun giant eye tentacle spawned"] =
            &RaidAq40TriggerContext::cthun_giant_eye_tentacle_spawned;
        creators["c'thun body is weakened"] = &RaidAq40TriggerContext::cthun_body_is_weakened;
        creators["c'thun bot in stomach with flesh tentacle"] =
            &RaidAq40TriggerContext::cthun_bot_in_stomach_with_flesh_tentacle;
        creators["c'thun bot should leave stomach"] =
            &RaidAq40TriggerContext::cthun_bot_should_leave_stomach;
        creators["c'thun ranged should spread"] =
            &RaidAq40TriggerContext::cthun_ranged_should_spread;
    }

private:
    static Trigger* aq40_no_encounter_in_progress(PlayerbotAI* botAI)
    {
        return new Aq40NoEncounterInProgressTrigger(botAI);
    }

    static Trigger* skeram_should_be_tanked(PlayerbotAI* botAI)
    {
        return new SkeramShouldBeTankedTrigger(botAI);
    }
    static Trigger* skeram_images_spawned(PlayerbotAI* botAI)
    {
        return new SkeramImagesSpawnedTrigger(botAI);
    }
    static Trigger* skeram_should_assign_dps_priority(PlayerbotAI* botAI)
    {
        return new SkeramShouldAssignDpsPriorityTrigger(botAI);
    }
    static Trigger* skeram_attacking_mind_controlled_ally(PlayerbotAI* botAI)
    {
        return new SkeramAttackingMindControlledAllyTrigger(botAI);
    }
    static Trigger* skeram_ranged_should_spread(PlayerbotAI* botAI)
    {
        return new Aq40RangedShouldSpreadTrigger(
            botAI, "the prophet skeram ranged should spread", Aq40Helpers::SKERAM_NAME,
            Aq40Helpers::SKERAM_RANGED_DISTANCE);
    }

    static Trigger* bug_trio_targets_should_be_tanked(PlayerbotAI* botAI)
    {
        return new BugTrioTargetsShouldBeTankedTrigger(botAI);
    }
    static Trigger* bug_trio_should_assign_dps_priority(PlayerbotAI* botAI)
    {
        return new BugTrioShouldAssignDpsPriorityTrigger(botAI);
    }
    static Trigger* bug_trio_bot_in_poison_cloud(PlayerbotAI* botAI)
    {
        // Kri dies first, so the cloud is on the floor while Yauj and Vem are still up.
        return new Aq40BotInHazardTrigger(
            botAI, "bug trio bot in poison cloud", Aq40Helpers::POISON_CLOUD_VALUE,
            Aq40Helpers::POISON_CLOUD_RADIUS,
            { Aq40Helpers::VEM_NAME, Aq40Helpers::PRINCESS_YAUJ_NAME,
              Aq40Helpers::LORD_KRI_NAME });
    }
    static Trigger* bug_trio_brood_spawned(PlayerbotAI* botAI)
    {
        return new Aq40AddsSpawnedTrigger(
            botAI, "bug trio brood spawned", Aq40Helpers::YAUJ_BROOD_VALUE,
            Aq40AddRole::MeleeAndTanks);
    }

    static Trigger* sartura_should_be_tanked(PlayerbotAI* botAI)
    {
        return new Aq40BossShouldBeTankedTrigger(
            botAI, "battleguard sartura should be tanked", Aq40Helpers::SARTURA_NAME);
    }
    static Trigger* sartura_royal_guards_should_be_tanked(PlayerbotAI* botAI)
    {
        return new SarturaRoyalGuardsShouldBeTankedTrigger(botAI);
    }
    static Trigger* sartura_melee_in_whirlwind_range(PlayerbotAI* botAI)
    {
        return new SarturaMeleeInWhirlwindRangeTrigger(botAI);
    }
    static Trigger* sartura_should_assign_dps_priority(PlayerbotAI* botAI)
    {
        return new SarturaShouldAssignDpsPriorityTrigger(botAI);
    }

    static Trigger* fankriss_should_be_tanked(PlayerbotAI* botAI)
    {
        return new Aq40BossShouldBeTankedTrigger(
            botAI, "fankriss the unyielding should be tanked", Aq40Helpers::FANKRISS_NAME);
    }
    static Trigger* fankriss_main_tank_has_mortal_wound_stacks(PlayerbotAI* botAI)
    {
        return new FankrissMainTankMortalWoundStacksTrigger(botAI);
    }
    static Trigger* fankriss_worms_spawned(PlayerbotAI* botAI)
    {
        return new Aq40AddsSpawnedTrigger(
            botAI, "fankriss the unyielding worms spawned", Aq40Helpers::FANKRISS_WORMS_VALUE,
            Aq40AddRole::AssistTanks);
    }

    static Trigger* viscidus_in_frost_phase(PlayerbotAI* botAI)
    {
        return new ViscidusInFrostPhaseTrigger(botAI);
    }
    static Trigger* viscidus_globs_spawned(PlayerbotAI* botAI)
    {
        return new Aq40AddsSpawnedTrigger(
            botAI, "viscidus globs spawned", Aq40Helpers::VISCIDUS_GLOBS_VALUE,
            Aq40AddRole::Everyone);
    }
    static Trigger* viscidus_ranged_should_spread(PlayerbotAI* botAI)
    {
        return new Aq40RangedShouldSpreadTrigger(
            botAI, "viscidus ranged should spread", Aq40Helpers::VISCIDUS_NAME,
            Aq40Helpers::VISCIDUS_RANGED_DISTANCE);
    }

    static Trigger* huhuran_should_be_tanked(PlayerbotAI* botAI)
    {
        return new Aq40BossShouldBeTankedTrigger(
            botAI, "princess huhuran should be tanked", Aq40Helpers::HUHURAN_NAME);
    }
    static Trigger* huhuran_bot_in_noxious_poison(PlayerbotAI* botAI)
    {
        return new Aq40BotInHazardTrigger(
            botAI, "princess huhuran bot in noxious poison", Aq40Helpers::NOXIOUS_POISON_VALUE,
            Aq40Helpers::NOXIOUS_POISON_RADIUS, { Aq40Helpers::HUHURAN_NAME });
    }
    static Trigger* huhuran_ranged_should_spread(PlayerbotAI* botAI)
    {
        // Poison Bolt Volley hits the raid wherever it stands, so this is only about spacing.
        constexpr float noDistanceFromBoss = 0.0f;
        return new Aq40RangedShouldSpreadTrigger(
            botAI, "princess huhuran ranged should spread", Aq40Helpers::HUHURAN_NAME,
            noDistanceFromBoss);
    }

    static Trigger* twin_emperors_should_be_tanked_apart(PlayerbotAI* botAI)
    {
        return new TwinEmperorsShouldBeTankedApartTrigger(botAI);
    }
    static Trigger* twin_emperors_melee_should_attack_veknilash(PlayerbotAI* botAI)
    {
        return new TwinEmperorsMeleeShouldAttackVeknilashTrigger(botAI);
    }
    static Trigger* twin_emperors_casters_should_attack_veklor(PlayerbotAI* botAI)
    {
        return new TwinEmperorsCastersShouldAttackVeklorTrigger(botAI);
    }
    static Trigger* twin_emperors_bot_in_blizzard(PlayerbotAI* botAI)
    {
        return new Aq40BotInHazardTrigger(
            botAI, "twin emperors bot in blizzard", Aq40Helpers::BLIZZARD_VALUE,
            Aq40Helpers::BLIZZARD_RADIUS,
            { Aq40Helpers::VEKLOR_NAME, Aq40Helpers::VEKNILASH_NAME });
    }

    static Trigger* ouro_should_be_tanked(PlayerbotAI* botAI)
    {
        return new Aq40BossShouldBeTankedTrigger(
            botAI, "ouro should be tanked", Aq40Helpers::OURO_NAME);
    }
    static Trigger* ouro_melee_in_front_of_boss(PlayerbotAI* botAI)
    {
        return new OuroMeleeInFrontOfBossTrigger(botAI);
    }
    static Trigger* ouro_ranged_should_spread(PlayerbotAI* botAI)
    {
        return new Aq40RangedShouldSpreadTrigger(
            botAI, "ouro ranged should spread", Aq40Helpers::OURO_NAME,
            Aq40Helpers::OURO_RANGED_DISTANCE);
    }
    static Trigger* ouro_submerged(PlayerbotAI* botAI) { return new OuroSubmergedTrigger(botAI); }
    static Trigger* ouro_scarabs_spawned(PlayerbotAI* botAI)
    {
        return new Aq40AddsSpawnedTrigger(
            botAI, "ouro scarabs spawned", Aq40Helpers::OURO_SCARABS_VALUE,
            Aq40AddRole::MeleeAndTanks);
    }

    static Trigger* cthun_dark_glare_incoming(PlayerbotAI* botAI)
    {
        return new CthunBotInDarkGlarePathTrigger(botAI);
    }
    static Trigger* cthun_claw_tentacle_spawned(PlayerbotAI* botAI)
    {
        return new Aq40AddsSpawnedTrigger(
            botAI, "eye of c'thun claw tentacle spawned",
            Aq40Helpers::CTHUN_CLAW_TENTACLES_VALUE, Aq40AddRole::MeleeAndTanks);
    }
    static Trigger* cthun_eye_ranged_should_spread(PlayerbotAI* botAI)
    {
        // Eye Tentacles spawn on top of the raid and Claw Tentacles rupture the ground under one
        // player, so this is only about spacing.
        constexpr float noDistanceFromBoss = 0.0f;
        return new Aq40RangedShouldSpreadTrigger(
            botAI, "eye of c'thun ranged should spread", Aq40Helpers::CTHUN_EYE_NAME,
            noDistanceFromBoss);
    }
    static Trigger* cthun_eye_tentacles_spawned(PlayerbotAI* botAI)
    {
        return new Aq40AddsSpawnedTrigger(
            botAI, "c'thun eye tentacles spawned", Aq40Helpers::CTHUN_EYE_TENTACLES_VALUE,
            Aq40AddRole::MeleeAndTanks);
    }
    static Trigger* cthun_giant_claw_tentacle_spawned(PlayerbotAI* botAI)
    {
        return new Aq40AddsSpawnedTrigger(
            botAI, "c'thun giant claw tentacle spawned",
            Aq40Helpers::CTHUN_GIANT_CLAW_TENTACLES_VALUE, Aq40AddRole::Tanks);
    }
    static Trigger* cthun_giant_eye_tentacle_spawned(PlayerbotAI* botAI)
    {
        return new Aq40AddsSpawnedTrigger(
            botAI, "c'thun giant eye tentacle spawned",
            Aq40Helpers::CTHUN_GIANT_EYE_TENTACLES_VALUE, Aq40AddRole::RangedDps);
    }
    static Trigger* cthun_body_is_weakened(PlayerbotAI* botAI)
    {
        return new CthunBodyWeakenedTrigger(botAI);
    }
    static Trigger* cthun_bot_in_stomach_with_flesh_tentacle(PlayerbotAI* botAI)
    {
        return new CthunFleshTentacleInStomachTrigger(botAI);
    }
    static Trigger* cthun_bot_should_leave_stomach(PlayerbotAI* botAI)
    {
        return new CthunShouldLeaveStomachTrigger(botAI);
    }
    static Trigger* cthun_ranged_should_spread(PlayerbotAI* botAI)
    {
        constexpr float noDistanceFromBoss = 0.0f;
        return new CthunRangedShouldSpreadTrigger(
            botAI, "c'thun ranged should spread", Aq40Helpers::CTHUN_NAME, noDistanceFromBoss);
    }
};

#endif
