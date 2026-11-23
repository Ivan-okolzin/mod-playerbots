/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#ifndef PLAYERBOTS_AQ20ACTIONS_H
#define PLAYERBOTS_AQ20ACTIONS_H

#include "Action.h"
#include "Aq20Helpers.h"
#include "AttackAction.h"
#include "MovementActions.h"
#include <string>

// Shared

// Take and keep threat on a boss. The taunt is for the bosses that wipe their threat list in the
// middle of the fight, where holding the target is not enough.
class Aq20TankBossAction : public AttackAction
{
public:
    Aq20TankBossAction(PlayerbotAI* botAI, std::string const& name, uint32 bossEntry, bool taunt)
        : AttackAction(botAI, name), _bossEntry(bossEntry), _taunt(taunt) {}
    bool Execute(Event event) override;

private:
    uint32 const _bossEntry;
    bool const _taunt;
};

class Aq20AttackNearestAddAction : public AttackAction
{
public:
    Aq20AttackNearestAddAction(PlayerbotAI* botAI, std::string const& name, char const* addsValue)
        : AttackAction(botAI, name), _addsValue(addsValue) {}
    bool Execute(Event event) override;

private:
    char const* const _addsValue;
};

class Aq20MoveAwayFromCreatureHazardAction : public MovementAction
{
public:
    Aq20MoveAwayFromCreatureHazardAction(
        PlayerbotAI* botAI, std::string const& name, char const* hazardValue, float radius)
        : MovementAction(botAI, name), _hazardValue(hazardValue), _radius(radius) {}
    bool Execute(Event event) override;

private:
    char const* const _hazardValue;
    float const _radius;
};

class Aq20MoveAwayFromGameObjectHazardAction : public MovementAction
{
public:
    Aq20MoveAwayFromGameObjectHazardAction(
        PlayerbotAI* botAI, std::string const& name, char const* hazardValue, float radius)
        : MovementAction(botAI, name), _hazardValue(hazardValue), _radius(radius) {}
    bool Execute(Event event) override;

private:
    char const* const _hazardValue;
    float const _radius;
};

// Buru the Gorger

// Walks the fixated bot onto the nearest egg so that Buru follows it there: the explosion only
// costs him health if he is standing in it (BUR:254).
class BuruLureBossToEggAction : public MovementAction
{
public:
    BuruLureBossToEggAction(PlayerbotAI* botAI)
        : MovementAction(botAI, "buru the gorger lure boss to egg") {}
    bool Execute(Event event) override;
};

// Puts the raid on the one egg Buru is standing by and marks it, so that human raid members see
// the same egg the bots picked.
class BuruAttackTargetEggAction : public AttackAction
{
public:
    BuruAttackTargetEggAction(PlayerbotAI* botAI)
        : AttackAction(botAI, "buru the gorger attack target egg") {}
    bool Execute(Event event) override;
};

// Ossirian the Unscarred

// Walks the tank to the next crystal, which brings the boss along: the weakness spell is cast
// from the crystal and reaches nothing further away (OSS:344, :460).
class OssirianTankMoveToCrystalAction : public MovementAction
{
public:
    OssirianTankMoveToCrystalAction(PlayerbotAI* botAI)
        : MovementAction(botAI, "ossirian the unscarred tank move to crystal") {}
    bool Execute(Event event) override;
};

// Clicks the crystal, which strips Strength of Ossirian and leaves a weakness in its place.
class OssirianUseCrystalAction : public Action
{
public:
    OssirianUseCrystalAction(PlayerbotAI* botAI)
        : Action(botAI, "ossirian the unscarred use crystal") {}
    bool Execute(Event event) override;
};

#endif
