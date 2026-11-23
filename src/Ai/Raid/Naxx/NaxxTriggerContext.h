/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#ifndef PLAYERBOTS_NAXXTRIGGERCONTEXT_H
#define PLAYERBOTS_NAXXTRIGGERCONTEXT_H

#include "NamedObjectContext.h"
#include "NaxxTriggers.h"

class RaidNaxxTriggerContext : public NamedObjectContext<Trigger>
{
public:
    RaidNaxxTriggerContext()
    {
        creators["mutating injection melee"] = &RaidNaxxTriggerContext::mutating_injection_melee;
        creators["mutating injection ranged"] = &RaidNaxxTriggerContext::mutating_injection_ranged;
        creators["mutating injection removed"] = &RaidNaxxTriggerContext::mutating_injection_removed;
        creators["grobbulus cloud"] = &RaidNaxxTriggerContext::grobbulus_cloud;
        creators["heigan melee"] = &RaidNaxxTriggerContext::heigan_melee;
        creators["heigan ranged"] = &RaidNaxxTriggerContext::heigan_ranged;

        creators["thaddius phase pet"] = &RaidNaxxTriggerContext::thaddius_phase_pet;
        creators["thaddius phase pet lose aggro"] = &RaidNaxxTriggerContext::thaddius_phase_pet_lose_aggro;
        creators["thaddius phase transition"] = &RaidNaxxTriggerContext::thaddius_phase_transition;
        creators["thaddius phase thaddius"] = &RaidNaxxTriggerContext::thaddius_phase_thaddius;

        creators["razuvious tank"] = &RaidNaxxTriggerContext::razuvious_tank;
        creators["razuvious nontank"] = &RaidNaxxTriggerContext::razuvious_nontank;

        creators["four horsemen attractors"] = &RaidNaxxTriggerContext::four_horsemen_attractors;
        creators["four horsemen except attractors"] = &RaidNaxxTriggerContext::four_horsemen_except_attractors;

        creators["sapphiron ground"] = &RaidNaxxTriggerContext::sapphiron_ground;
        creators["sapphiron flight"] = &RaidNaxxTriggerContext::sapphiron_flight;

        creators["kel'thuzad"] = &RaidNaxxTriggerContext::kelthuzad;

        creators["anub'rekhan"] = &RaidNaxxTriggerContext::anubrekhan;
        creators["faerlina"] = &RaidNaxxTriggerContext::faerlina;
        creators["maexxna"] = &RaidNaxxTriggerContext::maexxna;

        creators["noth the plaguebringer should be tanked"] = &RaidNaxxTriggerContext::noth_should_be_tanked;
        creators["noth the plaguebringer lost threat"] = &RaidNaxxTriggerContext::noth_lost_threat;
        creators["noth the plaguebringer skeletons should be tanked"] =
            &RaidNaxxTriggerContext::noth_skeletons_should_be_tanked;
        creators["noth the plaguebringer balcony phase"] = &RaidNaxxTriggerContext::noth_balcony_phase;

        creators["gothik the harvester should be tanked"] = &RaidNaxxTriggerContext::gothik_should_be_tanked;
        creators["gothik the harvester lost threat"] = &RaidNaxxTriggerContext::gothik_lost_threat;
        creators["gothik the harvester unrelenting adds should be tanked"] =
            &RaidNaxxTriggerContext::gothik_living_adds_should_be_tanked;
        creators["gothik the harvester unrelenting adds spawned"] =
            &RaidNaxxTriggerContext::gothik_living_adds_spawned;
        creators["gothik the harvester spectral adds should be tanked"] =
            &RaidNaxxTriggerContext::gothik_dead_adds_should_be_tanked;
        creators["gothik the harvester spectral adds spawned"] = &RaidNaxxTriggerContext::gothik_dead_adds_spawned;

        creators["patchwerk should be tanked"] = &RaidNaxxTriggerContext::patchwerk_should_be_tanked;
        creators["patchwerk lost threat"] = &RaidNaxxTriggerContext::patchwerk_lost_threat;
        creators["patchwerk should be soaked"] = &RaidNaxxTriggerContext::patchwerk_should_be_soaked;
        creators["patchwerk non-melee in hateful strike range"] =
            &RaidNaxxTriggerContext::patchwerk_non_melee_in_hateful_strike_range;

        creators["gluth"] = &RaidNaxxTriggerContext::gluth;
        creators["gluth main tank mortal wound"] = &RaidNaxxTriggerContext::gluth_main_tank_mortal_wound;

        creators["loatheb"] = &RaidNaxxTriggerContext::loatheb;
    }

private:
    static Trigger* mutating_injection_melee(PlayerbotAI* botAI) { return new MutatingInjectionMeleeTrigger(botAI); }
    static Trigger* mutating_injection_ranged(PlayerbotAI* botAI) { return new MutatingInjectionRangedTrigger(botAI); }
    static Trigger* mutating_injection_removed(PlayerbotAI* botAI) { return new MutatingInjectionRemovedTrigger(botAI); }
    static Trigger* grobbulus_cloud(PlayerbotAI* botAI) { return new GrobbulusCloudTrigger(botAI); }
    static Trigger* heigan_melee(PlayerbotAI* botAI) { return new HeiganMeleeTrigger(botAI); }
    static Trigger* heigan_ranged(PlayerbotAI* botAI) { return new HeiganRangedTrigger(botAI); }

    static Trigger* thaddius_phase_pet(PlayerbotAI* botAI) { return new ThaddiusPhasePetTrigger(botAI); }
    static Trigger* thaddius_phase_pet_lose_aggro(PlayerbotAI* botAI) { return new ThaddiusPhasePetLoseAggroTrigger(botAI); }
    static Trigger* thaddius_phase_transition(PlayerbotAI* botAI) { return new ThaddiusPhaseTransitionTrigger(botAI); }
    static Trigger* thaddius_phase_thaddius(PlayerbotAI* botAI) { return new ThaddiusPhaseThaddiusTrigger(botAI); }
    static Trigger* razuvious_tank(PlayerbotAI* botAI) { return new RazuviousTankTrigger(botAI); }
    static Trigger* razuvious_nontank(PlayerbotAI* botAI) { return new RazuviousNontankTrigger(botAI); }

    static Trigger* four_horsemen_attractors(PlayerbotAI* botAI) { return new FourHorsemenAttractorsTrigger(botAI); }
    static Trigger* four_horsemen_except_attractors(PlayerbotAI* botAI) { return new FourHorsemenExceptAttractorsTrigger(botAI); }

    static Trigger* sapphiron_ground(PlayerbotAI* botAI) { return new SapphironGroundTrigger(botAI); }
    static Trigger* sapphiron_flight(PlayerbotAI* botAI) { return new SapphironFlightTrigger(botAI); }
    static Trigger* kelthuzad(PlayerbotAI* botAI) { return new KelthuzadTrigger(botAI); }
    static Trigger* anubrekhan(PlayerbotAI* botAI) { return new AnubrekhanTrigger(botAI); }
    static Trigger* faerlina(PlayerbotAI* botAI) { return new FaerlinaTrigger(botAI); }
    static Trigger* maexxna(PlayerbotAI* botAI) { return new MaexxnaTrigger(botAI); }

    static Trigger* noth_should_be_tanked(PlayerbotAI* botAI)
    {
        return new NaxxBossShouldBeTankedTrigger(
            botAI, "noth the plaguebringer should be tanked", NaxxHelpers::Id(NaxxHelpers::NaxxNpcs::NPC_NOTH));
    }
    static Trigger* noth_lost_threat(PlayerbotAI* botAI)
    {
        return new NaxxBossLostThreatTrigger(
            botAI, "noth the plaguebringer lost threat", NaxxHelpers::Id(NaxxHelpers::NaxxNpcs::NPC_NOTH));
    }
    // The waves go to the assist tanks in both phases; the main tank keeps Noth himself.
    static Trigger* noth_skeletons_should_be_tanked(PlayerbotAI* botAI)
    {
        return new NaxxAddsSpawnedTrigger(
            botAI, "noth the plaguebringer skeletons should be tanked", NaxxHelpers::NOTH_SKELETONS_VALUE,
            NaxxHelpers::NaxxRole::AssistTanks, NaxxHelpers::Id(NaxxHelpers::NaxxNpcs::NPC_NOTH));
    }
    static Trigger* noth_balcony_phase(PlayerbotAI* botAI)
    {
        return new NothBalconyAddsTrigger(
            botAI, "noth the plaguebringer balcony phase", NaxxHelpers::NaxxRole::Dps);
    }

    static Trigger* gothik_should_be_tanked(PlayerbotAI* botAI)
    {
        return new NaxxBossShouldBeTankedTrigger(
            botAI, "gothik the harvester should be tanked", NaxxHelpers::Id(NaxxHelpers::NaxxNpcs::NPC_GOTHIK));
    }
    static Trigger* gothik_lost_threat(PlayerbotAI* botAI)
    {
        return new NaxxBossLostThreatTrigger(
            botAI, "gothik the harvester lost threat", NaxxHelpers::Id(NaxxHelpers::NaxxNpcs::NPC_GOTHIK));
    }
    // Every tank is an add tank in this fight: there is no boss to hold for its first four and a
    // half minutes, and each half of the room fights its own waves.
    static Trigger* gothik_living_adds_should_be_tanked(PlayerbotAI* botAI)
    {
        return new GothikAddsSpawnedTrigger(
            botAI, "gothik the harvester unrelenting adds should be tanked",
            NaxxHelpers::GOTHIK_LIVING_ADDS_VALUE, NaxxHelpers::NaxxRole::Tanks);
    }
    static Trigger* gothik_living_adds_spawned(PlayerbotAI* botAI)
    {
        return new GothikAddsSpawnedTrigger(
            botAI, "gothik the harvester unrelenting adds spawned", NaxxHelpers::GOTHIK_LIVING_ADDS_VALUE,
            NaxxHelpers::NaxxRole::Dps);
    }
    static Trigger* gothik_dead_adds_should_be_tanked(PlayerbotAI* botAI)
    {
        return new GothikAddsSpawnedTrigger(
            botAI, "gothik the harvester spectral adds should be tanked", NaxxHelpers::GOTHIK_DEAD_ADDS_VALUE,
            NaxxHelpers::NaxxRole::Tanks);
    }
    static Trigger* gothik_dead_adds_spawned(PlayerbotAI* botAI)
    {
        return new GothikAddsSpawnedTrigger(
            botAI, "gothik the harvester spectral adds spawned", NaxxHelpers::GOTHIK_DEAD_ADDS_VALUE,
            NaxxHelpers::NaxxRole::Dps);
    }

    static Trigger* patchwerk_should_be_tanked(PlayerbotAI* botAI)
    {
        return new NaxxBossShouldBeTankedTrigger(
            botAI, "patchwerk should be tanked", NaxxHelpers::Id(NaxxHelpers::NaxxNpcs::NPC_PATCHWERK));
    }
    static Trigger* patchwerk_lost_threat(PlayerbotAI* botAI)
    {
        return new NaxxBossLostThreatTrigger(
            botAI, "patchwerk lost threat", NaxxHelpers::Id(NaxxHelpers::NaxxNpcs::NPC_PATCHWERK));
    }
    // Hateful Strike leaves out whoever Patchwerk is already swinging at (BPA:135), so the assist
    // tanks take it, and they can only do that from inside his melee range.
    static Trigger* patchwerk_should_be_soaked(PlayerbotAI* botAI)
    {
        return new NaxxBossShouldBeTankedTrigger(
            botAI, "patchwerk should be soaked", NaxxHelpers::Id(NaxxHelpers::NaxxNpcs::NPC_PATCHWERK),
            NaxxHelpers::NaxxRole::AssistTanks);
    }
    static Trigger* patchwerk_non_melee_in_hateful_strike_range(PlayerbotAI* botAI)
    {
        return new PatchwerkNonMeleeInStrikeRangeTrigger(botAI);
    }

    static Trigger* gluth(PlayerbotAI* botAI) { return new GluthTrigger(botAI); }
    static Trigger* gluth_main_tank_mortal_wound(PlayerbotAI* botAI) { return new GluthMainTankMortalWoundTrigger(botAI); }
    static Trigger* loatheb(PlayerbotAI* botAI) { return new LoathebTrigger(botAI); }
};

#endif
