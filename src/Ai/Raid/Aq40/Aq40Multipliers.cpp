/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#include "Aq40Multipliers.h"
#include "Aq40Actions.h"
#include "Aq40Helpers.h"
#include "GenericSpellActions.h"
#include "Playerbots.h"
#include "ReachTargetActions.h"
#include "ThreatHelpers.h"

using namespace Aq40Helpers;
using namespace EncounterHelpers;

float HuhuranDoNotDispelWyvernStingMultiplier::GetValueInEncounter(Action* action)
{
    if (!dynamic_cast<CurePartyMemberAction*>(action) &&
        !dynamic_cast<CastCureSpellAction*>(action))
    {
        return 1.0f;
    }

    if (!FindThreatTarget(bot, HUHURAN_NAME))
        return 1.0f;

    Unit* target = action->GetTarget();
    if (!target)
        target = bot;

    return target->HasAura(Id(Aq40Spells::SPELL_WYVERN_STING)) ? 0.0f : 1.0f;
}

float TwinEmperorsMeleeTargetMultiplier::GetValueInEncounter(Action* action)
{
    if (PlayerbotAI::IsTank(bot) || !PlayerbotAI::IsMelee(bot))
        return 1.0f;

    // The switch to Vek'nilash is how a melee bot gets off of Vek'lor in the first place.
    if (dynamic_cast<TwinEmperorsSwitchTargetAction*>(action))
        return 1.0f;

    if (!dynamic_cast<AttackAction*>(action) && !dynamic_cast<CastSpellAction*>(action) &&
        !dynamic_cast<ReachTargetAction*>(action))
    {
        return 1.0f;
    }

    Unit* veklor = FindThreatTarget(bot, VEKLOR_NAME);
    return veklor && action->GetTarget() == veklor ? 0.0f : 1.0f;
}

float CthunDoNotAttackCarapacedBodyMultiplier::GetValueInEncounter(Action* action)
{
    if (!IsDpsHoldCandidate(bot, action))
        return 1.0f;

    Unit* body = GetCthunBody(botAI);
    if (!body || IsCthunBodyWeakened(body))
        return 1.0f;

    return action->GetTarget() == body ? 0.0f : 1.0f;
}
