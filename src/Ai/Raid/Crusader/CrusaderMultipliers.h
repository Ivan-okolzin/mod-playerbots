/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#ifndef PLAYERBOTS_CRUSADERMULTIPLIERS_H
#define PLAYERBOTS_CRUSADERMULTIPLIERS_H

#include "CrusaderHelpers.h"
#include "EncounterHelpers.h"
#include "Multiplier.h"
#include <string>

class CrusaderEncounterMultiplier : public Multiplier
{
public:
    CrusaderEncounterMultiplier(PlayerbotAI* botAI, std::string const name)
        : Multiplier(botAI, name) {}

    float GetValue(Action* action) final
    {
        return EncounterHelpers::IsEncounterInProgress(bot, CrusaderHelpers::CRUSADER_MAP_ID) ?
            GetValueInEncounter(action) : 1.0f;
    }

protected:
    virtual float GetValueInEncounter(Action* action) = 0;
};

// Ten champions healing each other outlast anything but focused damage, and threat cannot be used
// to keep them together (boss_faction_champions.cpp:105), so a bot that has drifted onto another
// champion stops hitting it while the one the raid is killing is still within reach.
class FactionChampionsFocusTargetMultiplier : public CrusaderEncounterMultiplier
{
public:
    FactionChampionsFocusTargetMultiplier(PlayerbotAI* botAI)
        : CrusaderEncounterMultiplier(botAI, "faction champions focus target") {}

protected:
    float GetValueInEncounter(Action* action) override;
};

// Twin's Pact heals the caster for as long as her shield holds (BTV:443), and the twins share
// their health pool (BTV:265): damage on the other sister neither breaks the shield nor stops the
// heal, so for its few seconds all of it belongs on the one that is casting.
class ValkyrPactTargetMultiplier : public CrusaderEncounterMultiplier
{
public:
    ValkyrPactTargetMultiplier(PlayerbotAI* botAI)
        : CrusaderEncounterMultiplier(botAI, "twin val'kyr pact target") {}

protected:
    float GetValueInEncounter(Action* action) override;
};

#endif
