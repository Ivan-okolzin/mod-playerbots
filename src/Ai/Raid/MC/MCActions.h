/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#ifndef PLAYERBOTS_MCACTIONS_H
#define PLAYERBOTS_MCACTIONS_H

#include "AttackAction.h"
#include "MCHelpers.h"
#include "MovementActions.h"
#include "PlayerbotAI.h"
#include "Playerbots.h"
#include <string>

// Shared

// Take the boss, or switch back to it: the same job for eight of the ten bosses, told apart by
// its trigger.
class McAttackBossAction : public AttackAction
{
public:
    McAttackBossAction(
        PlayerbotAI* botAI, std::string const& name, uint32 bossEntry,
        char const* bossValue = nullptr)
        : AttackAction(botAI, name), _bossEntry(bossEntry), _bossValue(bossValue) {}
    bool Execute(Event event) override;

private:
    uint32 const _bossEntry;
    char const* const _bossValue;
};

// Pull the boss back off whoever a scripted threat wipe handed it to.
class McTauntBossAction : public AttackAction
{
public:
    McTauntBossAction(
        PlayerbotAI* botAI, std::string const& name, uint32 bossEntry, char const* bossValue)
        : AttackAction(botAI, name), _bossEntry(bossEntry), _bossValue(bossValue) {}
    bool Execute(Event event) override;

private:
    uint32 const _bossEntry;
    char const* const _bossValue;
};

class McAttackNearestAddAction : public AttackAction
{
public:
    McAttackNearestAddAction(PlayerbotAI* botAI, std::string const& name, char const* addsValue)
        : AttackAction(botAI, name), _addsValue(addsValue) {}
    bool Execute(Event event) override;

private:
    char const* const _addsValue;
};

// Step off a patch of fire on the floor, to the closest point outside every one of them.
class McMoveOutOfHazardAction : public MovementAction
{
public:
    McMoveOutOfHazardAction(
        PlayerbotAI* botAI, std::string const& name, char const* hazardValue, float radius)
        : MovementAction(botAI, name), _hazardValue(hazardValue), _radius(radius) {}
    bool Execute(Event event) override;

private:
    char const* const _hazardValue;
    float const _radius;
};

// Run out of a boss aura that burns everything around the boss: Baron Geddon's Inferno and his
// Armageddon.
class McFleeFromBossAction : public MovementAction
{
public:
    McFleeFromBossAction(
        PlayerbotAI* botAI, std::string const& name, uint32 bossEntry, char const* bossValue,
        float distance)
        : MovementAction(botAI, name), _bossEntry(bossEntry), _bossValue(bossValue),
          _distance(distance) {}
    bool Execute(Event event) override;

private:
    uint32 const _bossEntry;
    char const* const _bossValue;
    float const _distance;
};

// Baron Geddon

class McMoveFromGroupAction : public MovementAction
{
public:
    McMoveFromGroupAction(PlayerbotAI* botAI, std::string const name = "mc move from group")
        : MovementAction(botAI, name) {}
    bool Execute(Event event) override;
};

// Shazzrah

class McShazzrahMoveAwayAction : public MovementAction
{
public:
    McShazzrahMoveAwayAction(PlayerbotAI* botAI, std::string const name = "mc shazzrah move away")
        : MovementAction(botAI, name) {}
    bool Execute(Event event) override;
};

// Golemagg the Incinerator

class McGolemaggBackOffAction : public MovementAction
{
public:
    McGolemaggBackOffAction(PlayerbotAI* botAI, std::string const name = "mc golemagg back off")
        : MovementAction(botAI, name) {}
    bool Execute(Event event) override;
};

class McGolemaggMarkBossAction : public Action
{
public:
    McGolemaggMarkBossAction(PlayerbotAI* botAI, std::string const name = "mc golemagg mark boss")
        : Action(botAI, name) {};
    bool Execute(Event event) override;
};

class McGolemaggTankAction : public AttackAction
{
public:
    McGolemaggTankAction(PlayerbotAI* botAI, std::string const name)
        : AttackAction(botAI, name) {}
protected:
    bool MoveUnitToPosition(Unit* target, Position const& tankPosition, float maxDistance, float stepDistance = 3.0f);
    bool FindCoreRagers(Unit*& coreRager1, Unit*& coreRager2) const;
};

class McGolemaggMainTankAttackGolemaggAction : public McGolemaggTankAction
{
public:
    McGolemaggMainTankAttackGolemaggAction(PlayerbotAI* botAI, std::string const name = "mc golemagg main tank attack golemagg")
        : McGolemaggTankAction(botAI, name) {};
    bool Execute(Event event) override;
};

class McGolemaggAssistTankAttackCoreRagerAction : public McGolemaggTankAction
{
public:
    McGolemaggAssistTankAttackCoreRagerAction(PlayerbotAI* botAI, std::string const name = "mc golemagg assist tank attack core rager")
        : McGolemaggTankAction(botAI, name) {};
    bool Execute(Event event) override;
};

class McGolemaggHealerPositionAction : public MovementAction
{
public:
    McGolemaggHealerPositionAction(PlayerbotAI* botAI, std::string const name = "mc golemagg healer position")
        : MovementAction(botAI, name) {}
    bool Execute(Event event) override;
};

// Majordomo Executus

class McMajordomoStopAttackAction : public Action
{
public:
    McMajordomoStopAttackAction(PlayerbotAI* botAI, std::string const name = "mc majordomo stop attack")
        : Action(botAI, name) {};
    bool Execute(Event event) override;
};

// Trash and anywhere in the instance

class McCoreHoundMarkAction : public Action
{
public:
    McCoreHoundMarkAction(PlayerbotAI* botAI, std::string const name = "mc core hound mark")
        : Action(botAI, name) {};
    Unit* GetTarget() override;
    bool Execute(Event event) override;
};

class McMoveFromLavaAction : public MovementAction
{
public:
    McMoveFromLavaAction(PlayerbotAI* botAI, std::string const name = "mc move from lava")
        : MovementAction(botAI, name) {}
    bool Execute(Event event) override;
};

#endif
