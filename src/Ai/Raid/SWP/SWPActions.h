/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#ifndef PLAYERBOTS_SWPACTIONS_H
#define PLAYERBOTS_SWPACTIONS_H

#include "Action.h"
#include "AttackAction.h"
#include "MovementActions.h"
#include "SWPHelpers.h"
#include <string>

// Shared

// Hold threat, pick a boss back up after a realm change, or switch to the twin that is this bot's
// job: all three are the same job, told apart by their trigger.
class SwpAttackCreatureAction : public AttackAction
{
public:
    SwpAttackCreatureAction(PlayerbotAI* botAI, std::string const& name, uint32 entry)
        : AttackAction(botAI, name), _entry(entry) {}
    bool Execute(Event event) override;

private:
    uint32 const _entry;
};

class KalecgosAttackRealmBossAction : public AttackAction
{
public:
    KalecgosAttackRealmBossAction(PlayerbotAI* botAI, bool spectral)
        : AttackAction(botAI, spectral ? "kalecgos attack sathrovarr" : "kalecgos attack boss"), _spectral(spectral) {}
    bool Execute(Event event) override;

private:
    bool const _spectral;
};

class SwpAttackNearestAddAction : public AttackAction
{
public:
    SwpAttackNearestAddAction(PlayerbotAI* botAI, std::string const& name, char const* addsValue)
        : AttackAction(botAI, name), _addsValue(addsValue) {}
    bool Execute(Event event) override;

private:
    char const* const _addsValue;
};

class SwpSpreadRangedAction : public MovementAction
{
public:
    SwpSpreadRangedAction(
        PlayerbotAI* botAI, std::string const& name, uint32 bossEntry, float distanceFromBoss)
        : MovementAction(botAI, name), _bossEntry(bossEntry), _distanceFromBoss(distanceFromBoss) {}
    bool Execute(Event event) override;

private:
    uint32 const _bossEntry;
    float const _distanceFromBoss;
};

class SwpMoveAwayFromHazardAction : public MovementAction
{
public:
    SwpMoveAwayFromHazardAction(
        PlayerbotAI* botAI, std::string const& name, char const* hazardValue, float radius)
        : MovementAction(botAI, name), _hazardValue(hazardValue), _radius(radius) {}
    bool Execute(Event event) override;

private:
    char const* const _hazardValue;
    float const _radius;
};

class SwpStopAttackingCharmedAllyAction : public Action
{
public:
    SwpStopAttackingCharmedAllyAction(PlayerbotAI* botAI, std::string const& name, uint32 bossEntry)
        : Action(botAI, name), _bossEntry(bossEntry) {}
    bool Execute(Event event) override;

private:
    uint32 const _bossEntry;
};

// Brutallus

// Serves both sides of Burn: the burning bot leaves the raid, and a bot standing next to a burning
// ally leaves him. In both cases the nearest player is the one to get away from.
class SwpFleeNearestPlayerAction : public MovementAction
{
public:
    SwpFleeNearestPlayerAction(PlayerbotAI* botAI, std::string const& name, float distance)
        : MovementAction(botAI, name), _distance(distance) {}
    bool Execute(Event event) override;

private:
    float const _distance;
};

// Circles the boss to its back half at the distance the bot already keeps, so a ranged bot does
// not walk into melee range to get out of a frontal cone.
class SwpMoveBehindBossAction : public MovementAction
{
public:
    SwpMoveBehindBossAction(PlayerbotAI* botAI, std::string const& name, uint32 bossEntry)
        : MovementAction(botAI, name), _bossEntry(bossEntry) {}
    bool Execute(Event event) override;

private:
    uint32 const _bossEntry;
};

// Eredar Twins

// The main tank takes Sacrolash and the first assist tank Alythess, so that the shadow damage and
// the fire damage each stay on one tank: a tank with both touched debuffs dies to Dark Flame.
class EredarTwinsAssignTanksAction : public AttackAction
{
public:
    EredarTwinsAssignTanksAction(PlayerbotAI* botAI)
        : AttackAction(botAI, "eredar twins assign tanks") {}
    bool Execute(Event event) override;
};

// Felmyst

// Steps sideways out of the lane Felmyst is breathing down, to whichever side the bot is already
// closer to.
class FelmystMoveOutOfBreathPathAction : public MovementAction
{
public:
    FelmystMoveOutOfBreathPathAction(PlayerbotAI* botAI)
        : MovementAction(botAI, "felmyst move out of breath path") {}
    bool Execute(Event event) override;
};

#endif
