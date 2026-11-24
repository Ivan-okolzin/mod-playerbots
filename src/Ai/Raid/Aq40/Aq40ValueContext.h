/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#ifndef PLAYERBOTS_AQ40VALUECONTEXT_H
#define PLAYERBOTS_AQ40VALUECONTEXT_H

#include "Aq40Helpers.h"
#include "EncounterHelpers.h"
#include "NamedObjectContext.h"
#include "Position.h"
#include "Value.h"
#include <string>
#include <vector>

class Aq40CreatureGuidsValue : public CalculatedValue<GuidVector>
{
public:
    Aq40CreatureGuidsValue(
        PlayerbotAI* botAI, std::string const& name, std::vector<uint32> const& entries)
        : CalculatedValue<GuidVector>(botAI, name, Aq40Helpers::AQ40_CACHE_INTERVAL_MS),
          _entries(entries) {}

protected:
    GuidVector Calculate() override
    {
        return Aq40Helpers::FindCreatureGuids(bot, _entries, Aq40Helpers::ADD_SEARCH_RADIUS);
    }

private:
    std::vector<uint32> const _entries;
};

class Aq40HazardPositionsValue : public CalculatedValue<std::vector<Position>>
{
public:
    Aq40HazardPositionsValue(PlayerbotAI* botAI, std::string const& name, uint32 spellId)
        : CalculatedValue<std::vector<Position>>(
              botAI, name, Aq40Helpers::AQ40_CACHE_INTERVAL_MS),
          _spellId(spellId) {}

protected:
    std::vector<Position> Calculate() override
    {
        return EncounterHelpers::GetDynamicObjectPositions(
            bot, Aq40Helpers::HAZARD_SEARCH_RADIUS, _spellId);
    }

private:
    uint32 const _spellId;
};

// The Dark Glare sweep direction, sampled rather than read: see DarkGlareSweepSampler.
class Aq40DarkGlareSweepValue : public CalculatedValue<float>
{
public:
    Aq40DarkGlareSweepValue(PlayerbotAI* botAI)
        : CalculatedValue<float>(
              botAI, Aq40Helpers::CTHUN_DARK_GLARE_SWEEP_VALUE,
              Aq40Helpers::DARK_GLARE_SAMPLE_INTERVAL_MS) {}

protected:
    float Calculate() override { return _sampler.Sample(botAI); }

private:
    Aq40Helpers::DarkGlareSweepSampler _sampler;
};

class RaidAq40ValueContext : public NamedObjectContext<UntypedValue>
{
public:
    RaidAq40ValueContext()
    {
        creators[Aq40Helpers::SKERAM_COPIES_VALUE] = &RaidAq40ValueContext::skeram_copies;
        creators[Aq40Helpers::YAUJ_BROOD_VALUE] = &RaidAq40ValueContext::yauj_brood;
        creators[Aq40Helpers::ROYAL_GUARDS_VALUE] = &RaidAq40ValueContext::royal_guards;
        creators[Aq40Helpers::FANKRISS_WORMS_VALUE] = &RaidAq40ValueContext::fankriss_worms;
        creators[Aq40Helpers::FANKRISS_SPAWNS_VALUE] = &RaidAq40ValueContext::fankriss_spawns;
        creators[Aq40Helpers::VISCIDUS_GLOBS_VALUE] = &RaidAq40ValueContext::viscidus_globs;
        creators[Aq40Helpers::DIRT_MOUNDS_VALUE] = &RaidAq40ValueContext::dirt_mounds;
        creators[Aq40Helpers::OURO_SCARABS_VALUE] = &RaidAq40ValueContext::ouro_scarabs;
        creators[Aq40Helpers::POISON_CLOUD_VALUE] = &RaidAq40ValueContext::poison_cloud;
        creators[Aq40Helpers::NOXIOUS_POISON_VALUE] = &RaidAq40ValueContext::noxious_poison;
        creators[Aq40Helpers::BLIZZARD_VALUE] = &RaidAq40ValueContext::blizzard;
        creators[Aq40Helpers::CTHUN_CLAW_TENTACLES_VALUE] =
            &RaidAq40ValueContext::cthun_claw_tentacles;
        creators[Aq40Helpers::CTHUN_EYE_TENTACLES_VALUE] =
            &RaidAq40ValueContext::cthun_eye_tentacles;
        creators[Aq40Helpers::CTHUN_GIANT_CLAW_TENTACLES_VALUE] =
            &RaidAq40ValueContext::cthun_giant_claw_tentacles;
        creators[Aq40Helpers::CTHUN_GIANT_EYE_TENTACLES_VALUE] =
            &RaidAq40ValueContext::cthun_giant_eye_tentacles;
        creators[Aq40Helpers::CTHUN_FLESH_TENTACLES_VALUE] =
            &RaidAq40ValueContext::cthun_flesh_tentacles;
        creators[Aq40Helpers::CTHUN_DARK_GLARE_SWEEP_VALUE] =
            &RaidAq40ValueContext::cthun_dark_glare_sweep;
    }

private:
    static UntypedValue* skeram_copies(PlayerbotAI* botAI)
    {
        return new Aq40CreatureGuidsValue(
            botAI, Aq40Helpers::SKERAM_COPIES_VALUE,
            { Aq40Helpers::Id(Aq40Helpers::Aq40Npcs::NPC_SKERAM) });
    }
    static UntypedValue* yauj_brood(PlayerbotAI* botAI)
    {
        return new Aq40CreatureGuidsValue(
            botAI, Aq40Helpers::YAUJ_BROOD_VALUE,
            { Aq40Helpers::Id(Aq40Helpers::Aq40Npcs::NPC_YAUJ_BROOD) });
    }
    static UntypedValue* royal_guards(PlayerbotAI* botAI)
    {
        return new Aq40CreatureGuidsValue(
            botAI, Aq40Helpers::ROYAL_GUARDS_VALUE,
            { Aq40Helpers::Id(Aq40Helpers::Aq40Npcs::NPC_SARTURA_ROYAL_GUARD) });
    }
    static UntypedValue* fankriss_worms(PlayerbotAI* botAI)
    {
        return new Aq40CreatureGuidsValue(
            botAI, Aq40Helpers::FANKRISS_WORMS_VALUE,
            { Aq40Helpers::Id(Aq40Helpers::Aq40Npcs::NPC_VEKNISS_HATCHLING),
              Aq40Helpers::Id(Aq40Helpers::Aq40Npcs::NPC_SPAWN_OF_FANKRISS) });
    }
    static UntypedValue* fankriss_spawns(PlayerbotAI* botAI)
    {
        return new Aq40CreatureGuidsValue(
            botAI, Aq40Helpers::FANKRISS_SPAWNS_VALUE,
            { Aq40Helpers::Id(Aq40Helpers::Aq40Npcs::NPC_SPAWN_OF_FANKRISS) });
    }
    static UntypedValue* viscidus_globs(PlayerbotAI* botAI)
    {
        return new Aq40CreatureGuidsValue(
            botAI, Aq40Helpers::VISCIDUS_GLOBS_VALUE,
            { Aq40Helpers::Id(Aq40Helpers::Aq40Npcs::NPC_GLOB_OF_VISCIDUS) });
    }
    static UntypedValue* dirt_mounds(PlayerbotAI* botAI)
    {
        return new Aq40CreatureGuidsValue(
            botAI, Aq40Helpers::DIRT_MOUNDS_VALUE,
            { Aq40Helpers::Id(Aq40Helpers::Aq40Npcs::NPC_DIRT_MOUND) });
    }
    static UntypedValue* ouro_scarabs(PlayerbotAI* botAI)
    {
        return new Aq40CreatureGuidsValue(
            botAI, Aq40Helpers::OURO_SCARABS_VALUE,
            { Aq40Helpers::Id(Aq40Helpers::Aq40Npcs::NPC_OURO_SCARAB) });
    }
    static UntypedValue* poison_cloud(PlayerbotAI* botAI)
    {
        return new Aq40HazardPositionsValue(
            botAI, Aq40Helpers::POISON_CLOUD_VALUE,
            Aq40Helpers::Id(Aq40Helpers::Aq40Spells::SPELL_POISON_CLOUD));
    }
    static UntypedValue* noxious_poison(PlayerbotAI* botAI)
    {
        return new Aq40HazardPositionsValue(
            botAI, Aq40Helpers::NOXIOUS_POISON_VALUE,
            Aq40Helpers::Id(Aq40Helpers::Aq40Spells::SPELL_NOXIOUS_POISON));
    }
    static UntypedValue* blizzard(PlayerbotAI* botAI)
    {
        return new Aq40HazardPositionsValue(
            botAI, Aq40Helpers::BLIZZARD_VALUE,
            Aq40Helpers::Id(Aq40Helpers::Aq40Spells::SPELL_BLIZZARD));
    }
    static UntypedValue* cthun_claw_tentacles(PlayerbotAI* botAI)
    {
        return new Aq40CreatureGuidsValue(
            botAI, Aq40Helpers::CTHUN_CLAW_TENTACLES_VALUE,
            { Aq40Helpers::Id(Aq40Helpers::Aq40Npcs::NPC_CLAW_TENTACLE) });
    }
    static UntypedValue* cthun_eye_tentacles(PlayerbotAI* botAI)
    {
        return new Aq40CreatureGuidsValue(
            botAI, Aq40Helpers::CTHUN_EYE_TENTACLES_VALUE,
            { Aq40Helpers::Id(Aq40Helpers::Aq40Npcs::NPC_EYE_TENTACLE) });
    }
    static UntypedValue* cthun_giant_claw_tentacles(PlayerbotAI* botAI)
    {
        return new Aq40CreatureGuidsValue(
            botAI, Aq40Helpers::CTHUN_GIANT_CLAW_TENTACLES_VALUE,
            { Aq40Helpers::Id(Aq40Helpers::Aq40Npcs::NPC_GIANT_CLAW_TENTACLE) });
    }
    static UntypedValue* cthun_giant_eye_tentacles(PlayerbotAI* botAI)
    {
        return new Aq40CreatureGuidsValue(
            botAI, Aq40Helpers::CTHUN_GIANT_EYE_TENTACLES_VALUE,
            { Aq40Helpers::Id(Aq40Helpers::Aq40Npcs::NPC_GIANT_EYE_TENTACLE) });
    }
    // The stomach is some 200 yards below the chamber, so this search only ever sees the tentacles
    // when the bot itself has been swallowed.
    static UntypedValue* cthun_flesh_tentacles(PlayerbotAI* botAI)
    {
        return new Aq40CreatureGuidsValue(
            botAI, Aq40Helpers::CTHUN_FLESH_TENTACLES_VALUE,
            { Aq40Helpers::Id(Aq40Helpers::Aq40Npcs::NPC_FLESH_TENTACLE) });
    }
    static UntypedValue* cthun_dark_glare_sweep(PlayerbotAI* botAI)
    {
        return new Aq40DarkGlareSweepValue(botAI);
    }
};

#endif
