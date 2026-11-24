/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#ifndef PLAYERBOTS_ULDHELPERS_H
#define PLAYERBOTS_ULDHELPERS_H

#include "Common.h"
#include "ObjectGuid.h"
#include "Position.h"
#include <type_traits>
#include <vector>

class Player;
class PlayerbotAI;
class Unit;

namespace UldHelpers
{

template <typename T, std::enable_if_t<std::is_enum_v<T>, int> = 0>
constexpr uint32 Id(T value)
{
    return static_cast<uint32>(value);
}

// Spell and creature ids are taken from the encounter scripts of
// src/server/scripts/Northrend/Ulduar/Ulduar/. The references name the file and line:
// BXT = boss_xt002.cpp, BIG = boss_ignis.cpp, BAU = boss_auriaya.cpp,
// BAL = boss_algalon_the_observer.cpp, ULD = ulduar.h.
// The 25-man ids are the DifficultySpellID_2 column of spelldifficulty_dbc; the spells without a
// row there keep one id for both raid sizes.
enum class UldSpells : uint32
{
    // XT-002 Deconstructor
    SPELL_SEARING_LIGHT              = 63018,  // BXT:40, one random non-tank, then a Life Spark
    SPELL_SEARING_LIGHT_25           = 65121,  // BXT:718
    SPELL_GRAVITY_BOMB               = 63024,  // BXT:43, one random non-tank, then a Void Zone
    SPELL_GRAVITY_BOMB_25            = 64234,  // BXT:763
    SPELL_EXPOSED_HEART              = 63849,  // BXT:60, channelled while the heart is out (BXT:293)

    // Ignis the Furnace Master
    SPELL_STRENGTH_OF_THE_CREATOR    = 64473,  // BIG:34, one stack per living construct (BIG:125)
    SPELL_MOLTEN                     = 62373,  // BIG:45, at ten Heat stacks (BIG:133-140)
    SPELL_BRITTLE                    = 62382,  // BIG:46, in the water (BIG:161-166)
    SPELL_BRITTLE_25                 = 67114,  // BIG:481, the second id the Brittle script covers

    // Algalon the Observer
    SPELL_PHASE_PUNCH                = 64412,  // BAL:42, on the victim every 15.5s (BAL:716)
    SPELL_BIG_BANG                   = 64443,  // BAL:43, an 8s cast every 90.5s (BAL:757)
    SPELL_BIG_BANG_25                = 64584,
};

enum class UldNpcs : uint32
{
    // XT-002 Deconstructor. The 25-man entries are difficulty_entry_1 in creature_template.
    NPC_XT002                        = 33293,  // ULD:167
    NPC_XT002_25                     = 33885,
    NPC_HEART_OF_DECONSTRUCTOR       = 33329,  // ULD:170, the vehicle passenger of the heart phase
    NPC_HEART_OF_DECONSTRUCTOR_25    = 33995,
    NPC_SCRAPBOT                     = 33343,  // ULD:169, heals XT-002 on arrival (BXT:508-513)
    NPC_SCRAPBOT_25                  = 33887,
    NPC_PUMMELLER                    = 33344,  // npc_pummeller (BXT:534), the only add that tanks
    NPC_PUMMELLER_25                 = 33888,
    NPC_BOOMBOT                      = 33346,  // npc_boombot (BXT:592), explodes at half health
    NPC_BOOMBOT_25                   = 33886,
    NPC_LIFE_SPARK                   = 34004,  // npc_life_spark (BXT:659), out of Searing Light
    NPC_LIFE_SPARK_25                = 34005,
    NPC_XT_VOID_ZONE                 = 34001,  // npc_xt_void_zone (BXT:697), out of Gravity Bomb

    // Ignis the Furnace Master
    NPC_IGNIS                        = 33118,  // ULD:165
    NPC_IGNIS_25                     = 33190,
    NPC_IRON_CONSTRUCT               = 33121,  // BIG:52
    NPC_IRON_CONSTRUCT_25            = 33191,
    NPC_SCORCHED_GROUND              = 33123,  // BIG:53, left 20 yards ahead of Ignis (BIG:405)
    // The water the script itself looks for to turn a Molten construct Brittle (BIG:54, :162).
    // Only two of these are spawned on map 603, one in each pool of the Ignis room.
    NPC_WATER_TRIGGER                = 22515,

    // Auriaya
    NPC_AURIAYA                      = 33515,  // ULD:175
    NPC_AURIAYA_25                   = 34175,
    NPC_SANCTUM_SENTRY               = 34014,  // BAU:63, in her formation from the pull
    NPC_SANCTUM_SENTRY_25            = 34166,
    NPC_FERAL_DEFENDER               = 34035,  // BAU:62, eight lives (BAU:322)
    NPC_FERAL_DEFENDER_25            = 34171,
    NPC_SEEPING_FERAL_ESSENCE        = 34098,  // BAU:64, one pool per life spent (BAU:350)
    NPC_SEEPING_FERAL_ESSENCE_25     = 34174,

    // Algalon the Observer
    NPC_ALGALON                      = 32871,  // ULD:186
    NPC_ALGALON_25                   = 33070,
    NPC_COLLAPSING_STAR              = 32955,  // ULD:247, four of them every minute (BXT, BAL:720)
    NPC_COLLAPSING_STAR_25           = 34215,
    NPC_BLACK_HOLE                   = 32953,  // ULD:248, what a killed Collapsing Star leaves
    NPC_BLACK_HOLE_25                = 34296,
    NPC_LIVING_CONSTELLATION         = 33052,  // ULD:245, three activated every 50s (BAL:350-363)
    NPC_LIVING_CONSTELLATION_25      = 33116,
    NPC_ASTEROID_TARGET_01           = 33104,  // ULD:251, the Cosmic Smash mark on the floor
    NPC_ASTEROID_TARGET_02           = 33105,  // ULD:252, the asteroid 35 yards above it (BAL:577)
    NPC_ASTEROID_TARGET_02_25        = 34131,
    NPC_UNLEASHED_DARK_MATTER        = 34097,  // ULD:253, out of the phase two Worm Holes (BAL:619)
    NPC_UNLEASHED_DARK_MATTER_25     = 34222,
};

inline constexpr uint32 ULD_MAP_ID = 603;
inline constexpr uint32 ULD_CACHE_INTERVAL_MS = 200;
inline constexpr float ADD_SEARCH_RADIUS = 100.0f;

// Cached add and hazard values, registered in UldValueContext.h.
inline constexpr char const* XT002_HEARTS_VALUE = "ulduar xt-002 hearts";
inline constexpr char const* XT002_VOID_ZONES_VALUE = "ulduar xt-002 void zones";
inline constexpr char const* XT002_LIFE_SPARKS_VALUE = "ulduar xt-002 life sparks";
inline constexpr char const* HODIR_PLAYER_ICE_VALUE = "ulduar hodir player ice";
inline constexpr char const* FREYA_STRENGTHENED_IRON_ROOTS_VALUE = "ulduar freya strengthened iron roots";
inline constexpr char const* VEZAX_SARONITE_ANIMUS_VALUE = "ulduar vezax saronite animus";
inline constexpr char const* XT002_SCRAPBOTS_VALUE = "ulduar xt-002 scrapbots";
inline constexpr char const* XT002_PUMMELLERS_VALUE = "ulduar xt-002 pummellers";
inline constexpr char const* XT002_BOOMBOTS_VALUE = "ulduar xt-002 boombots";
inline constexpr char const* IGNIS_CONSTRUCTS_VALUE = "ulduar ignis iron constructs";
inline constexpr char const* IGNIS_SCORCHED_GROUND_VALUE = "ulduar ignis scorched ground";
inline constexpr char const* IGNIS_WATER_TRIGGERS_VALUE = "ulduar ignis water triggers";
inline constexpr char const* AURIAYA_SENTRIES_VALUE = "ulduar auriaya sanctum sentries";
inline constexpr char const* AURIAYA_FERAL_DEFENDERS_VALUE = "ulduar auriaya feral defenders";
inline constexpr char const* AURIAYA_SEEPING_ESSENCES_VALUE = "ulduar auriaya seeping essences";
inline constexpr char const* ALGALON_COLLAPSING_STARS_VALUE = "ulduar algalon collapsing stars";
inline constexpr char const* ALGALON_BLACK_HOLES_VALUE = "ulduar algalon black holes";
inline constexpr char const* ALGALON_CONSTELLATIONS_VALUE = "ulduar algalon living constellations";
inline constexpr char const* ALGALON_COSMIC_SMASH_VALUE = "ulduar algalon cosmic smash targets";
inline constexpr char const* ALGALON_DARK_MATTER_VALUE = "ulduar algalon unleashed dark matter";

// Spacing for the spells that pick one random player and hurt the ground around it: Searing Light
// and Gravity Bomb (BXT:372, :376, :724-730) and Arcane Barrage (BAL:1095).
inline constexpr float SPREAD_DISTANCE = 10.0f;
// How far a bot walks per tick when it follows a path.
inline constexpr float PATH_STEP_DISTANCE = 3.5f;

// Hazard reaches. Only the Cosmic Smash figure is in a script; the rest are the mechanic's visual
// size plus a yard of slack, and each is to be confirmed by a live test.
inline constexpr float VOID_ZONE_RADIUS = 12.0f;
inline constexpr float BOOMBOT_BLAST_RADIUS = 12.0f;
inline constexpr float SCORCHED_GROUND_RADIUS = 10.0f;
inline constexpr float SEEPING_ESSENCE_RADIUS = 10.0f;
// Cosmic Smash damage is divided by the distance past 6 yards and halved again past 10 (BAL:1316).
inline constexpr float COSMIC_SMASH_RADIUS = 12.0f;
// Gravity Bomb pulls the raid in and then hurts everyone around its carrier (BXT:782-791), so the
// carrier walks this far out of the raid. An estimate, like the hazard radii above.
inline constexpr float GRAVITY_BOMB_SPREAD_DISTANCE = 15.0f;
// A Molten construct turns Brittle within 18 yards of the water (BIG:162); the tank aims closer
// than that so the construct is inside the range while the next tick is pending.
inline constexpr float WATER_DOUSE_DISTANCE = 12.0f;
// Big Bang spares only what is inside a Black Hole. Neither the hole's reach nor its visual size
// is in the script, so a bot walks into the middle of it: an estimate to confirm by a live test.
inline constexpr float BLACK_HOLE_SHELTER_RADIUS = 3.0f;

// Phase Punch banishes the tank at five stacks (BAL:1246), so the second tank takes over before.
inline constexpr uint8 PHASE_PUNCH_SWAP_STACKS = 4;

// Bosses and adds

// The threat-list lookup of "find target", by creature entry rather than by name. Names cannot
// address this raid: every boss and almost every add of it has a second creature template under
// the same name for the 25-man raid, and three templates are called "Void Zone".
Unit* FindThreatCreature(Player* bot, std::vector<uint32> const& entries);
GuidVector FindCreatureGuids(Player* bot, std::vector<uint32> const& entries, float radius);
std::vector<Unit*> GetCachedUnits(PlayerbotAI* botAI, char const* value);
Unit* GetNearestCachedUnit(PlayerbotAI* botAI, char const* value);
// Several of this raid's adds spend part of their life untargetable: an Iron Construct before
// Ignis activates it (BIG:104), the heart while XT-002 stands (BXT:463), and the Feral Defender
// between its lives (BAU:346). None of them is worth an attack order.
bool IsAttackableNow(Unit* unit);
Unit* GetNearestAttackableCachedUnit(PlayerbotAI* botAI, char const* value);

// Creature hazards

bool IsNearCachedUnit(PlayerbotAI* botAI, char const* value, float radius);
// The closest point outside every hazard of this value, searched on rings around the bot.
bool FindPositionAwayFromCachedUnits(
    PlayerbotAI* botAI, char const* value, float radius, Position& outPos);

// Tanking

// Same class switch as CrusaderHelpers::CastTankTaunt, VoAHelpers::CastTankTaunt and
// SSCHelpers::CastTankTaunt; another copy, and overdue for a move into EncounterHelpers.
bool CastTankTaunt(PlayerbotAI* botAI, Unit* target);
uint8 GetAuraStacks(Unit* unit, uint32 spellId);

// XT-002 Deconstructor

// The heart is out for 30 seconds at 75%, 50% and 25% health (BXT:240, :388-399). XT-002 is
// unselectable and passive for all of it (BXT:236, :394) and the heart is unselectable outside
// it (BXT:463), so the heart being attackable is what bounds the phase on both sides.
Unit* GetExposedHeart(PlayerbotAI* botAI);
bool HasGravityBomb(Player* bot);

// Ignis the Furnace Master

// Ignis activates one construct every 30 to 40 seconds and gains a stack of Strength of the
// Creator for it (BIG:220, :306-316). The ones that are still asleep cannot be touched (BIG:104).
Unit* GetNearestActiveConstruct(PlayerbotAI* botAI);
// Molten resets the construct's threat as it lands (BIG:140), so the tank has to take it again.
bool IsConstructMolten(Unit* construct);
// Brittle dies to the next hit of 5000 damage, whoever lands it (BIG:491-503).
bool IsConstructBrittle(Unit* construct);
Unit* GetBrittleConstruct(PlayerbotAI* botAI);
// The Molten construct this bot is holding, which is the one it can walk into the water.
Unit* GetHeldMoltenConstruct(PlayerbotAI* botAI);
Unit* GetNearestWaterTrigger(PlayerbotAI* botAI);

// Algalon the Observer

// Big Bang is cast rather than triggered (BAL:757) and takes 8 seconds, which is the window the
// raid has to reach a Black Hole.
bool IsBigBangIncoming(Unit* algalon);
// The Black Holes are gone from 20% health onwards, when Algalon despawns them (BAL:613), so from
// there on Big Bang is healed through instead of hidden from.
Unit* GetNearestBlackHole(PlayerbotAI* botAI);
// A Constellation despawns, with the Black Hole, when the two meet (BAL:1063-1078); nothing else
// removes one. The bot it is chasing is the one that can walk it there.
Unit* GetChasingConstellation(PlayerbotAI* botAI);

}

#endif
