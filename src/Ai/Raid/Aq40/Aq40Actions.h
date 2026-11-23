/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#ifndef PLAYERBOTS_AQ40ACTIONS_H
#define PLAYERBOTS_AQ40ACTIONS_H

#include "Action.h"
#include "Aq40Helpers.h"
#include "AttackAction.h"
#include "MovementActions.h"
#include "Position.h"
#include <string>

// Shared

class Aq40ResetEncounterStatesAction : public Action
{
public:
    Aq40ResetEncounterStatesAction(PlayerbotAI* botAI)
        : Action(botAI, "aq40 reset encounter states") {}
    bool Execute(Event event) override;
};

// Sartura, Fankriss, Huhuran, and Ouro: hold threat on the boss, nothing else.
class Aq40MainTankAttackBossAction : public AttackAction
{
public:
    Aq40MainTankAttackBossAction(
        PlayerbotAI* botAI, std::string const& name, std::string const& bossName)
        : AttackAction(botAI, name), _bossName(bossName) {}
    bool Execute(Event event) override;

private:
    std::string const _bossName;
};

class Aq40SpreadRangedAction : public MovementAction
{
public:
    Aq40SpreadRangedAction(
        PlayerbotAI* botAI, std::string const& name, std::string const& bossName,
        float distanceFromBoss)
        : MovementAction(botAI, name), _bossName(bossName), _distanceFromBoss(distanceFromBoss) {}
    bool Execute(Event event) override;

private:
    std::string const _bossName;
    float const _distanceFromBoss;
};

class Aq40MoveOutOfHazardAction : public MovementAction
{
public:
    Aq40MoveOutOfHazardAction(
        PlayerbotAI* botAI, std::string const& name, char const* hazardValue, float radius)
        : MovementAction(botAI, name), _hazardValue(hazardValue), _radius(radius) {}
    bool Execute(Event event) override;

private:
    char const* const _hazardValue;
    float const _radius;
};

class Aq40AttackNearestAddAction : public AttackAction
{
public:
    Aq40AttackNearestAddAction(
        PlayerbotAI* botAI, std::string const& name, char const* addsValue)
        : AttackAction(botAI, name), _addsValue(addsValue) {}
    bool Execute(Event event) override;

private:
    char const* const _addsValue;
};

// The Prophet Skeram

class SkeramMainTankAttackBossAction : public AttackAction
{
public:
    SkeramMainTankAttackBossAction(PlayerbotAI* botAI)
        : AttackAction(botAI, "the prophet skeram main tank attack boss") {}
    bool Execute(Event event) override;
};

class SkeramAssistTankAttackImageAction : public AttackAction
{
public:
    SkeramAssistTankAttackImageAction(PlayerbotAI* botAI)
        : AttackAction(botAI, "the prophet skeram assist tank attack image") {}
    bool Execute(Event event) override;
};

class SkeramAssignDpsPriorityAction : public AttackAction
{
public:
    SkeramAssignDpsPriorityAction(PlayerbotAI* botAI)
        : AttackAction(botAI, "the prophet skeram assign dps priority") {}
    bool Execute(Event event) override;
};

class SkeramStopAttackingMindControlledAllyAction : public Action
{
public:
    SkeramStopAttackingMindControlledAllyAction(PlayerbotAI* botAI)
        : Action(botAI, "the prophet skeram stop attacking mind controlled ally") {}
    bool Execute(Event event) override;
};

// Silithid Royalty

class BugTrioAssignTanksAction : public AttackAction
{
public:
    BugTrioAssignTanksAction(PlayerbotAI* botAI)
        : AttackAction(botAI, "bug trio assign tanks") {}
    bool Execute(Event event) override;
};

class BugTrioAssignDpsPriorityAction : public AttackAction
{
public:
    BugTrioAssignDpsPriorityAction(PlayerbotAI* botAI)
        : AttackAction(botAI, "bug trio assign dps priority") {}
    bool Execute(Event event) override;
};

// Battleguard Sartura

class SarturaAssistTankAttackGuardAction : public AttackAction
{
public:
    SarturaAssistTankAttackGuardAction(PlayerbotAI* botAI)
        : AttackAction(botAI, "battleguard sartura assist tank attack guard") {}
    bool Execute(Event event) override;
};

class SarturaMeleeBackOffAction : public MovementAction
{
public:
    SarturaMeleeBackOffAction(PlayerbotAI* botAI)
        : MovementAction(botAI, "battleguard sartura melee back off") {}
    bool Execute(Event event) override;
};

class SarturaAssignDpsPriorityAction : public AttackAction
{
public:
    SarturaAssignDpsPriorityAction(PlayerbotAI* botAI)
        : AttackAction(botAI, "battleguard sartura assign dps priority") {}
    bool Execute(Event event) override;
};

// Fankriss the Unyielding

class FankrissTankSwapAction : public AttackAction
{
public:
    FankrissTankSwapAction(PlayerbotAI* botAI)
        : AttackAction(botAI, "fankriss the unyielding tank swap") {}
    bool Execute(Event event) override;
};

// Viscidus

class ViscidusCastFrostSpellAction : public Action
{
public:
    ViscidusCastFrostSpellAction(PlayerbotAI* botAI)
        : Action(botAI, "viscidus cast frost spell") {}
    bool Execute(Event event) override;
};

// Twin Emperors

class TwinEmperorsTankPositionBossAction : public AttackAction
{
public:
    TwinEmperorsTankPositionBossAction(PlayerbotAI* botAI)
        : AttackAction(botAI, "twin emperors tank position boss") {}
    bool Execute(Event event) override;
};

class TwinEmperorsSwitchTargetAction : public AttackAction
{
public:
    TwinEmperorsSwitchTargetAction(
        PlayerbotAI* botAI, std::string const& name, std::string const& bossName)
        : AttackAction(botAI, name), _bossName(bossName) {}
    bool Execute(Event event) override;

private:
    std::string const _bossName;
};

// C'Thun

class CthunMoveOutOfDarkGlareAction : public MovementAction
{
public:
    CthunMoveOutOfDarkGlareAction(PlayerbotAI* botAI)
        : MovementAction(botAI, "eye of c'thun move out of dark glare") {}
    bool Execute(Event event) override;
};

class CthunAttackBodyAction : public AttackAction
{
public:
    CthunAttackBodyAction(PlayerbotAI* botAI)
        : AttackAction(botAI, "c'thun attack body") {}
    bool Execute(Event event) override;
};

class CthunLeaveStomachAction : public MovementAction
{
public:
    CthunLeaveStomachAction(PlayerbotAI* botAI)
        : MovementAction(botAI, "c'thun leave stomach") {}
    bool Execute(Event event) override;
};

// Ouro

class OuroSpreadFromDirtMoundsAction : public MovementAction
{
public:
    OuroSpreadFromDirtMoundsAction(PlayerbotAI* botAI)
        : MovementAction(botAI, "ouro spread from dirt mounds") {}
    bool Execute(Event event) override;
};

#endif
