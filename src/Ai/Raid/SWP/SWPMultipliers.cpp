/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#include "SWPMultipliers.h"
#include "EncounterHelpers.h"
#include "Playerbots.h"
#include "SWPActions.h"
#include "SWPHelpers.h"

using namespace EncounterHelpers;
using namespace SwpHelpers;

float EredarTwinsMeleeTargetMultiplier::GetValueInEncounter(Action* action)
{
    if (PlayerbotAI::IsTank(bot) || !PlayerbotAI::IsMelee(bot))
        return 1.0f;

    // The switch to Sacrolash is how a melee bot gets off of Alythess in the first place.
    if (dynamic_cast<SwpAttackCreatureAction*>(action))
        return 1.0f;

    if (!IsDpsHoldCandidate(bot, action))
        return 1.0f;

    Unit* alythess = FindThreatCreature(bot, Id(SwpNpcs::NPC_GRAND_WARLOCK_ALYTHESS));
    return alythess && action->GetTarget() == alythess ? 0.0f : 1.0f;
}

float KalecgosWrongRealmTargetMultiplier::GetValueInEncounter(Action* action)
{
    if (dynamic_cast<SwpAttackCreatureAction*>(action))
        return 1.0f;

    if (!IsDpsHoldCandidate(bot, action))
        return 1.0f;

    uint32 const unreachable = IsInSpectralRealm(bot) ?
        Id(SwpNpcs::NPC_KALECGOS) : Id(SwpNpcs::NPC_SATHROVARR);

    Unit* boss = FindThreatCreature(bot, unreachable);
    return boss && action->GetTarget() == boss ? 0.0f : 1.0f;
}
