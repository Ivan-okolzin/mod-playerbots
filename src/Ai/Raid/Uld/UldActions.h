/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#ifndef PLAYERBOTS_ULDACTIONS_H
#define PLAYERBOTS_ULDACTIONS_H

#include "Action.h"
#include "AttackAction.h"
#include "GenericSpellActions.h"
#include "MovementActions.h"
#include "PlayerbotAI.h"
#include "Playerbots.h"
#include "UldBossHelper.h"
#include "UldHelpers.h"
#include "UldTriggers.h"
#include "Vehicle.h"
#include <string>
#include <vector>

//
//  Flame Leviathan
//

class FlameLeviathanVehicleAction : public MovementAction
{
public:
    FlameLeviathanVehicleAction(PlayerbotAI* botAI) : MovementAction(botAI, "flame leviathan vehicle") {}
    bool Execute(Event event) override;

protected:
    bool MoveAvoidChasing(Unit* target);
    bool DemolisherAction(Unit* target);
    bool DemolisherTurretAction(Unit* target);
    bool SiegeEngineAction(Unit* target);
    bool SiegeEngineTurretAction(Unit* target);
    bool ChopperAction(Unit* target);
    Unit* GetAttacker();
    Unit* vehicleBase_;
    Vehicle* vehicle_;
    int avoidChaseIdx = -1;
};

class FlameLeviathanEnterVehicleAction : public MovementAction
{
public:
    FlameLeviathanEnterVehicleAction(PlayerbotAI* botAI) : MovementAction(botAI, "flame leviathan enter vehicle") {}
    bool Execute(Event event);

protected:
    bool EnterVehicle(Unit* vehicleBase, bool moveIfFar);
    bool ShouldEnter(Unit* vehicleBase);
    bool AllMainVehiclesOnUse();
};

//
//  Razorscale
//

class RazorscaleAvoidDevouringFlameAction : public MovementAction
{
public:
    RazorscaleAvoidDevouringFlameAction(PlayerbotAI* botAI) : MovementAction(botAI, "razorscale avoid devouring flames") {}
    bool Execute(Event event) override;
    bool isUseful() override;
};

class RazorscaleAvoidSentinelAction : public MovementAction
{
public:
    RazorscaleAvoidSentinelAction(PlayerbotAI* botAI) : MovementAction(botAI, "razorscale avoid sentinel") {}
    bool Execute(Event event) override;
    bool isUseful() override;
};

class RazorscaleIgnoreBossAction : public AttackAction
{
public:
    RazorscaleIgnoreBossAction(PlayerbotAI* botAI) : AttackAction(botAI, "razorscale ignore flying alone") {}
    bool Execute(Event event) override;
    bool isUseful() override;
};

class RazorscaleAvoidWhirlwindAction : public MovementAction
{
public:
    RazorscaleAvoidWhirlwindAction(PlayerbotAI* botAI) : MovementAction(botAI, "razorscale avoid whirlwind") {}
    bool Execute(Event event) override;
    bool isUseful() override;
};

class RazorscaleGroundedAction : public AttackAction
{
public:
    RazorscaleGroundedAction(PlayerbotAI* botAI) : AttackAction(botAI, "razorscale grounded") {}
    bool Execute(Event event) override;
    bool isUseful() override;
};

class RazorscaleHarpoonAction : public MovementAction
{
public:
    RazorscaleHarpoonAction(PlayerbotAI* botAI) : MovementAction(botAI, "razorscale harpoon action") {}
    bool Execute(Event event) override;
    bool isUseful() override;
};

class RazorscaleFuseArmorAction : public MovementAction
{
public:
    RazorscaleFuseArmorAction(PlayerbotAI* botAI) : MovementAction(botAI, "razorscale fuse armor action") {}
    bool Execute(Event event) override;
    bool isUseful() override;
};

class HodirMoveSnowpackedIcicleAction : public MovementAction
{
public:
    HodirMoveSnowpackedIcicleAction(PlayerbotAI* botAI) : MovementAction(botAI, "hodir move snowpacked icicle") {}
    bool Execute(Event event) override;
    bool isUseful() override;
};

class IronAssemblyLightningTendrilsAction : public MovementAction
{
public:
    IronAssemblyLightningTendrilsAction(PlayerbotAI* botAI) : MovementAction(botAI, "iron assembly lightning tendrils action") {}
    bool Execute(Event event) override;
    bool isUseful() override;
};

class IronAssemblyOverloadAction : public MovementAction
{
public:
    IronAssemblyOverloadAction(PlayerbotAI* botAI) : MovementAction(botAI, "iron assembly overload action") {}
    bool Execute(Event event) override;
    bool isUseful() override;
};

class IronAssemblyRuneOfPowerAction : public MovementAction
{
public:
    IronAssemblyRuneOfPowerAction(PlayerbotAI* botAI) : MovementAction(botAI, "iron assembly rune of power action") {}
    bool Execute(Event event) override;
    bool isUseful() override;
};

class KologarnMarkDpsTargetAction : public Action
{
public:
    KologarnMarkDpsTargetAction(PlayerbotAI* botAI) : Action(botAI, "kologarn mark dps target action") {}
    bool Execute(Event event) override;
    bool isUseful() override;
};

class KologarnFallFromFloorAction : public Action
{
public:
    KologarnFallFromFloorAction(PlayerbotAI* botAI) : Action(botAI, "kologarn fall from floor action") {}
    bool Execute(Event event) override;
    bool isUseful() override;
};

class KologarnRubbleSlowdownAction : public Action
{
public:
    KologarnRubbleSlowdownAction(PlayerbotAI* botAI) : Action(botAI, "kologarn rubble slowdown action") {}
    bool Execute(Event event) override;
};

class KologarnEyebeamAction : public MovementAction
{
public:
    KologarnEyebeamAction(PlayerbotAI* botAI) : MovementAction(botAI, "kologarn eyebeam action") {}
    bool Execute(Event event) override;
    bool isUseful() override;
};

class KologarnRtiTargetAction : public Action
{
public:
    KologarnRtiTargetAction(PlayerbotAI* botAI) : Action(botAI, "kologarn rti target action") {}
    bool Execute(Event event) override;
    bool isUseful() override;
};

class KologarnCrunchArmorAction : public Action
{
public:
    KologarnCrunchArmorAction(PlayerbotAI* botAI) : Action(botAI, "kologarn crunch armor action") {}
    bool Execute(Event event) override;
    bool isUseful() override;
};

class AuriayaFallFromFloorAction : public Action
{
public:
    AuriayaFallFromFloorAction(PlayerbotAI* botAI) : Action(botAI, "auriaya fall from floor action") {}
    bool Execute(Event event) override;
    bool isUseful() override;
};

class HodirBitingColdJumpAction : public MovementAction
{
public:
    HodirBitingColdJumpAction(PlayerbotAI* botAI) : MovementAction(botAI, "hodir biting cold jump") {}
    bool Execute(Event event) override;
    bool isUseful() override;
};

class FreyaMoveAwayNatureBombAction : public MovementAction
{
public:
    FreyaMoveAwayNatureBombAction(PlayerbotAI* botAI) : MovementAction(botAI, "freya move away nature bomb") {}
    bool Execute(Event event) override;
    bool isUseful() override;
};

class FreyaMarkDpsTargetAction : public MovementAction
{
public:
    FreyaMarkDpsTargetAction(PlayerbotAI* botAI) : MovementAction(botAI, "freya mark dps target action") {}
    bool Execute(Event event) override;
    bool isUseful() override;
};

class FreyaMoveToHealingSporeAction : public MovementAction
{
public:
    FreyaMoveToHealingSporeAction(PlayerbotAI* botAI) : MovementAction(botAI, "freya move to healing spore action") {}

    bool Execute(Event event) override;
    bool isUseful() override;
};

class ThorimUnbalancingStrikeAction : public Action
{
public:
    ThorimUnbalancingStrikeAction(PlayerbotAI* botAI) : Action(botAI, "thorim unbalancing strike action") {}

    bool Execute(Event event) override;
    bool isUseful() override;
};

class ThorimMarkDpsTargetAction : public Action
{
public:
    ThorimMarkDpsTargetAction(PlayerbotAI* botAI) : Action(botAI, "thorim mark dps target action") {}

    bool Execute(Event event) override;
    bool isUseful() override;
};

class ThorimArenaPositioningAction : public MovementAction
{
public:
    ThorimArenaPositioningAction(PlayerbotAI* botAI) : MovementAction(botAI, "thorim arena positioning action") {}

    bool Execute(Event event) override;
    bool isUseful() override;
};

class ThorimGauntletPositioningAction : public MovementAction
{
public:
    ThorimGauntletPositioningAction(PlayerbotAI* botAI) : MovementAction(botAI, "thorim gauntlet positioning action") {}

    bool Execute(Event event) override;
    bool isUseful() override;
};

class ThorimFallFromFloorAction : public Action
{
public:
    ThorimFallFromFloorAction(PlayerbotAI* botAI) : Action(botAI, "thorim fall from floor action") {}
    bool Execute(Event event) override;
    bool isUseful() override;
};

class ThorimPhase2PositioningAction : public MovementAction
{
public:
    ThorimPhase2PositioningAction(PlayerbotAI* botAI) : MovementAction(botAI, "thorim phase 2 positioning action") {}

    bool Execute(Event event) override;
    bool isUseful() override;
};

class MimironShockBlastAction : public MovementAction
{
public:
    MimironShockBlastAction(PlayerbotAI* botAI) : MovementAction(botAI, "mimiron shock blast action") {}

    bool Execute(Event event) override;
    bool isUseful() override;
};

class MimironPhase1PositioningAction : public MovementAction
{
public:
    MimironPhase1PositioningAction(PlayerbotAI* botAI) : MovementAction(botAI, "mimiron phase 1 positioning action") {}

    bool Execute(Event event) override;
    bool isUseful() override;
};

class MimironP3Wx2LaserBarrageAction : public MovementAction
{
public:
    MimironP3Wx2LaserBarrageAction(PlayerbotAI* botAI, float distance = 24.0f, float delta_angle = M_PI / 8)
        : MovementAction(botAI, "mimiron p3wx2 laser barrage action")
    {
        this->distance = distance;
        this->delta_angle = delta_angle;
    }
    virtual bool Execute(Event event);

protected:
    float distance, delta_angle;
};

class MimironRapidBurstAction : public MovementAction
{
public:
    MimironRapidBurstAction(PlayerbotAI* botAI) : MovementAction(botAI, "mimiron rapid burst action") {}

    bool Execute(Event event) override;
    bool isUseful() override;
};

class MimironAerialCommandUnitAction : public Action
{
public:
    MimironAerialCommandUnitAction(PlayerbotAI* botAI) : Action(botAI, "mimiron aerial command unit action") {}

    bool Execute(Event event) override;
};

class MimironRocketStrikeAction : public MovementAction
{
public:
    MimironRocketStrikeAction(PlayerbotAI* botAI) : MovementAction(botAI, "mimiron rocket strike action") {}

    bool Execute(Event event) override;
    bool isUseful() override;
};

class MimironPhase4MarkDpsAction : public Action
{
public:
    MimironPhase4MarkDpsAction(PlayerbotAI* botAI) : Action(botAI, "mimiron phase 4 mark dps action") {}

    bool Execute(Event event) override;
};

class MimironCheatAction : public Action
{
public:
    MimironCheatAction(PlayerbotAI* botAI) : Action(botAI, "mimiron cheat action") {}

    bool Execute(Event event) override;
};

class VezaxCheatAction : public Action
{
public:
    VezaxCheatAction(PlayerbotAI* botAI) : Action(botAI, "vezax cheat action") {}

    bool Execute(Event event) override;
};

class VezaxShadowCrashAction : public MovementAction
{
public:
    VezaxShadowCrashAction(PlayerbotAI* botAI) : MovementAction(botAI, "vezax shadow crash action") {}

    bool Execute(Event event) override;
};

class VezaxMarkOfTheFacelessAction : public MovementAction
{
public:
    VezaxMarkOfTheFacelessAction(PlayerbotAI* botAI) : MovementAction(botAI, "vezax mark of the faceless action") {}

    bool Execute(Event event) override;
};

class YoggSaronOminousCloudCheatAction : public Action
{
public:
    YoggSaronOminousCloudCheatAction(PlayerbotAI* botAI) : Action(botAI, "yogg-saron ominous cloud cheat action") {}

    bool Execute(Event event) override;
};

class YoggSaronGuardianPositioningAction : public MovementAction
{
public:
    YoggSaronGuardianPositioningAction(PlayerbotAI* botAI) : MovementAction(botAI, "yogg-saron guardian positioning action") {}

    bool Execute(Event event) override;
};

class YoggSaronSanityAction : public MovementAction
{
public:
    YoggSaronSanityAction(PlayerbotAI* botAI) : MovementAction(botAI, "yogg-saron sanity action") {}

    bool Execute(Event event) override;
};

class YoggSaronDeathOrbAction : public MoveAwayFromCreatureAction
{
public:
    YoggSaronDeathOrbAction(PlayerbotAI* botAI) : MoveAwayFromCreatureAction(botAI, "yogg-saron death orb action", NPC_DEATH_ORB, 10.0f) {}
};

class YoggSaronMaladyOfTheMindAction : public MoveAwayFromPlayerWithDebuffAction
{
public:
    YoggSaronMaladyOfTheMindAction(PlayerbotAI* botAI) : MoveAwayFromPlayerWithDebuffAction(botAI, "yogg-saron malady of the mind action", SPELL_MALADY_OF_THE_MIND, 15.0f) {}
};

class YoggSaronMarkTargetAction : public Action
{
public:
    YoggSaronMarkTargetAction(PlayerbotAI* botAI) : Action(botAI, "yogg-saron mark target action") {}

    bool Execute(Event event) override;
};

class YoggSaronBrainLinkAction : public MovementAction
{
public:
    YoggSaronBrainLinkAction(PlayerbotAI* botAI) : MovementAction(botAI, "yogg-saron brain link action") {}

    bool Execute(Event event) override;
};

class YoggSaronMoveToEnterPortalAction : public MovementAction
{
public:
    YoggSaronMoveToEnterPortalAction(PlayerbotAI* botAI) : MovementAction(botAI, "yogg-saron move to enter portal action") {}

    bool Execute(Event event) override;
};

class YoggSaronFallFromFloorAction : public MovementAction
{
public:
    YoggSaronFallFromFloorAction(PlayerbotAI* botAI) : MovementAction(botAI, "yogg-saron fall from floor action") {}

    bool Execute(Event event) override;
};

class YoggSaronBossRoomMovementCheatAction : public MovementAction
{
public:
    YoggSaronBossRoomMovementCheatAction(PlayerbotAI* botAI) : MovementAction(botAI, "yogg-saron boss room movement cheat action") {}

    bool Execute(Event event) override;
};

class YoggSaronUsePortalAction : public Action
{
public:
    YoggSaronUsePortalAction(PlayerbotAI* botAI) : Action(botAI, "yogg-saron use portal action") {}

    bool Execute(Event event) override;
};

class YoggSaronIllusionRoomAction : public MovementAction
{
public:
    YoggSaronIllusionRoomAction(PlayerbotAI* botAI) : MovementAction(botAI, "yogg-saron illusion room action") {}

    bool Execute(Event event) override;

private:
    bool SetRtiMark(YoggSaronTrigger yoggSaronTrigger);
    bool SetIllusionRtiTarget(YoggSaronTrigger yoggSaronTrigger);
    bool SetBrainRtiTarget(YoggSaronTrigger yoggSaronTrigger);
};

class YoggSaronMoveToExitPortalAction : public MovementAction
{
public:
    YoggSaronMoveToExitPortalAction(PlayerbotAI* botAI) : MovementAction(botAI, "yogg-saron move to exit portal action") {}

    bool Execute(Event event) override;
};

class YoggSaronLunaticGazeAction : public MovementAction
{
public:
    YoggSaronLunaticGazeAction(PlayerbotAI* botAI) : MovementAction(botAI, "yogg-saron lunatic gaze action") {}

    bool Execute(Event event) override;
};

class YoggSaronPhase3PositioningAction : public MovementAction
{
public:
    YoggSaronPhase3PositioningAction(PlayerbotAI* botAI) : MovementAction(botAI, "yogg-saron phase 3 positioning action") {}

    bool Execute(Event event) override;
};

// Shared

// Hold threat on a boss, or switch to the one this bot is meant to be hitting: the same job, told
// apart by its trigger.
class UldAttackCreatureAction : public AttackAction
{
public:
    UldAttackCreatureAction(
        PlayerbotAI* botAI, std::string const& name, std::vector<uint32> const& entries)
        : AttackAction(botAI, name), _entries(entries) {}
    bool Execute(Event event) override;

private:
    std::vector<uint32> const _entries;
};

// Takes an add and keeps it. The adds of this raid pick their own target rather than wait for
// threat: an Iron Construct copies Ignis's victim (BIG:126) and the Sanctum Sentries drag Auriaya
// into the fight from wherever they are (BAU:242-249), so a tank has to taunt them off.
class UldTankAttackNearestAddAction : public AttackAction
{
public:
    UldTankAttackNearestAddAction(
        PlayerbotAI* botAI, std::string const& name, char const* addsValue)
        : AttackAction(botAI, name), _addsValue(addsValue) {}
    bool Execute(Event event) override;

private:
    char const* const _addsValue;
};

class UldAttackNearestAddAction : public AttackAction
{
public:
    UldAttackNearestAddAction(PlayerbotAI* botAI, std::string const& name, char const* addsValue)
        : AttackAction(botAI, name), _addsValue(addsValue) {}
    bool Execute(Event event) override;

private:
    char const* const _addsValue;
};

class UldSpreadRangedAction : public MovementAction
{
public:
    UldSpreadRangedAction(
        PlayerbotAI* botAI, std::string const& name, std::vector<uint32> const& bossEntries)
        : MovementAction(botAI, name), _bossEntries(bossEntries) {}
    bool Execute(Event event) override;

private:
    std::vector<uint32> const _bossEntries;
};

class UldMoveAwayFromHazardAction : public MovementAction
{
public:
    UldMoveAwayFromHazardAction(
        PlayerbotAI* botAI, std::string const& name, char const* hazardValue, float radius)
        : MovementAction(botAI, name), _hazardValue(hazardValue), _radius(radius) {}
    bool Execute(Event event) override;

private:
    char const* const _hazardValue;
    float const _radius;
};

// XT-002 Deconstructor

// Damage dealt to the exposed heart is passed on to XT-002 (BXT:1003-1012), and for those 30
// seconds it is the only thing in the room that can be hit.
class Xt002AttackExposedHeartAction : public AttackAction
{
public:
    Xt002AttackExposedHeartAction(PlayerbotAI* botAI)
        : AttackAction(botAI, "xt-002 attack exposed heart") {}
    bool Execute(Event event) override;
};

// Walks the Gravity Bomb out of the raid, so that neither its damage nor the Void Zone it leaves
// behind lands where the raid is standing.
class Xt002MoveAwayFromRaidAction : public MovementAction
{
public:
    Xt002MoveAwayFromRaidAction(PlayerbotAI* botAI)
        : MovementAction(botAI, "xt-002 move away from raid") {}
    bool Execute(Event event) override;
};

// Ignis the Furnace Master

// Walks the Molten construct this tank is holding into the water, which is the only thing that
// turns it Brittle (BIG:161-166).
class IgnisDragMoltenConstructToWaterAction : public MovementAction
{
public:
    IgnisDragMoltenConstructToWaterAction(PlayerbotAI* botAI)
        : MovementAction(botAI, "ignis drag molten construct to water") {}
    bool Execute(Event event) override;
};

class IgnisAttackBrittleConstructAction : public AttackAction
{
public:
    IgnisAttackBrittleConstructAction(PlayerbotAI* botAI)
        : AttackAction(botAI, "ignis attack brittle construct") {}
    bool Execute(Event event) override;
};

// Auriaya

// Puts the raid's damage on one cat at a time: the Sentries buff each other while they live
// (BAU:255), so the longer they are up the harder they all hit.
class AuriayaAttackSanctumSentryAction : public AttackAction
{
public:
    AuriayaAttackSanctumSentryAction(PlayerbotAI* botAI)
        : AttackAction(botAI, "auriaya attack sanctum sentry") {}
    bool Execute(Event event) override;
};

// Algalon the Observer

// The second tank takes Algalon over before Phase Punch banishes the first one (BAL:1246).
class AlgalonTankSwapAction : public AttackAction
{
public:
    AlgalonTankSwapAction(PlayerbotAI* botAI) : AttackAction(botAI, "algalon tank swap") {}
    bool Execute(Event event) override;
};

// Walks into the nearest Black Hole, which is the only cover Big Bang leaves.
class AlgalonHideInBlackHoleAction : public MovementAction
{
public:
    AlgalonHideInBlackHoleAction(PlayerbotAI* botAI)
        : MovementAction(botAI, "algalon hide in black hole") {}
    bool Execute(Event event) override;
};

// Walks the Living Constellation that is chasing this bot into a Black Hole, which despawns both
// of them (BAL:1063-1078).
class AlgalonLeadConstellationToBlackHoleAction : public MovementAction
{
public:
    AlgalonLeadConstellationToBlackHoleAction(PlayerbotAI* botAI)
        : MovementAction(botAI, "algalon lead constellation to black hole") {}
    bool Execute(Event event) override;
};

#endif
