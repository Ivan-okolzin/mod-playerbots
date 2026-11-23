/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#ifndef PLAYERBOTS_NAXXTRIGGERS_H
#define PLAYERBOTS_NAXXTRIGGERS_H

#include "EncounterHelpers.h"
#include "EventMap.h"
#include "GenericTriggers.h"
#include "NaxxBossHelper.h"
#include "NaxxHelpers.h"
#include "PlayerbotAIConfig.h"
#include "Trigger.h"
#include <string>

class MutatingInjectionTrigger : public HasAuraTrigger
{
public:
    MutatingInjectionTrigger(PlayerbotAI* botAI) : HasAuraTrigger(botAI, "mutating injection", 1) {}
};

class MutatingInjectionMeleeTrigger : public MutatingInjectionTrigger
{
public:
    MutatingInjectionMeleeTrigger(PlayerbotAI* botAI) : MutatingInjectionTrigger(botAI) {}
    bool IsActive() override;
};

class MutatingInjectionRangedTrigger : public MutatingInjectionTrigger
{
public:
    MutatingInjectionRangedTrigger(PlayerbotAI* botAI) : MutatingInjectionTrigger(botAI) {}
    bool IsActive() override;
};

class AuraRemovedTrigger : public Trigger
{
public:
    AuraRemovedTrigger(PlayerbotAI* botAI, std::string name) : Trigger(botAI, name, 1)
    {
        this->prev_check = false;
    }
    virtual bool IsActive() override;

protected:
    bool prev_check;
};

class MutatingInjectionRemovedTrigger : public HasNoAuraTrigger
{
public:
    MutatingInjectionRemovedTrigger(PlayerbotAI* botAI) : HasNoAuraTrigger(botAI, "mutating injection") {}
    virtual bool IsActive();
};

class GrobbulusCloudTrigger : public Trigger
{
public:
    GrobbulusCloudTrigger(PlayerbotAI* botAI) : Trigger(botAI, "grobbulus cloud event"), last_cloud_ms(0) {}
    bool IsActive() override;

private:
    uint32 last_cloud_ms;
    static constexpr uint32 CloudRotationDelayMs = 15000;
};

class HeiganMeleeTrigger : public Trigger
{
public:
    explicit HeiganMeleeTrigger(PlayerbotAI* botAI) : Trigger(botAI, "heigan melee"), helper(botAI) {}
    bool IsActive() override;

private:
    HeiganBossHelper helper;
};

class HeiganRangedTrigger : public Trigger
{
public:
    explicit HeiganRangedTrigger(PlayerbotAI* botAI) : Trigger(botAI, "heigan ranged"), helper(botAI) {}
    bool IsActive() override;

private:
    HeiganBossHelper helper;
};

class RazuviousTankTrigger : public Trigger
{
public:
    RazuviousTankTrigger(PlayerbotAI* botAI) : Trigger(botAI, "instructor razuvious tank"), helper(botAI) {}
    bool IsActive() override;

private:
    RazuviousBossHelper helper;
};

class RazuviousNontankTrigger : public Trigger
{
public:
    RazuviousNontankTrigger(PlayerbotAI* botAI) : Trigger(botAI, "instructor razuvious non-tank"), helper(botAI) {}
    bool IsActive() override;

private:
    RazuviousBossHelper helper;
};

class KelthuzadTrigger : public Trigger
{
public:
    KelthuzadTrigger(PlayerbotAI* botAI) : Trigger(botAI, "kel'thuzad trigger"), helper(botAI) {}
    bool IsActive() override;

private:
    KelthuzadBossHelper helper;
};

class AnubrekhanTrigger : public Trigger
{
public:
    AnubrekhanTrigger(PlayerbotAI* botAI) : Trigger(botAI, "anub'rekhan") {}
    bool IsActive() override;
};

 class FaerlinaTrigger : public Trigger
 {
 public:
     FaerlinaTrigger(PlayerbotAI* botAI) : Trigger(botAI, "faerlina") {}
     bool IsActive() override;
 };

class MaexxnaTrigger : public Trigger
{
public:
    MaexxnaTrigger(PlayerbotAI* botAI) : Trigger(botAI, "maexxna") {}
    bool IsActive() override;
};

class ThaddiusPhasePetTrigger : public Trigger
{
public:
    ThaddiusPhasePetTrigger(PlayerbotAI* botAI) : Trigger(botAI, "thaddius phase pet"), helper(botAI) {}
    bool IsActive() override;

private:
    ThaddiusBossHelper helper;
};

class ThaddiusPhasePetLoseAggroTrigger : public ThaddiusPhasePetTrigger
{
public:
    ThaddiusPhasePetLoseAggroTrigger(PlayerbotAI* botAI) : ThaddiusPhasePetTrigger(botAI) {}
    virtual bool IsActive()
    {
        Unit* target = AI_VALUE(Unit*, "current target");
        return ThaddiusPhasePetTrigger::IsActive() && PlayerbotAI::IsTank(bot) && target && target->GetVictim() != bot;
    }
};

class ThaddiusPhaseTransitionTrigger : public Trigger
{
public:
    ThaddiusPhaseTransitionTrigger(PlayerbotAI* botAI) : Trigger(botAI, "thaddius phase transition"), helper(botAI) {}
    bool IsActive() override;

private:
    ThaddiusBossHelper helper;
};

class ThaddiusPhaseThaddiusTrigger : public Trigger
{
public:
    ThaddiusPhaseThaddiusTrigger(PlayerbotAI* botAI) : Trigger(botAI, "thaddius phase thaddius"), helper(botAI) {}
    bool IsActive() override;

private:
    ThaddiusBossHelper helper;
};

class FourHorsemenAttractorsTrigger : public Trigger
{
public:
    FourHorsemenAttractorsTrigger(PlayerbotAI* botAI) : Trigger(botAI, "four horsemen attractors"), helper(botAI) {}
    bool IsActive() override;

private:
    FourHorsemenBossHelper helper;
};

class FourHorsemenExceptAttractorsTrigger : public Trigger
{
public:
    FourHorsemenExceptAttractorsTrigger(PlayerbotAI* botAI) : Trigger(botAI, "four horsemen except attractors"), helper(botAI) {}
    bool IsActive() override;

private:
    FourHorsemenBossHelper helper;
};

class SapphironGroundTrigger : public Trigger
{
public:
    SapphironGroundTrigger(PlayerbotAI* botAI) : Trigger(botAI, "sapphiron ground"), helper(botAI) {}
    bool IsActive() override;

private:
    SapphironBossHelper helper;
};

class SapphironFlightTrigger : public Trigger
{
public:
    SapphironFlightTrigger(PlayerbotAI* botAI) : Trigger(botAI, "sapphiron flight"), helper(botAI) {}
    bool IsActive() override;

private:
    SapphironBossHelper helper;
};

class GluthTrigger : public Trigger
{
public:
    GluthTrigger(PlayerbotAI* botAI) : Trigger(botAI, "gluth trigger"), helper(botAI) {}
    bool IsActive() override;

private:
    GluthBossHelper helper;
};

class GluthMainTankMortalWoundTrigger : public Trigger
{
public:
    GluthMainTankMortalWoundTrigger(PlayerbotAI* botAI) : Trigger(botAI, "gluth main tank mortal wound trigger"), helper(botAI) {}
    bool IsActive() override;

private:
    GluthBossHelper helper;
};

class LoathebTrigger : public Trigger
{
public:
    LoathebTrigger(PlayerbotAI* botAI) : Trigger(botAI, "loatheb"), helper(botAI) {}
    bool IsActive() override;

private:
    LoathebBossHelper helper;
};

// Noth, Gothik and Patchwerk
//
// These three are written against observable state only, the way the rest of this raid is: the
// instance's own encounter flag gates every one of them, the boss is found by entry on the bot's
// threat list, and the adds come from cached grid searches (NaxxValueContext.h).

class NaxxEncounterTrigger : public Trigger
{
public:
    NaxxEncounterTrigger(PlayerbotAI* botAI, std::string const name, int32 checkInterval = 1)
        : Trigger(botAI, name, checkInterval) {}

    bool IsActive() final
    {
        return EncounterHelpers::IsEncounterInProgress(bot, NAXX_MAP_ID) && IsActiveInEncounter();
    }

protected:
    virtual bool IsActiveInEncounter() = 0;
};

// All three of these bosses want the same thing of the tank holding them: threat, and a boss that
// keeps hitting him. The role tells apart the main tank, who holds the boss, from the assist tanks,
// who stand in Patchwerk's melee range so that Hateful Strike has one of them to hit.
class NaxxBossShouldBeTankedTrigger : public NaxxEncounterTrigger
{
public:
    NaxxBossShouldBeTankedTrigger(
        PlayerbotAI* botAI, std::string const& name, uint32 bossEntry,
        NaxxHelpers::NaxxRole role = NaxxHelpers::NaxxRole::MainTank)
        : NaxxEncounterTrigger(botAI, name), _bossEntry(bossEntry), _role(role) {}

protected:
    bool IsActiveInEncounter() override;

private:
    uint32 const _bossEntry;
    NaxxHelpers::NaxxRole const _role;
};

// Noth's Blink and Gothik's teleport both wipe the whole threat list (BNO:224, BGO:436), and every
// Hateful Strike hands 500 threat to whoever it hit (BPA:145), so a tank that sees the boss
// swinging at a non-tank takes it back.
class NaxxBossLostThreatTrigger : public NaxxEncounterTrigger
{
public:
    NaxxBossLostThreatTrigger(PlayerbotAI* botAI, std::string const& name, uint32 bossEntry)
        : NaxxEncounterTrigger(botAI, name), _bossEntry(bossEntry) {}

protected:
    bool IsActiveInEncounter() override;

private:
    uint32 const _bossEntry;
};

// Noth's skeleton waves and Gothik's two halves of adds: creatures the raid kills on sight,
// differing only in who goes for them.
class NaxxAddsSpawnedTrigger : public NaxxEncounterTrigger
{
public:
    NaxxAddsSpawnedTrigger(
        PlayerbotAI* botAI, std::string const& name, char const* addsValue,
        NaxxHelpers::NaxxRole role, uint32 bossEntry)
        : NaxxEncounterTrigger(botAI, name), _addsValue(addsValue), _role(role),
          _bossEntry(bossEntry) {}

protected:
    bool IsActiveInEncounter() override;
    // Bounds the mechanic on the boss's side: true wherever the adds belong to the whole fight.
    virtual bool IsAddPhase(Unit* /*boss*/) { return true; }
    virtual Unit* FindAdd();

    char const* const _addsValue;

private:
    NaxxHelpers::NaxxRole const _role;
    uint32 const _bossEntry;
};

// While Noth is on his balcony there is nothing else to hit, so the damage dealers join the tanks
// on the waves instead of standing under a boss they cannot touch.
class NothBalconyAddsTrigger : public NaxxAddsSpawnedTrigger
{
public:
    NothBalconyAddsTrigger(PlayerbotAI* botAI, std::string const& name, NaxxHelpers::NaxxRole role)
        : NaxxAddsSpawnedTrigger(
              botAI, name, NaxxHelpers::NOTH_SKELETONS_VALUE, role,
              NaxxHelpers::Id(NaxxHelpers::NaxxNpcs::NPC_NOTH)) {}

protected:
    bool IsAddPhase(Unit* boss) override { return NaxxHelpers::IsNothOnBalcony(boss); }
};

// Gothik's gate cuts the room in two, and an add on the far side of it is unreachable however
// close it looks.
class GothikAddsSpawnedTrigger : public NaxxAddsSpawnedTrigger
{
public:
    GothikAddsSpawnedTrigger(
        PlayerbotAI* botAI, std::string const& name, char const* addsValue,
        NaxxHelpers::NaxxRole role)
        : NaxxAddsSpawnedTrigger(
              botAI, name, addsValue, role,
              NaxxHelpers::Id(NaxxHelpers::NaxxNpcs::NPC_GOTHIK)) {}

protected:
    Unit* FindAdd() override;
};

// Hateful Strike reaches 12.5 yards and picks the healthiest of the top threat players inside it
// (BPA:133), so everyone who does not have to be in there stays out.
class PatchwerkNonMeleeInStrikeRangeTrigger : public NaxxEncounterTrigger
{
public:
    PatchwerkNonMeleeInStrikeRangeTrigger(PlayerbotAI* botAI)
        : NaxxEncounterTrigger(botAI, "patchwerk non-melee in hateful strike range") {}

protected:
    bool IsActiveInEncounter() override;
};

#endif
