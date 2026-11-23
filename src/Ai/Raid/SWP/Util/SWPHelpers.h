/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#ifndef PLAYERBOTS_SWPHELPERS_H
#define PLAYERBOTS_SWPHELPERS_H

#include "Common.h"
#include "ObjectGuid.h"
#include "Position.h"
#include <cmath>
#include <type_traits>
#include <vector>

class Player;
class PlayerbotAI;
class Unit;

namespace SwpHelpers
{

template <typename T, std::enable_if_t<std::is_enum_v<T>, int> = 0>
constexpr uint32 Id(T value)
{
    return static_cast<uint32>(value);
}

enum class SwpSpells : uint32
{
    // Kalecgos
    SPELL_SPECTRAL_REALM               = 46021,

    // Brutallus
    SPELL_METEOR_SLASH                 = 45150,
    SPELL_BURN_DAMAGE                  = 46394,

    // Felmyst
    SPELL_ENCAPSULATE_CHANNEL          = 45661,
    SPELL_FELMYST_SPEED_BURST          = 45495,
    SPELL_FOG_OF_CORRUPTION_CHARM      = 45717,
    SPELL_FOG_OF_CORRUPTION_CHARM2     = 45726,
};

enum class SwpNpcs : uint32
{
    NPC_KALECGOS                       = 24850,
    NPC_SATHROVARR                     = 24892,
    NPC_BRUTALLUS                      = 24882,
    NPC_FELMYST                        = 25038,
    NPC_DEMONIC_VAPOR_TRAIL            = 25267,
    NPC_UNYIELDING_DEAD                = 25268,
    NPC_LADY_SACROLASH                 = 25165,
    NPC_GRAND_WARLOCK_ALYTHESS         = 25166,
    NPC_MURU                           = 25741,
    NPC_ENTROPIUS                      = 25840,
    NPC_DARKNESS                       = 25879,
    NPC_SINGULARITY                    = 25855,
    NPC_VOID_SENTINEL                  = 25772,
    NPC_VOID_SPAWN                     = 25824,
    NPC_DARK_FIEND                     = 25744,
    NPC_SHADOWSWORD_BERSERKER          = 25798,
    NPC_SHADOWSWORD_FURY_MAGE          = 25799,
    NPC_KILJAEDEN                      = 25315,
    NPC_SHIELD_ORB                     = 25502,
    NPC_SINISTER_REFLECTION            = 25708,
    NPC_ARMAGEDDON_TARGET              = 25735,
    NPC_HAND_OF_THE_DECEIVER           = 25588,
};

inline constexpr uint32 SWP_MAP_ID = 580;
inline constexpr uint32 SWP_CACHE_INTERVAL_MS = 200;
inline constexpr float ADD_SEARCH_RADIUS = 100.0f;

// Cached add and hazard values, registered in SWPValueContext.h.
inline constexpr char const* FELMYST_UNYIELDING_DEAD_VALUE = "swp felmyst unyielding dead";
inline constexpr char const* FELMYST_VAPOR_TRAILS_VALUE = "swp felmyst vapor trails";
inline constexpr char const* MURU_DARK_FIENDS_VALUE = "swp m'uru dark fiends";
inline constexpr char const* MURU_VOID_SENTINELS_VALUE = "swp m'uru void sentinels";
inline constexpr char const* MURU_ADDS_VALUE = "swp m'uru adds";
inline constexpr char const* MURU_DARKNESS_VALUE = "swp m'uru darkness";
inline constexpr char const* ENTROPIUS_SINGULARITIES_VALUE = "swp entropius singularities";
inline constexpr char const* KILJAEDEN_SHIELD_ORBS_VALUE = "swp kil'jaeden shield orbs";
inline constexpr char const* KILJAEDEN_REFLECTIONS_VALUE = "swp kil'jaeden reflections";
inline constexpr char const* KILJAEDEN_HANDS_VALUE = "swp kil'jaeden hands of the deceiver";
inline constexpr char const* KILJAEDEN_ARMAGEDDON_VALUE = "swp kil'jaeden armageddon targets";

// Hazard radii. Each is the mechanic's own reach plus a yard of slack, so a bot that steps out
// stays out while its next tick is pending.

// The Vapor Trail chases a player and leaves a damaging cloud wherever it has been
// (boss_felmyst.cpp:427, SPELL_DEMONIC_VAPOR_TRAIL_PERIODIC).
inline constexpr float VAPOR_TRAIL_RADIUS = 12.0f;
// Darkness is a void zone that keeps spawning Void Spawns (boss_muru.cpp, SPELL_DARKNESS_PERIODIC).
inline constexpr float DARKNESS_RADIUS = 12.0f;
// The Singularity pulls everything near it into Entropius (boss_muru.cpp, SPELL_BLACK_HOLE).
inline constexpr float SINGULARITY_RADIUS = 16.0f;
// Armageddon drops a meteor on each of these markers (boss_kiljaeden.cpp, SPELL_ARMAGEDDON_MISSILE).
inline constexpr float ARMAGEDDON_RADIUS = 14.0f;

// Spacing. Fire Bloom and Legion Lightning chain through a clumped raid, and so do Conflagration
// and Shadow Nova on the Twins.
inline constexpr float SPREAD_DISTANCE = 10.0f;
// Burn jumps to whoever stands next to the burning player (boss_brutallus.cpp:100, Burn picks a
// target without the debuff), so the burning bot takes itself out of the raid.
inline constexpr float BURN_ESCAPE_DISTANCE = 15.0f;
// Alythess's Pyrogenics and Flame Sear punish anyone standing in her melee range.
inline constexpr float ALYTHESS_RANGED_DISTANCE = 15.0f;

// Kalecgos's chamber floor is at z 53 and the Spectral Realm below it at z -74; the boss scripts
// split the two realms at z 50 (boss_kalecgos.cpp:100, :330 CanAIAttack). Only this encounter's
// own objects may use the height test: other rooms of the plateau lie below z 50 as well.
inline constexpr float SPECTRAL_REALM_Z_CEILING = 50.0f;

// Felmyst's breath sweeps the length of a lane while she flies it, and the lane is wide.
inline constexpr float BREATH_LANE_WIDTH = 18.0f;
inline constexpr float BREATH_DODGE_DISTANCE = 20.0f;
// Meteor Slash splits its damage between everyone it hits, out of Brutallus's front half.
inline constexpr float METEOR_SLASH_ARC = static_cast<float>(M_PI);

// Bosses and adds

// The threat-list lookup of "find target", by creature entry rather than by name. Three creatures
// of this raid are called Kalecgos (24850, 24891, 25319) and two are called Kil'jaeden (25315,
// 25608), so names cannot address them.
Unit* FindThreatCreature(Player* bot, uint32 entry);
GuidVector FindCreatureGuids(Player* bot, std::vector<uint32> const& entries, float radius);
std::vector<Unit*> GetCachedUnits(PlayerbotAI* botAI, char const* value);
Unit* GetNearestCachedUnit(PlayerbotAI* botAI, char const* value);
// The cached unit of the given index, by GUID order, so every bot picks the same one.
Unit* GetCachedUnitOfIndex(PlayerbotAI* botAI, char const* value, uint8 index);

// Creature hazards

bool IsNearCachedUnit(PlayerbotAI* botAI, char const* value, float radius);
// The closest point outside every hazard of this value, searched on rings around the bot.
bool FindPositionAwayFromCachedUnits(
    PlayerbotAI* botAI, char const* value, float radius, Position& outPos);

// Kalecgos

// Swallowed by Spectral Blast, or standing in the Spectral Realm for any other reason: only
// Sathrovarr can be reached from there, and only Kalecgos from the dragon realm.
bool IsInSpectralRealm(Player* bot);

// Brutallus

bool IsBurning(Unit* unit);

}

#endif
