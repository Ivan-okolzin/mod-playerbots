/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#ifndef PLAYERBOTS_MCTRIGGERS_H
#define PLAYERBOTS_MCTRIGGERS_H

#include "EncounterHelpers.h"
#include "MCHelpers.h"
#include "PlayerbotAI.h"
#include "Playerbots.h"
#include "Trigger.h"
#include <string>

class McMagmadarTremorTrigger : public Trigger
{
public:
    McMagmadarTremorTrigger(PlayerbotAI* botAI) : Trigger(botAI, "mc magmadar tremor", 1) {}
    bool IsActive() override;
};

// Shared

// Every Molten Core boss script is a BossAI, so each reports IN_PROGRESS on the pull: the gate
// keeps a boss mechanic out of the trash pulls and the run back between bosses.
class McEncounterTrigger : public Trigger
{
public:
    McEncounterTrigger(PlayerbotAI* botAI, std::string const name, int32 checkInterval = 1)
        : Trigger(botAI, name, checkInterval) {}

    bool IsActive() final
    {
        return EncounterHelpers::IsEncounterInProgress(bot, MoltenCoreHelpers::MC_MAP_ID) &&
            IsActiveInEncounter();
    }

protected:
    virtual bool IsActiveInEncounter() = 0;
};

// Eight of the ten bosses want the same of their main tank: threat on the boss, held where the
// raid put it. The cached value is passed only for the bosses whose scripts wipe their threat
// list; see MoltenCoreHelpers::FindBoss.
class McBossShouldBeTankedTrigger : public McEncounterTrigger
{
public:
    McBossShouldBeTankedTrigger(
        PlayerbotAI* botAI, std::string const& name, uint32 bossEntry,
        char const* bossValue = nullptr)
        : McEncounterTrigger(botAI, name), _bossEntry(bossEntry), _bossValue(bossValue) {}

protected:
    bool IsActiveInEncounter() override;

private:
    uint32 const _bossEntry;
    char const* const _bossValue;
};

// Shazzrah's Gate, Majordomo's Hate to Zero and Ragnaros's emerge all hand the boss to somebody
// who is not the tank. The tank takes it back.
class McBossLostThreatTrigger : public McEncounterTrigger
{
public:
    McBossLostThreatTrigger(
        PlayerbotAI* botAI, std::string const& name, uint32 bossEntry, char const* bossValue)
        : McEncounterTrigger(botAI, name), _bossEntry(bossEntry), _bossValue(bossValue) {}

protected:
    bool IsActiveInEncounter() override;

private:
    uint32 const _bossEntry;
    char const* const _bossValue;
};

enum class McAddRole : uint8
{
    // Everyone but the healers: an add the whole raid drops what it is doing for.
    Everyone,
    // The adds of the four add bosses stand next to their boss, so the main tank keeps the boss
    // and the assist tanks take the adds off the raid.
    AssistTanks,
};

// Lucifron's Protectors, Gehennas's Flamewakers, Garr's Firesworn, Sulfuron's Priests,
// Majordomo's eight adds and Ragnaros's Sons of Flame: adds the raid picks up on sight, differing
// only in who goes for them.
class McAddsSpawnedTrigger : public McEncounterTrigger
{
public:
    McAddsSpawnedTrigger(
        PlayerbotAI* botAI, std::string const& name, char const* addsValue, McAddRole role)
        : McEncounterTrigger(botAI, name), _addsValue(addsValue), _role(role) {}

protected:
    bool IsActiveInEncounter() override;

private:
    char const* const _addsValue;
    McAddRole const _role;
};

// A patch of fire on the floor: Magmadar's Lava Bomb, Gehennas's Rain of Fire, Ragnaros's Lava
// Burst.
class McBotInHazardTrigger : public McEncounterTrigger
{
public:
    McBotInHazardTrigger(
        PlayerbotAI* botAI, std::string const& name, char const* hazardValue, float radius)
        : McEncounterTrigger(botAI, name), _hazardValue(hazardValue), _radius(radius) {}

protected:
    bool IsActiveInEncounter() override;

private:
    char const* const _hazardValue;
    float const _radius;
};

// A boss aura that burns everything near the boss for as long as it holds: Baron Geddon's Inferno
// and his Armageddon. Fires only while the bot is still inside the distance, so that an
// already-safe bot does not attempt a failing move every tick.
class McBossAuraHazardTrigger : public McEncounterTrigger
{
public:
    McBossAuraHazardTrigger(
        PlayerbotAI* botAI, std::string const& name, uint32 bossEntry, char const* bossValue,
        uint32 spellId, float distance)
        : McEncounterTrigger(botAI, name), _bossEntry(bossEntry), _bossValue(bossValue),
          _spellId(spellId), _distance(distance) {}

protected:
    bool IsActiveInEncounter() override;

private:
    uint32 const _bossEntry;
    char const* const _bossValue;
    uint32 const _spellId;
    float const _distance;
};

// Baron Geddon

// The bomb goes off on its carrier and everyone standing with it, and it outlives Geddon himself,
// so this one is not gated on the encounter.
class McLivingBombDebuffTrigger : public Trigger
{
public:
    McLivingBombDebuffTrigger(PlayerbotAI* botAI) : Trigger(botAI, "mc living bomb debuff") {}
    bool IsActive() override;
};

// Shazzrah

class McShazzrahRangedTrigger : public Trigger
{
public:
    McShazzrahRangedTrigger(PlayerbotAI* botAI) : Trigger(botAI, "mc shazzrah ranged") {}
    bool IsActive() override;
};

// Golemagg the Incinerator

class McGolemaggMarkBossTrigger : public Trigger
{
public:
    McGolemaggMarkBossTrigger(PlayerbotAI* botAI) : Trigger(botAI, "mc golemagg mark boss") {}
    bool IsActive() override;
};

class McGolemaggIsMainTankTrigger : public Trigger
{
public:
    McGolemaggIsMainTankTrigger(PlayerbotAI* botAI) : Trigger(botAI, "mc golemagg is main tank") {}
    bool IsActive() override;
};

class McGolemaggIsAssistTankTrigger : public Trigger
{
public:
    McGolemaggIsAssistTankTrigger(PlayerbotAI* botAI) : Trigger(botAI, "mc golemagg is assist tank") {}
    bool IsActive() override;
};

class McGolemaggIsHealerTrigger : public Trigger
{
public:
    McGolemaggIsHealerTrigger(PlayerbotAI* botAI) : Trigger(botAI, "mc golemagg is healer") {}
    bool IsActive() override;
};

class McGolemaggMagmaSplashTrigger : public Trigger
{
public:
    McGolemaggMagmaSplashTrigger(PlayerbotAI* botAI) : Trigger(botAI, "mc golemagg magma splash") {}
    bool IsActive() override;
};

// Majordomo Executus

class McMajordomoDamageShieldTrigger : public Trigger
{
public:
    McMajordomoDamageShieldTrigger(PlayerbotAI* botAI) : Trigger(botAI, "mc majordomo damage shield") {}
    bool IsActive() override;
};

// Trash and anywhere in the instance

class McCoreHoundMarkTrigger : public Trigger
{
public:
    McCoreHoundMarkTrigger(PlayerbotAI* botAI) : Trigger(botAI, "mc core hound mark") {}
    bool IsActive() override;
};

// Standing/swimming in magma (knocked into a lava pool by Ragnaros' Wrath or an Eruption)
class McInLavaTrigger : public Trigger
{
public:
    McInLavaTrigger(PlayerbotAI* botAI) : Trigger(botAI, "mc in lava") {}
    bool IsActive() override;
};

#endif
