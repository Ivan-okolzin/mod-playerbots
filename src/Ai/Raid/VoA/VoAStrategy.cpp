/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#include "VoAStrategy.h"
#include "Action.h"
#include "VoAMultipliers.h"
#include "Strategy.h"
#include "Trigger.h"
#include "vector"

void RaidVoAStrategy::InitTriggers(std::vector<TriggerNode*>& triggers)
{
    //
    // Archavon the Stone Watcher
    triggers.push_back(new TriggerNode(
        "archavon attacking non tank",
        { NextAction("archavon taunt boss", ACTION_RAID + 2) }));
    //
    triggers.push_back(new TriggerNode(
        "archavon should be tanked",
        { NextAction("archavon main tank attack boss", ACTION_RAID + 1) }));

    triggers.push_back(new TriggerNode(
        "archavon ranged should spread",
        { NextAction("archavon spread ranged", ACTION_MOVE + 2) }));

    //
    // Emalon the Storm Watcher
    //
    triggers.push_back(new TriggerNode(
        "emalon should be tanked",
        { NextAction("emalon main tank attack boss", ACTION_RAID + 1) }));

    triggers.push_back(new TriggerNode(
        "emalon tempest minions spawned",
        { NextAction("emalon tank attack nearest minion", ACTION_RAID + 2) }));

    // The overcharged minion outranks every other target: it bursts ten stacks after it was
    // picked, and it comes back to full health on the way in.
    triggers.push_back(new TriggerNode(
        "emalon overcharged minion should be killed",
        { NextAction("emalon attack overcharged minion", ACTION_RAID + 3) }));

    triggers.push_back(new TriggerNode(
        "emalon ranged should spread",
        { NextAction("emalon spread ranged", ACTION_MOVE + 2) }));

    triggers.push_back(new TriggerNode(
        "emalon lighting nova trigger",
        { NextAction("emalon lighting nova action", ACTION_RAID + 1) }));

    triggers.push_back(new TriggerNode(
        "emalon mark boss trigger",
        { NextAction("emalon mark boss action", ACTION_RAID) }));

    triggers.push_back(new TriggerNode(
        "emalon overcharge trigger",
        { NextAction("emalon overcharge action", ACTION_RAID) }));

    triggers.push_back(new TriggerNode(
        "emalon fall from floor trigger",
        { NextAction("emalon fall from floor action", ACTION_RAID) }));

    triggers.push_back(new TriggerNode(
        "emalon nature resistance trigger",
        { NextAction("emalon nature resistance action", ACTION_RAID) }));

    //
    // Koralon the Flame Watcher
    //

    triggers.push_back(new TriggerNode(
        "koralon fire resistance trigger",
        { NextAction("koralon fire resistance action", ACTION_RAID) }));

    triggers.push_back(new TriggerNode(
        "koralon should be tanked",
        { NextAction("koralon main tank attack boss", ACTION_RAID + 1) }));

    triggers.push_back(new TriggerNode(
        "koralon burning breath incoming",
        { NextAction("koralon move behind koralon", ACTION_EMERGENCY + 7) }));

    triggers.push_back(new TriggerNode(
        "koralon ranged should spread",
        { NextAction("koralon spread ranged", ACTION_MOVE + 2) }));

    //
    // Toravon the Ice Watcher
    //
    triggers.push_back(new TriggerNode(
        "toravon should be tanked",
        { NextAction("toravon main tank attack boss", ACTION_RAID + 1) }));

    triggers.push_back(new TriggerNode(
        "toravon frozen orbs spawned",
        { NextAction("toravon attack nearest frozen orb", ACTION_RAID + 2) }));

    // The pursued player runs; everybody else only has to stay out of the orb's reach.
    triggers.push_back(new TriggerNode(
        "toravon bot pursued by frozen orb",
        { NextAction("toravon flee from frozen orb", ACTION_EMERGENCY + 6) }));

    triggers.push_back(new TriggerNode(
        "toravon bot near frozen orb",
        { NextAction("toravon move away from frozen orb", ACTION_EMERGENCY + 7) }));

    triggers.push_back(new TriggerNode(
        "toravon bot in freezing ground",
        { NextAction("toravon move out of freezing ground", ACTION_EMERGENCY + 7) }));
}

void RaidVoAStrategy::InitMultipliers(std::vector<Multiplier*>& multipliers)
{
    multipliers.push_back(new EmalonOverchargedMinionMultiplier(botAI));
}
