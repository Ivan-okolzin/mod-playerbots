/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#include "Aq20Multipliers.h"
#include "Aq20Helpers.h"
#include "EncounterHelpers.h"
#include "Playerbots.h"

using namespace Aq20Helpers;
using namespace EncounterHelpers;

float MoamStonePhaseTargetMultiplier::GetValueInEncounter(Action* action)
{
    // The tank keeps its threat on Moam through the phase, or he picks a new victim the moment it
    // ends.
    if (PlayerbotAI::IsTank(bot) || PlayerbotAI::IsHeal(bot))
        return 1.0f;

    if (!IsDpsHoldCandidate(bot, action))
        return 1.0f;

    Unit* target = action->GetTarget();
    if (!target || target->GetEntry() != Id(Aq20Npcs::NPC_MOAM))
        return 1.0f;

    if (!IsMoamInStonePhase(target))
        return 1.0f;

    // Only worth redirecting while there is a Fiend left to redirect onto.
    return GetNearestAttackableCachedUnit(botAI, MOAM_MANA_FIENDS_VALUE) ? 0.0f : 1.0f;
}

float BuruThornsTargetMultiplier::GetValueInEncounter(Action* action)
{
    if (!PlayerbotAI::IsMelee(bot) || PlayerbotAI::IsHeal(bot))
        return 1.0f;

    if (!IsDpsHoldCandidate(bot, action))
        return 1.0f;

    Unit* target = action->GetTarget();
    if (!target || target->GetEntry() != Id(Aq20Npcs::NPC_BURU))
        return 1.0f;

    if (!IsBuruInEggPhase(target))
        return 1.0f;

    // Only while there is somewhere better to put the swing: the egg Buru is standing by, or a
    // Hatchling. With neither in reach the reflected damage is worth taking rather than idling.
    return GetBuruTargetEgg(botAI) || GetNearestAttackableCachedUnit(botAI, BURU_HATCHLINGS_VALUE) ?
        0.0f : 1.0f;
}

float AyamissAirPhaseTargetMultiplier::GetValueInEncounter(Action* action)
{
    if (!PlayerbotAI::IsMelee(bot) || PlayerbotAI::IsHeal(bot))
        return 1.0f;

    if (!IsDpsHoldCandidate(bot, action))
        return 1.0f;

    Unit* target = action->GetTarget();
    if (!target || target->GetEntry() != Id(Aq20Npcs::NPC_AYAMISS))
        return 1.0f;

    return IsAyamissInAirPhase(target) ? 0.0f : 1.0f;
}
