/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#ifndef PLAYERBOTS_ZGMULTIPLIERS_H
#define PLAYERBOTS_ZGMULTIPLIERS_H

#include "EncounterHelpers.h"
#include "Multiplier.h"
#include "ZGHelpers.h"

class ZulGurubEncounterMultiplier : public Multiplier
{
public:
    ZulGurubEncounterMultiplier(PlayerbotAI* botAI, std::string const name) : Multiplier(botAI, name) {}

    float GetValue(Action* action) final
    {
        return EncounterHelpers::IsEncounterInProgress(bot, ZulGurubHelpers::ZG_MAP_ID) ? GetValueInEncounter(action)
                                                                                        : 1.0f;
    }

protected:
    virtual float GetValueInEncounter(Action* action) = 0;
};

class HakkarKeepPoisonousBloodMultiplier : public ZulGurubEncounterMultiplier
{
public:
    HakkarKeepPoisonousBloodMultiplier(PlayerbotAI* botAI)
        : ZulGurubEncounterMultiplier(botAI, "hakkar keep poisonous blood")
    {
    }

protected:
    float GetValueInEncounter(Action* action) override;
};

// Mandokir charges the player he is watching as soon as that player earns threat (BMA:257,
// :292), so a watched bot does nothing at all until the gaze expires.
class MandokirWatchHoldMultiplier : public ZulGurubEncounterMultiplier
{
public:
    MandokirWatchHoldMultiplier(PlayerbotAI* botAI)
        : ZulGurubEncounterMultiplier(botAI, "bloodlord mandokir watch hold")
    {
    }

protected:
    float GetValueInEncounter(Action* action) override;
};

// Arlokk flags herself out of reach for the whole of her stalking phase (BAR:233) and Thekal does
// the same while he plays dead (BTH:178). An attack on either one cannot land, and chasing the
// target is how a raid walks itself into the prowlers or out of the room.
class ZulGurubDoNotAttackUnassailableBossMultiplier : public ZulGurubEncounterMultiplier
{
public:
    ZulGurubDoNotAttackUnassailableBossMultiplier(
        PlayerbotAI* botAI, std::string const name, uint32 bossEntry)
        : ZulGurubEncounterMultiplier(botAI, name), _bossEntry(bossEntry)
    {
    }

protected:
    float GetValueInEncounter(Action* action) override;

private:
    uint32 const _bossEntry;
};

#endif
