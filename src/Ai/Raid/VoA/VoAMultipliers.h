/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#ifndef PLAYERBOTS_VOAMULTIPLIERS_H
#define PLAYERBOTS_VOAMULTIPLIERS_H

#include "EncounterHelpers.h"
#include "Multiplier.h"
#include "VoAHelpers.h"
#include <string>

class VoAEncounterMultiplier : public Multiplier
{
public:
    VoAEncounterMultiplier(PlayerbotAI* botAI, std::string const name) : Multiplier(botAI, name) {}

    float GetValue(Action* action) final
    {
        return EncounterHelpers::IsEncounterInProgress(bot, VoAHelpers::VOA_MAP_ID) ?
            GetValueInEncounter(action) : 1.0f;
    }

protected:
    virtual float GetValueInEncounter(Action* action) = 0;
};

// Overcharge refills the minion it lands on (BE:142) and bursts it ten stacks later (BE:241), so
// the damage spent on Emalon or on another minion in those ten seconds is the damage that makes
// the burst happen. While one is overcharged, nothing else is worth hitting.
class EmalonOverchargedMinionMultiplier : public VoAEncounterMultiplier
{
public:
    EmalonOverchargedMinionMultiplier(PlayerbotAI* botAI)
        : VoAEncounterMultiplier(botAI, "emalon overcharged minion target") {}

protected:
    float GetValueInEncounter(Action* action) override;
};

#endif
