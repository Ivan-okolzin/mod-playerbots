/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#ifndef PLAYERBOTS_VOAVALUECONTEXT_H
#define PLAYERBOTS_VOAVALUECONTEXT_H

#include "EncounterHelpers.h"
#include "NamedObjectContext.h"
#include "Position.h"
#include "Value.h"
#include "VoAHelpers.h"
#include <string>
#include <vector>

// The adds of this raid are searched once per cache interval instead of once per trigger: four
// Tempest Minions and up to three Frozen Orbs are looked at by several objects on every tick.
class VoACreatureGuidsValue : public CalculatedValue<GuidVector>
{
public:
    VoACreatureGuidsValue(
        PlayerbotAI* botAI, std::string const& name, std::vector<uint32> const& entries)
        : CalculatedValue<GuidVector>(botAI, name, VoAHelpers::VOA_CACHE_INTERVAL_MS),
          _entries(entries) {}

protected:
    GuidVector Calculate() override
    {
        return VoAHelpers::FindCreatureGuids(bot, _entries, VoAHelpers::ADD_SEARCH_RADIUS);
    }

private:
    std::vector<uint32> const _entries;
};

// Freezing Ground is left on the floor by a spell and not by a creature, so it is found as the
// spell's dynamic object.
class VoAHazardPositionsValue : public CalculatedValue<std::vector<Position>>
{
public:
    VoAHazardPositionsValue(PlayerbotAI* botAI, std::string const& name, uint32 spellId)
        : CalculatedValue<std::vector<Position>>(botAI, name, VoAHelpers::VOA_CACHE_INTERVAL_MS),
          _spellId(spellId) {}

protected:
    std::vector<Position> Calculate() override
    {
        return EncounterHelpers::GetDynamicObjectPositions(
            bot, VoAHelpers::HAZARD_SEARCH_RADIUS, _spellId);
    }

private:
    uint32 const _spellId;
};

class RaidVoAValueContext : public NamedObjectContext<UntypedValue>
{
public:
    RaidVoAValueContext()
    {
        creators[VoAHelpers::EMALON_MINIONS_VALUE] = &RaidVoAValueContext::emalon_minions;
        creators[VoAHelpers::TORAVON_FROZEN_ORBS_VALUE] = &RaidVoAValueContext::toravon_frozen_orbs;
        creators[VoAHelpers::TORAVON_FREEZING_GROUND_VALUE] =
            &RaidVoAValueContext::toravon_freezing_ground;
    }

private:
    // Both entries of the minion: the 25-man raid summons difficulty_entry_1 of 33998 instead.
    static UntypedValue* emalon_minions(PlayerbotAI* botAI)
    {
        return new VoACreatureGuidsValue(
            botAI, VoAHelpers::EMALON_MINIONS_VALUE,
            { VoAHelpers::Id(VoAHelpers::VoANpcs::NPC_TEMPEST_MINION),
              VoAHelpers::Id(VoAHelpers::VoANpcs::NPC_TEMPEST_MINION_25) });
    }
    static UntypedValue* toravon_frozen_orbs(PlayerbotAI* botAI)
    {
        return new VoACreatureGuidsValue(
            botAI, VoAHelpers::TORAVON_FROZEN_ORBS_VALUE,
            { VoAHelpers::Id(VoAHelpers::VoANpcs::NPC_FROZEN_ORB) });
    }
    static UntypedValue* toravon_freezing_ground(PlayerbotAI* botAI)
    {
        return new VoAHazardPositionsValue(
            botAI, VoAHelpers::TORAVON_FREEZING_GROUND_VALUE,
            VoAHelpers::Id(VoAHelpers::VoASpells::SPELL_FREEZING_GROUND));
    }
};

#endif
