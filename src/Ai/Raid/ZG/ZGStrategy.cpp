/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#include "ZGStrategy.h"
#include "ZGHelpers.h"
#include "ZGMultipliers.h"

using namespace ZulGurubHelpers;

void RaidZulGurubStrategy::InitTriggers(std::vector<TriggerNode*>& triggers)
{
    // Shared

    triggers.push_back(new TriggerNode("zg no encounter in progress",
        { NextAction("zg reset encounter states", ACTION_EMERGENCY + 10) }));

    // Blood Siphon turns the poison of a dying Son of Hakkar into damage on Hakkar, and strips it
    // again afterwards, so the raid walks back into a cloud between pulls. Out of combat only.
    triggers.push_back(new TriggerNode("zg bot should pick up poisonous blood",
        { NextAction("zg move into poisonous cloud", ACTION_MOVE + 3) }));

    //
    // High Priest Venoxis
    //
    triggers.push_back(new TriggerNode("high priest venoxis should be tanked",
        { NextAction("high priest venoxis main tank attack boss", ACTION_RAID + 1) }));

    triggers.push_back(new TriggerNode("high priest venoxis lost threat",
        { NextAction("high priest venoxis tank taunt boss", ACTION_RAID + 3) }));

    triggers.push_back(new TriggerNode("high priest venoxis serpents spawned",
        { NextAction("high priest venoxis attack nearest serpent", ACTION_RAID) }));

    triggers.push_back(new TriggerNode("high priest venoxis bot in poison cloud",
        { NextAction("high priest venoxis move out of poison cloud", ACTION_EMERGENCY + 7) }));

    //
    // High Priestess Jeklik
    //
    triggers.push_back(new TriggerNode("high priestess jeklik should be tanked",
        { NextAction("high priestess jeklik main tank attack boss", ACTION_RAID + 1) }));

    triggers.push_back(new TriggerNode("high priestess jeklik lost threat",
        { NextAction("high priestess jeklik tank taunt boss", ACTION_RAID + 3) }));

    triggers.push_back(new TriggerNode("high priestess jeklik bats spawned",
        { NextAction("high priestess jeklik attack nearest bat", ACTION_RAID) }));

    triggers.push_back(new TriggerNode("high priestess jeklik bot in liquid fire",
        { NextAction("high priestess jeklik move out of liquid fire", ACTION_EMERGENCY + 7) }));

    //
    // High Priestess Mar'li
    //
    triggers.push_back(new TriggerNode("high priestess mar'li should be tanked",
        { NextAction("high priestess mar'li main tank attack boss", ACTION_RAID + 1) }));

    triggers.push_back(new TriggerNode("high priestess mar'li lost threat",
        { NextAction("high priestess mar'li tank taunt boss", ACTION_RAID + 3) }));

    // A Spawn of Mar'li is harmless for its first twenty seconds and hits like an add afterwards,
    // so the raid kills them as they hatch.
    triggers.push_back(new TriggerNode("high priestess mar'li spawns hatched",
        { NextAction("high priestess mar'li attack nearest spawn", ACTION_RAID + 1) }));

    //
    // Bloodlord Mandokir
    //
    triggers.push_back(new TriggerNode("bloodlord mandokir should be tanked",
        { NextAction("bloodlord mandokir main tank attack boss", ACTION_RAID + 1) }));

    triggers.push_back(new TriggerNode("bloodlord mandokir lost threat",
        { NextAction("bloodlord mandokir tank taunt boss", ACTION_RAID + 3) }));

    // Above everything else of this fight: a watched bot that earns threat is charged for it.
    triggers.push_back(new TriggerNode("bloodlord mandokir bot is watched",
        { NextAction("bloodlord mandokir stop attacking while watched", ACTION_RAID + 5) }));

    triggers.push_back(new TriggerNode("bloodlord mandokir ohgan should be tanked",
        { NextAction("bloodlord mandokir assist tank attack ohgan", ACTION_RAID + 2) }));

    // Ohgan sunders whoever holds him and buffs Mandokir when he dies, and the raid takes the
    // buff over the raptor.
    triggers.push_back(new TriggerNode("bloodlord mandokir ohgan spawned",
        { NextAction("bloodlord mandokir attack ohgan", ACTION_RAID + 2) }));

    triggers.push_back(new TriggerNode("bloodlord mandokir melee in whirlwind range",
        { NextAction("bloodlord mandokir melee back off", ACTION_RAID + 2) }));

    //
    // High Priest Thekal
    //
    // The main tank keeps Thekal in both phases; the trigger's own guard drops him while he is
    // flagged out of reach playing dead.
    triggers.push_back(new TriggerNode("high priest thekal should be tanked",
        { NextAction("high priest thekal main tank attack boss", ACTION_RAID + 1) }));

    triggers.push_back(new TriggerNode("high priest thekal zealots should be tanked",
        { NextAction("high priest thekal assist tank attack zealot", ACTION_RAID + 1) }));

    // All three have to die together, so the raid keeps their health bars level instead of
    // focusing one of them down.
    triggers.push_back(new TriggerNode("high priest thekal should balance trio damage",
        { NextAction("high priest thekal attack healthiest trio target", ACTION_RAID + 1) }));

    triggers.push_back(new TriggerNode("high priest thekal lost threat",
        { NextAction("high priest thekal tank taunt boss", ACTION_RAID + 3) }));

    triggers.push_back(new TriggerNode("high priest thekal tigers spawned",
        { NextAction("high priest thekal attack nearest tiger", ACTION_RAID) }));

    //
    // High Priestess Arlokk
    //
    triggers.push_back(new TriggerNode("high priestess arlokk should be tanked",
        { NextAction("high priestess arlokk main tank attack boss", ACTION_RAID + 1) }));

    triggers.push_back(new TriggerNode("high priestess arlokk lost threat",
        { NextAction("high priestess arlokk tank taunt boss", ACTION_RAID + 3) }));

    // The prowlers are what the raid fights while she stalks the room.
    triggers.push_back(new TriggerNode("high priestess arlokk prowlers spawned",
        { NextAction("high priestess arlokk attack nearest prowler", ACTION_RAID) }));

    //
    // Jin'do the Hexxer
    //
    triggers.push_back(new TriggerNode("jin'do the hexxer should be tanked",
        { NextAction("jin'do the hexxer main tank attack boss", ACTION_RAID + 1) }));

    // The ward heals Jin'do every three seconds, which outlasts the raid's damage.
    triggers.push_back(new TriggerNode("jin'do the hexxer healing ward spawned",
        { NextAction("jin'do the hexxer attack healing ward", ACTION_RAID + 3) }));

    triggers.push_back(new TriggerNode("jin'do the hexxer brain wash totem spawned",
        { NextAction("jin'do the hexxer attack brain wash totem", ACTION_RAID + 2) }));

    triggers.push_back(new TriggerNode("jin'do the hexxer shades spawned",
        { NextAction("jin'do the hexxer attack nearest shade", ACTION_RAID) }));

    triggers.push_back(new TriggerNode("jin'do the hexxer hexed the tank",
        { NextAction("jin'do the hexxer assist tank taunt boss", ACTION_RAID + 4) }));

    //
    // Hakkar
    //
    triggers.push_back(new TriggerNode("hakkar should be tanked",
        { NextAction("hakkar main tank attack boss", ACTION_RAID + 1) }));

    triggers.push_back(new TriggerNode("hakkar lost threat",
        { NextAction("hakkar tank taunt boss", ACTION_RAID + 3) }));

    triggers.push_back(new TriggerNode("hakkar attacking insane ally",
        { NextAction("hakkar stop attacking insane ally", ACTION_RAID + 4) }));

    //
    // Gahz'ranka
    //
    triggers.push_back(new TriggerNode("gahz'ranka should be tanked",
        { NextAction("gahz'ranka main tank attack boss", ACTION_RAID + 1) }));

    triggers.push_back(new TriggerNode("gahz'ranka lost threat",
        { NextAction("gahz'ranka tank taunt boss", ACTION_RAID + 3) }));

    //
    // Edge of Madness: one of Gri'lek, Hazza'rah, Renataki, or Wushoolay, chosen by the active
    // game event, so only one of these four sets is ever live in an instance.
    //
    triggers.push_back(new TriggerNode("gri'lek should be tanked",
        { NextAction("gri'lek main tank attack boss", ACTION_RAID + 1) }));

    triggers.push_back(new TriggerNode("gri'lek lost threat",
        { NextAction("gri'lek tank taunt boss", ACTION_RAID + 3) }));

    triggers.push_back(new TriggerNode("gri'lek bot is pursued",
        { NextAction("gri'lek run from boss", ACTION_EMERGENCY + 7) }));

    triggers.push_back(new TriggerNode("hazza'rah should be tanked",
        { NextAction("hazza'rah main tank attack boss", ACTION_RAID + 1) }));

    triggers.push_back(new TriggerNode("hazza'rah illusions spawned",
        { NextAction("hazza'rah attack nearest illusion", ACTION_RAID) }));

    triggers.push_back(new TriggerNode("hazza'rah ranged should spread",
        { NextAction("hazza'rah spread ranged", ACTION_MOVE + 2) }));

    triggers.push_back(new TriggerNode("renataki should be tanked",
        { NextAction("renataki main tank attack boss", ACTION_RAID + 1) }));

    triggers.push_back(new TriggerNode("renataki lost threat",
        { NextAction("renataki tank taunt boss", ACTION_RAID + 3) }));

    triggers.push_back(new TriggerNode("wushoolay should be tanked",
        { NextAction("wushoolay main tank attack boss", ACTION_RAID + 1) }));

    triggers.push_back(new TriggerNode("wushoolay bot in lightning cloud",
        { NextAction("wushoolay move out of lightning cloud", ACTION_EMERGENCY + 7) }));

    triggers.push_back(new TriggerNode("wushoolay ranged should spread",
        { NextAction("wushoolay spread ranged", ACTION_MOVE + 2) }));
}

void RaidZulGurubStrategy::InitMultipliers(std::vector<Multiplier*>& multipliers)
{
    multipliers.push_back(new HakkarKeepPoisonousBloodMultiplier(botAI));
    multipliers.push_back(new MandokirWatchHoldMultiplier(botAI));
    multipliers.push_back(new ZulGurubDoNotAttackUnassailableBossMultiplier(
        botAI, "high priestess arlokk do not chase stalking boss",
        Id(ZulGurubNpcs::NPC_ARLOKK)));
    multipliers.push_back(new ZulGurubDoNotAttackUnassailableBossMultiplier(
        botAI, "high priest thekal do not attack feigned death",
        Id(ZulGurubNpcs::NPC_THEKAL)));
}
