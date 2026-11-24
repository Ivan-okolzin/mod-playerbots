/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#ifndef PLAYERBOTS_AQ40HELPERS_H
#define PLAYERBOTS_AQ40HELPERS_H

#include "Common.h"
#include "ObjectGuid.h"
#include "Position.h"
#include <cmath>
#include <optional>
#include <type_traits>
#include <vector>

class Player;
class PlayerbotAI;
class Unit;

namespace Aq40Helpers
{

template <typename T, std::enable_if_t<std::is_enum_v<T>, int> = 0>
constexpr uint32 Id(T value)
{
    return static_cast<uint32>(value);
}

enum class Aq40Spells : uint32
{
    // The Prophet Skeram
    SPELL_TRUE_FULFILLMENT     = 785,

    // Silithid Royalty
    SPELL_POISON_CLOUD         = 26590,

    // Battleguard Sartura
    SPELL_WHIRLWIND            = 26083,
    SPELL_GUARD_WHIRLWIND      = 26038,

    // Fankriss the Unyielding
    SPELL_MORTAL_WOUND         = 25646,

    // Viscidus
    SPELL_VISCIDUS_FREEZE      = 25937,

    // Princess Huhuran
    SPELL_NOXIOUS_POISON       = 26053,
    SPELL_WYVERN_STING         = 26180,

    // Twin Emperors
    SPELL_BLIZZARD             = 26607,

    // C'Thun
    SPELL_FREEZE_ANIM          = 16245,
    SPELL_RED_COLORATION       = 22518,
    SPELL_CARAPACE_OF_CTHUN    = 26156,
    SPELL_DIGESTIVE_ACID       = 26476,
};

enum class Aq40Npcs : uint32
{
    NPC_SKERAM                 = 15263,
    NPC_VEM                    = 15544,
    NPC_LORD_KRI               = 15511,
    NPC_PRINCESS_YAUJ          = 15543,
    NPC_YAUJ_BROOD             = 15621,
    NPC_SARTURA                = 15516,
    NPC_SARTURA_ROYAL_GUARD    = 15984,
    NPC_FANKRISS               = 15510,
    NPC_SPAWN_OF_FANKRISS      = 15630,
    NPC_VEKNISS_HATCHLING      = 15962,
    NPC_VISCIDUS               = 15299,
    NPC_GLOB_OF_VISCIDUS       = 15667,
    NPC_HUHURAN                = 15509,
    NPC_VEKNILASH              = 15275,
    NPC_VEKLOR                 = 15276,
    NPC_OURO                   = 15517,
    NPC_DIRT_MOUND             = 15712,
    NPC_OURO_SCARAB            = 15718,
    NPC_EYE_OF_CTHUN           = 15589,
    NPC_CTHUN                  = 15727,
    NPC_CLAW_TENTACLE          = 15725,
    NPC_EYE_TENTACLE           = 15726,
    NPC_GIANT_CLAW_TENTACLE    = 15728,
    NPC_GIANT_EYE_TENTACLE     = 15334,
    NPC_FLESH_TENTACLE         = 15802,
};

inline constexpr uint32 AQ40_MAP_ID = 531;
inline constexpr uint32 AQ40_CACHE_INTERVAL_MS = 200;
inline constexpr float ADD_SEARCH_RADIUS = 100.0f;
inline constexpr float HAZARD_SEARCH_RADIUS = 60.0f;

// Boss names as the creature templates spell them, for "find target".
inline constexpr char const* SKERAM_NAME = "the prophet skeram";
inline constexpr char const* VEM_NAME = "vem";
inline constexpr char const* LORD_KRI_NAME = "lord kri";
inline constexpr char const* PRINCESS_YAUJ_NAME = "princess yauj";
inline constexpr char const* SARTURA_NAME = "battleguard sartura";
inline constexpr char const* FANKRISS_NAME = "fankriss the unyielding";
inline constexpr char const* VISCIDUS_NAME = "viscidus";
inline constexpr char const* HUHURAN_NAME = "princess huhuran";
inline constexpr char const* VEKNILASH_NAME = "emperor vek'nilash";
inline constexpr char const* VEKLOR_NAME = "emperor vek'lor";
inline constexpr char const* OURO_NAME = "ouro";
inline constexpr char const* CTHUN_EYE_NAME = "eye of c'thun";
inline constexpr char const* CTHUN_NAME = "c'thun";

// Cached add and hazard values, registered in Aq40ValueContext.h.
inline constexpr char const* SKERAM_COPIES_VALUE = "aq40 skeram copies";
inline constexpr char const* YAUJ_BROOD_VALUE = "aq40 yauj brood";
inline constexpr char const* ROYAL_GUARDS_VALUE = "aq40 royal guards";
inline constexpr char const* FANKRISS_SPAWNS_VALUE = "aq40 spawns of fankriss";
inline constexpr char const* FANKRISS_WORMS_VALUE = "aq40 fankriss worms";
inline constexpr char const* VISCIDUS_GLOBS_VALUE = "aq40 viscidus globs";
inline constexpr char const* DIRT_MOUNDS_VALUE = "aq40 dirt mounds";
inline constexpr char const* OURO_SCARABS_VALUE = "aq40 ouro scarabs";
inline constexpr char const* POISON_CLOUD_VALUE = "aq40 poison cloud";
inline constexpr char const* NOXIOUS_POISON_VALUE = "aq40 noxious poison";
inline constexpr char const* BLIZZARD_VALUE = "aq40 blizzard";
inline constexpr char const* CTHUN_CLAW_TENTACLES_VALUE = "aq40 c'thun claw tentacles";
inline constexpr char const* CTHUN_EYE_TENTACLES_VALUE = "aq40 c'thun eye tentacles";
inline constexpr char const* CTHUN_GIANT_CLAW_TENTACLES_VALUE =
    "aq40 c'thun giant claw tentacles";
inline constexpr char const* CTHUN_GIANT_EYE_TENTACLES_VALUE =
    "aq40 c'thun giant eye tentacles";
inline constexpr char const* CTHUN_FLESH_TENTACLES_VALUE = "aq40 c'thun flesh tentacles";
inline constexpr char const* CTHUN_DARK_GLARE_SWEEP_VALUE = "aq40 c'thun dark glare sweep";

// Hazard radii. Each is the spell's own radius plus a yard of slack, so a bot that steps out stays
// out while its next tick is pending.
inline constexpr float POISON_CLOUD_RADIUS = 11.0f;
inline constexpr float NOXIOUS_POISON_RADIUS = 11.0f;
inline constexpr float BLIZZARD_RADIUS = 11.0f;
// Ouro re-emerges from one of his Dirt Mounds, knocking back and rupturing the ground around it.
inline constexpr float DIRT_MOUND_RADIUS = 15.0f;

// Skeram's Arcane Explosion and True Fulfillment both punish standing next to him: the mind
// control picks the second closest player, so only the tank belongs in melee range.
inline constexpr float SKERAM_RANGED_DISTANCE = 20.0f;
// Sand Blast wipes the threat of everyone it hits (boss_ouro.cpp, SpellHitTarget), so non-tanks
// stay out of it. This distance is a rough proxy for its radius.
inline constexpr float OURO_RANGED_DISTANCE = 20.0f;
// Poison Shock is an AoE centred on Viscidus.
inline constexpr float VISCIDUS_RANGED_DISTANCE = 15.0f;
// Sweep and Sand Blast come out of Ouro's front half.
inline constexpr float OURO_FRONT_ARC = static_cast<float>(M_PI);
// Poison Bolt Volley in Huhuran's Berserk phase and Sartura's Whirlwind both chain through a
// clumped raid.
inline constexpr float SPREAD_DISTANCE = 8.0f;
// Sartura and her Royal Guards both Whirlwind. Melee step out of its reach instead of trying to
// stun it: the boss is immune to stuns while whirlwinding (boss_sartura.cpp).
inline constexpr float WHIRLWIND_ESCAPE_DISTANCE = 12.0f;
// Mortal Wound is a stacking healing debuff on the tank. Five stacks is the usual swap point.
inline constexpr uint8 MORTAL_WOUND_SWAP_STACKS = 5;
// The Twins heal each other every 3.6s while within 60 yards (boss_twinemperors.cpp), so each
// tank parks his twin on the twin's own spawn point. The two are ~158 yards apart.
inline constexpr float TWIN_SEPARATION_DISTANCE = 60.0f;
inline Position const VEKNILASH_STATION = { -9023.67f, 1176.24f, -104.23f, 0.77f };
inline Position const VEKLOR_STATION = { -8868.31f, 1205.97f, -104.23f, 2.71f };
// Dark Glare hits only what is within 5 yards of the line the Eye faces (boss_cthun.cpp:838,
// spell_cthun_dark_glare::FilterTargets), but the beam sweeps about a degree every 200ms
// (boss_cthun.cpp:280), so bots start moving while it is still this far from them.
inline constexpr float DARK_GLARE_LINE_WIDTH = 14.0f;
// How far around the Eye a bot runs to get behind the sweep. The beam covers half a circle in 35
// seconds, so 40 degrees of clearance is worth about 8 seconds.
inline constexpr float DARK_GLARE_DODGE_ANGLE = 0.7f;
// Circling the Eye achieves nothing right next to it, so bots dodge at this radius at least.
inline constexpr float DARK_GLARE_MIN_RADIUS = 20.0f;
inline constexpr float DARK_GLARE_STEP_DISTANCE = 10.0f;
// Two samples of the Eye's orientation this far apart tell the sweep's direction, which the script
// picks at random and exposes nowhere (boss_cthun.cpp:267).
inline constexpr uint32 DARK_GLARE_SAMPLE_INTERVAL_MS = 500;
// The smallest orientation change that is the beam turning rather than float noise.
inline constexpr float DARK_GLARE_SWEEP_EPSILON = 0.005f;
// Swallowed players carry Digestive Acid and stand below the floor of the Eye's chamber, which is
// above z 100 (boss_cthun.cpp:126 NotInStomachSelector, :178). Only this encounter's own triggers
// may use the height test: the rest of the temple lies below z 0 as well.
inline constexpr float CTHUN_STOMACH_Z_CEILING = 0.0f;
// Areatrigger 4033 (at_cthun_stomach_exit), radius 5. It is the only exit the core implements.
inline Position const CTHUN_STOMACH_EXIT = { -8546.23f, 1987.65f, -96.52f, 0.0f };
inline constexpr float CTHUN_STOMACH_EXIT_ARRIVAL_DISTANCE = 2.0f;

// Adds and hazards

GuidVector FindCreatureGuids(Player* bot, std::vector<uint32> const& entries, float radius);
std::vector<Unit*> GetCachedUnits(PlayerbotAI* botAI, char const* value);
Unit* GetNearestCachedUnit(PlayerbotAI* botAI, char const* value);
// The cached unit of the given index, by GUID order, so every bot picks the same one.
Unit* GetCachedUnitOfIndex(PlayerbotAI* botAI, char const* value, uint8 index);
std::vector<Position> const& GetCachedHazardPositions(PlayerbotAI* botAI, char const* value);
bool IsInHazard(PlayerbotAI* botAI, char const* value, float radius);
// The closest point outside every hazard of this value, searched on rings around the bot.
bool FindPositionOutsideHazards(
    PlayerbotAI* botAI, char const* value, float radius, Position& outPos);

// The Prophet Skeram

// Skeram's images carry his name and entry, and only the real one is not a summon
// (boss_skeram.cpp uses the same test).
bool IsSkeramImage(Unit* unit);
Unit* GetRealSkeram(PlayerbotAI* botAI);
std::vector<Unit*> GetSkeramImages(PlayerbotAI* botAI);

// Silithid Royalty

// Kri first (his Toxic Volley hurts the most), then Yauj, whose Heal would undo the raid's
// damage, and Vem last: his death buffs whoever is still alive with attack speed and damage.
Unit* GetBugTrioKillTarget(PlayerbotAI* botAI);

// Viscidus

// Only direct frost damage counts toward freezing him, and only hit count matters, not damage
// (boss_viscidus.cpp), so the cheapest frost spell the bot has is the right one.
char const* GetCheapestFrostSpell(Player* bot);
bool IsViscidusFrozen(Unit* viscidus);

// C'Thun

// Phase 1 is the Eye. Phase 2 starts when it dies and the body becomes attackable, and both are
// found by name, so neither lookup needs a grid search.
Unit* GetCthunEye(PlayerbotAI* botAI);
Unit* GetCthunBody(PlayerbotAI* botAI);
// The Eye freezes its own animation and turns red a second before it starts aiming the beam, and
// keeps both auras until the sweep ends (boss_cthun.cpp:258, :269, :292).
bool IsEyeCastingDarkGlare(Unit* eye);
// Carapace of C'Thun makes the body immune. Killing both Flesh Tentacles in the stomach strips it
// for 45 seconds, then it comes back with two fresh tentacles (boss_cthun.cpp:495, :497). False
// for an unattackable body, which also keeps phase 1 out of the phase 2 objects.
bool IsCthunBodyWeakened(Unit* body);
bool IsInCthunStomach(Player* bot);
// An angle difference folded into (-pi, pi].
float NormalizeAngleDelta(float angle);
// Which way the beam is turning, kept between samples by the cached value that owns it: 1
// counter-clockwise, -1 clockwise, 0 while that is still unknown.
struct DarkGlareSweepSampler
{
    std::optional<float> lastAngle;
    float sweep = 0.0f;

    float Sample(PlayerbotAI* botAI);
};

// Tanking

// Same class switch as SSCHelpers::CastTankTaunt; worth promoting to EncounterHelpers if a fourth
// raid needs it.
bool CastTankTaunt(PlayerbotAI* botAI, Unit* target);
uint8 GetAuraStacks(Unit* unit, uint32 spellId);

}

#endif
