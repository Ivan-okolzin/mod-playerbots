/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#ifndef PLAYERBOTS_CRUSADERSTRATEGY_H
#define PLAYERBOTS_CRUSADERSTRATEGY_H

#include "Strategy.h"
#include <string>
#include <vector>

class RaidCrusaderStrategy : public Strategy
{
public:
    RaidCrusaderStrategy(PlayerbotAI* botAI) : Strategy(botAI) {}
    std::string const getName() override { return "trialofthecrusader"; }

    void InitTriggers(std::vector<TriggerNode*>& triggers) override;
    void InitMultipliers(std::vector<Multiplier*>& multipliers) override;
};

#endif
