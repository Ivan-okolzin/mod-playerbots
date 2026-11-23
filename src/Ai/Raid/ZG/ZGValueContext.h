/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#ifndef PLAYERBOTS_ZGVALUECONTEXT_H
#define PLAYERBOTS_ZGVALUECONTEXT_H

#include "EncounterHelpers.h"
#include "NamedObjectContext.h"
#include "Position.h"
#include "Value.h"
#include "ZGHelpers.h"
#include <string>
#include <vector>

class ZulGurubCreatureGuidsValue : public CalculatedValue<GuidVector>
{
public:
    ZulGurubCreatureGuidsValue(
        PlayerbotAI* botAI, std::string const& name, std::vector<uint32> const& entries,
        float radius = ZulGurubHelpers::ADD_SEARCH_RADIUS, bool summonsOnly = false)
        : CalculatedValue<GuidVector>(botAI, name, ZulGurubHelpers::ZG_CACHE_INTERVAL_MS),
          _entries(entries), _radius(radius), _summonsOnly(summonsOnly) {}

protected:
    GuidVector Calculate() override
    {
        return ZulGurubHelpers::FindCreatureGuids(bot, _entries, _radius, _summonsOnly);
    }

private:
    std::vector<uint32> const _entries;
    float const _radius;
    bool const _summonsOnly;
};

class ZulGurubHazardPositionsValue : public CalculatedValue<std::vector<Position>>
{
public:
    ZulGurubHazardPositionsValue(PlayerbotAI* botAI, std::string const& name, uint32 spellId)
        : CalculatedValue<std::vector<Position>>(
              botAI, name, ZulGurubHelpers::ZG_CACHE_INTERVAL_MS),
          _spellId(spellId) {}

protected:
    std::vector<Position> Calculate() override
    {
        return EncounterHelpers::GetDynamicObjectPositions(
            bot, ZulGurubHelpers::HAZARD_SEARCH_RADIUS, _spellId);
    }

private:
    uint32 const _spellId;
};

// Jeklik's bombs land as trap objects rather than as spell areas, so they need the game object
// counterpart of the hazard value.
class ZulGurubTrapPositionsValue : public CalculatedValue<std::vector<Position>>
{
public:
    ZulGurubTrapPositionsValue(PlayerbotAI* botAI, std::string const& name, uint32 entry)
        : CalculatedValue<std::vector<Position>>(
              botAI, name, ZulGurubHelpers::ZG_CACHE_INTERVAL_MS),
          _entry(entry) {}

protected:
    std::vector<Position> Calculate() override
    {
        return ZulGurubHelpers::FindGameObjectPositions(
            bot, _entry, ZulGurubHelpers::HAZARD_SEARCH_RADIUS);
    }

private:
    uint32 const _entry;
};

class RaidZulGurubValueContext : public NamedObjectContext<UntypedValue>
{
public:
    RaidZulGurubValueContext()
    {
        creators[ZulGurubHelpers::VENOXIS_SERPENTS_VALUE] =
            &RaidZulGurubValueContext::venoxis_serpents;
        creators[ZulGurubHelpers::VENOXIS_POISON_CLOUD_VALUE] =
            &RaidZulGurubValueContext::venoxis_poison_cloud;
        creators[ZulGurubHelpers::JEKLIK_BATS_VALUE] = &RaidZulGurubValueContext::jeklik_bats;
        creators[ZulGurubHelpers::JEKLIK_LIQUID_FIRE_VALUE] =
            &RaidZulGurubValueContext::jeklik_liquid_fire;
        creators[ZulGurubHelpers::MARLI_SPAWNS_VALUE] = &RaidZulGurubValueContext::marli_spawns;
        creators[ZulGurubHelpers::MANDOKIR_OHGAN_VALUE] = &RaidZulGurubValueContext::mandokir_ohgan;
        creators[ZulGurubHelpers::THEKAL_TRIO_VALUE] = &RaidZulGurubValueContext::thekal_trio;
        creators[ZulGurubHelpers::THEKAL_TIGERS_VALUE] = &RaidZulGurubValueContext::thekal_tigers;
        creators[ZulGurubHelpers::ARLOKK_PROWLERS_VALUE] =
            &RaidZulGurubValueContext::arlokk_prowlers;
        creators[ZulGurubHelpers::JINDO_HEALING_WARDS_VALUE] =
            &RaidZulGurubValueContext::jindo_healing_wards;
        creators[ZulGurubHelpers::JINDO_BRAIN_WASH_TOTEMS_VALUE] =
            &RaidZulGurubValueContext::jindo_brain_wash_totems;
        creators[ZulGurubHelpers::JINDO_SHADES_VALUE] = &RaidZulGurubValueContext::jindo_shades;
        creators[ZulGurubHelpers::HAZZARAH_ILLUSIONS_VALUE] =
            &RaidZulGurubValueContext::hazzarah_illusions;
        creators[ZulGurubHelpers::WUSHOOLAY_LIGHTNING_CLOUD_VALUE] =
            &RaidZulGurubValueContext::wushoolay_lightning_cloud;
        creators[ZulGurubHelpers::POISONOUS_CLOUDS_VALUE] =
            &RaidZulGurubValueContext::poisonous_clouds;
    }

private:
    static UntypedValue* venoxis_serpents(PlayerbotAI* botAI)
    {
        return new ZulGurubCreatureGuidsValue(
            botAI, ZulGurubHelpers::VENOXIS_SERPENTS_VALUE,
            { ZulGurubHelpers::Id(ZulGurubHelpers::ZulGurubNpcs::NPC_PARASITIC_SERPENT) });
    }
    static UntypedValue* venoxis_poison_cloud(PlayerbotAI* botAI)
    {
        return new ZulGurubHazardPositionsValue(
            botAI, ZulGurubHelpers::VENOXIS_POISON_CLOUD_VALUE,
            ZulGurubHelpers::Id(ZulGurubHelpers::ZulGurubSpells::SPELL_POISON_CLOUD));
    }
    // Bloodseeker Bats are also instance trash, so only Jeklik's own summons count.
    static UntypedValue* jeklik_bats(PlayerbotAI* botAI)
    {
        constexpr bool summonsOnly = true;
        return new ZulGurubCreatureGuidsValue(
            botAI, ZulGurubHelpers::JEKLIK_BATS_VALUE,
            { ZulGurubHelpers::Id(ZulGurubHelpers::ZulGurubNpcs::NPC_BLOODSEEKER_BAT) },
            ZulGurubHelpers::ADD_SEARCH_RADIUS, summonsOnly);
    }
    static UntypedValue* jeklik_liquid_fire(PlayerbotAI* botAI)
    {
        return new ZulGurubTrapPositionsValue(
            botAI, ZulGurubHelpers::JEKLIK_LIQUID_FIRE_VALUE, ZulGurubHelpers::GO_LIQUID_FIRE);
    }
    static UntypedValue* marli_spawns(PlayerbotAI* botAI)
    {
        return new ZulGurubCreatureGuidsValue(
            botAI, ZulGurubHelpers::MARLI_SPAWNS_VALUE,
            { ZulGurubHelpers::Id(ZulGurubHelpers::ZulGurubNpcs::NPC_SPAWN_OF_MARLI) });
    }
    // Ohgan is a plain ScriptedAI and never zones the raid into combat, so he is found by search
    // rather than on a threat list.
    static UntypedValue* mandokir_ohgan(PlayerbotAI* botAI)
    {
        return new ZulGurubCreatureGuidsValue(
            botAI, ZulGurubHelpers::MANDOKIR_OHGAN_VALUE,
            { ZulGurubHelpers::Id(ZulGurubHelpers::ZulGurubNpcs::NPC_OHGAN) });
    }
    // The two zealots are ScriptedAI as well, and the trio's health bars have to be compared.
    static UntypedValue* thekal_trio(PlayerbotAI* botAI)
    {
        return new ZulGurubCreatureGuidsValue(
            botAI, ZulGurubHelpers::THEKAL_TRIO_VALUE,
            { ZulGurubHelpers::Id(ZulGurubHelpers::ZulGurubNpcs::NPC_THEKAL),
              ZulGurubHelpers::Id(ZulGurubHelpers::ZulGurubNpcs::NPC_ZEALOT_LORKHAN),
              ZulGurubHelpers::Id(ZulGurubHelpers::ZulGurubNpcs::NPC_ZEALOT_ZATH) });
    }
    // Zulian Tigers are also instance trash, so only Thekal's own summons count.
    static UntypedValue* thekal_tigers(PlayerbotAI* botAI)
    {
        constexpr bool summonsOnly = true;
        return new ZulGurubCreatureGuidsValue(
            botAI, ZulGurubHelpers::THEKAL_TIGERS_VALUE,
            { ZulGurubHelpers::Id(ZulGurubHelpers::ZulGurubNpcs::NPC_ZULGURUB_TIGER) },
            ZulGurubHelpers::ADD_SEARCH_RADIUS, summonsOnly);
    }
    static UntypedValue* arlokk_prowlers(PlayerbotAI* botAI)
    {
        return new ZulGurubCreatureGuidsValue(
            botAI, ZulGurubHelpers::ARLOKK_PROWLERS_VALUE,
            { ZulGurubHelpers::Id(ZulGurubHelpers::ZulGurubNpcs::NPC_ZULIAN_PROWLER) });
    }
    static UntypedValue* jindo_healing_wards(PlayerbotAI* botAI)
    {
        return new ZulGurubCreatureGuidsValue(
            botAI, ZulGurubHelpers::JINDO_HEALING_WARDS_VALUE,
            { ZulGurubHelpers::NPC_POWERFUL_HEALING_WARD });
    }
    static UntypedValue* jindo_brain_wash_totems(PlayerbotAI* botAI)
    {
        return new ZulGurubCreatureGuidsValue(
            botAI, ZulGurubHelpers::JINDO_BRAIN_WASH_TOTEMS_VALUE,
            { ZulGurubHelpers::Id(ZulGurubHelpers::ZulGurubNpcs::NPC_BRAIN_WASH_TOTEM) });
    }
    static UntypedValue* jindo_shades(PlayerbotAI* botAI)
    {
        return new ZulGurubCreatureGuidsValue(
            botAI, ZulGurubHelpers::JINDO_SHADES_VALUE,
            { ZulGurubHelpers::Id(ZulGurubHelpers::ZulGurubNpcs::NPC_SHADE_OF_JINDO) });
    }
    static UntypedValue* hazzarah_illusions(PlayerbotAI* botAI)
    {
        return new ZulGurubCreatureGuidsValue(
            botAI, ZulGurubHelpers::HAZZARAH_ILLUSIONS_VALUE,
            { ZulGurubHelpers::Id(ZulGurubHelpers::ZulGurubNpcs::NPC_NIGHTMARE_ILLUSION) });
    }
    static UntypedValue* wushoolay_lightning_cloud(PlayerbotAI* botAI)
    {
        return new ZulGurubHazardPositionsValue(
            botAI, ZulGurubHelpers::WUSHOOLAY_LIGHTNING_CLOUD_VALUE,
            ZulGurubHelpers::Id(ZulGurubHelpers::ZulGurubSpells::SPELL_LIGHTNING_CLOUD));
    }
    // The clouds a dying Son of Hakkar leaves behind, searched only as far as a bot would walk
    // for one.
    static UntypedValue* poisonous_clouds(PlayerbotAI* botAI)
    {
        return new ZulGurubCreatureGuidsValue(
            botAI, ZulGurubHelpers::POISONOUS_CLOUDS_VALUE,
            { ZulGurubHelpers::Id(ZulGurubHelpers::ZulGurubNpcs::NPC_POISONOUS_CLOUD) },
            ZulGurubHelpers::POISON_PICKUP_SEARCH_RADIUS);
    }
};

#endif
