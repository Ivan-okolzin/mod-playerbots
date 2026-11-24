/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#ifndef PLAYERBOTS_MCHELPERS_H
#define PLAYERBOTS_MCHELPERS_H

#include "ObjectGuid.h"
#include "Position.h"
#include "Unit.h"
#include <vector>

class Player;
class PlayerbotAI;

namespace MoltenCoreHelpers
{
// Creature entries, spell ids, phases and timings are taken from the encounter scripts of
// src/server/scripts/EasternKingdoms/BlackrockMountain/MoltenCore/. References name the file and
// line: MCH = molten_core.h, MCC = molten_core.cpp, BL = boss_lucifron.cpp, BM = boss_magmadar.cpp,
// BG = boss_gehennas.cpp, BGA = boss_garr.cpp, BSH = boss_shazzrah.cpp, BBG = boss_baron_geddon.cpp,
// BSU = boss_sulfuron_harbinger.cpp, BGO = boss_golemagg.cpp, BMJ = boss_majordomo_executus.cpp,
// BR = boss_ragnaros.cpp. Mechanics that live in the database instead of C++ reference
// acore_world.smart_scripts by entry and id (SS <entry>:<id>).
enum MoltenCoreNPCs
{
    // Lucifron
    NPC_LUCIFRON = 12118,                // MCH:78
    NPC_FLAMEWAKER_PROTECTOR = 12119,    // MCH:79

    // Magmadar
    NPC_MAGMADAR = 11982,                // MCH:57

    // Gehennas
    NPC_GEHENNAS = 12259,                // MCH:70
    NPC_FLAMEWAKER = 11661,              // MCH:71

    // Garr
    NPC_GARR = 12057,                    // MCH:66
    NPC_FIRESWORN = 12099,               // MCH:67

    // Shazzrah
    NPC_SHAZZRAH = 12264,                // MCH:58

    // Baron Geddon
    NPC_BARON_GEDDON = 12056,            // MCH:59

    // Sulfuron Harbinger
    NPC_SULFURON_HARBINGER = 12098,      // MCH:82
    NPC_FLAMEWAKER_PRIEST = 11662,       // MCH:83

    // Golemagg
    NPC_GOLEMAGG = 11988,                // MCH:74
    NPC_CORE_RAGER = 11672,              // MCH:75

    // Majordomo Executus
    NPC_MAJORDOMO_EXECUTUS = 12018,      // MCH:86
    NPC_FLAMEWAKER_HEALER = 11663,       // MCH:61
    NPC_FLAMEWAKER_ELITE = 11664,        // MCH:62

    // Ragnaros
    NPC_RAGNAROS = 11502,                // MCH:60
    NPC_SON_OF_FLAME = 12143,            // BR:100

    // Core Hound (trash)
    NPC_CORE_HOUND = 11671,              // MCH:63
};
enum MoltenCoreSpells
{
    // Baron Geddon
    SPELL_INFERNO = 19695,               // BBG:32, pulses for 10s while the aura holds (BBG:140)
    SPELL_LIVING_BOMB = 20475,           // BBG:35, on a random player every 11-16s (BBG:100)
    SPELL_ARMAGEDDON = 20478,            // BBG:36, cast once below 2% health (BBG:70)

    // Gehennas
    SPELL_RAIN_OF_FIRE = 19717,          // BG:25, on a random player every 6s (BG:59)

    // Golemagg
    SPELL_GOLEMAGGS_TRUST = 20553,       // applied to the Core Ragers by 20556 (BGO:35, :58)
    SPELL_MAGMA_SPLASH = 13880,          // applied to melee attackers by 13879 (BGO:34, :57)

    // Majordomo Executus
    SPELL_MAGIC_REFLECTION = 20619,      // BMJ:53, one of the two shields, 10s every 30s (BMJ:319)
    SPELL_DAMAGE_SHIELD = 21075,         // BMJ:54 (SPELL_DAMAGE_REFLECTION there)
};
enum MoltenCoreGameObjects
{
    // The trap Magmadar's Lava Bomb drops. Both bomb spells spawn it, for 30s and 60s
    // respectively (BM:34, :36), and it casts 19428 on whoever walks in.
    GO_LAVA_BOMB = 177704,
    // Ragnaros's Lava Burst marker. The boss makes it cast 21158 about a second after it
    // appears (MCH:113, BR:260).
    GO_LAVA_BURST = 178088,
};

inline constexpr uint32 MC_MAP_ID = 409;
inline constexpr uint32 MC_CACHE_INTERVAL_MS = 200;
inline constexpr float ADD_SEARCH_RADIUS = 100.0f;
inline constexpr float HAZARD_SEARCH_RADIUS = 60.0f;

// Cached boss, add and hazard values, registered in MCValueContext.h. Only the bosses that have
// to be found without the bot's threat list get a cached lookup: see FindBoss.
inline constexpr char const* BARON_GEDDON_VALUE = "mc baron geddon guid";
inline constexpr char const* SHAZZRAH_VALUE = "mc shazzrah guid";
inline constexpr char const* MAJORDOMO_VALUE = "mc majordomo guid";
inline constexpr char const* RAGNAROS_VALUE = "mc ragnaros guid";
inline constexpr char const* LUCIFRON_PROTECTORS_VALUE = "mc lucifron protectors";
inline constexpr char const* GEHENNAS_FLAMEWAKERS_VALUE = "mc gehennas flamewakers";
inline constexpr char const* GARR_FIRESWORN_VALUE = "mc garr firesworn";
inline constexpr char const* SULFURON_PRIESTS_VALUE = "mc sulfuron priests";
inline constexpr char const* MAJORDOMO_ADDS_VALUE = "mc majordomo adds";
inline constexpr char const* RAGNAROS_SONS_OF_FLAME_VALUE = "mc ragnaros sons of flame";
inline constexpr char const* MAGMADAR_LAVA_BOMBS_VALUE = "mc magmadar lava bombs";
inline constexpr char const* GEHENNAS_RAIN_OF_FIRE_VALUE = "mc gehennas rain of fire";
inline constexpr char const* RAGNAROS_LAVA_BURSTS_VALUE = "mc ragnaros lava bursts";

constexpr uint32 MAGMA_SPLASH_BACK_OFF_STACKS = 20;
constexpr float MAGMA_SPLASH_BACK_OFF_DISTANCE = 12.0f;

// Shazzrah's Arcane Explosion radius
constexpr float ARCANE_EXPLOSION_DISTANCE = 26.0f;

// How far Baron Geddon's Inferno reaches. The damage comes from the server-side 19698 (BBG:33),
// whose radius is not in the script, so this is the 20 yards this raid has always used, to
// confirm by a live test.
inline constexpr float INFERNO_DISTANCE = 20.0f;

// Hazard radii, each the mechanic's own reach plus a yard of slack so that a bot which steps out
// stays out while its next tick is pending.
// The Lava Bomb trap template (gameobject_template 177704, type 6) carries diameter 5, which
// GameObject::Update halves into a 2.5 yard activation radius (GameObject.cpp:771).
inline constexpr float LAVA_BOMB_RADIUS = 5.0f;
// Rain of Fire's and the Lava Burst trap's own radii are in the client's spell data, not in the
// script or the database, so these two are estimates to confirm by a live test.
inline constexpr float RAIN_OF_FIRE_RADIUS = 11.0f;
inline constexpr float LAVA_BURST_RADIUS = 6.0f;

inline bool IsMajordomoAdd(Unit const* unit)
{
    return unit && (unit->GetEntry() == NPC_FLAMEWAKER_HEALER || unit->GetEntry() == NPC_FLAMEWAKER_ELITE);
}

// Bosses and adds

// The threat-list lookup of "find target", by creature entry rather than by name. Names cannot
// address this raid: five creature templates are called Flamewaker something (11661, 11662, 11663,
// 11664, 12119) and the Core Hound 11671 shares its name with the Ancient Core Hound 11673.
Unit* FindThreatCreature(Player* bot, uint32 entry);
// The boss an encounter's objects work on. The threat list cannot always answer: Shazzrah's Gate
// (BSH:148), Majordomo's Hate to Zero (BMJ:336, :345) and Ragnaros's submerge (BR:395) each wipe
// the boss's threat list, which takes the boss off the bot's threatened-by-me list as well, and a
// healer that has never attacked the boss was never on it. Passing a cached value adds a grid
// search by entry as the fallback, which is what lets a tank taunt a boss back and a healer run
// out of a boss aura.
Unit* FindBoss(PlayerbotAI* botAI, uint32 entry, char const* cachedValue = nullptr);
GuidVector FindCreatureGuids(Player* bot, std::vector<uint32> const& entries, float radius);
std::vector<Unit*> GetCachedUnits(PlayerbotAI* botAI, char const* value);
// An add that spends part of its life untargetable is no use as an attack order.
bool IsAttackableNow(Unit* unit);
Unit* GetNearestAttackableCachedUnit(PlayerbotAI* botAI, char const* value);
Unit* GetNearestCachedUnitOfEntry(PlayerbotAI* botAI, char const* value, uint32 entry);

// Ground hazards

// Positions of the game object traps of an entry around the bot. Magmadar's Lava Bomb and
// Ragnaros's Lava Burst are both game objects rather than dynamic objects, so neither can be
// found through EncounterHelpers::GetDynamicObjectPositions.
std::vector<Position> FindGameObjectPositions(
    Player* bot, std::vector<uint32> const& entries, float radius);
std::vector<Position> const& GetCachedHazardPositions(PlayerbotAI* botAI, char const* value);
bool IsInHazard(PlayerbotAI* botAI, char const* value, float radius);
// The closest point outside every hazard of this value, searched on rings around the bot.
bool FindPositionOutsideHazards(
    PlayerbotAI* botAI, char const* value, float radius, Position& outPos);
}

#endif
