/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#include "NaxxActions.h"
#include "NaxxHelpers.h"

using namespace NaxxHelpers;

bool PatchwerkBackOffFromBossAction::Execute(Event /*event*/)
{
    Unit* boss = FindThreatCreature(bot, Id(NaxxNpcs::NPC_PATCHWERK));
    if (!boss)
        return false;

    // Patchwerk never moves off his tank, so one step out is enough and there is no reason to keep
    // picking new spots every second.
    return FleePosition(boss->GetPosition(), PATCHWERK_STAND_CLEAR_DISTANCE);
}
