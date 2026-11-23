/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#ifndef PLAYERBOTS_ZGACTIONS_H
#define PLAYERBOTS_ZGACTIONS_H

#include "Action.h"
#include "AttackAction.h"
#include "MovementActions.h"
#include "ZGHelpers.h"
#include <string>

// Shared

class ZulGurubResetEncounterStatesAction : public Action
{
public:
    ZulGurubResetEncounterStatesAction(PlayerbotAI* botAI)
        : Action(botAI, "zg reset encounter states") {}
    bool Execute(Event event) override;
};

// Hold threat on the boss, nothing else.
class ZulGurubMainTankAttackBossAction : public AttackAction
{
public:
    ZulGurubMainTankAttackBossAction(
        PlayerbotAI* botAI, std::string const& name, uint32 bossEntry)
        : AttackAction(botAI, name), _bossEntry(bossEntry) {}
    bool Execute(Event event) override;

private:
    uint32 const _bossEntry;
};

// Take a boss back after a threat wipe. Also how the second tank picks Jin'do up off a hexed
// first tank.
class ZulGurubTankTauntBossAction : public AttackAction
{
public:
    ZulGurubTankTauntBossAction(PlayerbotAI* botAI, std::string const& name, uint32 bossEntry)
        : AttackAction(botAI, name), _bossEntry(bossEntry) {}
    bool Execute(Event event) override;

private:
    uint32 const _bossEntry;
};

class ZulGurubAttackNearestAddAction : public AttackAction
{
public:
    ZulGurubAttackNearestAddAction(
        PlayerbotAI* botAI, std::string const& name, char const* addsValue)
        : AttackAction(botAI, name), _addsValue(addsValue) {}
    bool Execute(Event event) override;

private:
    char const* const _addsValue;
};

class ZulGurubMoveOutOfHazardAction : public MovementAction
{
public:
    ZulGurubMoveOutOfHazardAction(
        PlayerbotAI* botAI, std::string const& name, char const* hazardValue, float radius)
        : MovementAction(botAI, name), _hazardValue(hazardValue), _radius(radius) {}
    bool Execute(Event event) override;

private:
    char const* const _hazardValue;
    float const _radius;
};

class ZulGurubSpreadRangedAction : public MovementAction
{
public:
    ZulGurubSpreadRangedAction(PlayerbotAI* botAI, std::string const& name)
        : MovementAction(botAI, name) {}
    bool Execute(Event event) override;
};

// Serves Mandokir's Whirlwind, where melee step out of its reach, and Gri'lek's Avatar, where the
// pursued player kites: in both cases the creature is what has to be put at a distance.
class ZulGurubFleeFromCreatureAction : public MovementAction
{
public:
    ZulGurubFleeFromCreatureAction(
        PlayerbotAI* botAI, std::string const& name, uint32 creatureEntry, float distance)
        : MovementAction(botAI, name), _creatureEntry(creatureEntry), _distance(distance) {}
    bool Execute(Event event) override;

private:
    uint32 const _creatureEntry;
    float const _distance;
};

class ZulGurubStopAttackingCharmedAllyAction : public Action
{
public:
    ZulGurubStopAttackingCharmedAllyAction(
        PlayerbotAI* botAI, std::string const& name, uint32 bossEntry)
        : Action(botAI, name), _bossEntry(bossEntry) {}
    bool Execute(Event event) override;

private:
    uint32 const _bossEntry;
};

// Walks into a Poisonous Cloud, which is where the poison Blood Siphon needs comes from.
class ZulGurubMoveIntoPoisonousCloudAction : public MovementAction
{
public:
    ZulGurubMoveIntoPoisonousCloudAction(PlayerbotAI* botAI)
        : MovementAction(botAI, "zg move into poisonous cloud") {}
    bool Execute(Event event) override;
};

// Bloodlord Mandokir

// Threatening Gaze punishes threat, not movement, so the bot drops everything aimed at an enemy
// and waits the aura out. The watch hold multiplier keeps it from starting again next tick.
class MandokirStopAttackingWhileWatchedAction : public Action
{
public:
    MandokirStopAttackingWhileWatchedAction(PlayerbotAI* botAI)
        : Action(botAI, "bloodlord mandokir stop attacking while watched") {}
    bool Execute(Event event) override;
};

// High Priest Thekal

class ThekalAssistTankAttackZealotAction : public AttackAction
{
public:
    ThekalAssistTankAttackZealotAction(PlayerbotAI* botAI)
        : AttackAction(botAI, "high priest thekal assist tank attack zealot") {}
    bool Execute(Event event) override;
};

class ThekalAttackTrioFocusAction : public AttackAction
{
public:
    ThekalAttackTrioFocusAction(PlayerbotAI* botAI)
        : AttackAction(botAI, "high priest thekal attack healthiest trio target") {}
    bool Execute(Event event) override;
};

#endif
