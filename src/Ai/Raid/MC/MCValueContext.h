/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#ifndef PLAYERBOTS_MCVALUECONTEXT_H
#define PLAYERBOTS_MCVALUECONTEXT_H

#include "EncounterHelpers.h"
#include "MCHelpers.h"
#include "NamedObjectContext.h"
#include "Position.h"
#include "Value.h"
#include <string>
#include <vector>

class McCreatureGuidsValue : public CalculatedValue<GuidVector>
{
public:
    McCreatureGuidsValue(
        PlayerbotAI* botAI, std::string const& name, std::vector<uint32> const& entries)
        : CalculatedValue<GuidVector>(botAI, name, MoltenCoreHelpers::MC_CACHE_INTERVAL_MS),
          _entries(entries) {}

protected:
    GuidVector Calculate() override
    {
        return MoltenCoreHelpers::FindCreatureGuids(
            bot, _entries, MoltenCoreHelpers::ADD_SEARCH_RADIUS);
    }

private:
    std::vector<uint32> const _entries;
};

// A hazard the raid walks out of that is a dynamic object, i.e. the ground area of a spell.
class McSpellHazardPositionsValue : public CalculatedValue<std::vector<Position>>
{
public:
    McSpellHazardPositionsValue(PlayerbotAI* botAI, std::string const& name, uint32 spellId)
        : CalculatedValue<std::vector<Position>>(
              botAI, name, MoltenCoreHelpers::MC_CACHE_INTERVAL_MS),
          _spellId(spellId) {}

protected:
    std::vector<Position> Calculate() override
    {
        return EncounterHelpers::GetDynamicObjectPositions(
            bot, MoltenCoreHelpers::HAZARD_SEARCH_RADIUS, _spellId);
    }

private:
    uint32 const _spellId;
};

// Molten Core's two fire patches on the floor are game object traps rather than dynamic objects,
// so they are found by game object entry.
class McGameObjectHazardPositionsValue : public CalculatedValue<std::vector<Position>>
{
public:
    McGameObjectHazardPositionsValue(
        PlayerbotAI* botAI, std::string const& name, std::vector<uint32> const& entries)
        : CalculatedValue<std::vector<Position>>(
              botAI, name, MoltenCoreHelpers::MC_CACHE_INTERVAL_MS),
          _entries(entries) {}

protected:
    std::vector<Position> Calculate() override
    {
        return MoltenCoreHelpers::FindGameObjectPositions(
            bot, _entries, MoltenCoreHelpers::HAZARD_SEARCH_RADIUS);
    }

private:
    std::vector<uint32> const _entries;
};

class RaidMcValueContext : public NamedObjectContext<UntypedValue>
{
public:
    RaidMcValueContext()
    {
        creators[MoltenCoreHelpers::BARON_GEDDON_VALUE] = &RaidMcValueContext::baron_geddon;
        creators[MoltenCoreHelpers::SHAZZRAH_VALUE] = &RaidMcValueContext::shazzrah;
        creators[MoltenCoreHelpers::MAJORDOMO_VALUE] = &RaidMcValueContext::majordomo;
        creators[MoltenCoreHelpers::RAGNAROS_VALUE] = &RaidMcValueContext::ragnaros;
        creators[MoltenCoreHelpers::LUCIFRON_PROTECTORS_VALUE] =
            &RaidMcValueContext::lucifron_protectors;
        creators[MoltenCoreHelpers::GEHENNAS_FLAMEWAKERS_VALUE] =
            &RaidMcValueContext::gehennas_flamewakers;
        creators[MoltenCoreHelpers::GARR_FIRESWORN_VALUE] = &RaidMcValueContext::garr_firesworn;
        creators[MoltenCoreHelpers::SULFURON_PRIESTS_VALUE] =
            &RaidMcValueContext::sulfuron_priests;
        creators[MoltenCoreHelpers::MAJORDOMO_ADDS_VALUE] = &RaidMcValueContext::majordomo_adds;
        creators[MoltenCoreHelpers::RAGNAROS_SONS_OF_FLAME_VALUE] =
            &RaidMcValueContext::ragnaros_sons_of_flame;
        creators[MoltenCoreHelpers::MAGMADAR_LAVA_BOMBS_VALUE] =
            &RaidMcValueContext::magmadar_lava_bombs;
        creators[MoltenCoreHelpers::GEHENNAS_RAIN_OF_FIRE_VALUE] =
            &RaidMcValueContext::gehennas_rain_of_fire;
        creators[MoltenCoreHelpers::RAGNAROS_LAVA_BURSTS_VALUE] =
            &RaidMcValueContext::ragnaros_lava_bursts;
    }

private:
    // Only the bosses that have to be found without the bot's threat list: Geddon for the healers
    // his auras burn, the other three because their scripts wipe their threat list.
    static UntypedValue* baron_geddon(PlayerbotAI* botAI)
    {
        return new McCreatureGuidsValue(
            botAI, MoltenCoreHelpers::BARON_GEDDON_VALUE, { MoltenCoreHelpers::NPC_BARON_GEDDON });
    }
    static UntypedValue* shazzrah(PlayerbotAI* botAI)
    {
        return new McCreatureGuidsValue(
            botAI, MoltenCoreHelpers::SHAZZRAH_VALUE, { MoltenCoreHelpers::NPC_SHAZZRAH });
    }
    static UntypedValue* majordomo(PlayerbotAI* botAI)
    {
        return new McCreatureGuidsValue(
            botAI, MoltenCoreHelpers::MAJORDOMO_VALUE,
            { MoltenCoreHelpers::NPC_MAJORDOMO_EXECUTUS });
    }
    static UntypedValue* ragnaros(PlayerbotAI* botAI)
    {
        return new McCreatureGuidsValue(
            botAI, MoltenCoreHelpers::RAGNAROS_VALUE, { MoltenCoreHelpers::NPC_RAGNAROS });
    }
    // Lucifron's two Flamewaker Protectors, which charm a raid member every few seconds
    // (SS 12119:0).
    static UntypedValue* lucifron_protectors(PlayerbotAI* botAI)
    {
        return new McCreatureGuidsValue(
            botAI, MoltenCoreHelpers::LUCIFRON_PROTECTORS_VALUE,
            { MoltenCoreHelpers::NPC_FLAMEWAKER_PROTECTOR });
    }
    static UntypedValue* gehennas_flamewakers(PlayerbotAI* botAI)
    {
        return new McCreatureGuidsValue(
            botAI, MoltenCoreHelpers::GEHENNAS_FLAMEWAKERS_VALUE,
            { MoltenCoreHelpers::NPC_FLAMEWAKER });
    }
    static UntypedValue* garr_firesworn(PlayerbotAI* botAI)
    {
        return new McCreatureGuidsValue(
            botAI, MoltenCoreHelpers::GARR_FIRESWORN_VALUE, { MoltenCoreHelpers::NPC_FIRESWORN });
    }
    static UntypedValue* sulfuron_priests(PlayerbotAI* botAI)
    {
        return new McCreatureGuidsValue(
            botAI, MoltenCoreHelpers::SULFURON_PRIESTS_VALUE,
            { MoltenCoreHelpers::NPC_FLAMEWAKER_PRIEST });
    }
    // Both kinds of Majordomo add in one value: his encounter ends when all eight are dead
    // (BMJ:264), so the raid treats them alike.
    static UntypedValue* majordomo_adds(PlayerbotAI* botAI)
    {
        return new McCreatureGuidsValue(
            botAI, MoltenCoreHelpers::MAJORDOMO_ADDS_VALUE,
            { MoltenCoreHelpers::NPC_FLAMEWAKER_HEALER, MoltenCoreHelpers::NPC_FLAMEWAKER_ELITE });
    }
    static UntypedValue* ragnaros_sons_of_flame(PlayerbotAI* botAI)
    {
        return new McCreatureGuidsValue(
            botAI, MoltenCoreHelpers::RAGNAROS_SONS_OF_FLAME_VALUE,
            { MoltenCoreHelpers::NPC_SON_OF_FLAME });
    }
    static UntypedValue* magmadar_lava_bombs(PlayerbotAI* botAI)
    {
        return new McGameObjectHazardPositionsValue(
            botAI, MoltenCoreHelpers::MAGMADAR_LAVA_BOMBS_VALUE,
            { MoltenCoreHelpers::GO_LAVA_BOMB });
    }
    static UntypedValue* gehennas_rain_of_fire(PlayerbotAI* botAI)
    {
        return new McSpellHazardPositionsValue(
            botAI, MoltenCoreHelpers::GEHENNAS_RAIN_OF_FIRE_VALUE,
            MoltenCoreHelpers::SPELL_RAIN_OF_FIRE);
    }
    static UntypedValue* ragnaros_lava_bursts(PlayerbotAI* botAI)
    {
        return new McGameObjectHazardPositionsValue(
            botAI, MoltenCoreHelpers::RAGNAROS_LAVA_BURSTS_VALUE,
            { MoltenCoreHelpers::GO_LAVA_BURST });
    }
};

#endif
