/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#ifndef PLAYERBOTS_AQ20HELPERS_H
#define PLAYERBOTS_AQ20HELPERS_H

#include "Common.h"
#include "ObjectGuid.h"
#include "Position.h"
#include <cmath>
#include <type_traits>
#include <vector>

class GameObject;
class Player;
class PlayerbotAI;
class Unit;

namespace Aq20Helpers
{

template <typename T, std::enable_if_t<std::is_enum_v<T>, int> = 0>
constexpr uint32 Id(T value)
{
    return static_cast<uint32>(value);
}

// Spell, creature and gameobject ids come from the encounter scripts of
// src/server/scripts/Kalimdor/RuinsOfAhnQiraj/. References name the file and line: KUR =
// boss_kurinnaxx.cpp, RAJ = boss_rajaxx.cpp, MOA = boss_moam.cpp, BUR = boss_buru.cpp, AYA =
// boss_ayamiss.cpp, OSS = boss_ossirian.cpp, RAQ = ruins_of_ahnqiraj.h, IRA =
// instance_ruins_of_ahnqiraj.cpp.
enum class Aq20Spells : uint32
{
    // Kurinnaxx
    SPELL_MORTAL_WOUND          = 25646,  // KUR:28, on the victim every 8-10s (KUR:54)

    // Moam
    SPELL_ENERGIZE              = 25685,  // MOA:42, held for the whole stone phase (MOA:121)

    // Buru the Gorger
    SPELL_THORNS                = 25640,  // BUR:35, held for the whole egg phase (BUR:86, :141)

    // Ossirian the Unscarred
    SPELL_STRENGTH_OF_OSSIRIAN  = 25176,  // OSS:44, re-applied whenever no weakness is on (OSS:275)
    SPELL_FIRE_WEAKNESS         = 25177,  // OSS:51, one of the five a crystal rolls (OSS:344)
    SPELL_FROST_WEAKNESS        = 25178,  // OSS:52
    SPELL_NATURE_WEAKNESS       = 25180,  // OSS:53
    SPELL_ARCANE_WEAKNESS       = 25181,  // OSS:54
    SPELL_SHADOW_WEAKNESS       = 25183,  // OSS:55
};

enum class Aq20Npcs : uint32
{
    NPC_KURINNAXX               = 15348,  // RAQ:54
    NPC_RAJAXX                  = 15341,  // RAQ:55
    NPC_MOAM                    = 15340,  // RAQ:56
    NPC_MANA_FIEND              = 15527,  // summon of SPELL_SUMMON_MANA_FIENDS 25684 (MOA:38)
    NPC_BURU                    = 15370,  // RAQ:57
    NPC_BURU_EGG                = 15514,  // RAQ:66
    NPC_HATCHLING               = 15521,  // RAQ:65, out of a dying egg (BUR:223)
    NPC_AYAMISS                 = 15369,  // RAQ:58
    NPC_HIVEZARA_SWARMER        = 15546,  // RAQ:61
    NPC_HIVEZARA_LARVA          = 15555,  // RAQ:62
    NPC_OSSIRIAN                = 15339,  // RAQ:59
    NPC_SAND_VORTEX             = 15428,  // RAQ:63, two of them on waypoints (OSS:187)
};

enum class Aq20GameObjects : uint32
{
    // The trap Sand Trap 25648 leaves under a random player, which Kurinnaxx then sets off
    // (KUR:62, :104-125). gameobject_template 180647, type 6 (trap), spell 25656.
    GO_SAND_TRAP                = 180647,
    GO_OSSIRIAN_CRYSTAL         = 180619,  // RAQ:82
};

inline constexpr uint32 AQ20_MAP_ID = 509;
inline constexpr uint32 AQ20_CACHE_INTERVAL_MS = 200;
inline constexpr float ADD_SEARCH_RADIUS = 100.0f;
inline constexpr float HAZARD_SEARCH_RADIUS = 100.0f;

// Cached add, hazard and crystal values, registered in Aq20ValueContext.h.
inline constexpr char const* KURINNAXX_SAND_TRAPS_VALUE = "aq20 kurinnaxx sand traps";
inline constexpr char const* MOAM_MANA_FIENDS_VALUE = "aq20 moam mana fiends";
inline constexpr char const* BURU_EGGS_VALUE = "aq20 buru eggs";
inline constexpr char const* BURU_HATCHLINGS_VALUE = "aq20 buru hatchlings";
inline constexpr char const* AYAMISS_LARVAE_VALUE = "aq20 ayamiss larvae";
inline constexpr char const* AYAMISS_SWARMERS_VALUE = "aq20 ayamiss swarmers";
inline constexpr char const* OSSIRIAN_CRYSTALS_VALUE = "aq20 ossirian crystals";
inline constexpr char const* OSSIRIAN_SAND_VORTEXES_VALUE = "aq20 ossirian sand vortexes";

// Mortal Wound stacks on whoever Kurinnaxx is hitting (KUR:54). Five stacks is the usual swap
// point, the same number AQ40 uses for Fankriss's copy of the spell.
inline constexpr uint8 MORTAL_WOUND_SWAP_STACKS = 5;

// Hazard radii. Each is the mechanic's own reach plus a yard of slack, so a bot that steps out
// stays out while its next tick is pending. Neither reach is in a script, so both are estimates to
// confirm by a live test: the Sand Trap's own gameobject_template row carries diameter 0, which
// leaves the radius to spell 25656, and the Sand Vortex 15428 has no script and no SmartAI at all.
inline constexpr float SAND_TRAP_RADIUS = 9.0f;
inline constexpr float SAND_VORTEX_RADIUS = 11.0f;

// How far a bot walks per tick when it follows a path.
inline constexpr float PATH_STEP_DISTANCE = 3.5f;

// A dying egg's Explode 19593 takes 7% of Buru's maximum health, but only while his Thorns is up
// (BUR:254), and that 7% is most of the egg phase: the instance holds six eggs. The spell's radius
// is not in the script, so this is the estimate for "Buru is on the egg", to confirm by a live
// test. The same explosion costs a player -16 * distance + 500 health (BUR:253), which the lured
// bot takes by design: Buru only follows it onto the egg if it stands there.
inline constexpr float EGG_EXPLOSION_REACH = 12.0f;

// Only the crystal's own trigger creature casts the weakness, and the spell keeps just Ossirian
// among its targets (OSS:344, spell_crystal_weakness at OSS:460), so the tank has to have the boss
// standing by the crystal when it goes off. The reach is the radius of those five weakness spells,
// which the script does not name either.
inline constexpr float CRYSTAL_WEAKNESS_REACH = 25.0f;
// The core's INTERACTION_DISTANCE is 5 yards, and the crystal has to be reached on foot.
inline constexpr float CRYSTAL_INTERACT_DISTANCE = 4.0f;
// The twelve spots a crystal can stand in are spread over most of Ossirian's arena (OSS:78-92),
// nearly 300 yards end to end, so the search for them is wider than the one for adds.
inline constexpr float CRYSTAL_SEARCH_RADIUS = 200.0f;
// A crystal takes a moment to go off, so it is clicked this long before the current weakness runs
// out, and the tank sets off this much earlier again.
inline constexpr uint32 CRYSTAL_ACTIVATION_LEAD_MS = 5000;
inline constexpr uint32 CRYSTAL_APPROACH_LEAD_MS = 20000;

// Bosses, adds and hazards

// The threat-list lookup of "find target", by creature entry rather than by name, so that a bot
// only ever acts on a boss it actually has threat on: the six encounters of this raid are fought
// in one instance, and Buru's eggs, Moam's Fiends and Ossirian's Sand Vortexes stay on the grid
// long enough to be found by a bot that is nowhere near them.
Unit* FindThreatCreature(Player* bot, uint32 entry);
GuidVector FindCreatureGuids(Player* bot, std::vector<uint32> const& entries, float radius);
GuidVector FindGameObjectGuids(Player* bot, std::vector<uint32> const& entries, float radius);
std::vector<Unit*> GetCachedUnits(PlayerbotAI* botAI, char const* value);
// Never order an attack on something the core has flagged unselectable: an add on its way out
// (BUR:234, AYA:188) or a boss mid-transition would otherwise hold a bot on a dead target.
bool IsAttackableNow(Unit* unit);
Unit* GetNearestAttackableCachedUnit(PlayerbotAI* botAI, char const* value);
bool IsNearCachedUnit(PlayerbotAI* botAI, char const* value, float radius);
// The closest point outside every hazard of this value, searched on rings around the bot.
bool FindPositionAwayFromCachedUnits(
    PlayerbotAI* botAI, char const* value, float radius, Position& outPos);

std::vector<GameObject*> GetCachedGameObjects(PlayerbotAI* botAI, char const* value);
bool IsNearCachedGameObject(PlayerbotAI* botAI, char const* value, float radius);
bool FindPositionAwayFromCachedGameObjects(
    PlayerbotAI* botAI, char const* value, float radius, Position& outPos);

// Tanking

// Same class switch as CrusaderHelpers::CastTankTaunt and Aq40Helpers::CastTankTaunt; the fifth
// copy, and overdue for a move into EncounterHelpers.
bool CastTankTaunt(PlayerbotAI* botAI, Unit* target);
uint8 GetAuraStacks(Unit* unit, uint32 spellId);

// Moam

// Moam turns to stone for the whole phase he summons his Mana Fiends in, and the aura comes off
// again when it ends (MOA:121, :126). The phase also ends early the moment the last Fiend dies
// (MOA:87-93), which is what makes them, and not Moam, worth hitting while it lasts.
bool IsMoamInStonePhase(Unit* moam);

// Buru the Gorger

// Thorns is on Buru for the whole egg phase and comes off at the transform (BUR:86, :141), which
// bounds every object written for either phase.
bool IsBuruInEggPhase(Unit* buru);
// Buru fixates one player at a time with a million threat and picks a new one on every egg death
// (BUR:84, :121-127), so the bot it is after is the one it is hitting.
bool IsFixatedByBuru(Player* bot);
// The egg the raid is to pop: the one closest to Buru, and only once he is close enough that the
// explosion reaches him. Every bot works it out from the same numbers, so the raid focuses one egg
// without being told. Null outside the egg phase.
Unit* GetBuruTargetEgg(PlayerbotAI* botAI);
// The egg the fixated bot leads Buru onto: the one closest to the bot, so the walk is short.
Unit* GetNearestBuruEgg(PlayerbotAI* botAI);

// Ayamiss the Hunter

// Ayamiss spends the fight above 70% health rooted in the air with gravity switched off, and
// switches it back on for the ground phase (AYA:95, :122, :204), so levitation is the phase test.
// Melee cannot reach her at all while it holds.
bool IsAyamissInAirPhase(Unit* ayamiss);

// Ossirian the Unscarred

// The crystal the tank is to drag Ossirian to: the closest one to the bot that is not already
// going off. A crystal whose trigger creature is mid-cast has just been used (OSS:341).
GameObject* GetUsableOssirianCrystal(PlayerbotAI* botAI);
// Strength of Ossirian doubles what he hits for and is re-applied the moment no weakness is left
// on him (OSS:257-277), so the raid's whole job is keeping one of the five weaknesses up. True
// while the weakness on him is close enough to running out that the next crystal is worth setting
// off, or while he is already back to full strength.
bool IsOssirianCrystalDue(Unit* ossirian, uint32 leadTimeMs);

}

#endif
