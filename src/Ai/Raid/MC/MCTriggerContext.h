/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#ifndef PLAYERBOTS_MCTRIGGERCONTEXT_H
#define PLAYERBOTS_MCTRIGGERCONTEXT_H

#include "BossAuraTriggers.h"
#include "MCHelpers.h"
#include "MCTriggers.h"
#include "NamedObjectContext.h"

class RaidMcTriggerContext : public NamedObjectContext<Trigger>
{
public:
    RaidMcTriggerContext()
    {
        creators["mc lucifron shadow resistance"] = &RaidMcTriggerContext::lucifron_shadow_resistance;
        creators["mc lucifron should be tanked"] = &RaidMcTriggerContext::lucifron_should_be_tanked;
        creators["mc lucifron protectors spawned"] = &RaidMcTriggerContext::lucifron_protectors_spawned;
        creators["mc magmadar tremor"] = &RaidMcTriggerContext::magmadar_tremor;
        creators["mc magmadar fire resistance"] = &RaidMcTriggerContext::magmadar_fire_resistance;
        creators["mc magmadar should be tanked"] = &RaidMcTriggerContext::magmadar_should_be_tanked;
        creators["mc magmadar bot in lava bomb"] = &RaidMcTriggerContext::magmadar_bot_in_lava_bomb;
        creators["mc gehennas shadow resistance"] = &RaidMcTriggerContext::gehennas_shadow_resistance;
        creators["mc gehennas should be tanked"] = &RaidMcTriggerContext::gehennas_should_be_tanked;
        creators["mc gehennas flamewakers spawned"] = &RaidMcTriggerContext::gehennas_flamewakers_spawned;
        creators["mc gehennas bot in rain of fire"] = &RaidMcTriggerContext::gehennas_bot_in_rain_of_fire;
        creators["mc garr fire resistance"] = &RaidMcTriggerContext::garr_fire_resistance;
        creators["mc garr should be tanked"] = &RaidMcTriggerContext::garr_should_be_tanked;
        creators["mc garr firesworn spawned"] = &RaidMcTriggerContext::garr_firesworn_spawned;
        creators["mc baron geddon fire resistance"] = &RaidMcTriggerContext::baron_geddon_fire_resistance;
        creators["mc living bomb debuff"] = &RaidMcTriggerContext::living_bomb_debuff;
        creators["mc baron geddon inferno"] = &RaidMcTriggerContext::baron_geddon_inferno;
        creators["mc shazzrah ranged"] = &RaidMcTriggerContext::shazzrah_ranged;
        creators["mc shazzrah should be tanked"] = &RaidMcTriggerContext::shazzrah_should_be_tanked;
        creators["mc shazzrah lost threat"] = &RaidMcTriggerContext::shazzrah_lost_threat;
        creators["mc sulfuron harbinger fire resistance"] = &RaidMcTriggerContext::sulfuron_harbinger_fire_resistance;
        creators["mc sulfuron harbinger should be tanked"] =
            &RaidMcTriggerContext::sulfuron_harbinger_should_be_tanked;
        creators["mc sulfuron harbinger priests spawned"] =
            &RaidMcTriggerContext::sulfuron_harbinger_priests_spawned;
        creators["mc golemagg fire resistance"] = &RaidMcTriggerContext::golemagg_fire_resistance;
        creators["mc golemagg mark boss"] = &RaidMcTriggerContext::golemagg_mark_boss;
        creators["mc golemagg is main tank"] = &RaidMcTriggerContext::golemagg_is_main_tank;
        creators["mc golemagg is assist tank"] = &RaidMcTriggerContext::golemagg_is_assist_tank;
        creators["mc golemagg magma splash"] = &RaidMcTriggerContext::golemagg_magma_splash;
        creators["mc golemagg is healer"] = &RaidMcTriggerContext::golemagg_is_healer;
        creators["mc majordomo shadow resistance"] = &RaidMcTriggerContext::majordomo_shadow_resistance;
        creators["mc majordomo damage shield"] = &RaidMcTriggerContext::majordomo_damage_shield;
        creators["mc majordomo should be tanked"] = &RaidMcTriggerContext::majordomo_should_be_tanked;
        creators["mc majordomo lost threat"] = &RaidMcTriggerContext::majordomo_lost_threat;
        creators["mc majordomo adds spawned"] = &RaidMcTriggerContext::majordomo_adds_spawned;
        creators["mc ragnaros fire resistance"] = &RaidMcTriggerContext::ragnaros_fire_resistance;
        creators["mc ragnaros should be tanked"] = &RaidMcTriggerContext::ragnaros_should_be_tanked;
        creators["mc ragnaros lost threat"] = &RaidMcTriggerContext::ragnaros_lost_threat;
        creators["mc ragnaros sons of flame spawned"] = &RaidMcTriggerContext::ragnaros_sons_of_flame_spawned;
        creators["mc ragnaros bot in lava burst"] = &RaidMcTriggerContext::ragnaros_bot_in_lava_burst;
        creators["mc core hound mark"] = &RaidMcTriggerContext::core_hound_mark;
        creators["mc in lava"] = &RaidMcTriggerContext::in_lava;
    }

private:
    // Lucifron
    static Trigger* lucifron_shadow_resistance(PlayerbotAI* botAI) { return new BossShadowResistanceTrigger(botAI, "lucifron"); }
    static Trigger* lucifron_should_be_tanked(PlayerbotAI* botAI)
    {
        return new McBossShouldBeTankedTrigger(
            botAI, "mc lucifron should be tanked", MoltenCoreHelpers::NPC_LUCIFRON);
    }
    static Trigger* lucifron_protectors_spawned(PlayerbotAI* botAI)
    {
        return new McAddsSpawnedTrigger(
            botAI, "mc lucifron protectors spawned", MoltenCoreHelpers::LUCIFRON_PROTECTORS_VALUE,
            McAddRole::AssistTanks);
    }

    // Magmadar
    static Trigger* magmadar_tremor(PlayerbotAI* botAI) { return new McMagmadarTremorTrigger(botAI); }
    static Trigger* magmadar_fire_resistance(PlayerbotAI* botAI) { return new BossFireResistanceTrigger(botAI, "magmadar"); }
    static Trigger* magmadar_should_be_tanked(PlayerbotAI* botAI)
    {
        return new McBossShouldBeTankedTrigger(
            botAI, "mc magmadar should be tanked", MoltenCoreHelpers::NPC_MAGMADAR);
    }
    static Trigger* magmadar_bot_in_lava_bomb(PlayerbotAI* botAI)
    {
        return new McBotInHazardTrigger(
            botAI, "mc magmadar bot in lava bomb", MoltenCoreHelpers::MAGMADAR_LAVA_BOMBS_VALUE,
            MoltenCoreHelpers::LAVA_BOMB_RADIUS);
    }

    // Gehennas
    static Trigger* gehennas_shadow_resistance(PlayerbotAI* botAI) { return new BossShadowResistanceTrigger(botAI, "gehennas"); }
    static Trigger* gehennas_should_be_tanked(PlayerbotAI* botAI)
    {
        return new McBossShouldBeTankedTrigger(
            botAI, "mc gehennas should be tanked", MoltenCoreHelpers::NPC_GEHENNAS);
    }
    static Trigger* gehennas_flamewakers_spawned(PlayerbotAI* botAI)
    {
        return new McAddsSpawnedTrigger(
            botAI, "mc gehennas flamewakers spawned", MoltenCoreHelpers::GEHENNAS_FLAMEWAKERS_VALUE,
            McAddRole::AssistTanks);
    }
    static Trigger* gehennas_bot_in_rain_of_fire(PlayerbotAI* botAI)
    {
        return new McBotInHazardTrigger(
            botAI, "mc gehennas bot in rain of fire", MoltenCoreHelpers::GEHENNAS_RAIN_OF_FIRE_VALUE,
            MoltenCoreHelpers::RAIN_OF_FIRE_RADIUS);
    }

    // Garr
    static Trigger* garr_fire_resistance(PlayerbotAI* botAI) { return new BossFireResistanceTrigger(botAI, "garr"); }
    static Trigger* garr_should_be_tanked(PlayerbotAI* botAI)
    {
        return new McBossShouldBeTankedTrigger(
            botAI, "mc garr should be tanked", MoltenCoreHelpers::NPC_GARR);
    }
    static Trigger* garr_firesworn_spawned(PlayerbotAI* botAI)
    {
        return new McAddsSpawnedTrigger(
            botAI, "mc garr firesworn spawned", MoltenCoreHelpers::GARR_FIRESWORN_VALUE,
            McAddRole::AssistTanks);
    }

    // Baron Geddon
    static Trigger* baron_geddon_fire_resistance(PlayerbotAI* botAI) { return new BossFireResistanceTrigger(botAI, "baron geddon"); }
    static Trigger* living_bomb_debuff(PlayerbotAI* botAI) { return new McLivingBombDebuffTrigger(botAI); }
    static Trigger* baron_geddon_inferno(PlayerbotAI* botAI)
    {
        return new McBossAuraHazardTrigger(
            botAI, "mc baron geddon inferno", MoltenCoreHelpers::NPC_BARON_GEDDON,
            MoltenCoreHelpers::BARON_GEDDON_VALUE, MoltenCoreHelpers::SPELL_INFERNO,
            MoltenCoreHelpers::INFERNO_DISTANCE);
    }

    // Shazzrah
    static Trigger* shazzrah_ranged(PlayerbotAI* botAI) { return new McShazzrahRangedTrigger(botAI); }
    static Trigger* shazzrah_should_be_tanked(PlayerbotAI* botAI)
    {
        return new McBossShouldBeTankedTrigger(
            botAI, "mc shazzrah should be tanked", MoltenCoreHelpers::NPC_SHAZZRAH,
            MoltenCoreHelpers::SHAZZRAH_VALUE);
    }
    static Trigger* shazzrah_lost_threat(PlayerbotAI* botAI)
    {
        return new McBossLostThreatTrigger(
            botAI, "mc shazzrah lost threat", MoltenCoreHelpers::NPC_SHAZZRAH,
            MoltenCoreHelpers::SHAZZRAH_VALUE);
    }

    // Sulfuron Harbinger
    // Alternatively, shadow resistance is also possible.
    static Trigger* sulfuron_harbinger_fire_resistance(PlayerbotAI* botAI) { return new BossFireResistanceTrigger(botAI, "sulfuron harbinger"); }
    static Trigger* sulfuron_harbinger_should_be_tanked(PlayerbotAI* botAI)
    {
        return new McBossShouldBeTankedTrigger(
            botAI, "mc sulfuron harbinger should be tanked",
            MoltenCoreHelpers::NPC_SULFURON_HARBINGER);
    }
    static Trigger* sulfuron_harbinger_priests_spawned(PlayerbotAI* botAI)
    {
        return new McAddsSpawnedTrigger(
            botAI, "mc sulfuron harbinger priests spawned", MoltenCoreHelpers::SULFURON_PRIESTS_VALUE,
            McAddRole::AssistTanks);
    }

    // Golemagg the Incinerator
    static Trigger* golemagg_fire_resistance(PlayerbotAI* botAI) { return new BossFireResistanceTrigger(botAI, "golemagg the incinerator"); }
    static Trigger* golemagg_mark_boss(PlayerbotAI* botAI) { return new McGolemaggMarkBossTrigger(botAI); }
    static Trigger* golemagg_is_main_tank(PlayerbotAI* botAI) { return new McGolemaggIsMainTankTrigger(botAI); }
    static Trigger* golemagg_is_assist_tank(PlayerbotAI* botAI) { return new McGolemaggIsAssistTankTrigger(botAI); }
    static Trigger* golemagg_magma_splash(PlayerbotAI* botAI) { return new McGolemaggMagmaSplashTrigger(botAI); }
    static Trigger* golemagg_is_healer(PlayerbotAI* botAI) { return new McGolemaggIsHealerTrigger(botAI); }

    // Majordomo Executus
    static Trigger* majordomo_shadow_resistance(PlayerbotAI* botAI) { return new BossShadowResistanceTrigger(botAI, "majordomo executus"); }
    static Trigger* majordomo_damage_shield(PlayerbotAI* botAI) { return new McMajordomoDamageShieldTrigger(botAI); }
    static Trigger* majordomo_should_be_tanked(PlayerbotAI* botAI)
    {
        return new McBossShouldBeTankedTrigger(
            botAI, "mc majordomo should be tanked", MoltenCoreHelpers::NPC_MAJORDOMO_EXECUTUS,
            MoltenCoreHelpers::MAJORDOMO_VALUE);
    }
    static Trigger* majordomo_lost_threat(PlayerbotAI* botAI)
    {
        return new McBossLostThreatTrigger(
            botAI, "mc majordomo lost threat", MoltenCoreHelpers::NPC_MAJORDOMO_EXECUTUS,
            MoltenCoreHelpers::MAJORDOMO_VALUE);
    }
    static Trigger* majordomo_adds_spawned(PlayerbotAI* botAI)
    {
        return new McAddsSpawnedTrigger(
            botAI, "mc majordomo adds spawned", MoltenCoreHelpers::MAJORDOMO_ADDS_VALUE,
            McAddRole::AssistTanks);
    }

    // Ragnaros
    static Trigger* ragnaros_fire_resistance(PlayerbotAI* botAI) { return new BossFireResistanceTrigger(botAI, "ragnaros"); }
    static Trigger* ragnaros_should_be_tanked(PlayerbotAI* botAI)
    {
        return new McBossShouldBeTankedTrigger(
            botAI, "mc ragnaros should be tanked", MoltenCoreHelpers::NPC_RAGNAROS,
            MoltenCoreHelpers::RAGNAROS_VALUE);
    }
    static Trigger* ragnaros_lost_threat(PlayerbotAI* botAI)
    {
        return new McBossLostThreatTrigger(
            botAI, "mc ragnaros lost threat", MoltenCoreHelpers::NPC_RAGNAROS,
            MoltenCoreHelpers::RAGNAROS_VALUE);
    }
    static Trigger* ragnaros_sons_of_flame_spawned(PlayerbotAI* botAI)
    {
        return new McAddsSpawnedTrigger(
            botAI, "mc ragnaros sons of flame spawned",
            MoltenCoreHelpers::RAGNAROS_SONS_OF_FLAME_VALUE, McAddRole::Everyone);
    }
    static Trigger* ragnaros_bot_in_lava_burst(PlayerbotAI* botAI)
    {
        return new McBotInHazardTrigger(
            botAI, "mc ragnaros bot in lava burst", MoltenCoreHelpers::RAGNAROS_LAVA_BURSTS_VALUE,
            MoltenCoreHelpers::LAVA_BURST_RADIUS);
    }

    // Trash and anywhere in the instance
    static Trigger* core_hound_mark(PlayerbotAI* botAI) { return new McCoreHoundMarkTrigger(botAI); }
    static Trigger* in_lava(PlayerbotAI* botAI) { return new McInLavaTrigger(botAI); }
};

#endif
