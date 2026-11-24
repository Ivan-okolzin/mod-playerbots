/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#ifndef PLAYERBOTS_NAXXVALUECONTEXT_H
#define PLAYERBOTS_NAXXVALUECONTEXT_H

#include "NamedObjectContext.h"
#include "NaxxHelpers.h"
#include "PlayerbotAI.h"
#include "Value.h"
#include <string>
#include <vector>

// Noth's waves and Gothik's two halves of adds are found by a grid search, which belongs behind a
// cached value: the triggers that ask for them run every tick for every bot in the raid.
class NaxxCreatureGuidsValue : public ObjectGuidListCalculatedValue
{
public:
    NaxxCreatureGuidsValue(
        PlayerbotAI* botAI, std::string const& name, std::vector<uint32> const& entries)
        : ObjectGuidListCalculatedValue(botAI, name, NaxxHelpers::NAXX_CACHE_INTERVAL_MS),
          _entries(entries) {}

protected:
    GuidVector Calculate() override
    {
        return NaxxHelpers::FindCreatureGuids(bot, _entries, NaxxHelpers::ADD_SEARCH_RADIUS);
    }

private:
    static UntypedValue* faerlina_adds(PlayerbotAI* botAI)
    {
        return new NaxxCreatureGuidsValue(botAI, NaxxHelpers::FAERLINA_ADDS_VALUE,
            { NaxxHelpers::Id(NaxxNpcs::NPC_FOLLOWER) });
    }

    static UntypedValue* maexxna_adds(PlayerbotAI* botAI)
    {
        return new NaxxCreatureGuidsValue(botAI, NaxxHelpers::MAEXXNA_ADDS_VALUE,
            { NaxxHelpers::Id(NaxxNpcs::NPC_WEB_WRAP) });
    }

    std::vector<uint32> const _entries;
};

// Whether Gothik's inner gate stands open, which is what decides whether the other half of his
// room can be walked into at all.
class NaxxGothikGateOpenValue : public BoolCalculatedValue
{
public:
    NaxxGothikGateOpenValue(PlayerbotAI* botAI)
        : BoolCalculatedValue(
              botAI, NaxxHelpers::GOTHIK_GATE_OPEN_VALUE, NaxxHelpers::NAXX_CACHE_INTERVAL_MS) {}

protected:
    bool Calculate() override
    {
        return NaxxHelpers::IsGameObjectOpen(
            bot, NaxxHelpers::GO_GOTHIK_INNER_GATE, NaxxHelpers::GATE_SEARCH_RADIUS);
    }
};

class RaidNaxxValueContext : public NamedObjectContext<UntypedValue>
{
public:
    RaidNaxxValueContext()
    {
        creators[NaxxHelpers::FAERLINA_ADDS_VALUE] = &RaidNaxxValueContext::faerlina_adds;
        creators[NaxxHelpers::MAEXXNA_ADDS_VALUE] = &RaidNaxxValueContext::maexxna_adds;
        creators[NaxxHelpers::NOTH_SKELETONS_VALUE] = &RaidNaxxValueContext::noth_skeletons;
        creators[NaxxHelpers::GOTHIK_LIVING_ADDS_VALUE] = &RaidNaxxValueContext::gothik_living_adds;
        creators[NaxxHelpers::GOTHIK_DEAD_ADDS_VALUE] = &RaidNaxxValueContext::gothik_dead_adds;
        creators[NaxxHelpers::GOTHIK_GATE_OPEN_VALUE] = &RaidNaxxValueContext::gothik_gate_open;
    }

private:
    using NaxxNpcs = NaxxHelpers::NaxxNpcs;

    // All three of Noth's wave creatures in one value: the ground phase only ever brings Plagued
    // Warriors, but a balcony wave can be alive while the next ground phase runs, and the raid
    // kills whichever of them is nearest. None of the three has a single static spawn in the world
    // database, so everything this finds belongs to the fight.
    static UntypedValue* noth_skeletons(PlayerbotAI* botAI)
    {
        return new NaxxCreatureGuidsValue(
            botAI, NaxxHelpers::NOTH_SKELETONS_VALUE,
            { NaxxHelpers::Id(NaxxNpcs::NPC_PLAGUED_WARRIOR),
              NaxxHelpers::Id(NaxxNpcs::NPC_PLAGUED_CHAMPION),
              NaxxHelpers::Id(NaxxNpcs::NPC_PLAGUED_GUARDIAN) });
    }
    static UntypedValue* gothik_living_adds(PlayerbotAI* botAI)
    {
        return new NaxxCreatureGuidsValue(
            botAI, NaxxHelpers::GOTHIK_LIVING_ADDS_VALUE,
            { NaxxHelpers::Id(NaxxNpcs::NPC_UNRELENTING_TRAINEE),
              NaxxHelpers::Id(NaxxNpcs::NPC_UNRELENTING_DEATH_KNIGHT),
              NaxxHelpers::Id(NaxxNpcs::NPC_UNRELENTING_RIDER) });
    }
    static UntypedValue* gothik_dead_adds(PlayerbotAI* botAI)
    {
        return new NaxxCreatureGuidsValue(
            botAI, NaxxHelpers::GOTHIK_DEAD_ADDS_VALUE,
            { NaxxHelpers::Id(NaxxNpcs::NPC_SPECTRAL_TRAINEE),
              NaxxHelpers::Id(NaxxNpcs::NPC_SPECTRAL_DEATH_KNIGHT),
              NaxxHelpers::Id(NaxxNpcs::NPC_SPECTRAL_HORSE),
              NaxxHelpers::Id(NaxxNpcs::NPC_SPECTRAL_RIDER) });
    }
    static UntypedValue* gothik_gate_open(PlayerbotAI* botAI)
    {
        return new NaxxGothikGateOpenValue(botAI);
    }
};

#endif
