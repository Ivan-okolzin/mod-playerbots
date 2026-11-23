/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#ifndef PLAYERBOTS_ZGTRIGGERCONTEXT_H
#define PLAYERBOTS_ZGTRIGGERCONTEXT_H

#include "NamedObjectContext.h"
#include "ZGHelpers.h"
#include "ZGTriggers.h"

class RaidZulGurubTriggerContext : public NamedObjectContext<Trigger>
{
public:
    RaidZulGurubTriggerContext() : NamedObjectContext<Trigger>()
    {
        creators["zg no encounter in progress"] =
            &RaidZulGurubTriggerContext::zg_no_encounter_in_progress;
        creators["zg bot should pick up poisonous blood"] =
            &RaidZulGurubTriggerContext::zg_bot_should_pick_up_poisonous_blood;

        // High Priest Venoxis
        creators["high priest venoxis should be tanked"] =
            &RaidZulGurubTriggerContext::venoxis_should_be_tanked;
        creators["high priest venoxis lost threat"] =
            &RaidZulGurubTriggerContext::venoxis_lost_threat;
        creators["high priest venoxis serpents spawned"] =
            &RaidZulGurubTriggerContext::venoxis_serpents_spawned;
        creators["high priest venoxis bot in poison cloud"] =
            &RaidZulGurubTriggerContext::venoxis_bot_in_poison_cloud;

        // High Priestess Jeklik
        creators["high priestess jeklik should be tanked"] =
            &RaidZulGurubTriggerContext::jeklik_should_be_tanked;
        creators["high priestess jeklik lost threat"] =
            &RaidZulGurubTriggerContext::jeklik_lost_threat;
        creators["high priestess jeklik bats spawned"] =
            &RaidZulGurubTriggerContext::jeklik_bats_spawned;
        creators["high priestess jeklik bot in liquid fire"] =
            &RaidZulGurubTriggerContext::jeklik_bot_in_liquid_fire;

        // High Priestess Mar'li
        creators["high priestess mar'li should be tanked"] =
            &RaidZulGurubTriggerContext::marli_should_be_tanked;
        creators["high priestess mar'li lost threat"] =
            &RaidZulGurubTriggerContext::marli_lost_threat;
        creators["high priestess mar'li spawns hatched"] =
            &RaidZulGurubTriggerContext::marli_spawns_hatched;

        // Bloodlord Mandokir
        creators["bloodlord mandokir should be tanked"] =
            &RaidZulGurubTriggerContext::mandokir_should_be_tanked;
        creators["bloodlord mandokir lost threat"] =
            &RaidZulGurubTriggerContext::mandokir_lost_threat;
        creators["bloodlord mandokir bot is watched"] =
            &RaidZulGurubTriggerContext::mandokir_bot_is_watched;
        creators["bloodlord mandokir ohgan should be tanked"] =
            &RaidZulGurubTriggerContext::mandokir_ohgan_should_be_tanked;
        creators["bloodlord mandokir ohgan spawned"] =
            &RaidZulGurubTriggerContext::mandokir_ohgan_spawned;
        creators["bloodlord mandokir melee in whirlwind range"] =
            &RaidZulGurubTriggerContext::mandokir_melee_in_whirlwind_range;

        // High Priest Thekal
        creators["high priest thekal should be tanked"] =
            &RaidZulGurubTriggerContext::thekal_should_be_tanked;
        creators["high priest thekal zealots should be tanked"] =
            &RaidZulGurubTriggerContext::thekal_zealots_should_be_tanked;
        creators["high priest thekal should balance trio damage"] =
            &RaidZulGurubTriggerContext::thekal_should_balance_trio_damage;
        creators["high priest thekal lost threat"] =
            &RaidZulGurubTriggerContext::thekal_lost_threat;
        creators["high priest thekal tigers spawned"] =
            &RaidZulGurubTriggerContext::thekal_tigers_spawned;

        // High Priestess Arlokk
        creators["high priestess arlokk should be tanked"] =
            &RaidZulGurubTriggerContext::arlokk_should_be_tanked;
        creators["high priestess arlokk lost threat"] =
            &RaidZulGurubTriggerContext::arlokk_lost_threat;
        creators["high priestess arlokk prowlers spawned"] =
            &RaidZulGurubTriggerContext::arlokk_prowlers_spawned;

        // Jin'do the Hexxer
        creators["jin'do the hexxer should be tanked"] =
            &RaidZulGurubTriggerContext::jindo_should_be_tanked;
        creators["jin'do the hexxer healing ward spawned"] =
            &RaidZulGurubTriggerContext::jindo_healing_ward_spawned;
        creators["jin'do the hexxer brain wash totem spawned"] =
            &RaidZulGurubTriggerContext::jindo_brain_wash_totem_spawned;
        creators["jin'do the hexxer shades spawned"] =
            &RaidZulGurubTriggerContext::jindo_shades_spawned;
        creators["jin'do the hexxer hexed the tank"] =
            &RaidZulGurubTriggerContext::jindo_hexed_the_tank;

        // Hakkar
        creators["hakkar should be tanked"] = &RaidZulGurubTriggerContext::hakkar_should_be_tanked;
        creators["hakkar lost threat"] = &RaidZulGurubTriggerContext::hakkar_lost_threat;
        creators["hakkar attacking insane ally"] =
            &RaidZulGurubTriggerContext::hakkar_attacking_insane_ally;

        // Gahz'ranka
        creators["gahz'ranka should be tanked"] =
            &RaidZulGurubTriggerContext::gahzranka_should_be_tanked;
        creators["gahz'ranka lost threat"] = &RaidZulGurubTriggerContext::gahzranka_lost_threat;

        // Edge of Madness
        creators["gri'lek should be tanked"] = &RaidZulGurubTriggerContext::grilek_should_be_tanked;
        creators["gri'lek lost threat"] = &RaidZulGurubTriggerContext::grilek_lost_threat;
        creators["gri'lek bot is pursued"] = &RaidZulGurubTriggerContext::grilek_bot_is_pursued;
        creators["hazza'rah should be tanked"] =
            &RaidZulGurubTriggerContext::hazzarah_should_be_tanked;
        creators["hazza'rah illusions spawned"] =
            &RaidZulGurubTriggerContext::hazzarah_illusions_spawned;
        creators["hazza'rah ranged should spread"] =
            &RaidZulGurubTriggerContext::hazzarah_ranged_should_spread;
        creators["renataki should be tanked"] =
            &RaidZulGurubTriggerContext::renataki_should_be_tanked;
        creators["renataki lost threat"] = &RaidZulGurubTriggerContext::renataki_lost_threat;
        creators["wushoolay should be tanked"] =
            &RaidZulGurubTriggerContext::wushoolay_should_be_tanked;
        creators["wushoolay bot in lightning cloud"] =
            &RaidZulGurubTriggerContext::wushoolay_bot_in_lightning_cloud;
        creators["wushoolay ranged should spread"] =
            &RaidZulGurubTriggerContext::wushoolay_ranged_should_spread;
    }

private:
    static Trigger* zg_no_encounter_in_progress(PlayerbotAI* botAI)
    {
        return new ZulGurubNoEncounterInProgressTrigger(botAI);
    }
    static Trigger* zg_bot_should_pick_up_poisonous_blood(PlayerbotAI* botAI)
    {
        return new ZulGurubShouldPickUpPoisonousBloodTrigger(botAI);
    }

    static Trigger* venoxis_should_be_tanked(PlayerbotAI* botAI)
    {
        return new ZulGurubBossShouldBeTankedTrigger(
            botAI, "high priest venoxis should be tanked",
            ZulGurubHelpers::Id(ZulGurubHelpers::ZulGurubNpcs::NPC_VENOXIS));
    }
    static Trigger* venoxis_lost_threat(PlayerbotAI* botAI)
    {
        return new ZulGurubBossLostThreatTrigger(
            botAI, "high priest venoxis lost threat",
            ZulGurubHelpers::Id(ZulGurubHelpers::ZulGurubNpcs::NPC_VENOXIS));
    }
    static Trigger* venoxis_serpents_spawned(PlayerbotAI* botAI)
    {
        return new ZulGurubAddsSpawnedTrigger(
            botAI, "high priest venoxis serpents spawned",
            ZulGurubHelpers::VENOXIS_SERPENTS_VALUE, ZulGurubAddRole::Dps,
            ZulGurubHelpers::Id(ZulGurubHelpers::ZulGurubNpcs::NPC_VENOXIS));
    }
    static Trigger* venoxis_bot_in_poison_cloud(PlayerbotAI* botAI)
    {
        // Snake form only, which the transform aura bounds on both sides.
        return new ZulGurubBotInHazardTrigger(
            botAI, "high priest venoxis bot in poison cloud",
            ZulGurubHelpers::VENOXIS_POISON_CLOUD_VALUE, ZulGurubHelpers::POISON_CLOUD_RADIUS,
            ZulGurubHelpers::Id(ZulGurubHelpers::ZulGurubNpcs::NPC_VENOXIS),
            ZulGurubHelpers::Id(ZulGurubHelpers::ZulGurubSpells::SPELL_VENOXIS_TRANSFORM));
    }

    static Trigger* jeklik_should_be_tanked(PlayerbotAI* botAI)
    {
        return new ZulGurubBossShouldBeTankedTrigger(
            botAI, "high priestess jeklik should be tanked",
            ZulGurubHelpers::Id(ZulGurubHelpers::ZulGurubNpcs::NPC_JEKLIK));
    }
    static Trigger* jeklik_lost_threat(PlayerbotAI* botAI)
    {
        return new ZulGurubBossLostThreatTrigger(
            botAI, "high priestess jeklik lost threat",
            ZulGurubHelpers::Id(ZulGurubHelpers::ZulGurubNpcs::NPC_JEKLIK));
    }
    static Trigger* jeklik_bats_spawned(PlayerbotAI* botAI)
    {
        return new ZulGurubAddsSpawnedTrigger(
            botAI, "high priestess jeklik bats spawned", ZulGurubHelpers::JEKLIK_BATS_VALUE,
            ZulGurubAddRole::Dps, ZulGurubHelpers::Id(ZulGurubHelpers::ZulGurubNpcs::NPC_JEKLIK));
    }
    static Trigger* jeklik_bot_in_liquid_fire(PlayerbotAI* botAI)
    {
        // The bombs come from her phase two Bat Riders, and the trap objects are their own proof
        // that the phase is running.
        return new ZulGurubBotInHazardTrigger(
            botAI, "high priestess jeklik bot in liquid fire",
            ZulGurubHelpers::JEKLIK_LIQUID_FIRE_VALUE, ZulGurubHelpers::LIQUID_FIRE_RADIUS,
            ZulGurubHelpers::Id(ZulGurubHelpers::ZulGurubNpcs::NPC_JEKLIK));
    }

    static Trigger* marli_should_be_tanked(PlayerbotAI* botAI)
    {
        return new ZulGurubBossShouldBeTankedTrigger(
            botAI, "high priestess mar'li should be tanked",
            ZulGurubHelpers::Id(ZulGurubHelpers::ZulGurubNpcs::NPC_MARLI));
    }
    static Trigger* marli_lost_threat(PlayerbotAI* botAI)
    {
        return new ZulGurubBossLostThreatTrigger(
            botAI, "high priestess mar'li lost threat",
            ZulGurubHelpers::Id(ZulGurubHelpers::ZulGurubNpcs::NPC_MARLI));
    }
    static Trigger* marli_spawns_hatched(PlayerbotAI* botAI)
    {
        return new ZulGurubAddsSpawnedTrigger(
            botAI, "high priestess mar'li spawns hatched", ZulGurubHelpers::MARLI_SPAWNS_VALUE,
            ZulGurubAddRole::Dps, ZulGurubHelpers::Id(ZulGurubHelpers::ZulGurubNpcs::NPC_MARLI));
    }

    static Trigger* mandokir_should_be_tanked(PlayerbotAI* botAI)
    {
        return new ZulGurubBossShouldBeTankedTrigger(
            botAI, "bloodlord mandokir should be tanked",
            ZulGurubHelpers::Id(ZulGurubHelpers::ZulGurubNpcs::NPC_MANDOKIR));
    }
    static Trigger* mandokir_lost_threat(PlayerbotAI* botAI)
    {
        return new ZulGurubBossLostThreatTrigger(
            botAI, "bloodlord mandokir lost threat",
            ZulGurubHelpers::Id(ZulGurubHelpers::ZulGurubNpcs::NPC_MANDOKIR));
    }
    static Trigger* mandokir_bot_is_watched(PlayerbotAI* botAI)
    {
        return new MandokirBotIsWatchedTrigger(botAI);
    }
    static Trigger* mandokir_ohgan_should_be_tanked(PlayerbotAI* botAI)
    {
        return new ZulGurubAddsSpawnedTrigger(
            botAI, "bloodlord mandokir ohgan should be tanked",
            ZulGurubHelpers::MANDOKIR_OHGAN_VALUE, ZulGurubAddRole::AssistTanks,
            ZulGurubHelpers::Id(ZulGurubHelpers::ZulGurubNpcs::NPC_MANDOKIR));
    }
    static Trigger* mandokir_ohgan_spawned(PlayerbotAI* botAI)
    {
        return new ZulGurubAddsSpawnedTrigger(
            botAI, "bloodlord mandokir ohgan spawned", ZulGurubHelpers::MANDOKIR_OHGAN_VALUE,
            ZulGurubAddRole::Dps,
            ZulGurubHelpers::Id(ZulGurubHelpers::ZulGurubNpcs::NPC_MANDOKIR));
    }
    static Trigger* mandokir_melee_in_whirlwind_range(PlayerbotAI* botAI)
    {
        return new MandokirMeleeInWhirlwindRangeTrigger(botAI);
    }

    static Trigger* thekal_should_be_tanked(PlayerbotAI* botAI)
    {
        return new ZulGurubBossShouldBeTankedTrigger(
            botAI, "high priest thekal should be tanked",
            ZulGurubHelpers::Id(ZulGurubHelpers::ZulGurubNpcs::NPC_THEKAL));
    }
    static Trigger* thekal_zealots_should_be_tanked(PlayerbotAI* botAI)
    {
        return new ThekalZealotsShouldBeTankedTrigger(botAI);
    }
    static Trigger* thekal_should_balance_trio_damage(PlayerbotAI* botAI)
    {
        return new ThekalShouldBalanceTrioDamageTrigger(botAI);
    }
    static Trigger* thekal_lost_threat(PlayerbotAI* botAI)
    {
        return new ZulGurubBossLostThreatTrigger(
            botAI, "high priest thekal lost threat",
            ZulGurubHelpers::Id(ZulGurubHelpers::ZulGurubNpcs::NPC_THEKAL));
    }
    static Trigger* thekal_tigers_spawned(PlayerbotAI* botAI)
    {
        return new ZulGurubAddsSpawnedTrigger(
            botAI, "high priest thekal tigers spawned", ZulGurubHelpers::THEKAL_TIGERS_VALUE,
            ZulGurubAddRole::Dps, ZulGurubHelpers::Id(ZulGurubHelpers::ZulGurubNpcs::NPC_THEKAL));
    }

    static Trigger* arlokk_should_be_tanked(PlayerbotAI* botAI)
    {
        return new ZulGurubBossShouldBeTankedTrigger(
            botAI, "high priestess arlokk should be tanked",
            ZulGurubHelpers::Id(ZulGurubHelpers::ZulGurubNpcs::NPC_ARLOKK));
    }
    static Trigger* arlokk_lost_threat(PlayerbotAI* botAI)
    {
        return new ZulGurubBossLostThreatTrigger(
            botAI, "high priestess arlokk lost threat",
            ZulGurubHelpers::Id(ZulGurubHelpers::ZulGurubNpcs::NPC_ARLOKK));
    }
    static Trigger* arlokk_prowlers_spawned(PlayerbotAI* botAI)
    {
        // No boss gate: she wipes her own threat list when she stalks (BAR:231), which is exactly
        // when the prowlers are the only thing left to kill. They are summons, so the value is
        // empty outside her fight anyway.
        return new ZulGurubAddsSpawnedTrigger(
            botAI, "high priestess arlokk prowlers spawned", ZulGurubHelpers::ARLOKK_PROWLERS_VALUE,
            ZulGurubAddRole::Dps);
    }

    static Trigger* jindo_should_be_tanked(PlayerbotAI* botAI)
    {
        return new ZulGurubBossShouldBeTankedTrigger(
            botAI, "jin'do the hexxer should be tanked",
            ZulGurubHelpers::Id(ZulGurubHelpers::ZulGurubNpcs::NPC_JINDO));
    }
    static Trigger* jindo_healing_ward_spawned(PlayerbotAI* botAI)
    {
        return new ZulGurubAddsSpawnedTrigger(
            botAI, "jin'do the hexxer healing ward spawned",
            ZulGurubHelpers::JINDO_HEALING_WARDS_VALUE, ZulGurubAddRole::Dps,
            ZulGurubHelpers::Id(ZulGurubHelpers::ZulGurubNpcs::NPC_JINDO));
    }
    static Trigger* jindo_brain_wash_totem_spawned(PlayerbotAI* botAI)
    {
        return new ZulGurubAddsSpawnedTrigger(
            botAI, "jin'do the hexxer brain wash totem spawned",
            ZulGurubHelpers::JINDO_BRAIN_WASH_TOTEMS_VALUE, ZulGurubAddRole::Dps,
            ZulGurubHelpers::Id(ZulGurubHelpers::ZulGurubNpcs::NPC_JINDO));
    }
    static Trigger* jindo_shades_spawned(PlayerbotAI* botAI)
    {
        return new ZulGurubAddsSpawnedTrigger(
            botAI, "jin'do the hexxer shades spawned", ZulGurubHelpers::JINDO_SHADES_VALUE,
            ZulGurubAddRole::Dps, ZulGurubHelpers::Id(ZulGurubHelpers::ZulGurubNpcs::NPC_JINDO));
    }
    static Trigger* jindo_hexed_the_tank(PlayerbotAI* botAI)
    {
        return new JindoHexedTankTrigger(botAI);
    }

    static Trigger* hakkar_should_be_tanked(PlayerbotAI* botAI)
    {
        return new ZulGurubBossShouldBeTankedTrigger(
            botAI, "hakkar should be tanked",
            ZulGurubHelpers::Id(ZulGurubHelpers::ZulGurubNpcs::NPC_HAKKAR));
    }
    static Trigger* hakkar_lost_threat(PlayerbotAI* botAI)
    {
        return new ZulGurubBossLostThreatTrigger(
            botAI, "hakkar lost threat",
            ZulGurubHelpers::Id(ZulGurubHelpers::ZulGurubNpcs::NPC_HAKKAR));
    }
    static Trigger* hakkar_attacking_insane_ally(PlayerbotAI* botAI)
    {
        return new ZulGurubAttackingCharmedAllyTrigger(
            botAI, "hakkar attacking insane ally",
            ZulGurubHelpers::Id(ZulGurubHelpers::ZulGurubSpells::SPELL_CAUSE_INSANITY));
    }

    static Trigger* gahzranka_should_be_tanked(PlayerbotAI* botAI)
    {
        return new ZulGurubBossShouldBeTankedTrigger(
            botAI, "gahz'ranka should be tanked",
            ZulGurubHelpers::Id(ZulGurubHelpers::ZulGurubNpcs::NPC_GAHZRANKA));
    }
    static Trigger* gahzranka_lost_threat(PlayerbotAI* botAI)
    {
        return new ZulGurubBossLostThreatTrigger(
            botAI, "gahz'ranka lost threat",
            ZulGurubHelpers::Id(ZulGurubHelpers::ZulGurubNpcs::NPC_GAHZRANKA));
    }

    static Trigger* grilek_should_be_tanked(PlayerbotAI* botAI)
    {
        return new ZulGurubBossShouldBeTankedTrigger(
            botAI, "gri'lek should be tanked",
            ZulGurubHelpers::Id(ZulGurubHelpers::ZulGurubNpcs::NPC_GRILEK));
    }
    static Trigger* grilek_lost_threat(PlayerbotAI* botAI)
    {
        return new ZulGurubBossLostThreatTrigger(
            botAI, "gri'lek lost threat",
            ZulGurubHelpers::Id(ZulGurubHelpers::ZulGurubNpcs::NPC_GRILEK));
    }
    static Trigger* grilek_bot_is_pursued(PlayerbotAI* botAI)
    {
        return new GrilekBotIsPursuedTrigger(botAI);
    }
    static Trigger* hazzarah_should_be_tanked(PlayerbotAI* botAI)
    {
        return new ZulGurubBossShouldBeTankedTrigger(
            botAI, "hazza'rah should be tanked",
            ZulGurubHelpers::Id(ZulGurubHelpers::ZulGurubNpcs::NPC_HAZZARAH));
    }
    static Trigger* hazzarah_illusions_spawned(PlayerbotAI* botAI)
    {
        return new ZulGurubAddsSpawnedTrigger(
            botAI, "hazza'rah illusions spawned", ZulGurubHelpers::HAZZARAH_ILLUSIONS_VALUE,
            ZulGurubAddRole::Dps,
            ZulGurubHelpers::Id(ZulGurubHelpers::ZulGurubNpcs::NPC_HAZZARAH));
    }
    static Trigger* hazzarah_ranged_should_spread(PlayerbotAI* botAI)
    {
        return new ZulGurubRangedShouldSpreadTrigger(
            botAI, "hazza'rah ranged should spread",
            ZulGurubHelpers::Id(ZulGurubHelpers::ZulGurubNpcs::NPC_HAZZARAH));
    }
    static Trigger* renataki_should_be_tanked(PlayerbotAI* botAI)
    {
        return new ZulGurubBossShouldBeTankedTrigger(
            botAI, "renataki should be tanked",
            ZulGurubHelpers::Id(ZulGurubHelpers::ZulGurubNpcs::NPC_RENATAKI));
    }
    static Trigger* renataki_lost_threat(PlayerbotAI* botAI)
    {
        return new ZulGurubBossLostThreatTrigger(
            botAI, "renataki lost threat",
            ZulGurubHelpers::Id(ZulGurubHelpers::ZulGurubNpcs::NPC_RENATAKI));
    }
    static Trigger* wushoolay_should_be_tanked(PlayerbotAI* botAI)
    {
        return new ZulGurubBossShouldBeTankedTrigger(
            botAI, "wushoolay should be tanked",
            ZulGurubHelpers::Id(ZulGurubHelpers::ZulGurubNpcs::NPC_WUSHOOLAY));
    }
    static Trigger* wushoolay_bot_in_lightning_cloud(PlayerbotAI* botAI)
    {
        return new ZulGurubBotInHazardTrigger(
            botAI, "wushoolay bot in lightning cloud",
            ZulGurubHelpers::WUSHOOLAY_LIGHTNING_CLOUD_VALUE,
            ZulGurubHelpers::LIGHTNING_CLOUD_RADIUS,
            ZulGurubHelpers::Id(ZulGurubHelpers::ZulGurubNpcs::NPC_WUSHOOLAY));
    }
    static Trigger* wushoolay_ranged_should_spread(PlayerbotAI* botAI)
    {
        return new ZulGurubRangedShouldSpreadTrigger(
            botAI, "wushoolay ranged should spread",
            ZulGurubHelpers::Id(ZulGurubHelpers::ZulGurubNpcs::NPC_WUSHOOLAY));
    }
};

#endif
