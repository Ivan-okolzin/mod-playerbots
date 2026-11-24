/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#ifndef PLAYERBOTS_AQ40TRIGGERS_H
#define PLAYERBOTS_AQ40TRIGGERS_H

#include "Aq40Helpers.h"
#include "EncounterHelpers.h"
#include "Trigger.h"
#include <string>
#include <utility>
#include <vector>

// Shared

class Aq40EncounterTrigger : public Trigger
{
public:
    Aq40EncounterTrigger(PlayerbotAI* botAI, std::string const name, int32 checkInterval = 1)
        : Trigger(botAI, name, checkInterval) {}

    bool IsActive() final
    {
        return EncounterHelpers::IsEncounterInProgress(bot, Aq40Helpers::AQ40_MAP_ID) &&
            IsActiveInEncounter();
    }

protected:
    virtual bool IsActiveInEncounter() = 0;
};

class Aq40NoEncounterInProgressTrigger : public Trigger
{
public:
    Aq40NoEncounterInProgressTrigger(PlayerbotAI* botAI)
        : Trigger(botAI, "aq40 no encounter in progress", 1000) {}
    bool IsActive() override;
};

// Covers Sartura, Fankriss, Huhuran, and Ouro, whose tanking needs nothing but threat and a boss
// that stays put. Skeram and the Twins have their own, and the Bug Trio needs three tanks.
class Aq40BossShouldBeTankedTrigger : public Aq40EncounterTrigger
{
public:
    Aq40BossShouldBeTankedTrigger(
        PlayerbotAI* botAI, std::string const& name, std::string const& bossName)
        : Aq40EncounterTrigger(botAI, name), _bossName(bossName) {}

protected:
    bool IsActiveInEncounter() override;

private:
    std::string const _bossName;
};

// Ranged spread out from each other, and keep their distance from the boss where its melee-range
// mechanics warrant it.
class Aq40RangedShouldSpreadTrigger : public Aq40EncounterTrigger
{
public:
    Aq40RangedShouldSpreadTrigger(
        PlayerbotAI* botAI, std::string const& name, std::string const& bossName,
        float distanceFromBoss)
        : Aq40EncounterTrigger(botAI, name), _bossName(bossName),
          _distanceFromBoss(distanceFromBoss) {}

protected:
    bool IsActiveInEncounter() override;

private:
    std::string const _bossName;
    float const _distanceFromBoss;
};

// Lord Kri's Poison Cloud, Huhuran's Noxious Poison, and Vek'lor's Blizzard are all dynamic-object
// ground hazards, so one trigger covers them.
class Aq40BotInHazardTrigger : public Aq40EncounterTrigger
{
public:
    // bossNames gates the hazard's grid search on the fight actually being the one that casts it.
    Aq40BotInHazardTrigger(
        PlayerbotAI* botAI, std::string const& name, char const* hazardValue, float radius,
        std::vector<std::string> bossNames)
        : Aq40EncounterTrigger(botAI, name), _hazardValue(hazardValue), _radius(radius),
          _bossNames(std::move(bossNames)) {}

protected:
    bool IsActiveInEncounter() override;

private:
    char const* const _hazardValue;
    float const _radius;
    std::vector<std::string> const _bossNames;
};

enum class Aq40AddRole : uint8
{
    Everyone,
    MeleeAndTanks,
    AssistTanks,
    Dps,
    Tanks,
    RangedDps,
};

// Yauj's Brood, Fankriss's worms, Viscidus's Globs, Ouro's Scarabs, and C'Thun's tentacles: adds
// that the raid kills on sight, differing only in who goes for them.
class Aq40AddsSpawnedTrigger : public Aq40EncounterTrigger
{
public:
    Aq40AddsSpawnedTrigger(
        PlayerbotAI* botAI, std::string const& name, char const* addsValue, Aq40AddRole role)
        : Aq40EncounterTrigger(botAI, name), _addsValue(addsValue), _role(role) {}

protected:
    bool IsActiveInEncounter() override;

private:
    char const* const _addsValue;
    Aq40AddRole const _role;
};

// The Prophet Skeram

class SkeramShouldBeTankedTrigger : public Aq40EncounterTrigger
{
public:
    SkeramShouldBeTankedTrigger(PlayerbotAI* botAI)
        : Aq40EncounterTrigger(botAI, "the prophet skeram should be tanked") {}

protected:
    bool IsActiveInEncounter() override;
};

class SkeramImagesSpawnedTrigger : public Aq40EncounterTrigger
{
public:
    SkeramImagesSpawnedTrigger(PlayerbotAI* botAI)
        : Aq40EncounterTrigger(botAI, "the prophet skeram images spawned") {}

protected:
    bool IsActiveInEncounter() override;
};

class SkeramShouldAssignDpsPriorityTrigger : public Aq40EncounterTrigger
{
public:
    SkeramShouldAssignDpsPriorityTrigger(PlayerbotAI* botAI)
        : Aq40EncounterTrigger(botAI, "the prophet skeram should assign dps priority") {}

protected:
    bool IsActiveInEncounter() override;
};

class SkeramAttackingMindControlledAllyTrigger : public Aq40EncounterTrigger
{
public:
    SkeramAttackingMindControlledAllyTrigger(PlayerbotAI* botAI)
        : Aq40EncounterTrigger(botAI, "the prophet skeram attacking mind controlled ally") {}

protected:
    bool IsActiveInEncounter() override;
};

// Silithid Royalty

class BugTrioTargetsShouldBeTankedTrigger : public Aq40EncounterTrigger
{
public:
    BugTrioTargetsShouldBeTankedTrigger(PlayerbotAI* botAI)
        : Aq40EncounterTrigger(botAI, "bug trio targets should be tanked") {}

protected:
    bool IsActiveInEncounter() override;
};

class BugTrioShouldAssignDpsPriorityTrigger : public Aq40EncounterTrigger
{
public:
    BugTrioShouldAssignDpsPriorityTrigger(PlayerbotAI* botAI)
        : Aq40EncounterTrigger(botAI, "bug trio should assign dps priority") {}

protected:
    bool IsActiveInEncounter() override;
};

// Battleguard Sartura

class SarturaRoyalGuardsShouldBeTankedTrigger : public Aq40EncounterTrigger
{
public:
    SarturaRoyalGuardsShouldBeTankedTrigger(PlayerbotAI* botAI)
        : Aq40EncounterTrigger(botAI, "battleguard sartura royal guards should be tanked") {}

protected:
    bool IsActiveInEncounter() override;
};

class SarturaMeleeInWhirlwindRangeTrigger : public Aq40EncounterTrigger
{
public:
    SarturaMeleeInWhirlwindRangeTrigger(PlayerbotAI* botAI)
        : Aq40EncounterTrigger(botAI, "battleguard sartura melee in whirlwind range") {}

protected:
    bool IsActiveInEncounter() override;
};

class SarturaShouldAssignDpsPriorityTrigger : public Aq40EncounterTrigger
{
public:
    SarturaShouldAssignDpsPriorityTrigger(PlayerbotAI* botAI)
        : Aq40EncounterTrigger(botAI, "battleguard sartura should assign dps priority") {}

protected:
    bool IsActiveInEncounter() override;
};

// Fankriss the Unyielding

class FankrissMainTankMortalWoundStacksTrigger : public Aq40EncounterTrigger
{
public:
    FankrissMainTankMortalWoundStacksTrigger(PlayerbotAI* botAI)
        : Aq40EncounterTrigger(botAI, "fankriss the unyielding main tank has mortal wound stacks")
    {
    }

protected:
    bool IsActiveInEncounter() override;
};

// Viscidus

class ViscidusInFrostPhaseTrigger : public Aq40EncounterTrigger
{
public:
    ViscidusInFrostPhaseTrigger(PlayerbotAI* botAI)
        : Aq40EncounterTrigger(botAI, "viscidus in frost phase") {}

protected:
    bool IsActiveInEncounter() override;
};

class ViscidusFrozenTrigger : public Aq40EncounterTrigger
{
public:
    ViscidusFrozenTrigger(PlayerbotAI* botAI)
        : Aq40EncounterTrigger(botAI, "viscidus frozen") {}

protected:
    bool IsActiveInEncounter() override;
};

// Twin Emperors

class TwinEmperorsShouldBeTankedApartTrigger : public Aq40EncounterTrigger
{
public:
    TwinEmperorsShouldBeTankedApartTrigger(PlayerbotAI* botAI)
        : Aq40EncounterTrigger(botAI, "twin emperors should be tanked apart") {}

protected:
    bool IsActiveInEncounter() override;
};

class TwinEmperorsMeleeShouldAttackVeknilashTrigger : public Aq40EncounterTrigger
{
public:
    TwinEmperorsMeleeShouldAttackVeknilashTrigger(PlayerbotAI* botAI)
        : Aq40EncounterTrigger(botAI, "twin emperors melee should attack vek'nilash") {}

protected:
    bool IsActiveInEncounter() override;
};

class TwinEmperorsCastersShouldAttackVeklorTrigger : public Aq40EncounterTrigger
{
public:
    TwinEmperorsCastersShouldAttackVeklorTrigger(PlayerbotAI* botAI)
        : Aq40EncounterTrigger(botAI, "twin emperors casters should attack vek'lor") {}

protected:
    bool IsActiveInEncounter() override;
};

// C'Thun

// Phase 1. The beam is a five yard wide line out of the Eye's front, so what matters is standing
// clear of that line, not the distance to the Eye.
class CthunBotInDarkGlarePathTrigger : public Aq40EncounterTrigger
{
public:
    CthunBotInDarkGlarePathTrigger(PlayerbotAI* botAI)
        : Aq40EncounterTrigger(botAI, "eye of c'thun dark glare incoming") {}

protected:
    bool IsActiveInEncounter() override;
};

// Phase 2. The 45 second window in which the body can be damaged at all.
class CthunBodyWeakenedTrigger : public Aq40EncounterTrigger
{
public:
    CthunBodyWeakenedTrigger(PlayerbotAI* botAI)
        : Aq40EncounterTrigger(botAI, "c'thun body is weakened") {}

protected:
    bool IsActiveInEncounter() override;
};

// Phase 2. Only a swallowed bot can reach the Flesh Tentacles, and killing both is what opens the
// weakened window.
class CthunFleshTentacleInStomachTrigger : public Aq40EncounterTrigger
{
public:
    CthunFleshTentacleInStomachTrigger(PlayerbotAI* botAI)
        : Aq40EncounterTrigger(botAI, "c'thun bot in stomach with flesh tentacle") {}

protected:
    bool IsActiveInEncounter() override;
};

class CthunShouldLeaveStomachTrigger : public Aq40EncounterTrigger
{
public:
    CthunShouldLeaveStomachTrigger(PlayerbotAI* botAI)
        : Aq40EncounterTrigger(botAI, "c'thun bot should leave stomach") {}

protected:
    bool IsActiveInEncounter() override;
};

// Spacing is pointless inside the stomach, where the bots have two tentacles to kill and nowhere
// to go.
class CthunRangedShouldSpreadTrigger : public Aq40RangedShouldSpreadTrigger
{
public:
    CthunRangedShouldSpreadTrigger(
        PlayerbotAI* botAI, std::string const& name, std::string const& bossName,
        float distanceFromBoss)
        : Aq40RangedShouldSpreadTrigger(botAI, name, bossName, distanceFromBoss) {}

protected:
    bool IsActiveInEncounter() override;
};

// Ouro

class OuroMeleeInFrontOfBossTrigger : public Aq40EncounterTrigger
{
public:
    OuroMeleeInFrontOfBossTrigger(PlayerbotAI* botAI)
        : Aq40EncounterTrigger(botAI, "ouro melee in front of boss") {}

protected:
    bool IsActiveInEncounter() override;
};

class OuroSubmergedTrigger : public Aq40EncounterTrigger
{
public:
    OuroSubmergedTrigger(PlayerbotAI* botAI)
        : Aq40EncounterTrigger(botAI, "ouro submerged") {}

protected:
    bool IsActiveInEncounter() override;
};

#endif
