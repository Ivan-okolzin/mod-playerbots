/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#ifndef PLAYERBOTS_AQ20VALUECONTEXT_H
#define PLAYERBOTS_AQ20VALUECONTEXT_H

#include "Aq20Helpers.h"
#include "NamedObjectContext.h"
#include "Value.h"
#include <string>
#include <vector>

class Aq20CreatureGuidsValue : public CalculatedValue<GuidVector>
{
public:
    Aq20CreatureGuidsValue(
        PlayerbotAI* botAI, std::string const& name, std::vector<uint32> const& entries)
        : CalculatedValue<GuidVector>(botAI, name, Aq20Helpers::AQ20_CACHE_INTERVAL_MS),
          _entries(entries) {}

protected:
    GuidVector Calculate() override
    {
        return Aq20Helpers::FindCreatureGuids(bot, _entries, Aq20Helpers::ADD_SEARCH_RADIUS);
    }

private:
    std::vector<uint32> const _entries;
};

// Kurinnaxx's Sand Traps and Ossirian's crystals are gameobjects rather than creatures, so the
// grid search they need is its own one. Neither entry has a spawn in the world table: both exist
// only while their encounter is being fought.
class Aq20GameObjectGuidsValue : public CalculatedValue<GuidVector>
{
public:
    Aq20GameObjectGuidsValue(
        PlayerbotAI* botAI, std::string const& name, std::vector<uint32> const& entries,
        float radius)
        : CalculatedValue<GuidVector>(botAI, name, Aq20Helpers::AQ20_CACHE_INTERVAL_MS),
          _entries(entries), _radius(radius) {}

protected:
    GuidVector Calculate() override
    {
        return Aq20Helpers::FindGameObjectGuids(bot, _entries, _radius);
    }

private:
    std::vector<uint32> const _entries;
    float const _radius;
};

class RaidAq20ValueContext : public NamedObjectContext<UntypedValue>
{
public:
    RaidAq20ValueContext()
    {
        creators[Aq20Helpers::KURINNAXX_SAND_TRAPS_VALUE] =
            &RaidAq20ValueContext::kurinnaxx_sand_traps;
        creators[Aq20Helpers::MOAM_MANA_FIENDS_VALUE] = &RaidAq20ValueContext::moam_mana_fiends;
        creators[Aq20Helpers::BURU_EGGS_VALUE] = &RaidAq20ValueContext::buru_eggs;
        creators[Aq20Helpers::BURU_HATCHLINGS_VALUE] = &RaidAq20ValueContext::buru_hatchlings;
        creators[Aq20Helpers::AYAMISS_LARVAE_VALUE] = &RaidAq20ValueContext::ayamiss_larvae;
        creators[Aq20Helpers::AYAMISS_SWARMERS_VALUE] = &RaidAq20ValueContext::ayamiss_swarmers;
        creators[Aq20Helpers::OSSIRIAN_CRYSTALS_VALUE] = &RaidAq20ValueContext::ossirian_crystals;
        creators[Aq20Helpers::OSSIRIAN_SAND_VORTEXES_VALUE] =
            &RaidAq20ValueContext::ossirian_sand_vortexes;
    }

private:
    static UntypedValue* kurinnaxx_sand_traps(PlayerbotAI* botAI)
    {
        return new Aq20GameObjectGuidsValue(
            botAI, Aq20Helpers::KURINNAXX_SAND_TRAPS_VALUE,
            { Aq20Helpers::Id(Aq20Helpers::Aq20GameObjects::GO_SAND_TRAP) },
            Aq20Helpers::HAZARD_SEARCH_RADIUS);
    }
    static UntypedValue* moam_mana_fiends(PlayerbotAI* botAI)
    {
        return new Aq20CreatureGuidsValue(
            botAI, Aq20Helpers::MOAM_MANA_FIENDS_VALUE,
            { Aq20Helpers::Id(Aq20Helpers::Aq20Npcs::NPC_MANA_FIEND) });
    }
    static UntypedValue* buru_eggs(PlayerbotAI* botAI)
    {
        return new Aq20CreatureGuidsValue(
            botAI, Aq20Helpers::BURU_EGGS_VALUE,
            { Aq20Helpers::Id(Aq20Helpers::Aq20Npcs::NPC_BURU_EGG) });
    }
    static UntypedValue* buru_hatchlings(PlayerbotAI* botAI)
    {
        return new Aq20CreatureGuidsValue(
            botAI, Aq20Helpers::BURU_HATCHLINGS_VALUE,
            { Aq20Helpers::Id(Aq20Helpers::Aq20Npcs::NPC_HATCHLING) });
    }
    static UntypedValue* ayamiss_larvae(PlayerbotAI* botAI)
    {
        return new Aq20CreatureGuidsValue(
            botAI, Aq20Helpers::AYAMISS_LARVAE_VALUE,
            { Aq20Helpers::Id(Aq20Helpers::Aq20Npcs::NPC_HIVEZARA_LARVA) });
    }
    static UntypedValue* ayamiss_swarmers(PlayerbotAI* botAI)
    {
        return new Aq20CreatureGuidsValue(
            botAI, Aq20Helpers::AYAMISS_SWARMERS_VALUE,
            { Aq20Helpers::Id(Aq20Helpers::Aq20Npcs::NPC_HIVEZARA_SWARMER) });
    }
    // Both the crystals still waiting and the ones already clicked: the flag they carry tells the
    // two apart, and the script spawns a replacement for every one that goes off (OSS:161).
    static UntypedValue* ossirian_crystals(PlayerbotAI* botAI)
    {
        return new Aq20GameObjectGuidsValue(
            botAI, Aq20Helpers::OSSIRIAN_CRYSTALS_VALUE,
            { Aq20Helpers::Id(Aq20Helpers::Aq20GameObjects::GO_OSSIRIAN_CRYSTAL) },
            Aq20Helpers::CRYSTAL_SEARCH_RADIUS);
    }
    static UntypedValue* ossirian_sand_vortexes(PlayerbotAI* botAI)
    {
        return new Aq20CreatureGuidsValue(
            botAI, Aq20Helpers::OSSIRIAN_SAND_VORTEXES_VALUE,
            { Aq20Helpers::Id(Aq20Helpers::Aq20Npcs::NPC_SAND_VORTEX) });
    }
};

#endif
