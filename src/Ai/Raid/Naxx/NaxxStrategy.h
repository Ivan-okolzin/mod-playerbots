/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#ifndef PLAYERBOTS_NAXXSTRATEGY_H
#define PLAYERBOTS_NAXXSTRATEGY_H

#include "Strategy.h"
#include <string>
#include <vector>

class RaidNaxxStrategy : public Strategy
{
public:
    RaidNaxxStrategy(PlayerbotAI* botAI) : Strategy(botAI) {}
    virtual std::string const getName() override { return "naxx"; }
    virtual void InitTriggers(std::vector<TriggerNode*>& triggers) override;
    virtual void InitMultipliers(std::vector<Multiplier*>& multipliers) override;
    void AppendTargetExclusions(GuidSet& exclusions, TargetValueExclusionType type) override;
    bool HasTargetExclusions() const override { return true; }
};

#endif
