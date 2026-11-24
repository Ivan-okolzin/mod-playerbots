/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#ifndef PLAYERBOTS_AQ20TRIGGERS_H
#define PLAYERBOTS_AQ20TRIGGERS_H

#include "Aq20Helpers.h"
#include "EncounterHelpers.h"
#include "Trigger.h"
#include <string>

// Shared

class Aq20EncounterTrigger : public Trigger
{
public:
    Aq20EncounterTrigger(PlayerbotAI* botAI, std::string const name, int32 checkInterval = 1)
        : Trigger(botAI, name, checkInterval) {}

    bool IsActive() final
    {
        return EncounterHelpers::IsEncounterInProgress(bot, Aq20Helpers::AQ20_MAP_ID) &&
            IsActiveInEncounter();
    }

protected:
    virtual bool IsActiveInEncounter() = 0;
};

// Kurinnaxx, Rajaxx, Moam and Ossirian all want the same of their tank: threat on a boss that
// stays where the raid put it. Rajaxx also wipes all threat on every Thundercrash (RAJ:117) and
// Ossirian has to be dragged from crystal to crystal, so for those two holding the target is not
// enough and the boss has to actually be hitting this bot, which is what requireVictim asks.
class Aq20BossShouldBeTankedTrigger : public Aq20EncounterTrigger
{
public:
    Aq20BossShouldBeTankedTrigger(
        PlayerbotAI* botAI, std::string const& name, uint32 bossEntry, bool requireVictim)
        : Aq20EncounterTrigger(botAI, name), _bossEntry(bossEntry),
          _requireVictim(requireVictim) {}

protected:
    bool IsActiveInEncounter() override;

private:
    uint32 const _bossEntry;
    bool const _requireVictim;
};

// A stacking debuff on whoever the boss is hitting, which the second tank takes over at.
class Aq20MainTankAuraStacksTrigger : public Aq20EncounterTrigger
{
public:
    Aq20MainTankAuraStacksTrigger(
        PlayerbotAI* botAI, std::string const& name, uint32 bossEntry, uint32 spellId,
        uint8 stacks)
        : Aq20EncounterTrigger(botAI, name), _bossEntry(bossEntry), _spellId(spellId),
          _stacks(stacks) {}

protected:
    bool IsActiveInEncounter() override;

private:
    uint32 const _bossEntry;
    uint32 const _spellId;
    uint8 const _stacks;
};

enum class Aq20AddRole : uint8
{
    Everyone,
    DamageAndOffTanks,
    MeleeAndTanks,
};

// Moam's Mana Fiends, Buru's Hatchlings and Ayamiss's Larvae and Swarmers: adds the raid kills on
// sight, differing only in who goes for them.
class Aq20AddsSpawnedTrigger : public Aq20EncounterTrigger
{
public:
    Aq20AddsSpawnedTrigger(
        PlayerbotAI* botAI, std::string const& name, char const* addsValue, Aq20AddRole role)
        : Aq20EncounterTrigger(botAI, name), _addsValue(addsValue), _role(role) {}

protected:
    bool IsActiveInEncounter() override;

private:
    char const* const _addsValue;
    Aq20AddRole const _role;
};

// Ossirian's Sand Vortexes are creatures walking a waypoint path over ground nobody wants to be
// standing on.
class Aq20BotNearCreatureHazardTrigger : public Aq20EncounterTrigger
{
public:
    Aq20BotNearCreatureHazardTrigger(
        PlayerbotAI* botAI, std::string const& name, char const* hazardValue, float radius)
        : Aq20EncounterTrigger(botAI, name), _hazardValue(hazardValue), _radius(radius) {}

protected:
    bool IsActiveInEncounter() override;

private:
    char const* const _hazardValue;
    float const _radius;
};

// Kurinnaxx's Sand Traps are the same thing as a gameobject.
class Aq20BotNearGameObjectHazardTrigger : public Aq20EncounterTrigger
{
public:
    Aq20BotNearGameObjectHazardTrigger(
        PlayerbotAI* botAI, std::string const& name, char const* hazardValue, float radius)
        : Aq20EncounterTrigger(botAI, name), _hazardValue(hazardValue), _radius(radius) {}

protected:
    bool IsActiveInEncounter() override;

private:
    char const* const _hazardValue;
    float const _radius;
};

// Buru the Gorger

// Buru ignores threat for the whole egg phase and chases one player with a million threat on it
// (BUR:84, :125). That player is the only one who can bring him onto an egg.
class BuruBotFixatedTrigger : public Aq20EncounterTrigger
{
public:
    BuruBotFixatedTrigger(PlayerbotAI* botAI)
        : Aq20EncounterTrigger(botAI, "buru the gorger bot is fixated") {}

protected:
    bool IsActiveInEncounter() override;
};

// An egg popped next to Buru costs him 7% of his maximum health (BUR:255), which is the only
// reason to hit an egg at all: one that goes off away from him just spawns a Hatchling.
class BuruEggShouldBeKilledTrigger : public Aq20EncounterTrigger
{
public:
    BuruEggShouldBeKilledTrigger(PlayerbotAI* botAI)
        : Aq20EncounterTrigger(botAI, "buru the gorger egg should be killed") {}

protected:
    bool IsActiveInEncounter() override;
};

// Only the transform phase has a tank: it resets the threat list and drops the fixate (BUR:146).
class BuruShouldBeTankedTrigger : public Aq20EncounterTrigger
{
public:
    BuruShouldBeTankedTrigger(PlayerbotAI* botAI)
        : Aq20EncounterTrigger(botAI, "buru the gorger should be tanked") {}

protected:
    bool IsActiveInEncounter() override;
};

// Ayamiss the Hunter

// Ayamiss is rooted in the air until 70% and resets her threat list on the way down (AYA:91-96),
// so the tank's job starts with the ground phase.
class AyamissShouldBeTankedTrigger : public Aq20EncounterTrigger
{
public:
    AyamissShouldBeTankedTrigger(PlayerbotAI* botAI)
        : Aq20EncounterTrigger(botAI, "ayamiss the hunter should be tanked") {}

protected:
    bool IsActiveInEncounter() override;
};

// Ossirian the Unscarred

// The crystal's weakness spell keeps only Ossirian among its targets (OSS:460), so the tank walks
// the boss over to the next crystal before the weakness that is on him runs out.
class OssirianTankShouldMoveToCrystalTrigger : public Aq20EncounterTrigger
{
public:
    OssirianTankShouldMoveToCrystalTrigger(PlayerbotAI* botAI)
        : Aq20EncounterTrigger(botAI, "ossirian the unscarred tank should move to crystal") {}

protected:
    bool IsActiveInEncounter() override;
};

// The other half of the same job: the boss is standing by the crystal, so it is time to click it.
class OssirianCrystalShouldBeUsedTrigger : public Aq20EncounterTrigger
{
public:
    OssirianCrystalShouldBeUsedTrigger(PlayerbotAI* botAI)
        : Aq20EncounterTrigger(botAI, "ossirian the unscarred crystal should be used") {}

protected:
    bool IsActiveInEncounter() override;
};

#endif
