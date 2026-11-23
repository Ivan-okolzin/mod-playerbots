/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#ifndef PLAYERBOTS_CRUSADERHELPERS_H
#define PLAYERBOTS_CRUSADERHELPERS_H

#include "Common.h"
#include "ObjectGuid.h"
#include "Position.h"
#include <cmath>
#include <type_traits>
#include <vector>

class Player;
class PlayerbotAI;
class Unit;

namespace CrusaderHelpers
{

template <typename T, std::enable_if_t<std::is_enum_v<T>, int> = 0>
constexpr uint32 Id(T value)
{
    return static_cast<uint32>(value);
}

// Spell ids are taken from the encounter scripts of
// src/server/scripts/Northrend/CrusadersColiseum/TrialOfTheCrusader/. The references name the file
// and line: BNB = boss_northrend_beasts.cpp, BLJ = boss_lord_jaraxxus.cpp, BTV = boss_twin_valkyr.cpp,
// BAT = boss_anubarak_trial.cpp, TOC = trial_of_the_crusader.h.
enum class CrusaderSpells : uint32
{
    // Gormok the Impaler
    SPELL_IMPALE                       = 66331,  // BNB:33, on the victim every 9-10s (BNB:412)
    SPELL_SNOBOLLED                    = 66406,  // BNB:38, on the Snobold's carrier (BNB:285)

    // Acidmaw and Dreadscale
    SPELL_PARALYTIC_TOXIN              = 66823,  // BNB:909, ramps to Paralysis 66830 (BNB:950)
    SPELL_PARALYTIC_TOXIN_25           = 67618,  // BNB:909
    SPELL_PARALYTIC_TOXIN_10H          = 67619,  // BNB:909
    SPELL_PARALYTIC_TOXIN_25H          = 67620,  // BNB:909

    // Twin Val'kyr
    SPELL_LIGHT_ESSENCE                = 65686,  // BTV:64, 10-man normal
    SPELL_LIGHT_ESSENCE_25             = 67222,  // BTV:641, difficulty table of the gossip handler
    SPELL_LIGHT_ESSENCE_10H            = 67223,  // BTV:648
    SPELL_LIGHT_ESSENCE_25H            = 67224,  // BTV:655
    SPELL_DARK_ESSENCE                 = 65684,  // BTV:66, 10-man normal
    SPELL_DARK_ESSENCE_25              = 67176,  // BTV:595
    SPELL_DARK_ESSENCE_10H             = 67177,  // BTV:602
    SPELL_DARK_ESSENCE_25H             = 67178,  // BTV:609

    // Anub'arak
    SPELL_ANUBARAK_SUBMERGE            = 65981,  // BAT:90, phase 2 for one minute (BAT:317)
    SPELL_PURSUING_SPIKE_MARK          = 67574,  // BAT:102, on the pursued player (BAT:803)
};

enum class CrusaderNpcs : uint32
{
    // Northrend Beasts
    NPC_GORMOK                         = 34796,  // TOC:161
    NPC_SNOBOLD_VASSAL                 = 34800,  // BNB:72
    NPC_DREADSCALE                     = 34799,  // TOC:162
    NPC_ACIDMAW                        = 35144,  // TOC:163
    NPC_SLIME_POOL                     = 35176,  // summon of SUMMON_SLIME_POOL 66883 (BNB:824)
    NPC_ICEHOWL                        = 34797,  // TOC:164
    NPC_FURIOUS_CHARGE_STALKER         = 35062,  // BNB:985, marks the charge lane (BNB:1169)

    // Lord Jaraxxus
    NPC_JARAXXUS                       = 34780,  // TOC:166
    NPC_LEGION_FLAME                   = 34784,  // summon of SPELL_LEGION_FLAME 66197 (BLJ:188)
    NPC_MISTRESS_OF_PAIN               = 34826,  // TOC:167
    NPC_FELFLAME_INFERNAL              = 34815,  // npc_fel_infernal (BLJ:233)

    // Faction Champions, horde side (TOC:188)
    NPC_HORDE_DRUID_RESTORATION        = 34459,  // TOC:190
    NPC_HORDE_PALADIN_HOLY             = 34445,  // TOC:193
    NPC_HORDE_PRIEST_DISCIPLINE        = 34447,  // TOC:195
    NPC_HORDE_SHAMAN_RESTORATION       = 34444,  // TOC:199
    NPC_HORDE_WARLOCK                  = 34450,  // TOC:200
    NPC_HORDE_MAGE                     = 34449,  // TOC:192
    NPC_HORDE_PRIEST_SHADOW            = 34441,  // TOC:196
    NPC_HORDE_DRUID_BALANCE            = 34451,  // TOC:189
    NPC_HORDE_HUNTER                   = 34448,  // TOC:191
    NPC_HORDE_ROGUE                    = 34454,  // TOC:197
    NPC_HORDE_DEATH_KNIGHT             = 34458,  // TOC:188
    NPC_HORDE_SHAMAN_ENHANCEMENT       = 34455,  // TOC:198
    NPC_HORDE_PALADIN_RETRIBUTION      = 34456,  // TOC:194
    NPC_HORDE_WARRIOR                  = 34453,  // TOC:201

    // Faction Champions, alliance side (TOC:173)
    NPC_ALLIANCE_DRUID_RESTORATION     = 34469,  // TOC:175
    NPC_ALLIANCE_PALADIN_HOLY          = 34465,  // TOC:178
    NPC_ALLIANCE_PRIEST_DISCIPLINE     = 34466,  // TOC:180
    NPC_ALLIANCE_SHAMAN_RESTORATION    = 34470,  // TOC:184
    NPC_ALLIANCE_WARLOCK               = 34474,  // TOC:185
    NPC_ALLIANCE_MAGE                  = 34468,  // TOC:177
    NPC_ALLIANCE_PRIEST_SHADOW         = 34473,  // TOC:181
    NPC_ALLIANCE_DRUID_BALANCE         = 34460,  // TOC:174
    NPC_ALLIANCE_HUNTER                = 34467,  // TOC:176
    NPC_ALLIANCE_ROGUE                 = 34472,  // TOC:182
    NPC_ALLIANCE_DEATH_KNIGHT          = 34461,  // TOC:173
    NPC_ALLIANCE_SHAMAN_ENHANCEMENT    = 34463,  // TOC:183
    NPC_ALLIANCE_PALADIN_RETRIBUTION   = 34471,  // TOC:179
    NPC_ALLIANCE_WARRIOR               = 34475,  // TOC:186

    // Twin Val'kyr
    NPC_FJOLA_LIGHTBANE                = 34497,  // TOC:206
    NPC_EYDIS_DARKBANE                 = 34496,  // TOC:207
    NPC_LIGHT_ESSENCE                  = 34568,  // BTV:57, gossip swaps the aura (BTV:578)
    NPC_DARK_ESSENCE                   = 34567,  // BTV:56, gossip swaps the aura (BTV:624)
    NPC_CONCENTRATED_LIGHT             = 34630,  // BTV:59
    NPC_CONCENTRATED_DARKNESS          = 34628,  // BTV:58

    // Anub'arak
    NPC_ANUBARAK                       = 34564,  // TOC:209
    NPC_FROST_SPHERE                   = 34606,  // BAT:45
    NPC_NERUBIAN_BURROWER              = 34607,  // BAT:47
    NPC_SWARM_SCARAB                   = 34605,  // BAT:48
    NPC_PURSUING_SPIKE                 = 34660,  // BAT:49
};

// Display ids of the mobile shape of each jormungar (BNB:604). The script itself tells the two
// shapes apart by display id, and they trade shapes on every submerge (BNB:786).
enum class CrusaderModels : uint32
{
    MODEL_ACIDMAW_MOBILE               = 29816,  // BNB:605
    MODEL_DREADSCALE_MOBILE            = 24564,  // BNB:607
};

inline constexpr uint32 CRUSADER_MAP_ID = 649;
inline constexpr uint32 CRUSADER_CACHE_INTERVAL_MS = 200;
inline constexpr float ADD_SEARCH_RADIUS = 100.0f;

// Cached add and hazard values, registered in CrusaderValueContext.h.
inline constexpr char const* GORMOK_SNOBOLDS_VALUE = "crusader gormok snobolds";
inline constexpr char const* JORMUNGAR_SLIME_POOLS_VALUE = "crusader jormungar slime pools";
inline constexpr char const* ICEHOWL_CHARGE_STALKERS_VALUE = "crusader icehowl charge stalkers";
inline constexpr char const* JARAXXUS_LEGION_FLAMES_VALUE = "crusader jaraxxus legion flames";
inline constexpr char const* JARAXXUS_DEMONS_VALUE = "crusader jaraxxus demons";
inline constexpr char const* VALKYR_ESSENCES_VALUE = "crusader twin val'kyr essences";
inline constexpr char const* VALKYR_LIGHT_BALLS_VALUE = "crusader twin val'kyr light balls";
inline constexpr char const* VALKYR_DARK_BALLS_VALUE = "crusader twin val'kyr dark balls";
inline constexpr char const* ANUBARAK_BURROWERS_VALUE = "crusader anub'arak burrowers";
inline constexpr char const* ANUBARAK_SCARABS_VALUE = "crusader anub'arak scarabs";
inline constexpr char const* ANUBARAK_FROST_SPHERES_VALUE = "crusader anub'arak frost spheres";
inline constexpr char const* ANUBARAK_SPIKES_VALUE = "crusader anub'arak pursuing spikes";

// The floor of the upper arena, which the Beasts, Jaraxxus, the Champions and the Val'kyr are
// fought on. Icehowl jumps here before his charge and the Val'kyr balls circle it (TOC:302).
inline constexpr float ARENA_CENTER_X = 563.673f;
inline constexpr float ARENA_CENTER_Y = 139.571f;
// Icehowl's charge ends 50 yards out from the centre, 46 towards the main gate (BNB:1163), which is
// where the arena wall stands. A bot further out than this has no room to step aside.
inline constexpr float ARENA_WALL_DISTANCE = 38.0f;
inline constexpr float ARENA_SAFE_DISTANCE = 30.0f;

// Hazard radii. Each is the mechanic's own reach plus a yard of slack, so a bot that steps out
// stays out while its next tick is pending. Both are estimates from the creature's visual size:
// neither ground effect's radius is in the script, so they are confirmed by a live test.
inline constexpr float SLIME_POOL_RADIUS = 10.0f;
inline constexpr float LEGION_FLAME_RADIUS = 7.0f;
// Trample hits everything within 12 yards of Icehowl while he charges (BNB:1066).
inline constexpr float TRAMPLE_LANE_WIDTH = 14.0f;
inline constexpr float TRAMPLE_DODGE_DISTANCE = 20.0f;
// A Concentrated ball bursts as soon as a player comes within 2.75 yards of it (BTV:880).
inline constexpr float BALL_BURST_RADIUS = 6.0f;
inline constexpr float BALL_COLLECT_RADIUS = 12.0f;
// The spike dies on a Frost Sphere within 8 yards of it (BAT:872), so the pursued player has to
// run over one. The Permafrost patch itself is on the floor, the unbroken spheres hover 13 yards
// above it (BAT:64, :594).
inline constexpr float PERMAFROST_REACH = 6.0f;
inline constexpr float SPIKE_ESCAPE_DISTANCE = 25.0f;
// The spike casts Impale around itself on every tick of its trail (BAT:881); the radius is not in
// the script, so this is an estimate to confirm by a live test.
inline constexpr float SPIKE_HAZARD_RADIUS = 8.0f;
// Spacing for the spells that pick a random player: Arctic Breath (BNB:1134), Fel Lightning and
// Legion Flame (BLJ:166, :185).
inline constexpr float SPREAD_DISTANCE = 10.0f;
// How far a bot walks per tick when it follows a path, and how close it has to be to an Essence
// before it can talk to it (the core's INTERACTION_DISTANCE is 5 yards).
inline constexpr float PATH_STEP_DISTANCE = 3.5f;
inline constexpr float ESSENCE_INTERACT_DISTANCE = 4.0f;

// Impale stacks on whoever Gormok is hitting (BNB:412). Three stacks is where the second tank
// takes over, as the raid guides have it.
inline constexpr uint8 IMPALE_SWAP_STACKS = 3;

// Bosses and adds

// The threat-list lookup of "find target", by creature entry rather than by name. Names cannot
// address this raid: the pursuing spike 34660 is called Anub'arak just like the boss 34564, and
// Gormok, Icehowl and both Val'kyr each share their name with a second creature template
// (35469, 35470, 36065, 36066).
Unit* FindThreatCreature(Player* bot, uint32 entry);
GuidVector FindCreatureGuids(Player* bot, std::vector<uint32> const& entries, float radius);
std::vector<Unit*> GetCachedUnits(PlayerbotAI* botAI, char const* value);
Unit* GetNearestCachedUnit(PlayerbotAI* botAI, char const* value);
Unit* GetNearestCachedUnitOfEntry(PlayerbotAI* botAI, char const* value, uint32 entry);
// Several of this raid's adds spend part of their life untargetable: the Burrowers while they are
// submerged (BAT:688), the Scarabs that decorate the floor before the pull (BAT:191), and the
// Snobolds that are still riding Gormok. None of them is worth an attack order.
bool IsAttackableNow(Unit* unit);
Unit* GetNearestAttackableCachedUnit(PlayerbotAI* botAI, char const* value);

// Creature hazards

bool IsNearCachedUnit(PlayerbotAI* botAI, char const* value, float radius);
// The closest point outside every hazard of this value, searched on rings around the bot.
bool FindPositionAwayFromCachedUnits(
    PlayerbotAI* botAI, char const* value, float radius, Position& outPos);

// Tanking

// Same class switch as SSCHelpers::CastTankTaunt and Aq40Helpers::CastTankTaunt; the fourth copy,
// and overdue for a move into EncounterHelpers.
bool CastTankTaunt(PlayerbotAI* botAI, Unit* target);
uint8 GetAuraStacks(Unit* unit, uint32 spellId);

// Gormok the Impaler

// Snobolled 66406 rides the carrier until its Snobold dies (BNB:318). The Snobold also attacks
// nobody but its carrier (BNB:122), which tells the same thing without depending on the aura id
// being the same on every difficulty.
bool IsSnobolled(PlayerbotAI* botAI, Player* bot);
// A Snobold still sitting on Gormok cannot be attacked at all (BNB:195, EnterVehicleUnattackable).
// The ones worth hitting are those latched onto a raid member and those a dead Gormok threw off
// (BNB:333), told apart by whose vehicle they are riding.
Unit* GetNearestLatchedSnobold(PlayerbotAI* botAI);

// Acidmaw and Dreadscale

// The mobile jormungar bites its tank and drops Slime Pools; the stationary one spits from where
// it stands. They trade shapes on every submerge, so the shape is read from the display id.
bool IsWormMobile(Unit* worm);
// Submerged for about 25 seconds in the middle of the swap, and not attackable until it is back
// (BNB:753, :801).
bool IsWormSubmerged(Unit* worm);
bool HasParalyticToxin(Unit* unit);
// The worm this bot is to hold: the tank without Paralytic Toxin takes the biting (mobile) worm
// and the other tank takes the one that stays put. Null for everyone who is not one of the two
// tanks, or while that worm is submerged.
Unit* GetAssignedWorm(PlayerbotAI* botAI);

// Icehowl

// Icehowl drops his victim for the whole jump-crash-stare-charge sequence and only takes one
// again once it is over (BNB:1142, :1106), which bounds every object written for it.
bool IsIcehowlCharging(Unit* icehowl);

// Faction Champions

// The champion the raid is to kill next: healers first, then the ranged, then the melee, and the
// lowest health of the tier among those still on the bot's threat list. Every bot works it out
// from the same numbers, so the raid focuses without being told.
Unit* FindFactionChampionFocus(Player* bot);
bool IsFactionChampion(uint32 entry);

// Twin Val'kyr

enum class CrusaderEssence : uint8
{
    None,
    Light,
    Dark,
};

// Light Essence absorbs the light damage of Fjola and her balls and turns it into Powering Up
// (BTV:742); dark damage lands in full. Dark Essence is the other way round.
CrusaderEssence GetEssence(Player* bot);
// Half the raid each, with the tanks matched to the twin they hold.
CrusaderEssence GetAssignedEssence(Player* bot);
// Only non-triggered heal the twins cast is Twin's Pact (BTV:444, :453), so a positive cast in
// progress is that heal, whatever the difficulty's spell id.
bool IsCastingHeal(Unit* unit);
Unit* GetPactingTwin(PlayerbotAI* botAI);
// The cached ball value this bot is to walk into, or the one it is to keep away from. Null until
// the bot holds an essence, since neither ball means anything to it before that.
char const* GetBallValue(Player* bot, bool matching);

// Anub'arak

// Phase 2: submerged, not attackable, and the pursuing spike is out (BAT:319).
bool IsAnubarakSubmerged(Unit* anubarak);
bool IsPursuedBySpike(PlayerbotAI* botAI, Player* bot);
// A Frost Sphere that has been shot down and is now a Permafrost patch on the floor, which is
// what kills the spike. Told apart from the hovering ones by height (BAT:594).
Unit* GetNearestPermafrost(PlayerbotAI* botAI);
Unit* GetNearestHoveringFrostSphere(PlayerbotAI* botAI);

}

#endif
