/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#ifndef PLAYERBOTS_SWPTRIGGERCONTEXT_H
#define PLAYERBOTS_SWPTRIGGERCONTEXT_H

#include "NamedObjectContext.h"
#include "SWPHelpers.h"
#include "SWPTriggers.h"

class RaidSwpTriggerContext : public NamedObjectContext<Trigger>
{
public:
    RaidSwpTriggerContext() : NamedObjectContext<Trigger>()
    {
        // Kalecgos
        creators["kalecgos bot in spectral realm"] =
            &RaidSwpTriggerContext::kalecgos_bot_in_spectral_realm;
        creators["kalecgos bot in dragon realm"] =
            &RaidSwpTriggerContext::kalecgos_bot_in_dragon_realm;

        // Brutallus
        creators["brutallus should be tanked"] = &RaidSwpTriggerContext::brutallus_should_be_tanked;
        creators["brutallus bot is burning"] = &RaidSwpTriggerContext::brutallus_bot_is_burning;
        creators["brutallus bot near burning ally"] =
            &RaidSwpTriggerContext::brutallus_bot_near_burning_ally;
        creators["brutallus bot has meteor slash"] =
            &RaidSwpTriggerContext::brutallus_bot_has_meteor_slash;

        // Felmyst
        creators["felmyst should be tanked"] = &RaidSwpTriggerContext::felmyst_should_be_tanked;
        creators["felmyst breath incoming"] = &RaidSwpTriggerContext::felmyst_breath_incoming;
        creators["felmyst bot near vapor trail"] =
            &RaidSwpTriggerContext::felmyst_bot_near_vapor_trail;
        creators["felmyst unyielding dead spawned"] =
            &RaidSwpTriggerContext::felmyst_unyielding_dead_spawned;
        creators["felmyst attacking charmed ally"] =
            &RaidSwpTriggerContext::felmyst_attacking_charmed_ally;
        creators["felmyst ranged should spread"] =
            &RaidSwpTriggerContext::felmyst_ranged_should_spread;

        // Eredar Twins
        creators["eredar twins should be tanked"] =
            &RaidSwpTriggerContext::eredar_twins_should_be_tanked;
        creators["eredar twins melee should attack lady sacrolash"] =
            &RaidSwpTriggerContext::eredar_twins_melee_should_attack_sacrolash;
        creators["eredar twins casters should attack alythess"] =
            &RaidSwpTriggerContext::eredar_twins_casters_should_attack_alythess;
        creators["eredar twins ranged should spread"] =
            &RaidSwpTriggerContext::eredar_twins_ranged_should_spread;

        // M'uru and Entropius
        creators["m'uru should be tanked"] = &RaidSwpTriggerContext::muru_should_be_tanked;
        creators["m'uru dark fiends spawned"] = &RaidSwpTriggerContext::muru_dark_fiends_spawned;
        creators["m'uru void sentinel spawned"] =
            &RaidSwpTriggerContext::muru_void_sentinel_spawned;
        creators["m'uru adds spawned"] = &RaidSwpTriggerContext::muru_adds_spawned;
        creators["m'uru bot in darkness"] = &RaidSwpTriggerContext::muru_bot_in_darkness;
        creators["entropius should be tanked"] =
            &RaidSwpTriggerContext::entropius_should_be_tanked;
        creators["entropius bot near singularity"] =
            &RaidSwpTriggerContext::entropius_bot_near_singularity;

        // Kil'jaeden
        creators["kil'jaeden should be tanked"] =
            &RaidSwpTriggerContext::kiljaeden_should_be_tanked;
        creators["kil'jaeden bot in armageddon"] =
            &RaidSwpTriggerContext::kiljaeden_bot_in_armageddon;
        creators["kil'jaeden shield orb spawned"] =
            &RaidSwpTriggerContext::kiljaeden_shield_orb_spawned;
        creators["kil'jaeden sinister reflection spawned"] =
            &RaidSwpTriggerContext::kiljaeden_sinister_reflection_spawned;
        creators["kil'jaeden hands of the deceiver spawned"] =
            &RaidSwpTriggerContext::kiljaeden_hands_spawned;
        creators["kil'jaeden ranged should spread"] =
            &RaidSwpTriggerContext::kiljaeden_ranged_should_spread;
    }

private:
    static Trigger* kalecgos_bot_in_spectral_realm(PlayerbotAI* botAI)
    {
        return new KalecgosBotInSpectralRealmTrigger(botAI);
    }
    static Trigger* kalecgos_bot_in_dragon_realm(PlayerbotAI* botAI)
    {
        return new KalecgosBotInDragonRealmTrigger(botAI);
    }

    static Trigger* brutallus_should_be_tanked(PlayerbotAI* botAI)
    {
        return new SwpBossShouldBeTankedTrigger(
            botAI, "brutallus should be tanked",
            SwpHelpers::Id(SwpHelpers::SwpNpcs::NPC_BRUTALLUS));
    }
    static Trigger* brutallus_bot_is_burning(PlayerbotAI* botAI)
    {
        return new BrutallusBotIsBurningTrigger(botAI);
    }
    static Trigger* brutallus_bot_near_burning_ally(PlayerbotAI* botAI)
    {
        return new BrutallusBotNearBurningAllyTrigger(botAI);
    }
    static Trigger* brutallus_bot_has_meteor_slash(PlayerbotAI* botAI)
    {
        return new BrutallusBotHasMeteorSlashTrigger(botAI);
    }

    static Trigger* felmyst_should_be_tanked(PlayerbotAI* botAI)
    {
        return new SwpBossShouldBeTankedTrigger(
            botAI, "felmyst should be tanked", SwpHelpers::Id(SwpHelpers::SwpNpcs::NPC_FELMYST));
    }
    static Trigger* felmyst_breath_incoming(PlayerbotAI* botAI)
    {
        return new FelmystBreathIncomingTrigger(botAI);
    }
    static Trigger* felmyst_bot_near_vapor_trail(PlayerbotAI* botAI)
    {
        return new SwpBotNearHazardTrigger(
            botAI, "felmyst bot near vapor trail", SwpHelpers::FELMYST_VAPOR_TRAILS_VALUE,
            SwpHelpers::VAPOR_TRAIL_RADIUS);
    }
    static Trigger* felmyst_unyielding_dead_spawned(PlayerbotAI* botAI)
    {
        return new SwpAddsSpawnedTrigger(
            botAI, "felmyst unyielding dead spawned", SwpHelpers::FELMYST_UNYIELDING_DEAD_VALUE,
            SwpAddRole::MeleeAndTanks);
    }
    static Trigger* felmyst_attacking_charmed_ally(PlayerbotAI* botAI)
    {
        return new SwpAttackingCharmedAllyTrigger(
            botAI, "felmyst attacking charmed ally",
            { SwpHelpers::Id(SwpHelpers::SwpSpells::SPELL_FOG_OF_CORRUPTION_CHARM),
              SwpHelpers::Id(SwpHelpers::SwpSpells::SPELL_FOG_OF_CORRUPTION_CHARM2) });
    }
    static Trigger* felmyst_ranged_should_spread(PlayerbotAI* botAI)
    {
        // Encapsulate and Gas Nova both punish a clumped raid; the distance to Felmyst herself is
        // the melee bots' business.
        constexpr float noDistanceFromBoss = 0.0f;
        return new SwpRangedShouldSpreadTrigger(
            botAI, "felmyst ranged should spread",
            SwpHelpers::Id(SwpHelpers::SwpNpcs::NPC_FELMYST), noDistanceFromBoss);
    }

    static Trigger* eredar_twins_should_be_tanked(PlayerbotAI* botAI)
    {
        return new EredarTwinsShouldBeTankedTrigger(botAI);
    }
    static Trigger* eredar_twins_melee_should_attack_sacrolash(PlayerbotAI* botAI)
    {
        constexpr bool forMelee = true;
        return new EredarTwinsShouldSwitchTargetTrigger(
            botAI, "eredar twins melee should attack lady sacrolash",
            SwpHelpers::Id(SwpHelpers::SwpNpcs::NPC_LADY_SACROLASH), forMelee);
    }
    static Trigger* eredar_twins_casters_should_attack_alythess(PlayerbotAI* botAI)
    {
        constexpr bool forMelee = false;
        return new EredarTwinsShouldSwitchTargetTrigger(
            botAI, "eredar twins casters should attack alythess",
            SwpHelpers::Id(SwpHelpers::SwpNpcs::NPC_GRAND_WARLOCK_ALYTHESS), forMelee);
    }
    static Trigger* eredar_twins_ranged_should_spread(PlayerbotAI* botAI)
    {
        return new SwpRangedShouldSpreadTrigger(
            botAI, "eredar twins ranged should spread",
            SwpHelpers::Id(SwpHelpers::SwpNpcs::NPC_GRAND_WARLOCK_ALYTHESS),
            SwpHelpers::ALYTHESS_RANGED_DISTANCE);
    }

    static Trigger* muru_should_be_tanked(PlayerbotAI* botAI)
    {
        return new SwpBossShouldBeTankedTrigger(
            botAI, "m'uru should be tanked", SwpHelpers::Id(SwpHelpers::SwpNpcs::NPC_MURU));
    }
    static Trigger* muru_dark_fiends_spawned(PlayerbotAI* botAI)
    {
        return new SwpAddsSpawnedTrigger(
            botAI, "m'uru dark fiends spawned", SwpHelpers::MURU_DARK_FIENDS_VALUE,
            SwpAddRole::Everyone);
    }
    static Trigger* muru_void_sentinel_spawned(PlayerbotAI* botAI)
    {
        return new SwpAddsSpawnedTrigger(
            botAI, "m'uru void sentinel spawned", SwpHelpers::MURU_VOID_SENTINELS_VALUE,
            SwpAddRole::Tanks);
    }
    static Trigger* muru_adds_spawned(PlayerbotAI* botAI)
    {
        return new SwpAddsSpawnedTrigger(
            botAI, "m'uru adds spawned", SwpHelpers::MURU_ADDS_VALUE,
            SwpAddRole::MeleeAndTanks);
    }
    static Trigger* muru_bot_in_darkness(PlayerbotAI* botAI)
    {
        return new SwpBotNearHazardTrigger(
            botAI, "m'uru bot in darkness", SwpHelpers::MURU_DARKNESS_VALUE,
            SwpHelpers::DARKNESS_RADIUS);
    }
    static Trigger* entropius_should_be_tanked(PlayerbotAI* botAI)
    {
        return new SwpBossShouldBeTankedTrigger(
            botAI, "entropius should be tanked",
            SwpHelpers::Id(SwpHelpers::SwpNpcs::NPC_ENTROPIUS));
    }
    static Trigger* entropius_bot_near_singularity(PlayerbotAI* botAI)
    {
        return new SwpBotNearHazardTrigger(
            botAI, "entropius bot near singularity", SwpHelpers::ENTROPIUS_SINGULARITIES_VALUE,
            SwpHelpers::SINGULARITY_RADIUS);
    }

    static Trigger* kiljaeden_should_be_tanked(PlayerbotAI* botAI)
    {
        return new SwpBossShouldBeTankedTrigger(
            botAI, "kil'jaeden should be tanked",
            SwpHelpers::Id(SwpHelpers::SwpNpcs::NPC_KILJAEDEN));
    }
    static Trigger* kiljaeden_bot_in_armageddon(PlayerbotAI* botAI)
    {
        return new SwpBotNearHazardTrigger(
            botAI, "kil'jaeden bot in armageddon", SwpHelpers::KILJAEDEN_ARMAGEDDON_VALUE,
            SwpHelpers::ARMAGEDDON_RADIUS);
    }
    static Trigger* kiljaeden_shield_orb_spawned(PlayerbotAI* botAI)
    {
        return new SwpAddsSpawnedTrigger(
            botAI, "kil'jaeden shield orb spawned", SwpHelpers::KILJAEDEN_SHIELD_ORBS_VALUE,
            SwpAddRole::RangedDps);
    }
    static Trigger* kiljaeden_sinister_reflection_spawned(PlayerbotAI* botAI)
    {
        return new SwpAddsSpawnedTrigger(
            botAI, "kil'jaeden sinister reflection spawned",
            SwpHelpers::KILJAEDEN_REFLECTIONS_VALUE, SwpAddRole::MeleeAndTanks);
    }
    static Trigger* kiljaeden_hands_spawned(PlayerbotAI* botAI)
    {
        return new SwpAddsSpawnedTrigger(
            botAI, "kil'jaeden hands of the deceiver spawned", SwpHelpers::KILJAEDEN_HANDS_VALUE,
            SwpAddRole::Everyone);
    }
    static Trigger* kiljaeden_ranged_should_spread(PlayerbotAI* botAI)
    {
        // Fire Bloom and Legion Lightning both chain through whoever is standing together.
        constexpr float noDistanceFromBoss = 0.0f;
        return new SwpRangedShouldSpreadTrigger(
            botAI, "kil'jaeden ranged should spread",
            SwpHelpers::Id(SwpHelpers::SwpNpcs::NPC_KILJAEDEN), noDistanceFromBoss);
    }
};

#endif
