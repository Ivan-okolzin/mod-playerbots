/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#include "TankAssistStrategy.h"
#include "EncounterHelpers.h"
#include "Multiplier.h"
#include "Playerbots.h"

namespace
{
class RaidBossTauntMultiplier : public Multiplier
{
public:
    RaidBossTauntMultiplier(PlayerbotAI* botAI) : Multiplier(botAI, "raid boss taunt") {}

    float GetValue(Action* action) override
    {
        if (!bot->IsInCombat() || !bot->GetMap()->IsRaid() || !EncounterHelpers::IsTauntAction(bot, action))
            return 1.0f;

        Unit* target = AI_VALUE(Unit*, "current target");
        Player* tank = EncounterHelpers::GetGenericRaidBossTank(bot, target);
        return tank && tank != bot ? 0.0f : 1.0f;
    }
};
}

void TankAssistStrategy::InitMultipliers(std::vector<Multiplier*>& multipliers)
{
    multipliers.push_back(new RaidBossTauntMultiplier(botAI));
}

void TankAssistStrategy::InitTriggers(std::vector<TriggerNode*>& triggers)
{
    triggers.push_back(new TriggerNode("has attackers", { NextAction("take over raid boss", ACTION_EMERGENCY + 2) }));
    triggers.push_back(
        new TriggerNode("tank assist", { NextAction("tank assist", 50.0f) }));
}
