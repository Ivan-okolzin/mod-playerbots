/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#include "UldMultipliers.h"
#include "EncounterHelpers.h"
#include "Playerbots.h"
#include "UldActions.h"
#include "UldHelpers.h"
#include <algorithm>
#include <vector>

using namespace EncounterHelpers;
using namespace UldHelpers;

namespace
{

bool IsOneOf(Unit* unit, std::vector<uint32> const& entries)
{
    if (!unit)
        return false;

    return std::find(entries.begin(), entries.end(), unit->GetEntry()) != entries.end();
}

}

float Xt002BoombotMeleeTargetMultiplier::GetValueInEncounter(Action* action)
{
    if (!PlayerbotAI::IsMelee(bot) && !PlayerbotAI::IsTank(bot))
        return 1.0f;

    if (!IsDpsHoldCandidate(bot, action))
        return 1.0f;

    std::vector<uint32> const boombots = {
        Id(UldNpcs::NPC_BOOMBOT), Id(UldNpcs::NPC_BOOMBOT_25) };
    return IsOneOf(action->GetTarget(), boombots) ? 0.0f : 1.0f;
}

float IgnisConstructTargetMultiplier::GetValueInEncounter(Action* action)
{
    // The tanks hold the constructs and walk them into the water, which is swinging at them.
    if (PlayerbotAI::IsTank(bot) || PlayerbotAI::IsHeal(bot))
        return 1.0f;

    // The switch onto a Brittle construct is how a bot gets off whatever it is on in the first
    // place, and that construct is the one exception to this hold.
    if (dynamic_cast<IgnisAttackBrittleConstructAction*>(action))
        return 1.0f;

    if (!IsDpsHoldCandidate(bot, action))
        return 1.0f;

    Unit* target = action->GetTarget();
    std::vector<uint32> const constructs = {
        Id(UldNpcs::NPC_IRON_CONSTRUCT), Id(UldNpcs::NPC_IRON_CONSTRUCT_25) };
    if (!IsOneOf(target, constructs))
        return 1.0f;

    return IsConstructBrittle(target) ? 1.0f : 0.0f;
}

float AuriayaSentryTargetMultiplier::GetValueInEncounter(Action* action)
{
    // The tanks hold whatever they took and the healers heal through it.
    if (PlayerbotAI::IsTank(bot) || PlayerbotAI::IsHeal(bot))
        return 1.0f;

    if (dynamic_cast<AuriayaAttackSanctumSentryAction*>(action))
        return 1.0f;

    if (!IsDpsHoldCandidate(bot, action))
        return 1.0f;

    Unit* sentry = GetNearestAttackableCachedUnit(botAI, AURIAYA_SENTRIES_VALUE);
    if (!sentry)
        return 1.0f;

    Unit* target = action->GetTarget();
    if (!target || target == sentry)
        return 1.0f;

    // A cat on the far side of the ledge is not worth chasing: whatever is in front of the bot
    // keeps taking damage until one is in reach.
    constexpr float sentryReach = 40.0f;
    return bot->GetExactDist(sentry) <= sentryReach ? 0.0f : 1.0f;
}
