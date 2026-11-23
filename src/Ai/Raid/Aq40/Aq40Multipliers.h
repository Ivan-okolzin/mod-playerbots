/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#ifndef PLAYERBOTS_AQ40MULTIPLIERS_H
#define PLAYERBOTS_AQ40MULTIPLIERS_H

#include "Aq40Helpers.h"
#include "EncounterHelpers.h"
#include "Multiplier.h"
#include <string>

class Aq40EncounterMultiplier : public Multiplier
{
public:
    Aq40EncounterMultiplier(PlayerbotAI* botAI, std::string const name)
        : Multiplier(botAI, name) {}

    float GetValue(Action* action) final
    {
        return EncounterHelpers::IsEncounterInProgress(bot, Aq40Helpers::AQ40_MAP_ID) ?
            GetValueInEncounter(action) : 1.0f;
    }

protected:
    virtual float GetValueInEncounter(Action* action) = 0;
};

// Dispelling Wyvern Sting deals 4,000 damage to the sleeping player (boss_huhuran.cpp casts
// SPELL_WYVERN_STING_DAMAGE on dispel), which is the usual way a raid kills its own healer here.
class HuhuranDoNotDispelWyvernStingMultiplier : public Aq40EncounterMultiplier
{
public:
    HuhuranDoNotDispelWyvernStingMultiplier(PlayerbotAI* botAI)
        : Aq40EncounterMultiplier(botAI, "princess huhuran do not dispel wyvern sting") {}

protected:
    float GetValueInEncounter(Action* action) override;
};

// Vek'lor's Arcane Burst goes off every second while any player stands in his melee range, so
// melee stay on Vek'nilash and leave Vek'lor to the ranged.
class TwinEmperorsMeleeTargetMultiplier : public Aq40EncounterMultiplier
{
public:
    TwinEmperorsMeleeTargetMultiplier(PlayerbotAI* botAI)
        : Aq40EncounterMultiplier(botAI, "twin emperors melee target") {}

protected:
    float GetValueInEncounter(Action* action) override;
};

// Between weakened windows the body carries Carapace of C'Thun and takes no damage at all, so
// everything aimed at it is wasted time the raid owes its tentacles.
class CthunDoNotAttackCarapacedBodyMultiplier : public Aq40EncounterMultiplier
{
public:
    CthunDoNotAttackCarapacedBodyMultiplier(PlayerbotAI* botAI)
        : Aq40EncounterMultiplier(botAI, "c'thun do not attack carapaced body") {}

protected:
    float GetValueInEncounter(Action* action) override;
};

#endif
