/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#ifndef PLAYERBOTS_SWPTRIGGERS_H
#define PLAYERBOTS_SWPTRIGGERS_H

#include "EncounterHelpers.h"
#include "SWPHelpers.h"
#include "Trigger.h"
#include <string>
#include <utility>
#include <vector>

// Shared

class SwpEncounterTrigger : public Trigger
{
public:
    SwpEncounterTrigger(PlayerbotAI* botAI, std::string const name, int32 checkInterval = 1)
        : Trigger(botAI, name, checkInterval) {}

    bool IsActive() final
    {
        return EncounterHelpers::IsEncounterInProgress(bot, SwpHelpers::SWP_MAP_ID) &&
            IsActiveInEncounter();
    }

protected:
    virtual bool IsActiveInEncounter() = 0;
};

// Brutallus, Felmyst, M'uru, Entropius, and Kil'jaeden all want nothing more of their tank than
// threat on a boss that stays put. Kalecgos needs the same, but only from the dragon realm.
class SwpBossShouldBeTankedTrigger : public SwpEncounterTrigger
{
public:
    SwpBossShouldBeTankedTrigger(PlayerbotAI* botAI, std::string const& name, uint32 bossEntry)
        : SwpEncounterTrigger(botAI, name), _bossEntry(bossEntry) {}

protected:
    bool IsActiveInEncounter() override;

private:
    uint32 const _bossEntry;
};

// Ranged spread out from each other, and keep their distance from the boss where its melee-range
// mechanics warrant it.
class SwpRangedShouldSpreadTrigger : public SwpEncounterTrigger
{
public:
    SwpRangedShouldSpreadTrigger(
        PlayerbotAI* botAI, std::string const& name, uint32 bossEntry, float distanceFromBoss)
        : SwpEncounterTrigger(botAI, name), _bossEntry(bossEntry),
          _distanceFromBoss(distanceFromBoss) {}

protected:
    bool IsActiveInEncounter() override;

private:
    uint32 const _bossEntry;
    float const _distanceFromBoss;
};

enum class SwpAddRole : uint8
{
    Everyone,
    MeleeAndTanks,
    Tanks,
    RangedDps,
};

// Felmyst's Unyielding Dead, M'uru's Dark Fiends, Void Sentinels and blood elves, and
// Kil'jaeden's Shield Orbs, Sinister Reflections and Hands of the Deceiver: adds the raid kills
// on sight, differing only in who goes for them.
class SwpAddsSpawnedTrigger : public SwpEncounterTrigger
{
public:
    SwpAddsSpawnedTrigger(
        PlayerbotAI* botAI, std::string const& name, char const* addsValue, SwpAddRole role)
        : SwpEncounterTrigger(botAI, name), _addsValue(addsValue), _role(role) {}

protected:
    bool IsActiveInEncounter() override;

private:
    char const* const _addsValue;
    SwpAddRole const _role;
};

// Felmyst's Vapor Trail, M'uru's Darkness, Entropius's Singularity, and Kil'jaeden's Armageddon
// markers are all creatures standing on ground nobody wants to be on.
class SwpBotNearHazardTrigger : public SwpEncounterTrigger
{
public:
    SwpBotNearHazardTrigger(
        PlayerbotAI* botAI, std::string const& name, char const* hazardValue, float radius)
        : SwpEncounterTrigger(botAI, name), _hazardValue(hazardValue), _radius(radius) {}

protected:
    bool IsActiveInEncounter() override;

private:
    char const* const _hazardValue;
    float const _radius;
};

// Kalecgos

// Spectral Blast drops a random raid member into the Spectral Realm, where Sathrovarr is the only
// thing that can be reached or attacked.
class KalecgosBotInSpectralRealmTrigger : public SwpEncounterTrigger
{
public:
    KalecgosBotInSpectralRealmTrigger(PlayerbotAI* botAI)
        : SwpEncounterTrigger(botAI, "kalecgos bot in spectral realm") {}

protected:
    bool IsActiveInEncounter() override;
};

// The other side of the same check: a bot back from the realm has to pick the dragon up again.
class KalecgosBotInDragonRealmTrigger : public SwpEncounterTrigger
{
public:
    KalecgosBotInDragonRealmTrigger(PlayerbotAI* botAI)
        : SwpEncounterTrigger(botAI, "kalecgos bot in dragon realm") {}

protected:
    bool IsActiveInEncounter() override;
};

// Brutallus

class BrutallusBotIsBurningTrigger : public SwpEncounterTrigger
{
public:
    BrutallusBotIsBurningTrigger(PlayerbotAI* botAI)
        : SwpEncounterTrigger(botAI, "brutallus bot is burning") {}

protected:
    bool IsActiveInEncounter() override;
};

class BrutallusBotNearBurningAllyTrigger : public SwpEncounterTrigger
{
public:
    BrutallusBotNearBurningAllyTrigger(PlayerbotAI* botAI)
        : SwpEncounterTrigger(botAI, "brutallus bot near burning ally") {}

protected:
    bool IsActiveInEncounter() override;
};

// Meteor Slash splits its damage between everyone in front of Brutallus and leaves them unable to
// take the next one, so whoever carries it steps out of his front half.
class BrutallusBotHasMeteorSlashTrigger : public SwpEncounterTrigger
{
public:
    BrutallusBotHasMeteorSlashTrigger(PlayerbotAI* botAI)
        : SwpEncounterTrigger(botAI, "brutallus bot has meteor slash") {}

protected:
    bool IsActiveInEncounter() override;
};

// Felmyst

// The Fog of Corruption charms whatever the breath touches, and the breath runs the length of the
// lane Felmyst is flying.
class FelmystBreathIncomingTrigger : public SwpEncounterTrigger
{
public:
    FelmystBreathIncomingTrigger(PlayerbotAI* botAI)
        : SwpEncounterTrigger(botAI, "felmyst breath incoming") {}

protected:
    bool IsActiveInEncounter() override;
};

// Charmed raid members turn on their own raid, and the bots' target selection picks them up.
class SwpAttackingCharmedAllyTrigger : public SwpEncounterTrigger
{
public:
    SwpAttackingCharmedAllyTrigger(
        PlayerbotAI* botAI, std::string const& name, std::vector<uint32> charmSpellIds)
        : SwpEncounterTrigger(botAI, name), _charmSpellIds(std::move(charmSpellIds)) {}

protected:
    bool IsActiveInEncounter() override;

private:
    std::vector<uint32> const _charmSpellIds;
};

// Eredar Twins

class EredarTwinsShouldBeTankedTrigger : public SwpEncounterTrigger
{
public:
    EredarTwinsShouldBeTankedTrigger(PlayerbotAI* botAI)
        : SwpEncounterTrigger(botAI, "eredar twins should be tanked") {}

protected:
    bool IsActiveInEncounter() override;
};

class EredarTwinsShouldSwitchTargetTrigger : public SwpEncounterTrigger
{
public:
    EredarTwinsShouldSwitchTargetTrigger(
        PlayerbotAI* botAI, std::string const& name, uint32 bossEntry, bool forMelee)
        : SwpEncounterTrigger(botAI, name), _bossEntry(bossEntry), _forMelee(forMelee) {}

protected:
    bool IsActiveInEncounter() override;

private:
    uint32 const _bossEntry;
    bool const _forMelee;
};

#endif
