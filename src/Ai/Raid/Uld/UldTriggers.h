/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#ifndef PLAYERBOTS_ULDTRIGGERS_H
#define PLAYERBOTS_ULDTRIGGERS_H

#include "EncounterHelpers.h"
#include "EventMap.h"
#include "GenericTriggers.h"
#include "Trigger.h"
#include "UldBossHelper.h"
#include "UldHelpers.h"
#include <string>
#include <vector>

//
// Flame Levi
//
class FlameLeviathanOnVehicleTrigger : public Trigger
{
public:
    FlameLeviathanOnVehicleTrigger(PlayerbotAI* botAI) : Trigger(botAI, "flame leviathan on vehicle") {}
    bool IsActive() override;
};

class FlameLeviathanVehicleNearTrigger : public Trigger
{
public:
    FlameLeviathanVehicleNearTrigger(PlayerbotAI* botAI) : Trigger(botAI, "flame leviathan vehicle near") {}
    bool IsActive() override;
};

//
// Razorscale
//
class RazorscaleFlyingAloneTrigger : public Trigger
{
public:
    RazorscaleFlyingAloneTrigger(PlayerbotAI* botAI) : Trigger(botAI, "razorscale flying alone") {}
    bool IsActive() override;
};

class RazorscaleDevouringFlamesTrigger : public Trigger
{
public:
    RazorscaleDevouringFlamesTrigger(PlayerbotAI* botAI) : Trigger(botAI, "razorscale avoid devouring flames") {}
    bool IsActive() override;
};

class RazorscaleAvoidSentinelTrigger : public Trigger
{
public:
    RazorscaleAvoidSentinelTrigger(PlayerbotAI* botAI) : Trigger(botAI, "razorscale avoid sentinel") {}
    bool IsActive() override;
};

class RazorscaleAvoidWhirlwindTrigger : public Trigger
{
public:
    RazorscaleAvoidWhirlwindTrigger(PlayerbotAI* botAI) : Trigger(botAI, "razorscale avoid whirlwind") {}
    bool IsActive() override;
};

class RazorscaleGroundedTrigger : public Trigger
{
public:
    RazorscaleGroundedTrigger(PlayerbotAI* botAI) : Trigger(botAI, "razorscale grounded") {}
    bool IsActive() override;
};

class RazorscaleHarpoonAvailableTrigger : public Trigger
{
public:
    RazorscaleHarpoonAvailableTrigger(PlayerbotAI* botAI) : Trigger(botAI, "razorscale harpoon trigger") {}
    bool IsActive() override;
};

class RazorscaleFuseArmorTrigger : public Trigger
{
public:
    RazorscaleFuseArmorTrigger(PlayerbotAI* botAI) : Trigger(botAI, "razorscale fuse armor trigger") {}
    bool IsActive() override;
};

//
// Iron Assembly
//
class IronAssemblyLightningTendrilsTrigger : public Trigger
{
public:
    IronAssemblyLightningTendrilsTrigger(PlayerbotAI* botAI) : Trigger(botAI, "iron assembly lightning tendrils trigger") {}
    bool IsActive() override;
};

class IronAssemblyOverloadTrigger : public Trigger
{
public:
    IronAssemblyOverloadTrigger(PlayerbotAI* botAI) : Trigger(botAI, "iron assembly overload trigger") {}
    bool IsActive() override;
};

class IronAssemblyRuneOfPowerTrigger : public Trigger
{
public:
    IronAssemblyRuneOfPowerTrigger(PlayerbotAI* botAI) : Trigger(botAI, "iron assembly rune of power trigger") {}
    bool IsActive() override;
};

//
// Kologarn
//
class KologarnMarkDpsTargetTrigger : public Trigger
{
public:
    KologarnMarkDpsTargetTrigger(PlayerbotAI* botAI) : Trigger(botAI, "kologarn mark dps target trigger") {}
    bool IsActive() override;
};

class KologarnFallFromFloorTrigger : public Trigger
{
public:
    KologarnFallFromFloorTrigger(PlayerbotAI* botAI) : Trigger(botAI, "kologarn fall from floor trigger") {}
    bool IsActive() override;
};

class KologarnRubbleSlowdownTrigger : public Trigger
{
public:
    KologarnRubbleSlowdownTrigger(PlayerbotAI* botAI) : Trigger(botAI, "kologarn rubble slowdown trigger") {}
    bool IsActive() override;
};

class KologarnEyebeamTrigger : public Trigger
{
public:
    KologarnEyebeamTrigger(PlayerbotAI* botAI) : Trigger(botAI, "kologarn eyebeam trigger") {}
    bool IsActive() override;
};

class KologarnAttackDpsTargetTrigger : public Trigger
{
public:
    KologarnAttackDpsTargetTrigger(PlayerbotAI* botAI) : Trigger(botAI, "kologarn attack dps target trigger") {}
    bool IsActive() override;
};

class KologarnRtiTargetTrigger : public Trigger
{
public:
    KologarnRtiTargetTrigger(PlayerbotAI* botAI) : Trigger(botAI, "kologarn rti target trigger") {}
    bool IsActive() override;
};

class KologarnCrunchArmorTrigger : public Trigger
{
public:
    KologarnCrunchArmorTrigger(PlayerbotAI* botAI) : Trigger(botAI, "kologarn crunch armor trigger") {}
    bool IsActive() override;
};

//
// Auriaya
//
class AuriayaFallFromFloorTrigger : public Trigger
{
public:
    AuriayaFallFromFloorTrigger(PlayerbotAI* botAI) : Trigger(botAI, "auriaya fall from floor trigger") {}
    bool IsActive() override;
};

//
// Hodir
//
class HodirBitingColdTrigger : public Trigger
{
public:
    HodirBitingColdTrigger(PlayerbotAI* botAI) : Trigger(botAI, "hodir biting cold") {}
    bool IsActive() override;
};

class HodirNearSnowpackedIcicleTrigger : public Trigger
{
public:
    HodirNearSnowpackedIcicleTrigger(PlayerbotAI* botAI) : Trigger(botAI, "hodir near snowpacked icicle") {}
    bool IsActive() override;
};

//
// Freya
//
class FreyaNearNatureBombTrigger : public Trigger
{
public:
    FreyaNearNatureBombTrigger(PlayerbotAI* botAI) : Trigger(botAI, "freya near nature bomb") {}
    bool IsActive() override;
};

class FreyaMarkDpsTargetTrigger : public Trigger
{
public:
    FreyaMarkDpsTargetTrigger(PlayerbotAI* botAI) : Trigger(botAI, "freya mark dps target trigger") {}
    bool IsActive() override;
};

class FreyaMoveToHealingSporeTrigger : public Trigger
{
public:
    FreyaMoveToHealingSporeTrigger(PlayerbotAI* botAI) : Trigger(botAI, "freya move to healing spore trigger") {}
    bool IsActive() override;
};

//
// Thorim
//
class ThorimUnbalancingStrikeTrigger : public Trigger
{
public:
    ThorimUnbalancingStrikeTrigger(PlayerbotAI* botAI) : Trigger(botAI, "thorim unbalancing strike trigger") {}
    bool IsActive() override;
};

class ThorimMarkDpsTargetTrigger : public Trigger
{
public:
    ThorimMarkDpsTargetTrigger(PlayerbotAI* botAI) : Trigger(botAI, "thorim mark dps target trigger") {}
    bool IsActive() override;
};

class ThorimGauntletPositioningTrigger : public Trigger
{
public:
    ThorimGauntletPositioningTrigger(PlayerbotAI* botAI) : Trigger(botAI, "thorim gauntlet positioning trigger") {}
    bool IsActive() override;
};

class ThorimArenaPositioningTrigger : public Trigger
{
public:
    ThorimArenaPositioningTrigger(PlayerbotAI* botAI) : Trigger(botAI, "thorim arena positioning trigger") {}
    bool IsActive() override;
};

class ThorimFallFromFloorTrigger : public Trigger
{
public:
    ThorimFallFromFloorTrigger(PlayerbotAI* botAI) : Trigger(botAI, "thorim fall from floor trigger") {}
    bool IsActive() override;
};

class ThorimPhase2PositioningTrigger : public Trigger
{
public:
    ThorimPhase2PositioningTrigger(PlayerbotAI* botAI) : Trigger(botAI, "thorim phase 2 positioning trigger") {}
    bool IsActive() override;
};

//
// Mimiron
//
class MimironShockBlastTrigger : public Trigger
{
public:
    MimironShockBlastTrigger(PlayerbotAI* botAI) : Trigger(botAI, "mimiron shock blast trigger") {}
    bool IsActive() override;
};

class MimironPhase1PositioningTrigger : public Trigger
{
public:
    MimironPhase1PositioningTrigger(PlayerbotAI* botAI) : Trigger(botAI, "mimiron phase 1 positioning trigger") {}
    bool IsActive() override;
};

class MimironP3Wx2LaserBarrageTrigger : public Trigger
{
public:
    MimironP3Wx2LaserBarrageTrigger(PlayerbotAI* botAI) : Trigger(botAI, "mimiron p3wx2 laser barrage trigger") {}
    bool IsActive() override;
};

class MimironRapidBurstTrigger : public Trigger
{
public:
    MimironRapidBurstTrigger(PlayerbotAI* botAI) : Trigger(botAI, "mimiron rapid burst trigger") {}
    bool IsActive() override;
};

class MimironAerialCommandUnitTrigger : public Trigger
{
public:
    MimironAerialCommandUnitTrigger(PlayerbotAI* botAI) : Trigger(botAI, "mimiron aerial command unit trigger") {}
    bool IsActive() override;
};

class MimironRocketStrikeTrigger : public Trigger
{
public:
    MimironRocketStrikeTrigger(PlayerbotAI* botAI) : Trigger(botAI, "mimiron rocket strike trigger") {}
    bool IsActive() override;
};

class MimironPhase4MarkDpsTrigger : public Trigger
{
public:
    MimironPhase4MarkDpsTrigger(PlayerbotAI* botAI) : Trigger(botAI, "mimiron phase 4 mark dps trigger") {}
    bool IsActive() override;
};

class MimironCheatTrigger : public Trigger
{
public:
    MimironCheatTrigger(PlayerbotAI* botAI) : Trigger(botAI, "mimiron cheat trigger") {}
    bool IsActive() override;
};

//
// General Vezax
//
class VezaxCheatTrigger : public Trigger
{
public:
    VezaxCheatTrigger(PlayerbotAI* botAI) : Trigger(botAI, "vezax cheat trigger") {}
    bool IsActive() override;
};

class VezaxShadowCrashTrigger : public Trigger
{
public:
    VezaxShadowCrashTrigger(PlayerbotAI* botAI) : Trigger(botAI, "vezax shadow crash trigger") {}
    bool IsActive() override;
};

class VezaxMarkOfTheFacelessTrigger : public Trigger
{
public:
    VezaxMarkOfTheFacelessTrigger(PlayerbotAI* botAI) : Trigger(botAI, "vezax mark of the faceless trigger") {}
    bool IsActive() override;
};

//
// Yogg-Saron
//
class YoggSaronTrigger : public Trigger
{
public:
    YoggSaronTrigger(PlayerbotAI* botAI, std::string const name = "yogg saron trigger", int32 checkInteval = 1)
        : Trigger(botAI, name, checkInteval) {}

    bool IsYoggSaronFight();
    bool IsPhase2();
    bool IsPhase3();
    bool IsInBrainLevel();
    bool IsInIllusionRoom();
    bool IsInStormwindKeeperIllusion();
    bool IsInIcecrownKeeperIllusion();
    bool IsInChamberOfTheAspectsIllusion();
    bool IsMasterIsInIllusionGroup();
    bool IsMasterIsInBrainRoom();
    Position GetIllusionRoomEntrancePosition();
    Unit* GetIllusionRoomRtiTarget();
    Unit* GetNextIllusionRoomRtiTarget();
    Unit* GetSaraIfAlive();
};

class YoggSaronOminousCloudCheatTrigger : public YoggSaronTrigger
{
public:
    YoggSaronOminousCloudCheatTrigger(PlayerbotAI* botAI) : YoggSaronTrigger(botAI, "yogg-saron ominous cloud cheat trigger") {}
    bool IsActive() override;
};

class YoggSaronGuardianPositioningTrigger : public YoggSaronTrigger
{
public:
    YoggSaronGuardianPositioningTrigger(PlayerbotAI* botAI) : YoggSaronTrigger(botAI, "yogg-saron guardian positioning trigger") {}
    bool IsActive() override;
};

class YoggSaronSanityTrigger : public YoggSaronTrigger
{
public:
    YoggSaronSanityTrigger(PlayerbotAI* botAI) : YoggSaronTrigger(botAI, "yogg-saron sanity trigger") {}
    bool IsActive() override;
};

class YoggSaronDeathOrbTrigger : public YoggSaronTrigger
{
public:
    YoggSaronDeathOrbTrigger(PlayerbotAI* botAI) : YoggSaronTrigger(botAI, "yogg-saron death orb trigger") {}
    bool IsActive() override;
};

class YoggSaronMaladyOfTheMindTrigger : public YoggSaronTrigger
{
public:
    YoggSaronMaladyOfTheMindTrigger(PlayerbotAI* botAI) : YoggSaronTrigger(botAI, "yogg-saron malady of the mind trigger") {}
    bool IsActive() override;
};

class YoggSaronMarkTargetTrigger : public YoggSaronTrigger
{
public:
    YoggSaronMarkTargetTrigger(PlayerbotAI* botAI) : YoggSaronTrigger(botAI, "yogg-saron mark target trigger") {}
    bool IsActive() override;
};

class YoggSaronBrainLinkTrigger : public YoggSaronTrigger
{
public:
    YoggSaronBrainLinkTrigger(PlayerbotAI* botAI) : YoggSaronTrigger(botAI, "yogg-saron brain link trigger") {}
    bool IsActive() override;
};

class YoggSaronMoveToEnterPortalTrigger : public YoggSaronTrigger
{
public:
    YoggSaronMoveToEnterPortalTrigger(PlayerbotAI* botAI) : YoggSaronTrigger(botAI, "yogg-saron move to enter portal trigger") {}
    bool IsActive() override;
};

class YoggSaronFallFromFloorTrigger : public YoggSaronTrigger
{
public:
    YoggSaronFallFromFloorTrigger(PlayerbotAI* botAI) : YoggSaronTrigger(botAI, "yogg-saron fall from floor trigger") {}
    bool IsActive() override;
};

class YoggSaronBossRoomMovementCheatTrigger : public YoggSaronTrigger
{
public:
    YoggSaronBossRoomMovementCheatTrigger(PlayerbotAI* botAI) : YoggSaronTrigger(botAI, "yogg-saron boss room movement cheat trigger") {}
    bool IsActive() override;
};

class YoggSaronUsePortalTrigger : public YoggSaronTrigger
{
public:
    YoggSaronUsePortalTrigger(PlayerbotAI* botAI) : YoggSaronTrigger(botAI, "yogg-saron use portal trigger") {}
    bool IsActive() override;
};

class YoggSaronIllusionRoomTrigger : public YoggSaronTrigger
{
public:
    YoggSaronIllusionRoomTrigger(PlayerbotAI* botAI) : YoggSaronTrigger(botAI, "yogg-saron illusion room trigger") {}
    bool IsActive() override;

private:
    bool GoToBrainRoomRequired();
    bool SetRtiMarkRequired();
    bool SetRtiTargetRequired();
};

class YoggSaronMoveToExitPortalTrigger : public YoggSaronTrigger
{
public:
    YoggSaronMoveToExitPortalTrigger(PlayerbotAI* botAI) : YoggSaronTrigger(botAI, "yogg-saron move to exit portal trigger") {}
    bool IsActive() override;
};

class YoggSaronLunaticGazeTrigger : public YoggSaronTrigger
{
public:
    YoggSaronLunaticGazeTrigger(PlayerbotAI* botAI) : YoggSaronTrigger(botAI, "yogg-saron lunatic gaze trigger") {}
    bool IsActive() override;
};

class YoggSaronPhase3PositioningTrigger : public YoggSaronTrigger
{
public:
    YoggSaronPhase3PositioningTrigger(PlayerbotAI* botAI) : YoggSaronTrigger(botAI, "yogg-saron phase 3 positioning trigger") {}
    bool IsActive() override;
};

// Shared

class UldEncounterTrigger : public Trigger
{
public:
    UldEncounterTrigger(PlayerbotAI* botAI, std::string const name, int32 checkInterval = 1)
        : Trigger(botAI, name, checkInterval) {}

    bool IsActive() final
    {
        return EncounterHelpers::IsEncounterInProgress(bot, UldHelpers::ULD_MAP_ID) &&
            IsActiveInEncounter();
    }

protected:
    virtual bool IsActiveInEncounter() = 0;
};

// XT-002, Ignis, Auriaya and Algalon all want the same of their main tank: threat on a boss that
// stays where the raid put it. Each of them also spends part of the fight untargetable, which is
// what keeps this object out of those phases.
class UldBossShouldBeTankedTrigger : public UldEncounterTrigger
{
public:
    UldBossShouldBeTankedTrigger(
        PlayerbotAI* botAI, std::string const& name, std::vector<uint32> const& bossEntries)
        : UldEncounterTrigger(botAI, name), _bossEntries(bossEntries) {}

protected:
    bool IsActiveInEncounter() override;

private:
    std::vector<uint32> const _bossEntries;
};

// XT-002 throws Searing Light and Gravity Bomb at one random player and hurts the ground around
// it (BXT:372, :376), so the ranged stand apart from each other.
class UldRangedShouldSpreadTrigger : public UldEncounterTrigger
{
public:
    UldRangedShouldSpreadTrigger(
        PlayerbotAI* botAI, std::string const& name, std::vector<uint32> const& bossEntries)
        : UldEncounterTrigger(botAI, name), _bossEntries(bossEntries) {}

protected:
    bool IsActiveInEncounter() override;

private:
    std::vector<uint32> const _bossEntries;
};

enum class UldAddRole : uint8
{
    Everyone,
    MeleeAndTanks,
    Tanks,
    RangedDps,
};

// XT-002's robots, Auriaya's cats and Algalon's stars: adds the raid deals with on sight,
// differing only in who goes for them.
class UldAddsSpawnedTrigger : public UldEncounterTrigger
{
public:
    UldAddsSpawnedTrigger(
        PlayerbotAI* botAI, std::string const& name, char const* addsValue, UldAddRole role)
        : UldEncounterTrigger(botAI, name), _addsValue(addsValue), _role(role) {}

protected:
    bool IsActiveInEncounter() override;

private:
    char const* const _addsValue;
    UldAddRole const _role;
};

// Void Zones, Scorched Ground, Seeping Feral Essence and the Cosmic Smash marks are all creatures
// standing on ground nobody wants to be on.
class UldBotNearHazardTrigger : public UldEncounterTrigger
{
public:
    UldBotNearHazardTrigger(
        PlayerbotAI* botAI, std::string const& name, char const* hazardValue, float radius)
        : UldEncounterTrigger(botAI, name), _hazardValue(hazardValue), _radius(radius) {}

protected:
    bool IsActiveInEncounter() override;

private:
    char const* const _hazardValue;
    float const _radius;
};

// XT-002 Deconstructor

// For 30 seconds at 75%, 50% and 25% health the heart is the only thing in the room that can be
// hit at all: XT-002 submerges and goes untargetable with it (BXT:388-399).
class Xt002HeartExposedTrigger : public UldEncounterTrigger
{
public:
    Xt002HeartExposedTrigger(PlayerbotAI* botAI)
        : UldEncounterTrigger(botAI, "xt-002 heart exposed") {}

protected:
    bool IsActiveInEncounter() override;
};

// Gravity Bomb hurts everything around its carrier and leaves a Void Zone where the carrier stood
// when it falls off (BXT:773-791), so the carrier takes both away from the raid.
class Xt002BotHasGravityBombTrigger : public UldEncounterTrigger
{
public:
    Xt002BotHasGravityBombTrigger(PlayerbotAI* botAI)
        : UldEncounterTrigger(botAI, "xt-002 bot has gravity bomb") {}

protected:
    bool IsActiveInEncounter() override;
};

// A Boombot explodes at half health for 15000 to 18000 damage (BXT:611, :638-645), which is why
// the melee keep away from it and only the ranged shoot it.
class Xt002BotNearBoombotTrigger : public UldEncounterTrigger
{
public:
    Xt002BotNearBoombotTrigger(PlayerbotAI* botAI)
        : UldEncounterTrigger(botAI, "xt-002 bot near boombot") {}

protected:
    bool IsActiveInEncounter() override;
};

// Ignis the Furnace Master

// Every activated construct is a stack of Strength of the Creator on Ignis until it dies
// (BIG:125, :150), and it picks its target from Ignis's victim rather than from threat (BIG:126).
class IgnisConstructShouldBeTankedTrigger : public UldEncounterTrigger
{
public:
    IgnisConstructShouldBeTankedTrigger(PlayerbotAI* botAI)
        : UldEncounterTrigger(botAI, "ignis iron construct should be tanked") {}

protected:
    bool IsActiveInEncounter() override;
};

// A construct that has stood by Ignis long enough turns Molten and resets its threat (BIG:133-141).
// Molten is also the only state the water can do anything with, so the tank holding it walks it in.
class IgnisMoltenConstructShouldBeDousedTrigger : public UldEncounterTrigger
{
public:
    IgnisMoltenConstructShouldBeDousedTrigger(PlayerbotAI* botAI)
        : UldEncounterTrigger(botAI, "ignis molten construct should be doused") {}

protected:
    bool IsActiveInEncounter() override;
};

// Brittle shatters on the next hit of 5000 damage and takes the construct with it (BIG:491-503),
// so a Brittle construct is a free kill for whoever is closest.
class IgnisBrittleConstructShouldBeKilledTrigger : public UldEncounterTrigger
{
public:
    IgnisBrittleConstructShouldBeKilledTrigger(PlayerbotAI* botAI)
        : UldEncounterTrigger(botAI, "ignis brittle construct should be killed") {}

protected:
    bool IsActiveInEncounter() override;
};

// Auriaya

// The four Sanctum Sentries buff each other while they live (BAU:255) and pounce anyone 8 to 25
// yards out (BAU:270-280), so the raid takes them off the board before it works on Auriaya.
class AuriayaSentryShouldBeKilledTrigger : public UldEncounterTrigger
{
public:
    AuriayaSentryShouldBeKilledTrigger(PlayerbotAI* botAI)
        : UldEncounterTrigger(botAI, "auriaya sanctum sentry should be killed") {}

protected:
    bool IsActiveInEncounter() override;
};

// Algalon the Observer

// Phase Punch stacks on whoever Algalon is hitting and banishes it at five (BAL:716, :1246), so
// the second tank takes him over before that.
class AlgalonMainTankPhasePunchStacksTrigger : public UldEncounterTrigger
{
public:
    AlgalonMainTankPhasePunchStacksTrigger(PlayerbotAI* botAI)
        : UldEncounterTrigger(botAI, "algalon main tank has phase punch stacks") {}

protected:
    bool IsActiveInEncounter() override;
};

// Big Bang kills everything it reaches and only a Black Hole is out of its reach, so the whole
// raid spends the eight seconds of the cast getting into one.
class AlgalonBigBangIncomingTrigger : public UldEncounterTrigger
{
public:
    AlgalonBigBangIncomingTrigger(PlayerbotAI* botAI)
        : UldEncounterTrigger(botAI, "algalon big bang incoming") {}

protected:
    bool IsActiveInEncounter() override;
};

// A Living Constellation cannot be removed by damage, only by being walked into a Black Hole
// (BAL:1063-1078). The bot it has picked is the one it follows there.
class AlgalonConstellationChasingBotTrigger : public UldEncounterTrigger
{
public:
    AlgalonConstellationChasingBotTrigger(PlayerbotAI* botAI)
        : UldEncounterTrigger(botAI, "algalon constellation chasing bot") {}

protected:
    bool IsActiveInEncounter() override;
};

#endif
