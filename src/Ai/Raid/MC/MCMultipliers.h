/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#ifndef PLAYERBOTS_MCMULTIPLIERS_H
#define PLAYERBOTS_MCMULTIPLIERS_H

#include "EncounterHelpers.h"
#include "MCHelpers.h"
#include "Multiplier.h"
#include <string>

class McEncounterMultiplier : public Multiplier
{
public:
    McEncounterMultiplier(PlayerbotAI* botAI, std::string const name) : Multiplier(botAI, name) {}

    float GetValue(Action* action) final
    {
        return EncounterHelpers::IsEncounterInProgress(bot, MoltenCoreHelpers::MC_MAP_ID) ?
            GetValueInEncounter(action) : 1.0f;
    }

protected:
    virtual float GetValueInEncounter(Action* action) = 0;
};

// A bot that has stepped out of a fire patch is walked straight back into it by the rotation's own
// chase actions, which path to the target without knowing what is on the floor between them. While
// the bot is still standing in one, those two actions are held so the escape spline finishes.
class McHazardChaseHoldMultiplier : public McEncounterMultiplier
{
public:
    McHazardChaseHoldMultiplier(
        PlayerbotAI* botAI, std::string const name, char const* hazardValue, float radius)
        : McEncounterMultiplier(botAI, name), _hazardValue(hazardValue), _radius(radius) {}

protected:
    float GetValueInEncounter(Action* action) override;

private:
    char const* const _hazardValue;
    float const _radius;
};

class GarrDisableDpsAoeMultiplier : public Multiplier
{
public:
    GarrDisableDpsAoeMultiplier(PlayerbotAI* botAI) : Multiplier(botAI, "garr disable dps aoe multiplier") {}
    float GetValue(Action* action) override;
};

class BaronGeddonAbilityMultiplier : public Multiplier
{
public:
    BaronGeddonAbilityMultiplier(PlayerbotAI* botAI) : Multiplier(botAI, "baron geddon ability multiplier") {}
    float GetValue(Action* action) override;
};

class GolemaggMultiplier : public Multiplier
{
public:
    GolemaggMultiplier(PlayerbotAI* botAI) : Multiplier(botAI, "golemagg multiplier") {}
    float GetValue(Action* action) override;
};

class MajordomoReflectionMultiplier : public Multiplier
{
public:
    MajordomoReflectionMultiplier(PlayerbotAI* botAI) : Multiplier(botAI, "majordomo reflection multiplier") {}
    float GetValue(Action* action) override;
};

#endif
