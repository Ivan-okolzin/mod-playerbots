/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#ifndef PLAYERBOTS_ULDMULTIPLIERS_H
#define PLAYERBOTS_ULDMULTIPLIERS_H

#include "EncounterHelpers.h"
#include "Multiplier.h"
#include "UldHelpers.h"
#include <string>

class UldEncounterMultiplier : public Multiplier
{
public:
    UldEncounterMultiplier(PlayerbotAI* botAI, std::string const name) : Multiplier(botAI, name) {}

    float GetValue(Action* action) final
    {
        return EncounterHelpers::IsEncounterInProgress(bot, UldHelpers::ULD_MAP_ID) ?
            GetValueInEncounter(action) : 1.0f;
    }

protected:
    virtual float GetValueInEncounter(Action* action) = 0;
};

// A Boombot explodes for 15000 to 18000 damage at half health, and the blast is an area spell
// around itself (BXT:611, :638-645). Anything that has to stand next to it to hit it kills the
// bot that lands the blow, so the melee and the tanks leave the Boombots to the ranged.
class Xt002BoombotMeleeTargetMultiplier : public UldEncounterMultiplier
{
public:
    Xt002BoombotMeleeTargetMultiplier(PlayerbotAI* botAI)
        : UldEncounterMultiplier(botAI, "xt-002 boombot melee target") {}

protected:
    float GetValueInEncounter(Action* action) override;
};

// An Iron Construct at full health takes as long to kill as Ignis himself, and in the water it
// dies to one hit of 5000 damage (BIG:491-503). Damage spent on a construct that is not Brittle
// yet is damage that neither kills it nor goes into the boss, so the dps stay off it and the
// tanks do the walking.
class IgnisConstructTargetMultiplier : public UldEncounterMultiplier
{
public:
    IgnisConstructTargetMultiplier(PlayerbotAI* botAI)
        : UldEncounterMultiplier(botAI, "ignis iron construct target") {}

protected:
    float GetValueInEncounter(Action* action) override;
};

// Strength of the Pack buffs every Sanctum Sentry that is still alive (BAU:255), so each one left
// standing makes the rest of them hit harder. While one is up, nothing else is worth hitting.
class AuriayaSentryTargetMultiplier : public UldEncounterMultiplier
{
public:
    AuriayaSentryTargetMultiplier(PlayerbotAI* botAI)
        : UldEncounterMultiplier(botAI, "auriaya sanctum sentry target") {}

protected:
    float GetValueInEncounter(Action* action) override;
};

#endif
