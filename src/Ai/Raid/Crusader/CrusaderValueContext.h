/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#ifndef PLAYERBOTS_CRUSADERVALUECONTEXT_H
#define PLAYERBOTS_CRUSADERVALUECONTEXT_H

#include "CrusaderHelpers.h"
#include "NamedObjectContext.h"
#include "Value.h"
#include <string>
#include <vector>

class CrusaderCreatureGuidsValue : public CalculatedValue<GuidVector>
{
public:
    CrusaderCreatureGuidsValue(
        PlayerbotAI* botAI, std::string const& name, std::vector<uint32> const& entries)
        : CalculatedValue<GuidVector>(botAI, name, CrusaderHelpers::CRUSADER_CACHE_INTERVAL_MS),
          _entries(entries) {}

protected:
    GuidVector Calculate() override
    {
        return CrusaderHelpers::FindCreatureGuids(
            bot, _entries, CrusaderHelpers::ADD_SEARCH_RADIUS);
    }

private:
    std::vector<uint32> const _entries;
};

class RaidCrusaderValueContext : public NamedObjectContext<UntypedValue>
{
public:
    RaidCrusaderValueContext()
    {
        creators[CrusaderHelpers::GORMOK_SNOBOLDS_VALUE] =
            &RaidCrusaderValueContext::gormok_snobolds;
        creators[CrusaderHelpers::JORMUNGAR_SLIME_POOLS_VALUE] =
            &RaidCrusaderValueContext::jormungar_slime_pools;
        creators[CrusaderHelpers::ICEHOWL_CHARGE_STALKERS_VALUE] =
            &RaidCrusaderValueContext::icehowl_charge_stalkers;
        creators[CrusaderHelpers::JARAXXUS_LEGION_FLAMES_VALUE] =
            &RaidCrusaderValueContext::jaraxxus_legion_flames;
        creators[CrusaderHelpers::JARAXXUS_DEMONS_VALUE] =
            &RaidCrusaderValueContext::jaraxxus_demons;
        creators[CrusaderHelpers::VALKYR_ESSENCES_VALUE] =
            &RaidCrusaderValueContext::valkyr_essences;
        creators[CrusaderHelpers::VALKYR_LIGHT_BALLS_VALUE] =
            &RaidCrusaderValueContext::valkyr_light_balls;
        creators[CrusaderHelpers::VALKYR_DARK_BALLS_VALUE] =
            &RaidCrusaderValueContext::valkyr_dark_balls;
        creators[CrusaderHelpers::ANUBARAK_BURROWERS_VALUE] =
            &RaidCrusaderValueContext::anubarak_burrowers;
        creators[CrusaderHelpers::ANUBARAK_SCARABS_VALUE] =
            &RaidCrusaderValueContext::anubarak_scarabs;
        creators[CrusaderHelpers::ANUBARAK_FROST_SPHERES_VALUE] =
            &RaidCrusaderValueContext::anubarak_frost_spheres;
        creators[CrusaderHelpers::ANUBARAK_SPIKES_VALUE] =
            &RaidCrusaderValueContext::anubarak_spikes;
    }

private:
    static UntypedValue* gormok_snobolds(PlayerbotAI* botAI)
    {
        return new CrusaderCreatureGuidsValue(
            botAI, CrusaderHelpers::GORMOK_SNOBOLDS_VALUE,
            { CrusaderHelpers::Id(CrusaderHelpers::CrusaderNpcs::NPC_SNOBOLD_VASSAL) });
    }
    static UntypedValue* jormungar_slime_pools(PlayerbotAI* botAI)
    {
        return new CrusaderCreatureGuidsValue(
            botAI, CrusaderHelpers::JORMUNGAR_SLIME_POOLS_VALUE,
            { CrusaderHelpers::Id(CrusaderHelpers::CrusaderNpcs::NPC_SLIME_POOL) });
    }
    // The stalker stands where the player Icehowl glared at was, and marks the charge lane.
    static UntypedValue* icehowl_charge_stalkers(PlayerbotAI* botAI)
    {
        return new CrusaderCreatureGuidsValue(
            botAI, CrusaderHelpers::ICEHOWL_CHARGE_STALKERS_VALUE,
            { CrusaderHelpers::Id(CrusaderHelpers::CrusaderNpcs::NPC_FURIOUS_CHARGE_STALKER) });
    }
    static UntypedValue* jaraxxus_legion_flames(PlayerbotAI* botAI)
    {
        return new CrusaderCreatureGuidsValue(
            botAI, CrusaderHelpers::JARAXXUS_LEGION_FLAMES_VALUE,
            { CrusaderHelpers::Id(CrusaderHelpers::CrusaderNpcs::NPC_LEGION_FLAME) });
    }
    // Mistress of Pain out of a Nether Portal and the Felflame Infernals out of a Volcano: the
    // two things Jaraxxus summons that can be fought at all.
    static UntypedValue* jaraxxus_demons(PlayerbotAI* botAI)
    {
        return new CrusaderCreatureGuidsValue(
            botAI, CrusaderHelpers::JARAXXUS_DEMONS_VALUE,
            { CrusaderHelpers::Id(CrusaderHelpers::CrusaderNpcs::NPC_MISTRESS_OF_PAIN),
              CrusaderHelpers::Id(CrusaderHelpers::CrusaderNpcs::NPC_FELFLAME_INFERNAL) });
    }
    // Both colours in one value: a bot walks up to the one that matches its own colour, so the
    // entry is picked at use time.
    static UntypedValue* valkyr_essences(PlayerbotAI* botAI)
    {
        return new CrusaderCreatureGuidsValue(
            botAI, CrusaderHelpers::VALKYR_ESSENCES_VALUE,
            { CrusaderHelpers::Id(CrusaderHelpers::CrusaderNpcs::NPC_LIGHT_ESSENCE),
              CrusaderHelpers::Id(CrusaderHelpers::CrusaderNpcs::NPC_DARK_ESSENCE) });
    }
    static UntypedValue* valkyr_light_balls(PlayerbotAI* botAI)
    {
        return new CrusaderCreatureGuidsValue(
            botAI, CrusaderHelpers::VALKYR_LIGHT_BALLS_VALUE,
            { CrusaderHelpers::Id(CrusaderHelpers::CrusaderNpcs::NPC_CONCENTRATED_LIGHT) });
    }
    static UntypedValue* valkyr_dark_balls(PlayerbotAI* botAI)
    {
        return new CrusaderCreatureGuidsValue(
            botAI, CrusaderHelpers::VALKYR_DARK_BALLS_VALUE,
            { CrusaderHelpers::Id(CrusaderHelpers::CrusaderNpcs::NPC_CONCENTRATED_DARKNESS) });
    }
    static UntypedValue* anubarak_burrowers(PlayerbotAI* botAI)
    {
        return new CrusaderCreatureGuidsValue(
            botAI, CrusaderHelpers::ANUBARAK_BURROWERS_VALUE,
            { CrusaderHelpers::Id(CrusaderHelpers::CrusaderNpcs::NPC_NERUBIAN_BURROWER) });
    }
    static UntypedValue* anubarak_scarabs(PlayerbotAI* botAI)
    {
        return new CrusaderCreatureGuidsValue(
            botAI, CrusaderHelpers::ANUBARAK_SCARABS_VALUE,
            { CrusaderHelpers::Id(CrusaderHelpers::CrusaderNpcs::NPC_SWARM_SCARAB) });
    }
    // Both the spheres still hovering and the Permafrost patches they turn into: the script keeps
    // them alive either way (BAT:560), and height tells the two apart.
    static UntypedValue* anubarak_frost_spheres(PlayerbotAI* botAI)
    {
        return new CrusaderCreatureGuidsValue(
            botAI, CrusaderHelpers::ANUBARAK_FROST_SPHERES_VALUE,
            { CrusaderHelpers::Id(CrusaderHelpers::CrusaderNpcs::NPC_FROST_SPHERE) });
    }
    static UntypedValue* anubarak_spikes(PlayerbotAI* botAI)
    {
        return new CrusaderCreatureGuidsValue(
            botAI, CrusaderHelpers::ANUBARAK_SPIKES_VALUE,
            { CrusaderHelpers::Id(CrusaderHelpers::CrusaderNpcs::NPC_PURSUING_SPIKE) });
    }
};

#endif
