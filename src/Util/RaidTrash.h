/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#ifndef PLAYERBOTS_RAID_TRASH_H
#define PLAYERBOTS_RAID_TRASH_H

#include "AttackAction.h"
#include "Strategy.h"

namespace RaidTrash
{
struct Pack
{
    bool bossEngaged = false;
    GuidSet protectedTargets;
    GuidSet otherTanksTargets;
    ObjectGuid tankTarget;
    ObjectGuid spaceFrom;
};

class PackValue : public CalculatedValue<Pack>
{
public:
    explicit PackValue(PlayerbotAI* ai) : CalculatedValue(ai, "raid trash pack", 100) {}
    Pack Calculate() override;
};

bool IsActive(Player* bot);

class ManageAction : public AttackAction
{
public:
    ManageAction(PlayerbotAI* ai) : AttackAction(ai, "manage raid trash") {}
    bool Execute(Event event) override;
};

class ManageTrigger : public Trigger
{
public:
    ManageTrigger(PlayerbotAI* ai) : Trigger(ai, "manage raid trash") {}
    bool IsActive() override;
};

class ProtectMultiplier : public Multiplier
{
public:
    ProtectMultiplier(PlayerbotAI* ai) : Multiplier(ai, "protect raid trash") {}
    float GetValue(Action* action) override;
};

}

class RaidTrashStrategy : public Strategy
{
public:
    explicit RaidTrashStrategy(PlayerbotAI* ai) : Strategy(ai) {}
    std::string const getName() override { return "raid trash"; }
    bool HasTargetExclusions() const override { return true; }
    void AppendTargetExclusions(GuidSet& exclusions, TargetValueExclusionType type) override;
    void InitTriggers(std::vector<TriggerNode*>& triggers) override;
    void InitMultipliers(std::vector<Multiplier*>& multipliers) override;
};
#endif
