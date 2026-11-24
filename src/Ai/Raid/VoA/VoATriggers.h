/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#ifndef PLAYERBOTS_VOATRIGGERS_H
#define PLAYERBOTS_VOATRIGGERS_H

#include "EncounterHelpers.h"
#include "GenericTriggers.h"
#include "Trigger.h"
#include "VoAHelpers.h"
#include <string>

enum VoAIDs
{
    // Emalon the Storm Watcher
    AURA_OVERCHARGE = 64217,
    BOSS_EMALON = 33993,
    NPC_TEMPEST_MINION = 33998,
    SPELL_LIGHTNING_NOVA_10_MAN = 64216,
    SPELL_LIGHTNING_NOVA_25_MAN = 65279,
};

//
// Emalon the Storm Watcher
//
class EmalonMarkBossTrigger : public Trigger
{
public:
    EmalonMarkBossTrigger(PlayerbotAI* botAI) : Trigger(botAI, "emalon mark boss trigger") {}
    bool IsActive() override;
};

class EmalonLightingNovaTrigger : public Trigger
{
public:
    EmalonLightingNovaTrigger(PlayerbotAI* botAI) : Trigger(botAI, "emalon lighting nova trigger") {}
    bool IsActive() override;
};

class EmalonOverchargeTrigger : public Trigger
{
public:
    EmalonOverchargeTrigger(PlayerbotAI* botAI) : Trigger(botAI, "emalon overcharge trigger") {}
    bool IsActive() override;
};

class EmalonFallFromFloorTrigger : public Trigger
{
public:
    EmalonFallFromFloorTrigger(PlayerbotAI* botAI) : Trigger(botAI, "emalon fall from floor trigger") {}
    bool IsActive() override;
};

// Shared

class VoAEncounterTrigger : public Trigger
{
public:
    VoAEncounterTrigger(PlayerbotAI* botAI, std::string const name, int32 checkInterval = 1)
        : Trigger(botAI, name, checkInterval) {}

    bool IsActive() final
    {
        return EncounterHelpers::IsEncounterInProgress(bot, VoAHelpers::VOA_MAP_ID) &&
            IsActiveInEncounter();
    }

protected:
    virtual bool IsActiveInEncounter() = 0;
};

// All four Watchers want the same of their tank: threat on a boss that stays where the raid put
// it. Archavon leaps away from his tank every 30 seconds (BA:142) and the orbs drag the raid
// around Toravon, so the hold has to be renewed rather than taken once.
class VoABossShouldBeTankedTrigger : public VoAEncounterTrigger
{
public:
    VoABossShouldBeTankedTrigger(PlayerbotAI* botAI, std::string const& name, uint32 bossEntry)
        : VoAEncounterTrigger(botAI, name), _bossEntry(bossEntry) {}

protected:
    bool IsActiveInEncounter() override;

private:
    uint32 const _bossEntry;
};

// Every Watcher but Toravon throws something at one random player that lands on the ground around
// it, so the ranged stand apart from each other.
class VoARangedShouldSpreadTrigger : public VoAEncounterTrigger
{
public:
    VoARangedShouldSpreadTrigger(PlayerbotAI* botAI, std::string const& name, uint32 bossEntry)
        : VoAEncounterTrigger(botAI, name), _bossEntry(bossEntry) {}

protected:
    bool IsActiveInEncounter() override;

private:
    uint32 const _bossEntry;
};

enum class VoAAddRole : uint8
{
    Tanks,
    RangedDps,
};

// Emalon's Tempest Minions and Toravon's Frozen Orbs: adds that are dealt with on sight, differing
// only in who goes for them.
class VoAAddsSpawnedTrigger : public VoAEncounterTrigger
{
public:
    VoAAddsSpawnedTrigger(
        PlayerbotAI* botAI, std::string const& name, char const* addsValue, VoAAddRole role)
        : VoAEncounterTrigger(botAI, name), _addsValue(addsValue), _role(role) {}

protected:
    bool IsActiveInEncounter() override;

private:
    char const* const _addsValue;
    VoAAddRole const _role;
};

// A Frozen Orb is a creature nobody wants to stand next to, because it carries its damage as an
// aura around itself (BT:180).
class VoABotNearAddTrigger : public VoAEncounterTrigger
{
public:
    VoABotNearAddTrigger(
        PlayerbotAI* botAI, std::string const& name, char const* addsValue, float radius)
        : VoAEncounterTrigger(botAI, name), _addsValue(addsValue), _radius(radius) {}

protected:
    bool IsActiveInEncounter() override;

private:
    char const* const _addsValue;
    float const _radius;
};

// Emalon the Storm Watcher

// The minions beat on whoever is nearest once they are in combat (BE:131), so the tanks that are
// not holding Emalon take them.
class EmalonTempestMinionsTrigger : public VoAAddsSpawnedTrigger
{
public:
    EmalonTempestMinionsTrigger(PlayerbotAI* botAI)
        : VoAAddsSpawnedTrigger(
              botAI, "emalon tempest minions spawned", VoAHelpers::EMALON_MINIONS_VALUE,
              VoAAddRole::Tanks) {}
};

// Ten stacks of Overcharge burst the minion and wipe its health bar clean on the way in (BE:142,
// :241), so everything that can hit it goes for it at once.
class EmalonOverchargedMinionTrigger : public VoAEncounterTrigger
{
public:
    EmalonOverchargedMinionTrigger(PlayerbotAI* botAI)
        : VoAEncounterTrigger(botAI, "emalon overcharged minion should be killed") {}

protected:
    bool IsActiveInEncounter() override;
};

// Koralon the Flame Watcher

// He breathes in front of himself and keeps turning for three seconds (BK:142, :113), so standing
// where he faces is only safe until he gets there.
class KoralonBurningBreathTrigger : public VoAEncounterTrigger
{
public:
    KoralonBurningBreathTrigger(PlayerbotAI* botAI)
        : VoAEncounterTrigger(botAI, "koralon burning breath incoming") {}

protected:
    bool IsActiveInEncounter() override;
};

// Toravon the Ice Watcher

// The orb that has this bot on its threat list is the one chasing it (BT:191): it has to be
// outrun, because the raid kills orbs slower than they reach their target.
class ToravonBotPursuedByOrbTrigger : public VoAEncounterTrigger
{
public:
    ToravonBotPursuedByOrbTrigger(PlayerbotAI* botAI)
        : VoAEncounterTrigger(botAI, "toravon bot pursued by frozen orb") {}

protected:
    bool IsActiveInEncounter() override;
};

// Freezing Ground is dropped at a random player every 20 seconds (BT:134) and stays on the floor.
class ToravonBotInFreezingGroundTrigger : public VoAEncounterTrigger
{
public:
    ToravonBotInFreezingGroundTrigger(PlayerbotAI* botAI)
        : VoAEncounterTrigger(botAI, "toravon bot in freezing ground") {}

protected:
    bool IsActiveInEncounter() override;
};

class ArchavonLostAggroTrigger : public VoAEncounterTrigger
{
public:
    ArchavonLostAggroTrigger(PlayerbotAI* botAI) : VoAEncounterTrigger(botAI, "archavon attacking non tank") {}

    bool IsActiveInEncounter() override
    {
        return VoAHelpers::GetArchavonToTaunt(bot) != nullptr;
    }
};

#endif
