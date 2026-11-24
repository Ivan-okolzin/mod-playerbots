/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#ifndef PLAYERBOTS_ZGHELPERS_H
#define PLAYERBOTS_ZGHELPERS_H

#include "Common.h"
#include "Define.h"
#include "ObjectGuid.h"
#include "Position.h"
#include <type_traits>
#include <vector>

class Player;
class PlayerbotAI;
class Unit;

namespace ZulGurubHelpers
{

template <typename T, std::enable_if_t<std::is_enum_v<T>, int> = 0>
constexpr uint32 Id(T value)
{
    return static_cast<uint32>(value);
}

constexpr uint32 ZG_MAP_ID = 309;

// Spell ids are taken from the encounter scripts of
// src/server/scripts/EasternKingdoms/ZulGurub/. The references name the file and line: BVE =
// boss_venoxis.cpp, BJE = boss_jeklik.cpp, BML = boss_marli.cpp, BMA = boss_mandokir.cpp, BTH =
// boss_thekal.cpp, BAR = boss_arlokk.cpp, BJI = boss_jindo.cpp, BHA = boss_hakkar.cpp, BGA =
// boss_gahzranka.cpp, BGR = boss_grilek.cpp, BHZ = boss_hazzarah.cpp, BRE = boss_renataki.cpp,
// BWU = boss_wushoolay.cpp, ZGH = zulgurub.h.
enum class ZulGurubSpells : uint32
{
    // Hakkar
    SPELL_POISONOUS_BLOOD   = 24321,  // BHA:58, damages Hakkar through Blood Siphon (BHA:357)
    SPELL_POISONOUS_CLOUD   = 24320,  // the Poisonous Cloud's own cast, see POISONOUS_CLOUD_NOTE
    SPELL_BLOOD_SIPHON      = 24324,  // BHA:46, every 90 seconds (BHA:117, :157)
    SPELL_CAUSE_INSANITY    = 24327,  // BHA:50, on the top threat within 30 yards (BHA:163)

    // High Priest Venoxis
    SPELL_VENOXIS_TRANSFORM = 23849,  // BVE:47, snake form at 50% health (BVE:128, :132)
    SPELL_POISON_CLOUD      = 23861,  // BVE:50, snake form only (BVE:140)

    // High Priestess Jeklik
    SPELL_BAT_FORM          = 23966,  // BJE:45, dropped at 50% health (BJE:202)
    SPELL_LIQUID_FIRE       = 23971,  // BJE:63, the bomb's ground fire (BJE:410)

    // High Priestess Mar'li
    SPELL_GROWTH            = 24086,  // BML:255
    SPELL_FULL_GROWN        = 24088,  // BML:261
    SPELL_SPIDER_FORM       = 24084,  // BML:54, one minute in each form (BML:180, :214)
    SPELL_ENVELOPING_WEB    = 24110,  // BML:43, wipes the threat of everyone hit (BML:308)

    // Bloodlord Mandokir
    SPELL_WATCH             = 24314,  // BMA:46, charges the watched player if it earns threat
    SPELL_WHIRLWIND         = 13736,  // BMA:43, every 22-26 seconds (BMA:418)

    // High Priest Thekal
    SPELL_TIGER_FORM        = 24169,  // BTH:46, the phase after all three rise (BTH:259)

    // High Priestess Arlokk
    SPELL_MARK_OF_ARLOKK    = 24210,  // BAR:35, sends the prowlers at one player (BAR:349)
    SPELL_SUPER_INVIS       = 24235,  // BAR:42, while she stalks the room (BAR:240)

    // Jin'do the Hexxer
    SPELL_HEX               = 17172,  // BJI:34, on whoever holds him (BJI:137)

    // Gri'lek
    SPELL_AVATAR            = 24646,  // BGR:24, pursues one player for 15 seconds (BGR:85, :100)

    // Renataki
    SPELL_RENATAKI_VANISH   = 24699,  // BRE:24, ambushes a random player 5 seconds later (BRE:145)

    // Wushoolay
    SPELL_LIGHTNING_CLOUD   = 24683,  // BWU:24, dropped on a random player (BWU:70)
};

enum class ZulGurubNpcs : uint32
{
    NPC_VENOXIS             = 14507,  // BVE:64
    NPC_PARASITIC_SERPENT   = 14884,  // BVE:66, summoned every 15s in snake form (BVE:146)
    NPC_JEKLIK              = 14517,  // ZGH:54
    NPC_BLOODSEEKER_BAT     = 11368,  // BJE:75, six at a time (BJE:186), also ZG trash
    NPC_MARLI               = 14510,  // ZGH:55
    NPC_SPAWN_OF_MARLI      = 15041,  // ZGH:56, grows into Full Grown in 20s (BML:251)
    NPC_MANDOKIR            = 11382,  // ZGH:62
    NPC_OHGAN               = 14988,  // ZGH:63, summoned on the pull (BMA:202)
    NPC_CHAINED_SPIRIT      = 15117,  // ZGH:65, revives dead players (BMA:118)
    NPC_THEKAL              = 14509,  // ZGH:57
    NPC_ZEALOT_LORKHAN      = 11347,  // ZGH:52
    NPC_ZEALOT_ZATH         = 11348,  // ZGH:53
    NPC_ZULGURUB_TIGER      = 11361,  // ZGH:67, summoned in tiger form (BTH:286), also ZG trash
    NPC_ARLOKK              = 14515,  // ZGH:49
    NPC_ZULIAN_PROWLER      = 15101,  // ZGH:51, one per side every 6s (BAR:193)
    NPC_JINDO               = 11380,  // ZGH:58
    NPC_BRAIN_WASH_TOTEM    = 15112,  // ZGH:68, casts on a random player (BJI:85)
    NPC_SHADE_OF_JINDO      = 14986,  // ZGH:60, summoned by Delusions of Jin'do (BJI:278)
    NPC_HAKKAR              = 14834,  // ZGH:66
    NPC_SON_OF_HAKKAR       = 11357,  // see POISONOUS_CLOUD_NOTE
    NPC_POISONOUS_CLOUD     = 14989,  // see POISONOUS_CLOUD_NOTE
    NPC_GAHZRANKA           = 15114,  // ZGH:69
    NPC_GRILEK              = 15082,  // ZGH:70
    NPC_HAZZARAH            = 15083,  // ZGH:71
    NPC_NIGHTMARE_ILLUSION  = 15163,  // ZGH:59, three at a time (BHZ:133)
    NPC_RENATAKI            = 15084,  // ZGH:72
    NPC_WUSHOOLAY           = 15085,  // ZGH:73
};

// Neither the Powerful Healing Ward creature nor the Poisonous Cloud chain is in zulgurub.h, so
// both come from the world database instead.
// The ward is the creature of ScriptName npc_healing_ward (BJI:301), which heals Jin'do every
// three seconds (BJI:176).
inline constexpr uint32 NPC_POWERFUL_HEALING_WARD = 14987;
// POISONOUS_CLOUD_NOTE: a dying Son of Hakkar (11357) summons a Poisonous Cloud (14989) for ten
// seconds, and the cloud casts Poisonous Blood (24320) on everything around it once a second;
// both steps are smart_scripts rows, not script code. Blood Siphon then turns that poison into
// damage on Hakkar (BHA:357), and strips it (BHA:379), so the raid re-poisons between siphons.
inline constexpr uint32 GO_LIQUID_FIRE = 180125;

inline constexpr uint32 ZG_CACHE_INTERVAL_MS = 200;
inline constexpr float ADD_SEARCH_RADIUS = 100.0f;
inline constexpr float HAZARD_SEARCH_RADIUS = 60.0f;

// Cached add, hazard, and trap values, registered in ZGValueContext.h.
inline constexpr char const* VENOXIS_SERPENTS_VALUE = "zg venoxis parasitic serpents";
inline constexpr char const* VENOXIS_POISON_CLOUD_VALUE = "zg venoxis poison cloud";
inline constexpr char const* JEKLIK_BATS_VALUE = "zg jeklik bloodseeker bats";
inline constexpr char const* JEKLIK_LIQUID_FIRE_VALUE = "zg jeklik liquid fire";
inline constexpr char const* MARLI_SPAWNS_VALUE = "zg marli spawns";
inline constexpr char const* MANDOKIR_OHGAN_VALUE = "zg mandokir ohgan";
inline constexpr char const* THEKAL_TRIO_VALUE = "zg thekal trio";
inline constexpr char const* THEKAL_TIGERS_VALUE = "zg thekal tigers";
inline constexpr char const* ARLOKK_PROWLERS_VALUE = "zg arlokk prowlers";
inline constexpr char const* JINDO_HEALING_WARDS_VALUE = "zg jindo healing wards";
inline constexpr char const* JINDO_BRAIN_WASH_TOTEMS_VALUE = "zg jindo brain wash totems";
inline constexpr char const* JINDO_SHADES_VALUE = "zg jindo shades";
inline constexpr char const* HAZZARAH_ILLUSIONS_VALUE = "zg hazzarah illusions";
inline constexpr char const* WUSHOOLAY_LIGHTNING_CLOUD_VALUE = "zg wushoolay lightning cloud";
inline constexpr char const* POISONOUS_CLOUDS_VALUE = "zg poisonous clouds";

// Hazard radii. Each is the mechanic's own reach plus a yard of slack, so a bot that steps out
// stays out while its next tick is pending.
// The Liquid Fire trap object (180125) carries its own six yard radius in gameobject_template.
inline constexpr float LIQUID_FIRE_RADIUS = 7.0f;
// Neither cloud's radius is in the script or the database, so both are estimates from the spell's
// visual, to confirm by a live test.
inline constexpr float POISON_CLOUD_RADIUS = 10.0f;
inline constexpr float LIGHTNING_CLOUD_RADIUS = 10.0f;
// Mandokir is immune to nothing while whirlwinding but switches target every swing, so melee step
// out of its reach rather than trying to hold him.
inline constexpr float WHIRLWIND_ESCAPE_DISTANCE = 12.0f;
// Chain Lightning (BWU:25) and Chain Burn (BHZ:28) both jump to whoever stands next to the player
// they land on.
inline constexpr float SPREAD_DISTANCE = 10.0f;
// Gri'lek's Avatar gives one player a million threat and chases him down (BGR:85, :100), so that
// player kites until it wears off.
inline constexpr float AVATAR_FLEE_DISTANCE = 25.0f;
// Walking into a Poisonous Cloud is how a raid member gets the poison Blood Siphon needs. The
// cloud hurts whoever stands in it, so only a healthy bot out of combat goes looking for one.
inline constexpr float POISON_PICKUP_SEARCH_RADIUS = 40.0f;
inline constexpr float POISON_PICKUP_STAND_DISTANCE = 2.0f;
inline constexpr float POISON_PICKUP_MIN_HEALTH_PCT = 80.0f;
inline constexpr float PATH_STEP_DISTANCE = 4.0f;

// Bosses and adds

// The threat-list lookup of "find target", by creature entry rather than by name. Every name of
// this raid is unique in creature_template, but entries keep the lookup independent of the
// client's locale, and two of its adds (11361, 11368) share name and entry with instance trash.
// Every boss of this raid is a BossAI and so calls DoZoneInCombat on the pull
// (ScriptedCreature.cpp:685), which is what puts each bot on the boss's threat list. Ohgan and
// Thekal's two zealots are plain ScriptedAI and do not, so they are found through cached values
// instead.
Unit* FindThreatCreature(Player* bot, uint32 entry);
// summonsOnly keeps the instance's own Zulian Tigers and Bloodseeker Bats out of the adds a boss
// summoned: only the summons belong to the fight.
GuidVector FindCreatureGuids(
    Player* bot, std::vector<uint32> const& entries, float radius, bool summonsOnly = false);
std::vector<Unit*> GetCachedUnits(PlayerbotAI* botAI, char const* value);
Unit* SelectCachedTarget(PlayerbotAI* botAI, char const* value);
Unit* GetCachedUnitOfEntry(PlayerbotAI* botAI, char const* value, uint32 entry);
// Arlokk while she stalks and Thekal while he plays dead are both flagged out of reach, and an
// order to attack either one only sends the bot running at a target it cannot touch.
bool IsUnassailable(Unit* unit);

// Ground hazards

std::vector<Position> FindGameObjectPositions(Player* bot, uint32 entry, float radius);
std::vector<Position> const& GetCachedHazardPositions(PlayerbotAI* botAI, char const* value);
bool IsInHazard(PlayerbotAI* botAI, char const* value, float radius);
// The closest point outside every hazard of this value, searched on rings around the bot.
bool FindPositionOutsideHazards(
    PlayerbotAI* botAI, char const* value, float radius, Position& outPos);

// Tanking

// Same class switch as Aq40Helpers::CastTankTaunt and CrusaderHelpers::CastTankTaunt; the fifth
// copy, and overdue for a move into EncounterHelpers.
bool CastTankTaunt(PlayerbotAI* botAI, Unit* target);
// True while the boss is swinging at someone who is not a tank, which is every threat wipe this
// raid has: Venoxis and Jeklik on their phase change (BVE:134, BJE:203), Mar'li's Enveloping Web
// (BML:308), Mandokir's Charge (BMA:456), Thekal's tiger Charge (BTH:280), Arlokk picking a
// random target when she reappears (BAR:253), Hakkar's Aspects of Mar'li and Arlokk (BHA:190,
// :202), and Gahz'ranka's Slam (BGA:84).
bool IsBossOnNonTank(Unit* boss);

// High Priest Thekal

// The three of them rise again unless they die within ten seconds of each other (BTH:161), so the
// raid spreads its damage instead of focusing: the healthiest of the three is always the target,
// which walks all three health bars down together. Skips Thekal while he plays dead, and returns
// null once only he is left, since the tiger phase is an ordinary single target.
Unit* GetThekalTrioFocus(PlayerbotAI* botAI);
// Thekal plays dead instead of dying while either zealot is up (BTH:172), which is also how the
// tiger phase is told apart: the trio value is empty of zealots by then.
bool IsThekalTrioFight(PlayerbotAI* botAI);

}  // namespace ZulGurubHelpers

#endif
