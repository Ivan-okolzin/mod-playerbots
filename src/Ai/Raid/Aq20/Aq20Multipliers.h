/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#ifndef PLAYERBOTS_AQ20MULTIPLIERS_H
#define PLAYERBOTS_AQ20MULTIPLIERS_H

#include "Aq20Helpers.h"
#include "EncounterHelpers.h"
#include "Multiplier.h"
#include <string>

class Aq20EncounterMultiplier : public Multiplier
{
public:
    Aq20EncounterMultiplier(PlayerbotAI* botAI, std::string const name)
        : Multiplier(botAI, name) {}

    float GetValue(Action* action) final
    {
        return EncounterHelpers::IsEncounterInProgress(bot, Aq20Helpers::AQ20_MAP_ID) ?
            GetValueInEncounter(action) : 1.0f;
    }

protected:
    virtual float GetValueInEncounter(Action* action) = 0;
};

// Moam's stone phase ends either when his mana fills, which costs the raid an Arcane Eruption
// (MOA:102-112), or the moment the last of his three Mana Fiends dies (MOA:87-93). For the few
// seconds it lasts, every bit of damage belongs on the Fiends, not on the boss.
class MoamStonePhaseTargetMultiplier : public Aq20EncounterMultiplier
{
public:
    MoamStonePhaseTargetMultiplier(PlayerbotAI* botAI)
        : Aq20EncounterMultiplier(botAI, "moam stone phase target") {}

protected:
    float GetValueInEncounter(Action* action) override;
};

// Thorns is on Buru for the whole egg phase (BUR:86) and pays melee back for every swing, while
// he spends that phase running after a fixated player and cannot be held. Melee hit the eggs and
// the Hatchlings instead; the ranged keep working on Buru, who still has to be brought to 20%.
class BuruThornsTargetMultiplier : public Aq20EncounterMultiplier
{
public:
    BuruThornsTargetMultiplier(PlayerbotAI* botAI)
        : Aq20EncounterMultiplier(botAI, "buru the gorger thorns target") {}

protected:
    float GetValueInEncounter(Action* action) override;
};

// Ayamiss spends the fight above 70% rooted 20 yards above the altar with gravity off (AYA:91-95,
// :204): melee cannot reach her, so a melee bot standing under her does nothing at all while her
// Swarmers and Larvae go unanswered.
class AyamissAirPhaseTargetMultiplier : public Aq20EncounterMultiplier
{
public:
    AyamissAirPhaseTargetMultiplier(PlayerbotAI* botAI)
        : Aq20EncounterMultiplier(botAI, "ayamiss the hunter air phase target") {}

protected:
    float GetValueInEncounter(Action* action) override;
};

#endif
