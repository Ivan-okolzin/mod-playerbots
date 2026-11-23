/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#ifndef PLAYERBOTS_SWPVALUECONTEXT_H
#define PLAYERBOTS_SWPVALUECONTEXT_H

#include "NamedObjectContext.h"
#include "SWPHelpers.h"
#include "Value.h"
#include <string>
#include <vector>

class SwpCreatureGuidsValue : public CalculatedValue<GuidVector>
{
public:
    SwpCreatureGuidsValue(
        PlayerbotAI* botAI, std::string const& name, std::vector<uint32> const& entries)
        : CalculatedValue<GuidVector>(botAI, name, SwpHelpers::SWP_CACHE_INTERVAL_MS),
          _entries(entries) {}

protected:
    GuidVector Calculate() override
    {
        return SwpHelpers::FindCreatureGuids(bot, _entries, SwpHelpers::ADD_SEARCH_RADIUS);
    }

private:
    std::vector<uint32> const _entries;
};

class RaidSwpValueContext : public NamedObjectContext<UntypedValue>
{
public:
    RaidSwpValueContext()
    {
        creators[SwpHelpers::FELMYST_UNYIELDING_DEAD_VALUE] =
            &RaidSwpValueContext::felmyst_unyielding_dead;
        creators[SwpHelpers::FELMYST_VAPOR_TRAILS_VALUE] =
            &RaidSwpValueContext::felmyst_vapor_trails;
        creators[SwpHelpers::MURU_DARK_FIENDS_VALUE] = &RaidSwpValueContext::muru_dark_fiends;
        creators[SwpHelpers::MURU_VOID_SENTINELS_VALUE] =
            &RaidSwpValueContext::muru_void_sentinels;
        creators[SwpHelpers::MURU_ADDS_VALUE] = &RaidSwpValueContext::muru_adds;
        creators[SwpHelpers::MURU_DARKNESS_VALUE] = &RaidSwpValueContext::muru_darkness;
        creators[SwpHelpers::ENTROPIUS_SINGULARITIES_VALUE] =
            &RaidSwpValueContext::entropius_singularities;
        creators[SwpHelpers::KILJAEDEN_SHIELD_ORBS_VALUE] =
            &RaidSwpValueContext::kiljaeden_shield_orbs;
        creators[SwpHelpers::KILJAEDEN_REFLECTIONS_VALUE] =
            &RaidSwpValueContext::kiljaeden_reflections;
        creators[SwpHelpers::KILJAEDEN_HANDS_VALUE] = &RaidSwpValueContext::kiljaeden_hands;
        creators[SwpHelpers::KILJAEDEN_ARMAGEDDON_VALUE] =
            &RaidSwpValueContext::kiljaeden_armageddon;
    }

private:
    static UntypedValue* felmyst_unyielding_dead(PlayerbotAI* botAI)
    {
        return new SwpCreatureGuidsValue(
            botAI, SwpHelpers::FELMYST_UNYIELDING_DEAD_VALUE,
            { SwpHelpers::Id(SwpHelpers::SwpNpcs::NPC_UNYIELDING_DEAD) });
    }
    static UntypedValue* felmyst_vapor_trails(PlayerbotAI* botAI)
    {
        return new SwpCreatureGuidsValue(
            botAI, SwpHelpers::FELMYST_VAPOR_TRAILS_VALUE,
            { SwpHelpers::Id(SwpHelpers::SwpNpcs::NPC_DEMONIC_VAPOR_TRAIL) });
    }
    static UntypedValue* muru_dark_fiends(PlayerbotAI* botAI)
    {
        return new SwpCreatureGuidsValue(
            botAI, SwpHelpers::MURU_DARK_FIENDS_VALUE,
            { SwpHelpers::Id(SwpHelpers::SwpNpcs::NPC_DARK_FIEND) });
    }
    static UntypedValue* muru_void_sentinels(PlayerbotAI* botAI)
    {
        return new SwpCreatureGuidsValue(
            botAI, SwpHelpers::MURU_VOID_SENTINELS_VALUE,
            { SwpHelpers::Id(SwpHelpers::SwpNpcs::NPC_VOID_SENTINEL) });
    }
    // The blood elves M'uru keeps summoning, plus the Void Spawns a dead Sentinel leaves behind.
    static UntypedValue* muru_adds(PlayerbotAI* botAI)
    {
        return new SwpCreatureGuidsValue(
            botAI, SwpHelpers::MURU_ADDS_VALUE,
            { SwpHelpers::Id(SwpHelpers::SwpNpcs::NPC_SHADOWSWORD_BERSERKER),
              SwpHelpers::Id(SwpHelpers::SwpNpcs::NPC_SHADOWSWORD_FURY_MAGE),
              SwpHelpers::Id(SwpHelpers::SwpNpcs::NPC_VOID_SPAWN) });
    }
    static UntypedValue* muru_darkness(PlayerbotAI* botAI)
    {
        return new SwpCreatureGuidsValue(
            botAI, SwpHelpers::MURU_DARKNESS_VALUE,
            { SwpHelpers::Id(SwpHelpers::SwpNpcs::NPC_DARKNESS) });
    }
    static UntypedValue* entropius_singularities(PlayerbotAI* botAI)
    {
        return new SwpCreatureGuidsValue(
            botAI, SwpHelpers::ENTROPIUS_SINGULARITIES_VALUE,
            { SwpHelpers::Id(SwpHelpers::SwpNpcs::NPC_SINGULARITY) });
    }
    static UntypedValue* kiljaeden_shield_orbs(PlayerbotAI* botAI)
    {
        return new SwpCreatureGuidsValue(
            botAI, SwpHelpers::KILJAEDEN_SHIELD_ORBS_VALUE,
            { SwpHelpers::Id(SwpHelpers::SwpNpcs::NPC_SHIELD_ORB) });
    }
    static UntypedValue* kiljaeden_reflections(PlayerbotAI* botAI)
    {
        return new SwpCreatureGuidsValue(
            botAI, SwpHelpers::KILJAEDEN_REFLECTIONS_VALUE,
            { SwpHelpers::Id(SwpHelpers::SwpNpcs::NPC_SINISTER_REFLECTION) });
    }
    static UntypedValue* kiljaeden_hands(PlayerbotAI* botAI)
    {
        return new SwpCreatureGuidsValue(
            botAI, SwpHelpers::KILJAEDEN_HANDS_VALUE,
            { SwpHelpers::Id(SwpHelpers::SwpNpcs::NPC_HAND_OF_THE_DECEIVER) });
    }
    // Armageddon Targets are the markers the meteors land on.
    static UntypedValue* kiljaeden_armageddon(PlayerbotAI* botAI)
    {
        return new SwpCreatureGuidsValue(
            botAI, SwpHelpers::KILJAEDEN_ARMAGEDDON_VALUE,
            { SwpHelpers::Id(SwpHelpers::SwpNpcs::NPC_ARMAGEDDON_TARGET) });
    }
};

#endif
