/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#include "VoAMultipliers.h"
#include "EncounterHelpers.h"
#include "Playerbots.h"
#include "VoAActions.h"
#include "VoAHelpers.h"

using namespace EncounterHelpers;
using namespace VoAHelpers;

float EmalonOverchargedMinionMultiplier::GetValueInEncounter(Action* action)
{
    // The healers heal and the main tank holds Emalon through the whole of it.
    if (PlayerbotAI::IsHeal(bot) || PlayerbotAI::IsMainTank(bot))
        return 1.0f;

    // The switch to the minion is how a bot gets off whatever it is on in the first place.
    if (dynamic_cast<EmalonAttackOverchargedMinionAction*>(action))
        return 1.0f;

    if (!IsDpsHoldCandidate(bot, action))
        return 1.0f;

    Unit* minion = GetOverchargedMinion(botAI);
    if (!minion)
        return 1.0f;

    Unit* target = action->GetTarget();
    if (!target || target == minion)
        return 1.0f;

    // A minion on the far side of the room is not worth chasing: whatever is in front of the bot
    // keeps taking damage until the overcharged one is in reach.
    constexpr float minionReach = 40.0f;
    return bot->GetExactDist(minion) <= minionReach ? 0.0f : 1.0f;
}
