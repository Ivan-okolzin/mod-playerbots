/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#ifndef PLAYERBOTS_VOAACTIONS_H
#define PLAYERBOTS_VOAACTIONS_H

#include "Action.h"
#include "AttackAction.h"
#include "Event.h"
#include "MovementActions.h"
#include "PlayerbotAI.h"
#include "VoAHelpers.h"
#include <string>

//
//  Emalon the Storm Watcher
//

class EmalonMarkBossAction : public MovementAction
{
public:
    EmalonMarkBossAction(PlayerbotAI* botAI) : MovementAction(botAI, "emalon mark boss action") {}
    bool Execute(Event event) override;
    bool isUseful() override;
};

class EmalonLightingNovaAction : public MovementAction
{
public:
    EmalonLightingNovaAction(PlayerbotAI* botAI) : MovementAction(botAI, "emalon lighting nova action") {}
    bool Execute(Event event) override;
    bool isUseful() override;
};

class EmalonOverchargeAction : public Action
{
public:
    EmalonOverchargeAction(PlayerbotAI* botAI) : Action(botAI, "emalon overcharge action") {}
    bool Execute(Event event) override;
    bool isUseful() override;
};

class EmalonFallFromFloorAction : public Action
{
public:
    EmalonFallFromFloorAction(PlayerbotAI* botAI) : Action(botAI, "emalon fall from floor action") {}
    bool Execute(Event event) override;
    bool isUseful() override;
};

// Shared

// Hold threat on a boss, or switch to the one this bot is meant to be hitting: the same job, told
// apart by its trigger.
class VoAAttackCreatureAction : public AttackAction
{
public:
    VoAAttackCreatureAction(PlayerbotAI* botAI, std::string const& name, uint32 entry)
        : AttackAction(botAI, name), _entry(entry) {}
    bool Execute(Event event) override;

private:
    uint32 const _entry;
};

// Takes an add and keeps it: the Tempest Minions pick their own target when they join the fight
// (BE:131, :209), so a tank has to taunt the ones that went for somebody else.
class VoATankAttackNearestAddAction : public AttackAction
{
public:
    VoATankAttackNearestAddAction(
        PlayerbotAI* botAI, std::string const& name, char const* addsValue)
        : AttackAction(botAI, name), _addsValue(addsValue) {}
    bool Execute(Event event) override;

private:
    char const* const _addsValue;
};

class VoAAttackNearestAddAction : public AttackAction
{
public:
    VoAAttackNearestAddAction(PlayerbotAI* botAI, std::string const& name, char const* addsValue)
        : AttackAction(botAI, name), _addsValue(addsValue) {}
    bool Execute(Event event) override;

private:
    char const* const _addsValue;
};

class VoASpreadRangedAction : public MovementAction
{
public:
    VoASpreadRangedAction(PlayerbotAI* botAI, std::string const& name, uint32 bossEntry)
        : MovementAction(botAI, name), _bossEntry(bossEntry) {}
    bool Execute(Event event) override;

private:
    uint32 const _bossEntry;
};

class VoAMoveAwayFromAddAction : public MovementAction
{
public:
    VoAMoveAwayFromAddAction(
        PlayerbotAI* botAI, std::string const& name, char const* addsValue, float radius)
        : MovementAction(botAI, name), _addsValue(addsValue), _radius(radius) {}
    bool Execute(Event event) override;

private:
    char const* const _addsValue;
    float const _radius;
};

// Emalon the Storm Watcher

class EmalonAttackOverchargedMinionAction : public AttackAction
{
public:
    EmalonAttackOverchargedMinionAction(PlayerbotAI* botAI)
        : AttackAction(botAI, "emalon attack overcharged minion") {}
    bool Execute(Event event) override;
};

// Koralon the Flame Watcher

// Steps to the far side of Koralon, which is the one place the breath does not reach while he
// turns through the half of the room he faces.
class KoralonMoveBehindBossAction : public MovementAction
{
public:
    KoralonMoveBehindBossAction(PlayerbotAI* botAI)
        : MovementAction(botAI, "koralon move behind koralon") {}
    bool Execute(Event event) override;
};

// Toravon the Ice Watcher

// The orb keeps the player it picked for ten seconds (BT:191); until it drops it, the only answer
// is distance.
class ToravonFleeFromOrbAction : public MovementAction
{
public:
    ToravonFleeFromOrbAction(PlayerbotAI* botAI)
        : MovementAction(botAI, "toravon flee from frozen orb") {}
    bool Execute(Event event) override;
};

class ToravonMoveOutOfFreezingGroundAction : public MovementAction
{
public:
    ToravonMoveOutOfFreezingGroundAction(PlayerbotAI* botAI)
        : MovementAction(botAI, "toravon move out of freezing ground") {}
    bool Execute(Event event) override;
};

#endif
