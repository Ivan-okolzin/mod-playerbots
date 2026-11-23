/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#ifndef PLAYERBOTS_CRUSADERTRIGGERS_H
#define PLAYERBOTS_CRUSADERTRIGGERS_H

#include "CrusaderHelpers.h"
#include "EncounterHelpers.h"
#include "Trigger.h"
#include <string>

// Shared

class CrusaderEncounterTrigger : public Trigger
{
public:
    CrusaderEncounterTrigger(PlayerbotAI* botAI, std::string const name, int32 checkInterval = 1)
        : Trigger(botAI, name, checkInterval) {}

    bool IsActive() final
    {
        return EncounterHelpers::IsEncounterInProgress(bot, CrusaderHelpers::CRUSADER_MAP_ID) &&
            IsActiveInEncounter();
    }

protected:
    virtual bool IsActiveInEncounter() = 0;
};

// Gormok, Icehowl, Jaraxxus and Anub'arak all want the same of their tank: threat on a boss that
// stays where the raid put it.
class CrusaderBossShouldBeTankedTrigger : public CrusaderEncounterTrigger
{
public:
    CrusaderBossShouldBeTankedTrigger(PlayerbotAI* botAI, std::string const& name, uint32 bossEntry)
        : CrusaderEncounterTrigger(botAI, name), _bossEntry(bossEntry) {}

protected:
    bool IsActiveInEncounter() override;

private:
    uint32 const _bossEntry;
};

// Ranged spread out from each other, and keep their distance from the boss where its melee-range
// mechanics warrant it.
class CrusaderRangedShouldSpreadTrigger : public CrusaderEncounterTrigger
{
public:
    CrusaderRangedShouldSpreadTrigger(
        PlayerbotAI* botAI, std::string const& name, uint32 bossEntry, float distanceFromBoss)
        : CrusaderEncounterTrigger(botAI, name), _bossEntry(bossEntry),
          _distanceFromBoss(distanceFromBoss) {}

protected:
    bool IsActiveInEncounter() override;

private:
    uint32 const _bossEntry;
    float const _distanceFromBoss;
};

enum class CrusaderAddRole : uint8
{
    Everyone,
    MeleeAndTanks,
    Tanks,
    RangedDps,
};

// Gormok's Snobolds, Jaraxxus's demons, and Anub'arak's Burrowers and Scarabs: adds the raid kills
// on sight, differing only in who goes for them.
class CrusaderAddsSpawnedTrigger : public CrusaderEncounterTrigger
{
public:
    CrusaderAddsSpawnedTrigger(
        PlayerbotAI* botAI, std::string const& name, char const* addsValue, CrusaderAddRole role)
        : CrusaderEncounterTrigger(botAI, name), _addsValue(addsValue), _role(role) {}

protected:
    bool IsActiveInEncounter() override;

private:
    char const* const _addsValue;
    CrusaderAddRole const _role;
};

// The jormungars' Slime Pools and Jaraxxus's Legion Flames are creatures standing on ground
// nobody wants to be on.
class CrusaderBotNearHazardTrigger : public CrusaderEncounterTrigger
{
public:
    CrusaderBotNearHazardTrigger(
        PlayerbotAI* botAI, std::string const& name, char const* hazardValue, float radius)
        : CrusaderEncounterTrigger(botAI, name), _hazardValue(hazardValue), _radius(radius) {}

protected:
    bool IsActiveInEncounter() override;

private:
    char const* const _hazardValue;
    float const _radius;
};

// Gormok the Impaler

// A Snobold rides a raid member until it is killed, interrupting its carrier's casts and cracking
// its skull (BNB:290, :306). The ranged take it off, because its carrier is wherever it is.
class GormokSnoboldOnRaidMemberTrigger : public CrusaderEncounterTrigger
{
public:
    GormokSnoboldOnRaidMemberTrigger(PlayerbotAI* botAI)
        : CrusaderEncounterTrigger(botAI, "gormok the impaler snobold on raid member") {}

protected:
    bool IsActiveInEncounter() override;
};

// The other side of the same job: the carrier is standing right under it, so it joins in unless
// it is holding the boss or healing.
class GormokBotIsSnobolledTrigger : public CrusaderEncounterTrigger
{
public:
    GormokBotIsSnobolledTrigger(PlayerbotAI* botAI)
        : CrusaderEncounterTrigger(botAI, "gormok the impaler bot is snobolled") {}

protected:
    bool IsActiveInEncounter() override;
};

// Impale stacks on whoever Gormok is hitting (BNB:412), so the second tank takes him over.
class GormokMainTankImpaleStacksTrigger : public CrusaderEncounterTrigger
{
public:
    GormokMainTankImpaleStacksTrigger(PlayerbotAI* botAI)
        : CrusaderEncounterTrigger(botAI, "gormok the impaler main tank has impale stacks") {}

protected:
    bool IsActiveInEncounter() override;
};

// Acidmaw and Dreadscale

// Both worms need a tank, and which tank takes which worm changes with Paralytic Toxin and with
// every submerge.
class JormungarShouldBeTankedTrigger : public CrusaderEncounterTrigger
{
public:
    JormungarShouldBeTankedTrigger(PlayerbotAI* botAI)
        : CrusaderEncounterTrigger(botAI, "acidmaw and dreadscale should be tanked") {}

protected:
    bool IsActiveInEncounter() override;
};

// Icehowl

// The charge runs from Icehowl through the stalker standing on the player he glared at and on
// into the arena wall (BNB:1161), and Trample hits everything within 12 yards of him on the way.
class IcehowlChargeIncomingTrigger : public CrusaderEncounterTrigger
{
public:
    IcehowlChargeIncomingTrigger(PlayerbotAI* botAI)
        : CrusaderEncounterTrigger(botAI, "icehowl charge incoming") {}

protected:
    bool IsActiveInEncounter() override;
};

// Massive Crash is the warning that a charge is coming: a bot caught against the wall has no room
// to step out of the lane, so it comes in off the wall while Icehowl is still staring.
class IcehowlBotNearArenaWallTrigger : public CrusaderEncounterTrigger
{
public:
    IcehowlBotNearArenaWallTrigger(PlayerbotAI* botAI)
        : CrusaderEncounterTrigger(botAI, "icehowl bot near arena wall") {}

protected:
    bool IsActiveInEncounter() override;
};

// Faction Champions

// There is no threat to hold here: the champions re-pick their target by distance and health every
// nine seconds (boss_faction_champions.cpp:105), so the only thing the raid controls is what it
// kills first.
class FactionChampionsShouldFocusTargetTrigger : public CrusaderEncounterTrigger
{
public:
    FactionChampionsShouldFocusTargetTrigger(PlayerbotAI* botAI)
        : CrusaderEncounterTrigger(botAI, "faction champions should focus target") {}

protected:
    bool IsActiveInEncounter() override;
};

// Twin Val'kyr

// Without an essence a raid member takes both sisters' damage in full and gains nothing from the
// balls, so the first thing everyone does is go and get one.
class ValkyrBotHasNoEssenceTrigger : public CrusaderEncounterTrigger
{
public:
    ValkyrBotHasNoEssenceTrigger(PlayerbotAI* botAI)
        : CrusaderEncounterTrigger(botAI, "twin val'kyr bot has no essence") {}

protected:
    bool IsActiveInEncounter() override;
};

class ValkyrShouldBeTankedTrigger : public CrusaderEncounterTrigger
{
public:
    ValkyrShouldBeTankedTrigger(PlayerbotAI* botAI)
        : CrusaderEncounterTrigger(botAI, "twin val'kyr should be tanked") {}

protected:
    bool IsActiveInEncounter() override;
};

// Twin's Pact heals the sister that casts it and shields her while it fills (BTV:443), so the
// damage goes where the shield is.
class ValkyrPactIncomingTrigger : public CrusaderEncounterTrigger
{
public:
    ValkyrPactIncomingTrigger(PlayerbotAI* botAI)
        : CrusaderEncounterTrigger(botAI, "twin val'kyr pact incoming") {}

protected:
    bool IsActiveInEncounter() override;
};

// A ball bursts on the first player within 2.75 yards of it (BTV:880). The bot's own colour is
// absorbed into Powering Up, the other colour lands in full, so the same pair of balls is a prize
// for one half of the raid and a hazard for the other.
class ValkyrBallNearbyTrigger : public CrusaderEncounterTrigger
{
public:
    ValkyrBallNearbyTrigger(PlayerbotAI* botAI, std::string const& name, bool matching, float radius)
        : CrusaderEncounterTrigger(botAI, name), _matching(matching), _radius(radius) {}

protected:
    bool IsActiveInEncounter() override;

private:
    bool const _matching;
    float const _radius;
};

// Anub'arak

// The spike follows one player and only stops on a Permafrost patch (BAT:872).
class AnubarakBotPursuedBySpikeTrigger : public CrusaderEncounterTrigger
{
public:
    AnubarakBotPursuedBySpikeTrigger(PlayerbotAI* botAI)
        : CrusaderEncounterTrigger(botAI, "anub'arak bot pursued by spike") {}

protected:
    bool IsActiveInEncounter() override;
};

// Everyone else keeps clear of it: its trail casts Impale around itself (BAT:881). The player it
// is after cannot, which is why that one has its own object.
class AnubarakBotNearSpikeTrigger : public CrusaderEncounterTrigger
{
public:
    AnubarakBotNearSpikeTrigger(PlayerbotAI* botAI)
        : CrusaderEncounterTrigger(botAI, "anub'arak bot near pursuing spike") {}

protected:
    bool IsActiveInEncounter() override;
};

// Permafrost only exists where a Frost Sphere has been shot down, and the spheres are only worth
// shooting while Anub'arak is under the floor and the spike is out.
class AnubarakFrostSphereShouldBeDroppedTrigger : public CrusaderEncounterTrigger
{
public:
    AnubarakFrostSphereShouldBeDroppedTrigger(PlayerbotAI* botAI)
        : CrusaderEncounterTrigger(botAI, "anub'arak frost sphere should be dropped") {}

protected:
    bool IsActiveInEncounter() override;
};

#endif
