/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#ifndef PLAYERBOTS_SWPMULTIPLIERS_H
#define PLAYERBOTS_SWPMULTIPLIERS_H

#include "EncounterHelpers.h"
#include "Multiplier.h"
#include "SWPHelpers.h"
#include <string>

class SwpEncounterMultiplier : public Multiplier
{
public:
    SwpEncounterMultiplier(PlayerbotAI* botAI, std::string const name)
        : Multiplier(botAI, name) {}

    float GetValue(Action* action) final
    {
        return EncounterHelpers::IsEncounterInProgress(bot, SwpHelpers::SWP_MAP_ID) ?
            GetValueInEncounter(action) : 1.0f;
    }

protected:
    virtual float GetValueInEncounter(Action* action) = 0;
};

// Alythess burns everything in her melee range with Pyrogenics and Flame Sear, and her tank
// collects Flame Touched: melee that pick up fire there and shadow on Sacrolash die to Dark Flame.
class EredarTwinsMeleeTargetMultiplier : public SwpEncounterMultiplier
{
public:
    EredarTwinsMeleeTargetMultiplier(PlayerbotAI* botAI)
        : SwpEncounterMultiplier(botAI, "eredar twins melee target") {}

protected:
    float GetValueInEncounter(Action* action) override;
};

// Kalecgos and Sathrovarr live in different realms and neither can be touched from the other
// (boss_kalecgos.cpp CanAIAttack), so a bot that still holds the wrong one stops swinging at it
// instead of standing there doing nothing.
class KalecgosWrongRealmTargetMultiplier : public SwpEncounterMultiplier
{
public:
    KalecgosWrongRealmTargetMultiplier(PlayerbotAI* botAI)
        : SwpEncounterMultiplier(botAI, "kalecgos wrong realm target") {}

protected:
    float GetValueInEncounter(Action* action) override;
};

#endif
