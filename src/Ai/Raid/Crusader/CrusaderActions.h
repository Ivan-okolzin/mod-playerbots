/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#ifndef PLAYERBOTS_CRUSADERACTIONS_H
#define PLAYERBOTS_CRUSADERACTIONS_H

#include "Action.h"
#include "AttackAction.h"
#include "CrusaderHelpers.h"
#include "MovementActions.h"
#include <string>

// Shared

// Hold threat on a boss, or switch to the one this bot is meant to be hitting: the same job,
// told apart by its trigger.
class CrusaderAttackCreatureAction : public AttackAction
{
public:
    CrusaderAttackCreatureAction(PlayerbotAI* botAI, std::string const& name, uint32 entry)
        : AttackAction(botAI, name), _entry(entry) {}
    bool Execute(Event event) override;

private:
    uint32 const _entry;
};

class CrusaderAttackNearestAddAction : public AttackAction
{
public:
    CrusaderAttackNearestAddAction(
        PlayerbotAI* botAI, std::string const& name, char const* addsValue)
        : AttackAction(botAI, name), _addsValue(addsValue) {}
    bool Execute(Event event) override;

private:
    char const* const _addsValue;
};

class CrusaderSpreadRangedAction : public MovementAction
{
public:
    CrusaderSpreadRangedAction(
        PlayerbotAI* botAI, std::string const& name, uint32 bossEntry, float distanceFromBoss)
        : MovementAction(botAI, name), _bossEntry(bossEntry), _distanceFromBoss(distanceFromBoss) {}
    bool Execute(Event event) override;

private:
    uint32 const _bossEntry;
    float const _distanceFromBoss;
};

class CrusaderMoveAwayFromHazardAction : public MovementAction
{
public:
    CrusaderMoveAwayFromHazardAction(
        PlayerbotAI* botAI, std::string const& name, char const* hazardValue, float radius)
        : MovementAction(botAI, name), _hazardValue(hazardValue), _radius(radius) {}
    bool Execute(Event event) override;

private:
    char const* const _hazardValue;
    float const _radius;
};

// Gormok the Impaler

// Only a Snobold that has been thrown at the raid can be hit at all, so this cannot go through
// the shared add action.
class GormokAttackNearestSnoboldAction : public AttackAction
{
public:
    GormokAttackNearestSnoboldAction(PlayerbotAI* botAI)
        : AttackAction(botAI, "gormok the impaler attack nearest snobold") {}
    bool Execute(Event event) override;
};

// The second tank takes Gormok off the first one once Impale has stacked up on it.
class GormokTankSwapAction : public AttackAction
{
public:
    GormokTankSwapAction(PlayerbotAI* botAI)
        : AttackAction(botAI, "gormok the impaler tank swap") {}
    bool Execute(Event event) override;
};

// Acidmaw and Dreadscale

// Takes and keeps the worm this tank is assigned: which worm that is changes with Paralytic Toxin
// and with every submerge, and every emerge drops the worms' threat (BNB:799).
class JormungarAssignTanksAction : public AttackAction
{
public:
    JormungarAssignTanksAction(PlayerbotAI* botAI)
        : AttackAction(botAI, "acidmaw and dreadscale assign tanks") {}
    bool Execute(Event event) override;
};

// Icehowl

// Steps sideways out of the lane Icehowl is about to charge down, to whichever side the bot is
// already closer to.
class IcehowlMoveOutOfChargePathAction : public MovementAction
{
public:
    IcehowlMoveOutOfChargePathAction(PlayerbotAI* botAI)
        : MovementAction(botAI, "icehowl move out of charge path") {}
    bool Execute(Event event) override;
};

// Comes in off the arena wall while Icehowl is still picking his target, so that there is room to
// step aside when he charges.
class IcehowlMoveAwayFromArenaWallAction : public MovementAction
{
public:
    IcehowlMoveAwayFromArenaWallAction(PlayerbotAI* botAI)
        : MovementAction(botAI, "icehowl move away from arena wall") {}
    bool Execute(Event event) override;
};

// Faction Champions

// Puts the raid on one champion at a time and marks it, so that human raid members see the same
// target the bots picked.
class FactionChampionsAttackFocusTargetAction : public AttackAction
{
public:
    FactionChampionsAttackFocusTargetAction(PlayerbotAI* botAI)
        : AttackAction(botAI, "faction champions attack focus target") {}
    bool Execute(Event event) override;
};

// Twin Val'kyr

// Walks to the Essence of this bot's colour and talks to it, which is what puts the aura on
// (BTV:574). Nothing else in the fight can be survived without one.
class ValkyrTakeEssenceAction : public MovementAction
{
public:
    ValkyrTakeEssenceAction(PlayerbotAI* botAI)
        : MovementAction(botAI, "twin val'kyr take essence") {}
    bool Execute(Event event) override;
};

// The main tank takes Fjola and the first assist tank Eydis, matching the essences they hold.
class ValkyrAssignTanksAction : public AttackAction
{
public:
    ValkyrAssignTanksAction(PlayerbotAI* botAI)
        : AttackAction(botAI, "twin val'kyr assign tanks") {}
    bool Execute(Event event) override;
};

class ValkyrAttackPactingTwinAction : public AttackAction
{
public:
    ValkyrAttackPactingTwinAction(PlayerbotAI* botAI)
        : AttackAction(botAI, "twin val'kyr attack pacting twin") {}
    bool Execute(Event event) override;
};

// The other colour's balls burst for full damage, and which colour that is depends on the bot's
// own essence, so the hazard cannot be named when the action is built.
class ValkyrMoveAwayFromBallAction : public MovementAction
{
public:
    ValkyrMoveAwayFromBallAction(PlayerbotAI* botAI)
        : MovementAction(botAI, "twin val'kyr move away from ball") {}
    bool Execute(Event event) override;
};

// Walks into the nearest ball of the bot's own colour: its burst is absorbed into Powering Up
// (BTV:742).
class ValkyrCollectMatchingBallAction : public MovementAction
{
public:
    ValkyrCollectMatchingBallAction(PlayerbotAI* botAI)
        : MovementAction(botAI, "twin val'kyr collect matching ball") {}
    bool Execute(Event event) override;
};

// Anub'arak

// Leads the spike onto a Permafrost patch, which is the only thing that stops it (BAT:872).
class AnubarakFleeToPermafrostAction : public MovementAction
{
public:
    AnubarakFleeToPermafrostAction(PlayerbotAI* botAI)
        : MovementAction(botAI, "anub'arak flee to permafrost") {}
    bool Execute(Event event) override;
};

// What is left when no sphere has been brought down yet: outrun the spike until one is.
class AnubarakFleeFromSpikeAction : public MovementAction
{
public:
    AnubarakFleeFromSpikeAction(PlayerbotAI* botAI)
        : MovementAction(botAI, "anub'arak flee from spike") {}
    bool Execute(Event event) override;
};

// Shoots a hovering Frost Sphere down: it drops to the floor and becomes the Permafrost patch the
// pursued player needs (BAT:560).
class AnubarakShootDownFrostSphereAction : public AttackAction
{
public:
    AnubarakShootDownFrostSphereAction(PlayerbotAI* botAI)
        : AttackAction(botAI, "anub'arak shoot down frost sphere") {}
    bool Execute(Event event) override;
};

#endif
