/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#include "CrusaderMultipliers.h"
#include "CrusaderActions.h"
#include "CrusaderHelpers.h"
#include "EncounterHelpers.h"
#include "Playerbots.h"

using namespace CrusaderHelpers;
using namespace EncounterHelpers;

float FactionChampionsFocusTargetMultiplier::GetValueInEncounter(Action* action)
{
    if (PlayerbotAI::IsHeal(bot))
        return 1.0f;

    // The switch to the focus is how a bot gets off the champion it is on in the first place.
    if (dynamic_cast<FactionChampionsAttackFocusTargetAction*>(action))
        return 1.0f;

    if (!IsDpsHoldCandidate(bot, action))
        return 1.0f;

    Unit* target = action->GetTarget();
    if (!target || !IsFactionChampion(target->GetEntry()))
        return 1.0f;

    Unit* focus = FindFactionChampionFocus(bot);
    if (!focus || focus == target)
        return 1.0f;

    // A champion that has run across the arena is not worth chasing: whoever is in front of the
    // bot keeps taking damage until the focus is back in reach.
    constexpr float focusReach = 40.0f;
    return bot->GetExactDist(focus) <= focusReach ? 0.0f : 1.0f;
}

float ValkyrPactTargetMultiplier::GetValueInEncounter(Action* action)
{
    if (PlayerbotAI::IsTank(bot) || PlayerbotAI::IsHeal(bot))
        return 1.0f;

    if (dynamic_cast<ValkyrAttackPactingTwinAction*>(action))
        return 1.0f;

    if (!IsDpsHoldCandidate(bot, action))
        return 1.0f;

    Unit* pacting = GetPactingTwin(botAI);
    if (!pacting)
        return 1.0f;

    Unit* target = action->GetTarget();
    if (!target || target == pacting)
        return 1.0f;

    bool const otherTwin = target->GetEntry() == Id(CrusaderNpcs::NPC_FJOLA_LIGHTBANE) ||
        target->GetEntry() == Id(CrusaderNpcs::NPC_EYDIS_DARKBANE);

    return otherTwin ? 0.0f : 1.0f;
}
