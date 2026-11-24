/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#ifndef PLAYERBOTS_ULDVALUECONTEXT_H
#define PLAYERBOTS_ULDVALUECONTEXT_H

#include "NamedObjectContext.h"
#include "UldHelpers.h"
#include "Value.h"
#include <string>
#include <vector>

// The adds and ground hazards of this raid are searched once per cache interval instead of once
// per trigger: XT-002 fills the room with robots and Algalon with stars, holes and constellations,
// and several objects look at the same ones on every tick.
class UldCreatureGuidsValue : public CalculatedValue<GuidVector>
{
public:
    UldCreatureGuidsValue(
        PlayerbotAI* botAI, std::string const& name, std::vector<uint32> const& entries)
        : CalculatedValue<GuidVector>(botAI, name, UldHelpers::ULD_CACHE_INTERVAL_MS),
          _entries(entries) {}

protected:
    GuidVector Calculate() override
    {
        return UldHelpers::FindCreatureGuids(bot, _entries, UldHelpers::ADD_SEARCH_RADIUS);
    }

private:
    std::vector<uint32> const _entries;
};

class RaidUlduarValueContext : public NamedObjectContext<UntypedValue>
{
public:
    RaidUlduarValueContext()
    {
        creators[UldHelpers::VEZAX_SARONITE_ANIMUS_VALUE] =
            &RaidUlduarValueContext::vezax_saronite_animus;
        creators[UldHelpers::FREYA_STRENGTHENED_IRON_ROOTS_VALUE] =
            &RaidUlduarValueContext::freya_strengthened_iron_roots;
        creators[UldHelpers::HODIR_PLAYER_ICE_VALUE] =
            &RaidUlduarValueContext::hodir_player_ice;
        creators[UldHelpers::XT002_HEARTS_VALUE] = &RaidUlduarValueContext::xt002_hearts;
        creators[UldHelpers::XT002_VOID_ZONES_VALUE] = &RaidUlduarValueContext::xt002_void_zones;
        creators[UldHelpers::XT002_LIFE_SPARKS_VALUE] = &RaidUlduarValueContext::xt002_life_sparks;
        creators[UldHelpers::XT002_SCRAPBOTS_VALUE] = &RaidUlduarValueContext::xt002_scrapbots;
        creators[UldHelpers::XT002_PUMMELLERS_VALUE] = &RaidUlduarValueContext::xt002_pummellers;
        creators[UldHelpers::XT002_BOOMBOTS_VALUE] = &RaidUlduarValueContext::xt002_boombots;
        creators[UldHelpers::IGNIS_CONSTRUCTS_VALUE] = &RaidUlduarValueContext::ignis_constructs;
        creators[UldHelpers::IGNIS_SCORCHED_GROUND_VALUE] =
            &RaidUlduarValueContext::ignis_scorched_ground;
        creators[UldHelpers::IGNIS_WATER_TRIGGERS_VALUE] =
            &RaidUlduarValueContext::ignis_water_triggers;
        creators[UldHelpers::AURIAYA_SENTRIES_VALUE] = &RaidUlduarValueContext::auriaya_sentries;
        creators[UldHelpers::AURIAYA_FERAL_DEFENDERS_VALUE] =
            &RaidUlduarValueContext::auriaya_feral_defenders;
        creators[UldHelpers::AURIAYA_SEEPING_ESSENCES_VALUE] =
            &RaidUlduarValueContext::auriaya_seeping_essences;
        creators[UldHelpers::ALGALON_COLLAPSING_STARS_VALUE] =
            &RaidUlduarValueContext::algalon_collapsing_stars;
        creators[UldHelpers::ALGALON_BLACK_HOLES_VALUE] =
            &RaidUlduarValueContext::algalon_black_holes;
        creators[UldHelpers::ALGALON_CONSTELLATIONS_VALUE] =
            &RaidUlduarValueContext::algalon_constellations;
        creators[UldHelpers::ALGALON_COSMIC_SMASH_VALUE] =
            &RaidUlduarValueContext::algalon_cosmic_smash_targets;
        creators[UldHelpers::ALGALON_DARK_MATTER_VALUE] =
            &RaidUlduarValueContext::algalon_dark_matter;
    }

private:
    // Both entries of every add: the 25-man raid spawns difficulty_entry_1 of the 10-man template
    // instead, and nothing tells a bot which raid size it is in.
    static UntypedValue* vezax_saronite_animus(PlayerbotAI* botAI)
    {
        return new UldCreatureGuidsValue(
            botAI, UldHelpers::VEZAX_SARONITE_ANIMUS_VALUE,
            { 33524, 34152 });
    }
    static UntypedValue* freya_strengthened_iron_roots(PlayerbotAI* botAI)
    {
        return new UldCreatureGuidsValue(
            botAI, UldHelpers::FREYA_STRENGTHENED_IRON_ROOTS_VALUE,
            { 33168, 33397 });
    }
    static UntypedValue* hodir_player_ice(PlayerbotAI* botAI)
    {
        return new UldCreatureGuidsValue(
            botAI, UldHelpers::HODIR_PLAYER_ICE_VALUE,
            { 32926, 33352 });
    }
    static UntypedValue* xt002_hearts(PlayerbotAI* botAI)
    {
        return new UldCreatureGuidsValue(
            botAI, UldHelpers::XT002_HEARTS_VALUE,
            { UldHelpers::Id(UldHelpers::UldNpcs::NPC_HEART_OF_DECONSTRUCTOR),
              UldHelpers::Id(UldHelpers::UldNpcs::NPC_HEART_OF_DECONSTRUCTOR_25) });
    }
    // One entry only: the Void Zone has no 25-man template of its own.
    static UntypedValue* xt002_void_zones(PlayerbotAI* botAI)
    {
        return new UldCreatureGuidsValue(
            botAI, UldHelpers::XT002_VOID_ZONES_VALUE,
            { UldHelpers::Id(UldHelpers::UldNpcs::NPC_XT_VOID_ZONE) });
    }
    static UntypedValue* xt002_life_sparks(PlayerbotAI* botAI)
    {
        return new UldCreatureGuidsValue(
            botAI, UldHelpers::XT002_LIFE_SPARKS_VALUE,
            { UldHelpers::Id(UldHelpers::UldNpcs::NPC_LIFE_SPARK),
              UldHelpers::Id(UldHelpers::UldNpcs::NPC_LIFE_SPARK_25) });
    }
    static UntypedValue* xt002_scrapbots(PlayerbotAI* botAI)
    {
        return new UldCreatureGuidsValue(
            botAI, UldHelpers::XT002_SCRAPBOTS_VALUE,
            { UldHelpers::Id(UldHelpers::UldNpcs::NPC_SCRAPBOT),
              UldHelpers::Id(UldHelpers::UldNpcs::NPC_SCRAPBOT_25) });
    }
    static UntypedValue* xt002_pummellers(PlayerbotAI* botAI)
    {
        return new UldCreatureGuidsValue(
            botAI, UldHelpers::XT002_PUMMELLERS_VALUE,
            { UldHelpers::Id(UldHelpers::UldNpcs::NPC_PUMMELLER),
              UldHelpers::Id(UldHelpers::UldNpcs::NPC_PUMMELLER_25) });
    }
    static UntypedValue* xt002_boombots(PlayerbotAI* botAI)
    {
        return new UldCreatureGuidsValue(
            botAI, UldHelpers::XT002_BOOMBOTS_VALUE,
            { UldHelpers::Id(UldHelpers::UldNpcs::NPC_BOOMBOT),
              UldHelpers::Id(UldHelpers::UldNpcs::NPC_BOOMBOT_25) });
    }
    static UntypedValue* ignis_constructs(PlayerbotAI* botAI)
    {
        return new UldCreatureGuidsValue(
            botAI, UldHelpers::IGNIS_CONSTRUCTS_VALUE,
            { UldHelpers::Id(UldHelpers::UldNpcs::NPC_IRON_CONSTRUCT),
              UldHelpers::Id(UldHelpers::UldNpcs::NPC_IRON_CONSTRUCT_25) });
    }
    static UntypedValue* ignis_scorched_ground(PlayerbotAI* botAI)
    {
        return new UldCreatureGuidsValue(
            botAI, UldHelpers::IGNIS_SCORCHED_GROUND_VALUE,
            { UldHelpers::Id(UldHelpers::UldNpcs::NPC_SCORCHED_GROUND) });
    }
    // The water of the Ignis room, which is what turns a Molten construct Brittle (BIG:162). The
    // entry is a generic world trigger, but map 603 spawns only the two in his pools.
    static UntypedValue* ignis_water_triggers(PlayerbotAI* botAI)
    {
        return new UldCreatureGuidsValue(
            botAI, UldHelpers::IGNIS_WATER_TRIGGERS_VALUE,
            { UldHelpers::Id(UldHelpers::UldNpcs::NPC_WATER_TRIGGER) });
    }
    static UntypedValue* auriaya_sentries(PlayerbotAI* botAI)
    {
        return new UldCreatureGuidsValue(
            botAI, UldHelpers::AURIAYA_SENTRIES_VALUE,
            { UldHelpers::Id(UldHelpers::UldNpcs::NPC_SANCTUM_SENTRY),
              UldHelpers::Id(UldHelpers::UldNpcs::NPC_SANCTUM_SENTRY_25) });
    }
    static UntypedValue* auriaya_feral_defenders(PlayerbotAI* botAI)
    {
        return new UldCreatureGuidsValue(
            botAI, UldHelpers::AURIAYA_FERAL_DEFENDERS_VALUE,
            { UldHelpers::Id(UldHelpers::UldNpcs::NPC_FERAL_DEFENDER),
              UldHelpers::Id(UldHelpers::UldNpcs::NPC_FERAL_DEFENDER_25) });
    }
    static UntypedValue* auriaya_seeping_essences(PlayerbotAI* botAI)
    {
        return new UldCreatureGuidsValue(
            botAI, UldHelpers::AURIAYA_SEEPING_ESSENCES_VALUE,
            { UldHelpers::Id(UldHelpers::UldNpcs::NPC_SEEPING_FERAL_ESSENCE),
              UldHelpers::Id(UldHelpers::UldNpcs::NPC_SEEPING_FERAL_ESSENCE_25) });
    }
    static UntypedValue* algalon_collapsing_stars(PlayerbotAI* botAI)
    {
        return new UldCreatureGuidsValue(
            botAI, UldHelpers::ALGALON_COLLAPSING_STARS_VALUE,
            { UldHelpers::Id(UldHelpers::UldNpcs::NPC_COLLAPSING_STAR),
              UldHelpers::Id(UldHelpers::UldNpcs::NPC_COLLAPSING_STAR_25) });
    }
    static UntypedValue* algalon_black_holes(PlayerbotAI* botAI)
    {
        return new UldCreatureGuidsValue(
            botAI, UldHelpers::ALGALON_BLACK_HOLES_VALUE,
            { UldHelpers::Id(UldHelpers::UldNpcs::NPC_BLACK_HOLE),
              UldHelpers::Id(UldHelpers::UldNpcs::NPC_BLACK_HOLE_25) });
    }
    static UntypedValue* algalon_constellations(PlayerbotAI* botAI)
    {
        return new UldCreatureGuidsValue(
            botAI, UldHelpers::ALGALON_CONSTELLATIONS_VALUE,
            { UldHelpers::Id(UldHelpers::UldNpcs::NPC_LIVING_CONSTELLATION),
              UldHelpers::Id(UldHelpers::UldNpcs::NPC_LIVING_CONSTELLATION_25) });
    }
    // Both halves of the Cosmic Smash mark: the stalker on the floor and the asteroid 35 yards
    // above it, which is the one that carries the damage (BAL:574-590).
    static UntypedValue* algalon_cosmic_smash_targets(PlayerbotAI* botAI)
    {
        return new UldCreatureGuidsValue(
            botAI, UldHelpers::ALGALON_COSMIC_SMASH_VALUE,
            { UldHelpers::Id(UldHelpers::UldNpcs::NPC_ASTEROID_TARGET_01),
              UldHelpers::Id(UldHelpers::UldNpcs::NPC_ASTEROID_TARGET_02),
              UldHelpers::Id(UldHelpers::UldNpcs::NPC_ASTEROID_TARGET_02_25) });
    }
    static UntypedValue* algalon_dark_matter(PlayerbotAI* botAI)
    {
        return new UldCreatureGuidsValue(
            botAI, UldHelpers::ALGALON_DARK_MATTER_VALUE,
            { UldHelpers::Id(UldHelpers::UldNpcs::NPC_UNLEASHED_DARK_MATTER),
              UldHelpers::Id(UldHelpers::UldNpcs::NPC_UNLEASHED_DARK_MATTER_25) });
    }
};

#endif
