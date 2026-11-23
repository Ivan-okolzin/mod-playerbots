/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#ifndef PLAYERBOTS_VOAHELPERS_H
#define PLAYERBOTS_VOAHELPERS_H

#include "Common.h"
#include "ObjectGuid.h"
#include "Position.h"
#include <type_traits>
#include <vector>

class Player;
class PlayerbotAI;
class Unit;

namespace VoAHelpers
{

template <typename T, std::enable_if_t<std::is_enum_v<T>, int> = 0>
constexpr uint32 Id(T value)
{
    return static_cast<uint32>(value);
}

// Spell and creature ids are taken from the encounter scripts of
// src/server/scripts/Northrend/VaultOfArchavon/. The references name the file and line:
// BA = boss_archavon.cpp, BE = boss_emalon.cpp, BK = boss_koralon.cpp, BT = boss_toravon.cpp.
// The 25-man ids are the DifficultySpellID_2 column of spelldifficulty_dbc; the spells without a
// row there keep one id for both raid sizes.
enum class VoASpells : uint32
{
    // Archavon the Stone Watcher
    SPELL_ROCK_SHARDS            = 58678,  // BA:27, at a random player every 15s (BA:134, :139)
    SPELL_CRUSHING_LEAP          = 58960,  // BA:31, at a random player 10 to 80 yards out (BA:142)
    SPELL_CRUSHING_LEAP_25       = 60894,
    SPELL_STOMP                  = 58663,  // BA:32, on the victim every 45s (BA:155, :157)
    SPELL_IMPALE                 = 58666,  // BA:33, on the victim 3s after the Stomp (BA:158, :162)

    // Emalon the Storm Watcher
    SPELL_OVERCHARGED            = 64217,  // BE:27, stacks on one minion and bursts it at ten (BE:241)
    SPELL_CHAIN_LIGHTNING        = 64213,  // BE:32, at a random player every 25s (BE:182, :184)
    SPELL_CHAIN_LIGHTNING_25     = 64215,
    SPELL_LIGHTNING_NOVA         = 64216,  // BE:33, self cast every 40s (BE:187, :188)
    SPELL_LIGHTNING_NOVA_25      = 65279,

    // Koralon the Flame Watcher
    SPELL_BURNING_BREATH         = 66665,  // BK:36, cast, then 3s of turning in place (BK:142, :113)
    SPELL_FLAMING_CINDER         = 66681,  // BK:38, one player within 100 yards (corrections of 66690)
    SPELL_METEOR_FISTS           = 66725,  // BK:42, procs on his melee hits (BK:201)

    // Toravon the Ice Watcher
    SPELL_FREEZING_GROUND        = 72090,  // BT:28, at a random player every 20s (BT:134, :136)
    SPELL_FROZEN_ORB_DAMAGE      = 72081,  // BT:35, periodic damage around an orb (BT:180)
    SPELL_WHITEOUT               = 72034,  // BT:30, self cast every 40s (BT:143, :145)
};

enum class VoANpcs : uint32
{
    NPC_ARCHAVON                 = 31125,  // instance_encounters of map 624
    NPC_EMALON                   = 33993,
    NPC_KORALON                  = 35013,
    NPC_TORAVON                  = 38433,
    // Four stand with Emalon from the start and a replacement joins 4s after each death (BE:51,
    // :89, :206). The 25-man entry is difficulty_entry_1 of 33998 in creature_template.
    NPC_TEMPEST_MINION           = 33998,
    NPC_TEMPEST_MINION_25        = 34200,
    // One orb in 10-man and three in 25-man (BT:139), each chasing a player of its own (BT:191).
    NPC_FROZEN_ORB               = 38456,
};

inline constexpr uint32 VOA_MAP_ID = 624;
inline constexpr uint32 VOA_CACHE_INTERVAL_MS = 200;
inline constexpr float ADD_SEARCH_RADIUS = 100.0f;
inline constexpr float HAZARD_SEARCH_RADIUS = 60.0f;

// Cached add and hazard values, registered in VoAValueContext.h.
inline constexpr char const* EMALON_MINIONS_VALUE = "voa emalon tempest minions";
inline constexpr char const* TORAVON_FROZEN_ORBS_VALUE = "voa toravon frozen orbs";
inline constexpr char const* TORAVON_FREEZING_GROUND_VALUE = "voa toravon freezing ground";

// Spacing for the spells that pick one random player and hit the ground around it: Rock Shards
// and Crushing Leap (BA:134, :142), Chain Lightning (BE:182) and Flaming Cinder (BK:151).
inline constexpr float SPREAD_DISTANCE = 10.0f;
// Hazard reaches. None of these radii is in the script, so each is the mechanic's visual size
// plus a yard of slack and is to be confirmed by a live test.
inline constexpr float FROZEN_ORB_RADIUS = 10.0f;
inline constexpr float FROZEN_ORB_ESCAPE_DISTANCE = 20.0f;
inline constexpr float FREEZING_GROUND_RADIUS = 8.0f;
// Koralon breathes in front of himself and turns while he does (BK:109-127). The arc and the
// length of the cone are not in the script either: a bot treats the half of the room he faces as
// unsafe out to this range, which is his own aggro radius, and steps behind him.
inline constexpr float BURNING_BREATH_REACH = 30.0f;
inline constexpr float BURNING_BREATH_HALF_ARC = 1.2f;  // radians, about 70 degrees to each side
inline constexpr float BURNING_BREATH_REAR_DISTANCE = 6.0f;

// Bosses and adds

// The threat-list lookup of "find target", by creature entry rather than by name: four creature
// templates in this raid are called "Tempest Minion" and three more are called "Frozen Orb".
Unit* FindThreatCreature(Player* bot, uint32 entry);
GuidVector FindCreatureGuids(Player* bot, std::vector<uint32> const& entries, float radius);
std::vector<Unit*> GetCachedUnits(PlayerbotAI* botAI, char const* value);
bool IsAttackableNow(Unit* unit);
Unit* GetNearestAttackableCachedUnit(PlayerbotAI* botAI, char const* value);

// Creature hazards

bool IsNearCachedUnit(PlayerbotAI* botAI, char const* value, float radius);
// The closest point outside every hazard of this value, searched on rings around the bot.
bool FindPositionAwayFromCachedUnits(
    PlayerbotAI* botAI, char const* value, float radius, Position& outPos);

// Ground hazards left by a spell rather than by a creature

std::vector<Position> const& GetCachedHazardPositions(PlayerbotAI* botAI, char const* value);
bool IsInHazard(PlayerbotAI* botAI, char const* value, float radius);
bool FindPositionOutsideHazards(
    PlayerbotAI* botAI, char const* value, float radius, Position& outPos);

// Tanking

// Same class switch as SSCHelpers::CastTankTaunt, Aq40Helpers::CastTankTaunt and
// CrusaderHelpers::CastTankTaunt; the fifth copy, and overdue for a move into EncounterHelpers.
bool CastTankTaunt(PlayerbotAI* botAI, Unit* target);

// Emalon the Storm Watcher

// Overcharge lands on one minion, refills its health (BE:142) and bursts it ten stacks later
// (BE:241), so the raid has those ten seconds to kill it.
Unit* GetOverchargedMinion(PlayerbotAI* botAI);

// Koralon the Flame Watcher

// Burning Breath is the only spell he casts rather than triggers (BK:143), so a cast in progress
// is that breath whatever the raid size's spell id turns out to be.
bool IsBreathingFire(Unit* koralon);
bool IsInFrontOfBreath(Player* bot, Unit* koralon);

// Toravon the Ice Watcher

// An orb resets its threat every ten seconds and puts all of it on one random player (BT:191),
// which is the player it is chasing.
Unit* GetPursuingFrozenOrb(PlayerbotAI* botAI);

}

#endif
