/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#ifndef PLAYERBOTS_NAXXHELPERS_H
#define PLAYERBOTS_NAXXHELPERS_H

#include "Common.h"
#include "Define.h"
#include "ObjectGuid.h"
#include <type_traits>
#include <vector>

class Player;
class PlayerbotAI;
class Unit;
class WorldObject;

namespace NaxxHelpers
{

template <typename T, std::enable_if_t<std::is_enum_v<T>, int> = 0>
constexpr uint32 Id(T value)
{
    return static_cast<uint32>(value);
}

// Creature entries of the fights served by this header. References name the core file and line:
// NAX = naxxramas.h, BNO = boss_noth.cpp, BGO = boss_gothik.cpp, BPA = boss_patchwerk.cpp, all
// under src/server/scripts/Northrend/Naxxramas/. Names cannot be used as keys in this raid: the
// world database holds four creatures named "Noth the Plaguebringer" and five named "Gothik the
// Harvester", so every lookup here goes by entry.
enum class NaxxNpcs : uint32
{
    NPC_MAEXXNA = 15952,
    NPC_WEB_WRAP = 16486,
    NPC_FAERLINA = 15953,
    NPC_FOLLOWER = 16505,
    NPC_PATCHWERK                = 16028,  // NAX:153
    NPC_NOTH                     = 15954,  // creature_template, ScriptName boss_noth
    NPC_PLAGUED_WARRIOR          = 16984,  // BNO:61, two or three per ground-phase wave (BNO:216)
    NPC_PLAGUED_CHAMPION         = 16983,  // BNO:62, the first two balcony waves (BNO:241, :244)
    NPC_PLAGUED_GUARDIAN         = 16981,  // BNO:63, the second and later balcony waves (BNO:245)
    NPC_GOTHIK                   = 16060,  // NAX:172
    NPC_UNRELENTING_TRAINEE      = 16124,  // BGO:77, living side
    NPC_UNRELENTING_DEATH_KNIGHT = 16125,  // BGO:78, living side
    NPC_UNRELENTING_RIDER        = 16126,  // BGO:79, living side
    NPC_SPECTRAL_TRAINEE         = 16127,  // BGO:80, dead side, from a dead trainee (BGO:733)
    NPC_SPECTRAL_DEATH_KNIGHT    = 16148,  // BGO:81, dead side, from a dead knight (BGO:736)
    NPC_SPECTRAL_HORSE           = 16149,  // BGO:82, dead side, with every spectral rider (BGO:740)
    NPC_SPECTRAL_RIDER           = 16150,  // BGO:83, dead side, from a dead rider (BGO:739)
};

// The gate that splits Gothik's room in two (NAX:107). It is a DOOR_TYPE_ROOM door of BOSS_GOTHIK
// (instance_naxxramas.cpp:128), so it stays shut for the whole encounter until Gothik opens it
// himself (BGO:348).
inline constexpr uint32 GO_GOTHIK_INNER_GATE = 181170;

inline constexpr uint32 NAXX_CACHE_INTERVAL_MS = 200;
inline constexpr float ADD_SEARCH_RADIUS = 100.0f;
// The gate stands in the middle of Gothik's room (2692.07, -3360.78, gameobject guid 65818), which
// is within this range of every spot either half of the room has.
inline constexpr float GATE_SEARCH_RADIUS = 120.0f;

// Cached add, gate and hazard values, registered in NaxxValueContext.h.
inline constexpr char const* MAEXXNA_ADDS_VALUE = "naxx maexxna web wrap";
inline constexpr char const* FAERLINA_ADDS_VALUE = "naxx faerlina follower";
inline constexpr char const* NOTH_SKELETONS_VALUE = "naxx noth skeletons";
inline constexpr char const* GOTHIK_LIVING_ADDS_VALUE = "naxx gothik unrelenting adds";
inline constexpr char const* GOTHIK_DEAD_ADDS_VALUE = "naxx gothik spectral adds";
inline constexpr char const* GOTHIK_GATE_OPEN_VALUE = "naxx gothik inner gate open";

// Gothik the Harvester

// The script's own IN_LIVE_SIDE (BGO:175, POS_Y_GATE at BGO:170): everything with a lower Y than
// the gate's line is the living half of the room, everything above it the dead half.
inline constexpr float GOTHIK_GATE_Y = -3360.78f;

// Patchwerk

// Hateful Strike (41926) picks its target among the players in melee range, tested with
// IsWithinCombatRange(target, 5.0f) (BPA:132, :135). That call adds both combat reaches to the
// five yards (Unit.cpp:784), and Patchwerk's reach is 6.0 against a player's 1.5
// (creature_model_info of display 16174), so the strike reaches 12.5 yards.
inline constexpr float PATCHWERK_HATEFUL_STRIKE_RANGE = 12.5f;
// A yard and a half of slack on top, so a bot that steps out of range stays out while its next
// tick is pending.
inline constexpr float PATCHWERK_STAND_CLEAR_RANGE = PATCHWERK_HATEFUL_STRIKE_RANGE + 1.5f;
// How long the step out of it is. MovementAction::FleePosition reads this as the length of the
// step, not as a distance to keep from the boss, and may take it sideways, so it is the whole
// range plus three yards rather than the difference.
inline constexpr float PATCHWERK_STAND_CLEAR_DISTANCE = PATCHWERK_STAND_CLEAR_RANGE + 3.0f;

// Roles

// Who a trigger of this raid speaks to. Healers are kept out of every target switch: a cut heal
// costs more than an add lives.
enum class NaxxRole : uint8
{
    MainTank,
    Tanks,
    AssistTanks,
    Dps,
};

bool HasRole(Player* bot, NaxxRole role);

// Bosses and adds

// The threat-list lookup of "find target", by creature entry rather than by name, as in
// ZulGurubHelpers::FindThreatCreature. Patchwerk, Noth and Gothik are all BossAI and call
// DoZoneInCombat on the pull, and every add of these two fights is put in combat with the zone as
// it is summoned (BNO:163, BGO:242, :268), so each of them has every bot on its threat list.
Unit* FindThreatCreature(Player* bot, uint32 entry);
GuidVector FindCreatureGuids(Player* bot, std::vector<uint32> const& entries, float radius);
std::vector<Unit*> GetCachedUnits(PlayerbotAI* botAI, char const* value);
Unit* GetNearestCachedUnit(PlayerbotAI* botAI, char const* value);
// A creature flagged out of reach cannot be damaged, and an order to attack one only sends the bot
// running at a target it cannot touch.
bool IsUnassailable(Unit* unit);
// True while the boss is swinging at someone who is not a tank: Noth's Blink drops his whole threat
// list (BNO:224) and Gothik's teleport does the same (BGO:436), and Hateful Strike hands 500 threat
// to whoever it hits (BPA:145).
bool IsBossOnNonTank(Unit* boss);
// True while the boss can be held at all. Noth is flagged out of reach on his balcony, and Gothik
// is rooted and takes no damage while he waves adds in, with half his room walled off on top.
bool IsBossEngageable(PlayerbotAI* botAI, Unit* boss);
bool IsGameObjectOpen(Player* bot, uint32 entry, float radius);

// Noth the Plaguebringer

// Noth spends 70 of every 180 seconds on his balcony, flagged not selectable and rooted (BNO:113,
// :117), while the raid fights the waves he summons from up there.
bool IsNothOnBalcony(Unit* noth);

// Gothik the Harvester

bool IsOnLiveSide(WorldObject const* who);
bool IsGothikGateOpen(PlayerbotAI* botAI);
// Until the gate opens, the half of the room a bot is not standing in may as well not exist.
bool IsReachableAcrossGothikGate(PlayerbotAI* botAI, WorldObject const* who);
// The nearest add of the value that this bot can actually walk up to.
Unit* GetNearestReachableGothikAdd(PlayerbotAI* botAI, char const* value);
// Gothik waves adds in from his balcony for the first four and a half minutes, rooted
// (UNIT_FLAG_DISABLE_MOVE, BGO:228) and taking no damage at all (BGO:360), and drops both the flag
// and the immunity when the last wave is out (BGO:471).
bool IsGothikWavePhase(Unit* gothik);

}  // namespace NaxxHelpers

#endif
