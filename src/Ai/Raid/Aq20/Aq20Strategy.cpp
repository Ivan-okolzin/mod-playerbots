/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#include "Aq20Strategy.h"
#include "Aq20Multipliers.h"
#include "Playerbots.h"

void RaidAq20Strategy::InitTriggers(std::vector<TriggerNode*>& triggers)
{
    //
    // Kurinnaxx
    //
    triggers.push_back(new TriggerNode("kurinnaxx should be tanked",
        { NextAction("kurinnaxx main tank attack boss", ACTION_RAID + 1) }));

    // Mortal Wound stacks a healing penalty on whoever he is hitting (KUR:54).
    triggers.push_back(new TriggerNode("kurinnaxx main tank has mortal wound stacks",
        { NextAction("kurinnaxx tank swap", ACTION_RAID + 3) }));

    triggers.push_back(new TriggerNode("kurinnaxx bot in sand trap",
        { NextAction("kurinnaxx move away from sand trap", ACTION_EMERGENCY + 7) }));

    //
    // General Rajaxx
    //
    // Thundercrash halves everyone's health and wipes his threat list with it (RAJ:116-118), so
    // the only thing the raid can do about it is take him back afterwards.
    triggers.push_back(new TriggerNode("general rajaxx should be tanked",
        { NextAction("general rajaxx main tank attack boss", ACTION_RAID + 1) }));

    //
    // Moam
    //
    triggers.push_back(new TriggerNode("moam should be tanked",
        { NextAction("moam main tank attack boss", ACTION_RAID + 1) }));

    // His stone phase ends as soon as the last Mana Fiend dies (MOA:87-93), which is the only way
    // to end it before his mana fills and Arcane Eruption goes off.
    triggers.push_back(new TriggerNode("moam mana fiends spawned",
        { NextAction("moam attack nearest mana fiend", ACTION_RAID + 2) }));

    //
    // Buru the Gorger
    //
    // Only the fixated bot can bring Buru onto an egg, and nothing else in the egg phase matters
    // as much, so it outranks holding a boss.
    triggers.push_back(new TriggerNode("buru the gorger bot is fixated",
        { NextAction("buru the gorger lure boss to egg", ACTION_RAID + 4) }));

    triggers.push_back(new TriggerNode("buru the gorger egg should be killed",
        { NextAction("buru the gorger attack target egg", ACTION_RAID + 2) }));

    triggers.push_back(new TriggerNode("buru the gorger hatchlings spawned",
        { NextAction("buru the gorger attack nearest hatchling", ACTION_RAID) }));

    triggers.push_back(new TriggerNode("buru the gorger should be tanked",
        { NextAction("buru the gorger main tank attack boss", ACTION_RAID + 1) }));

    //
    // Ayamiss the Hunter
    //
    // The Larva feeds on the player Paralyze pinned at the altar (AYA:224), so it comes first.
    triggers.push_back(new TriggerNode("ayamiss the hunter larvae spawned",
        { NextAction("ayamiss the hunter attack nearest larva", ACTION_RAID + 3) }));

    triggers.push_back(new TriggerNode("ayamiss the hunter swarmers spawned",
        { NextAction("ayamiss the hunter attack nearest swarmer", ACTION_RAID) }));

    triggers.push_back(new TriggerNode("ayamiss the hunter should be tanked",
        { NextAction("ayamiss the hunter main tank attack boss", ACTION_RAID + 2) }));

    //
    // Ossirian the Unscarred
    //
    // Strength of Ossirian comes straight back whenever no weakness is left on him (OSS:273-277),
    // and only a crystal takes it off, so walking him to the next one outranks everything else
    // the tank does.
    triggers.push_back(new TriggerNode("ossirian the unscarred crystal should be used",
        { NextAction("ossirian the unscarred use crystal", ACTION_RAID + 5) }));

    triggers.push_back(new TriggerNode("ossirian the unscarred tank should move to crystal",
        { NextAction("ossirian the unscarred tank move to crystal", ACTION_RAID + 4) }));

    triggers.push_back(new TriggerNode("ossirian the unscarred should be tanked",
        { NextAction("ossirian the unscarred main tank attack boss", ACTION_RAID + 1) }));

    triggers.push_back(new TriggerNode("ossirian the unscarred bot near sand vortex",
        { NextAction("ossirian the unscarred move away from sand vortex",
            ACTION_EMERGENCY + 7) }));
}

void RaidAq20Strategy::InitMultipliers(std::vector<Multiplier*>& multipliers)
{
    multipliers.push_back(new MoamStonePhaseTargetMultiplier(botAI));
    multipliers.push_back(new BuruThornsTargetMultiplier(botAI));
    multipliers.push_back(new AyamissAirPhaseTargetMultiplier(botAI));
}
