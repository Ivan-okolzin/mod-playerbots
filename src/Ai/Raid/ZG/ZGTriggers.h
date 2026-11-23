/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#ifndef PLAYERBOTS_ZGTRIGGERS_H
#define PLAYERBOTS_ZGTRIGGERS_H

#include "EncounterHelpers.h"
#include "Trigger.h"
#include "ZGHelpers.h"
#include <string>

// Shared

class ZulGurubEncounterTrigger : public Trigger
{
public:
    ZulGurubEncounterTrigger(PlayerbotAI* botAI, std::string const name, int32 checkInterval = 1)
        : Trigger(botAI, name, checkInterval) {}

    bool IsActive() final
    {
        return EncounterHelpers::IsEncounterInProgress(bot, ZulGurubHelpers::ZG_MAP_ID) &&
            IsActiveInEncounter();
    }

protected:
    virtual bool IsActiveInEncounter() = 0;
};

class ZulGurubNoEncounterInProgressTrigger : public Trigger
{
public:
    ZulGurubNoEncounterInProgressTrigger(PlayerbotAI* botAI)
        : Trigger(botAI, "zg no encounter in progress", 1000) {}
    bool IsActive() override;
};

// Every boss of this raid wants the same thing of its main tank: threat, and a boss that stays
// where it is put. Thekal's trio is the one exception and has its own.
class ZulGurubBossShouldBeTankedTrigger : public ZulGurubEncounterTrigger
{
public:
    ZulGurubBossShouldBeTankedTrigger(
        PlayerbotAI* botAI, std::string const& name, uint32 bossEntry)
        : ZulGurubEncounterTrigger(botAI, name), _bossEntry(bossEntry) {}

protected:
    bool IsActiveInEncounter() override;

private:
    uint32 const _bossEntry;
};

// This raid wipes tank threat more often than any other classic raid: see IsBossOnNonTank for
// the list. A tank that sees the boss swinging at someone else takes it back.
class ZulGurubBossLostThreatTrigger : public ZulGurubEncounterTrigger
{
public:
    ZulGurubBossLostThreatTrigger(PlayerbotAI* botAI, std::string const& name, uint32 bossEntry)
        : ZulGurubEncounterTrigger(botAI, name), _bossEntry(bossEntry) {}

protected:
    bool IsActiveInEncounter() override;

private:
    uint32 const _bossEntry;
};

enum class ZulGurubAddRole : uint8
{
    Dps,
    AssistTanks,
};

// Venoxis's serpents, Jeklik's bats, Mar'li's spawns, Ohgan, Thekal's tigers, Arlokk's prowlers,
// Jin'do's wards, totems and shades, and Hazza'rah's illusions: adds the raid kills on sight,
// differing only in who goes for them. The boss gate keeps each one inside its own fight.
class ZulGurubAddsSpawnedTrigger : public ZulGurubEncounterTrigger
{
public:
    ZulGurubAddsSpawnedTrigger(
        PlayerbotAI* botAI, std::string const& name, char const* addsValue, ZulGurubAddRole role,
        uint32 bossEntry = 0)
        : ZulGurubEncounterTrigger(botAI, name), _addsValue(addsValue), _role(role),
          _bossEntry(bossEntry) {}

protected:
    bool IsActiveInEncounter() override;

private:
    char const* const _addsValue;
    ZulGurubAddRole const _role;
    uint32 const _bossEntry;
};

// Venoxis's Poison Cloud, Jeklik's Liquid Fire, and Wushoolay's Lightning Cloud are all patches
// of ground nobody wants to be standing on. bossAura, where it is given, is the phase aura that
// bounds the mechanic on both sides.
class ZulGurubBotInHazardTrigger : public ZulGurubEncounterTrigger
{
public:
    ZulGurubBotInHazardTrigger(
        PlayerbotAI* botAI, std::string const& name, char const* hazardValue, float radius,
        uint32 bossEntry, uint32 bossAura = 0)
        : ZulGurubEncounterTrigger(botAI, name), _hazardValue(hazardValue), _radius(radius),
          _bossEntry(bossEntry), _bossAura(bossAura) {}

protected:
    bool IsActiveInEncounter() override;

private:
    char const* const _hazardValue;
    float const _radius;
    uint32 const _bossEntry;
    uint32 const _bossAura;
};

// Chain Lightning and Chain Burn are the only spells of this raid that jump between players, and
// both belong to the Edge of Madness, so spacing is about the raid and not about the boss.
class ZulGurubRangedShouldSpreadTrigger : public ZulGurubEncounterTrigger
{
public:
    ZulGurubRangedShouldSpreadTrigger(
        PlayerbotAI* botAI, std::string const& name, uint32 bossEntry)
        : ZulGurubEncounterTrigger(botAI, name), _bossEntry(bossEntry) {}

protected:
    bool IsActiveInEncounter() override;

private:
    uint32 const _bossEntry;
};

// Cause Insanity turns a raid member hostile, and the bots' own target selection happily picks
// that player up.
class ZulGurubAttackingCharmedAllyTrigger : public ZulGurubEncounterTrigger
{
public:
    ZulGurubAttackingCharmedAllyTrigger(
        PlayerbotAI* botAI, std::string const& name, uint32 charmSpellId)
        : ZulGurubEncounterTrigger(botAI, name), _charmSpellId(charmSpellId) {}

protected:
    bool IsActiveInEncounter() override;

private:
    uint32 const _charmSpellId;
};

// Not an encounter trigger: the poison is picked up between pulls, which is the only time the
// Poisonous Clouds of the Bloodfire Pit are both standing and safe to walk into.
class ZulGurubShouldPickUpPoisonousBloodTrigger : public Trigger
{
public:
    ZulGurubShouldPickUpPoisonousBloodTrigger(PlayerbotAI* botAI)
        : Trigger(botAI, "zg bot should pick up poisonous blood", 1000) {}
    bool IsActive() override;
};

// Bloodlord Mandokir

// Threatening Gaze charges the watched player, but only if he earned threat while it was on him
// (BMA:257, :292), so the answer is to stand still and do nothing until it expires.
class MandokirBotIsWatchedTrigger : public ZulGurubEncounterTrigger
{
public:
    MandokirBotIsWatchedTrigger(PlayerbotAI* botAI)
        : ZulGurubEncounterTrigger(botAI, "bloodlord mandokir bot is watched") {}

protected:
    bool IsActiveInEncounter() override;
};

class MandokirMeleeInWhirlwindRangeTrigger : public ZulGurubEncounterTrigger
{
public:
    MandokirMeleeInWhirlwindRangeTrigger(PlayerbotAI* botAI)
        : ZulGurubEncounterTrigger(botAI, "bloodlord mandokir melee in whirlwind range") {}

protected:
    bool IsActiveInEncounter() override;
};

// High Priest Thekal

// One tank each: the main tank keeps Thekal through both phases, the first assist tank takes
// Lor'Khan, whose Greater Heal is the one cast in this fight worth interrupting, and the second
// takes Zath, whose Gouge wipes his own tank's threat (BTH:469).
class ThekalZealotsShouldBeTankedTrigger : public ZulGurubEncounterTrigger
{
public:
    ThekalZealotsShouldBeTankedTrigger(PlayerbotAI* botAI)
        : ZulGurubEncounterTrigger(botAI, "high priest thekal zealots should be tanked") {}

protected:
    bool IsActiveInEncounter() override;
};

class ThekalShouldBalanceTrioDamageTrigger : public ZulGurubEncounterTrigger
{
public:
    ThekalShouldBalanceTrioDamageTrigger(PlayerbotAI* botAI)
        : ZulGurubEncounterTrigger(botAI, "high priest thekal should balance trio damage") {}

protected:
    bool IsActiveInEncounter() override;
};

// Jin'do the Hexxer

// Hex leaves whoever holds Jin'do unable to act (BJI:137), so the second tank takes over for as
// long as it lasts.
class JindoHexedTankTrigger : public ZulGurubEncounterTrigger
{
public:
    JindoHexedTankTrigger(PlayerbotAI* botAI)
        : ZulGurubEncounterTrigger(botAI, "jin'do the hexxer hexed the tank") {}

protected:
    bool IsActiveInEncounter() override;
};

// Gri'lek

class GrilekBotIsPursuedTrigger : public ZulGurubEncounterTrigger
{
public:
    GrilekBotIsPursuedTrigger(PlayerbotAI* botAI)
        : ZulGurubEncounterTrigger(botAI, "gri'lek bot is pursued") {}

protected:
    bool IsActiveInEncounter() override;
};

#endif
