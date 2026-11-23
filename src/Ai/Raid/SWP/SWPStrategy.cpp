/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#include "SWPStrategy.h"
#include "EncounterHelpers.h"
#include "Playerbots.h"
#include "SWPHelpers.h"
#include "SWPMultipliers.h"

using namespace EncounterHelpers;
using namespace SwpHelpers;

void RaidSwpStrategy::InitTriggers(std::vector<TriggerNode*>& triggers)
{
    //
    // Kalecgos
    //

    // The fight runs in two realms at once: Kalecgos in his chamber, Sathrovarr in the Spectral
    // Realm below it. Neither can be reached from the other side, so the only thing a bot has to
    // get right is which of the two it is standing next to.
    triggers.push_back(new TriggerNode("kalecgos bot in spectral realm",
        { NextAction("kalecgos attack sathrovarr", ACTION_RAID + 1) }));

    triggers.push_back(new TriggerNode("kalecgos bot in dragon realm",
        { NextAction("kalecgos attack boss", ACTION_RAID) }));

    //
    // Brutallus
    //
    triggers.push_back(new TriggerNode("brutallus should be tanked",
        { NextAction("brutallus main tank attack boss", ACTION_RAID + 1) }));

    // Burn spreads to whoever is standing next to the burning player, so both sides of it move.
    triggers.push_back(new TriggerNode("brutallus bot is burning",
        { NextAction("brutallus break off from burn", ACTION_EMERGENCY + 7) }));

    triggers.push_back(new TriggerNode("brutallus bot near burning ally",
        { NextAction("brutallus break off from burn", ACTION_EMERGENCY + 7) }));

    triggers.push_back(new TriggerNode("brutallus bot has meteor slash",
        { NextAction("brutallus move behind boss", ACTION_RAID + 2) }));

    //
    // Felmyst
    //
    triggers.push_back(new TriggerNode("felmyst should be tanked",
        { NextAction("felmyst main tank attack boss", ACTION_RAID + 1) }));

    triggers.push_back(new TriggerNode("felmyst breath incoming",
        { NextAction("felmyst move out of breath path", ACTION_EMERGENCY + 7) }));

    triggers.push_back(new TriggerNode("felmyst bot near vapor trail",
        { NextAction("felmyst move away from vapor trail", ACTION_EMERGENCY + 7) }));

    triggers.push_back(new TriggerNode("felmyst unyielding dead spawned",
        { NextAction("felmyst attack unyielding dead", ACTION_RAID) }));

    triggers.push_back(new TriggerNode("felmyst attacking charmed ally",
        { NextAction("felmyst stop attacking charmed ally", ACTION_RAID + 4) }));

    triggers.push_back(new TriggerNode("felmyst ranged should spread",
        { NextAction("felmyst spread ranged", ACTION_MOVE + 2) }));

    //
    // Eredar Twins
    //
    triggers.push_back(new TriggerNode("eredar twins should be tanked",
        { NextAction("eredar twins assign tanks", ACTION_RAID + 1) }));

    triggers.push_back(new TriggerNode("eredar twins melee should attack lady sacrolash",
        { NextAction("eredar twins melee attack lady sacrolash", ACTION_RAID + 1) }));

    triggers.push_back(new TriggerNode("eredar twins casters should attack alythess",
        { NextAction("eredar twins caster attack alythess", ACTION_RAID + 1) }));

    triggers.push_back(new TriggerNode("eredar twins ranged should spread",
        { NextAction("eredar twins spread ranged", ACTION_MOVE + 2) }));

    //
    // M'uru and Entropius
    //
    triggers.push_back(new TriggerNode("m'uru should be tanked",
        { NextAction("m'uru main tank attack boss", ACTION_RAID + 1) }));

    // The Dark Fiends run at the raid and blow up, so they come first.
    triggers.push_back(new TriggerNode("m'uru dark fiends spawned",
        { NextAction("m'uru attack nearest dark fiend", ACTION_RAID + 2) }));

    triggers.push_back(new TriggerNode("m'uru void sentinel spawned",
        { NextAction("m'uru tank attack void sentinel", ACTION_RAID + 2) }));

    triggers.push_back(new TriggerNode("m'uru adds spawned",
        { NextAction("m'uru attack nearest add", ACTION_RAID) }));

    triggers.push_back(new TriggerNode("m'uru bot in darkness",
        { NextAction("m'uru move away from darkness", ACTION_EMERGENCY + 7) }));

    triggers.push_back(new TriggerNode("entropius should be tanked",
        { NextAction("entropius main tank attack boss", ACTION_RAID + 1) }));

    triggers.push_back(new TriggerNode("entropius bot near singularity",
        { NextAction("entropius move away from singularity", ACTION_EMERGENCY + 7) }));

    //
    // Kil'jaeden
    //
    triggers.push_back(new TriggerNode("kil'jaeden should be tanked",
        { NextAction("kil'jaeden main tank attack boss", ACTION_RAID + 1) }));

    // Armageddon drops meteors on marker creatures, which is the one mechanic of the fight that a
    // bot can see coming.
    triggers.push_back(new TriggerNode("kil'jaeden bot in armageddon",
        { NextAction("kil'jaeden move away from armageddon", ACTION_EMERGENCY + 7) }));

    triggers.push_back(new TriggerNode("kil'jaeden shield orb spawned",
        { NextAction("kil'jaeden attack shield orb", ACTION_RAID + 1) }));

    triggers.push_back(new TriggerNode("kil'jaeden sinister reflection spawned",
        { NextAction("kil'jaeden attack sinister reflection", ACTION_RAID + 2) }));

    triggers.push_back(new TriggerNode("kil'jaeden hands of the deceiver spawned",
        { NextAction("kil'jaeden attack hand of the deceiver", ACTION_RAID) }));

    triggers.push_back(new TriggerNode("kil'jaeden ranged should spread",
        { NextAction("kil'jaeden spread ranged", ACTION_MOVE + 2) }));
}

void RaidSwpStrategy::InitMultipliers(std::vector<Multiplier*>& multipliers)
{
    multipliers.push_back(new EredarTwinsMeleeTargetMultiplier(botAI));
    multipliers.push_back(new KalecgosWrongRealmTargetMultiplier(botAI));
}

void RaidSwpStrategy::AppendTargetExclusions(GuidSet& exclusions, TargetValueExclusionType /*type*/)
{
    Player* bot = botAI->GetBot();
    if (!IsEncounterInProgress(bot, SWP_MAP_ID))
        return;

    // Keep target selection inside the bot's own realm: the boss on the other side of the floor
    // cannot be damaged and holding it means standing idle.
    uint32 const unreachable =
        IsInSpectralRealm(bot) ? Id(SwpNpcs::NPC_KALECGOS) : Id(SwpNpcs::NPC_SATHROVARR);

    if (Unit* boss = FindThreatCreature(bot, unreachable))
        exclusions.insert(boss->GetGUID());
}
