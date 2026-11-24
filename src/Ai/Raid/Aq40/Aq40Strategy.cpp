/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#include "Aq40Strategy.h"
#include "Aq40Multipliers.h"

void RaidAq40Strategy::InitTriggers(std::vector<TriggerNode*>& triggers)
{
    // Shared

    triggers.push_back(new TriggerNode("aq40 no encounter in progress",
        { NextAction("aq40 reset encounter states", ACTION_EMERGENCY + 10) }));

    //
    // The Prophet Skeram
    //
    triggers.push_back(new TriggerNode("the prophet skeram should be tanked",
        { NextAction("the prophet skeram main tank attack boss", ACTION_RAID + 1) }));

    triggers.push_back(new TriggerNode("the prophet skeram images spawned",
        { NextAction("the prophet skeram assist tank attack image", ACTION_RAID + 1) }));

    triggers.push_back(new TriggerNode("the prophet skeram should assign dps priority",
        { NextAction("the prophet skeram assign dps priority", ACTION_RAID) }));

    triggers.push_back(new TriggerNode("the prophet skeram attacking mind controlled ally",
        { NextAction("the prophet skeram stop attacking mind controlled ally", ACTION_RAID + 4) }));

    triggers.push_back(new TriggerNode("the prophet skeram ranged should spread",
        { NextAction("the prophet skeram spread ranged", ACTION_MOVE + 2) }));

    //
    // Silithid Royalty
    //
    triggers.push_back(new TriggerNode("bug trio targets should be tanked",
        { NextAction("bug trio assign tanks", ACTION_RAID + 1) }));

    triggers.push_back(new TriggerNode("bug trio should assign dps priority",
        { NextAction("bug trio assign dps priority", ACTION_RAID) }));

    triggers.push_back(new TriggerNode("bug trio bot in poison cloud",
        { NextAction("bug trio move out of poison cloud", ACTION_EMERGENCY + 7) }));

    triggers.push_back(new TriggerNode("bug trio brood spawned",
        { NextAction("bug trio attack nearest brood", ACTION_RAID) }));

    //
    // Battleguard Sartura
    //
    triggers.push_back(new TriggerNode("battleguard sartura should be tanked",
        { NextAction("battleguard sartura main tank attack boss", ACTION_RAID + 1) }));

    triggers.push_back(new TriggerNode("battleguard sartura royal guards should be tanked",
        { NextAction("battleguard sartura assist tank attack guard", ACTION_RAID + 1) }));

    triggers.push_back(new TriggerNode("battleguard sartura melee in whirlwind range",
        { NextAction("battleguard sartura melee back off", ACTION_RAID + 2) }));

    triggers.push_back(new TriggerNode("battleguard sartura should assign dps priority",
        { NextAction("battleguard sartura assign dps priority", ACTION_RAID) }));

    //
    // Fankriss the Unyielding
    //
    triggers.push_back(new TriggerNode("fankriss the unyielding should be tanked",
        { NextAction("fankriss the unyielding main tank attack boss", ACTION_RAID + 1) }));

    triggers.push_back(new TriggerNode("fankriss the unyielding main tank has mortal wound stacks",
        { NextAction("fankriss the unyielding tank swap", ACTION_RAID + 3) }));

    triggers.push_back(new TriggerNode("fankriss the unyielding worms spawned",
        { NextAction("fankriss the unyielding attack worms", ACTION_RAID) }));

    //
    triggers.push_back(new TriggerNode("fankriss the unyielding spawns present",
        { NextAction("fankriss the unyielding attack spawns", ACTION_RAID + 1) }));

    // Viscidus
    //
    triggers.push_back(new TriggerNode("viscidus frozen",
        { NextAction("viscidus attack frozen boss", ACTION_RAID + 3) }));

    triggers.push_back(new TriggerNode("viscidus in frost phase",
        { NextAction("viscidus cast frost spell", ACTION_RAID + 3) }));

    triggers.push_back(new TriggerNode("viscidus globs spawned",
        { NextAction("viscidus attack nearest glob", ACTION_RAID) }));

    triggers.push_back(new TriggerNode("viscidus ranged should spread",
        { NextAction("viscidus spread ranged", ACTION_MOVE + 2) }));

    //
    // Princess Huhuran
    //
    triggers.push_back(new TriggerNode("princess huhuran should be tanked",
        { NextAction("princess huhuran main tank attack boss", ACTION_RAID + 1) }));

    triggers.push_back(new TriggerNode("princess huhuran bot in noxious poison",
        { NextAction("princess huhuran move out of noxious poison", ACTION_EMERGENCY + 7) }));

    triggers.push_back(new TriggerNode("princess huhuran ranged should spread",
        { NextAction("princess huhuran spread ranged", ACTION_MOVE + 2) }));

    //
    // Twin Emperors
    //
    triggers.push_back(new TriggerNode("twin emperors should be tanked apart",
        { NextAction("twin emperors tank position boss", ACTION_RAID + 2) }));

    triggers.push_back(new TriggerNode("twin emperors melee should attack vek'nilash",
        { NextAction("twin emperors melee attack vek'nilash", ACTION_RAID + 1) }));

    triggers.push_back(new TriggerNode("twin emperors casters should attack vek'lor",
        { NextAction("twin emperors caster attack vek'lor", ACTION_RAID + 1) }));

    triggers.push_back(new TriggerNode("twin emperors bot in blizzard",
        { NextAction("twin emperors move out of blizzard", ACTION_EMERGENCY + 7) }));

    //
    // Ouro
    //
    triggers.push_back(new TriggerNode("ouro should be tanked",
        { NextAction("ouro main tank attack boss", ACTION_RAID + 1) }));

    // Sweep and Sand Blast come out of his front, and the base rear flank action already does
    // exactly what melee need here.
    triggers.push_back(new TriggerNode("ouro melee in front of boss",
        { NextAction("rear flank", ACTION_MOVE + 2) }));

    triggers.push_back(new TriggerNode("ouro ranged should spread",
        { NextAction("ouro spread ranged", ACTION_MOVE + 2) }));

    triggers.push_back(new TriggerNode("ouro submerged",
        { NextAction("ouro spread from dirt mounds", ACTION_RAID + 2) }));

    triggers.push_back(new TriggerNode("ouro scarabs spawned",
        { NextAction("ouro attack nearest scarab", ACTION_RAID) }));

    //
    // C'Thun
    //

    // Phase 1: the Eye. It cannot be tanked (it never moves and has no melee), so the raid's whole
    // job is dodging the Dark Glare and clearing tentacles.
    triggers.push_back(new TriggerNode("eye of c'thun dark glare incoming",
        { NextAction("eye of c'thun move out of dark glare", ACTION_EMERGENCY + 7) }));

    triggers.push_back(new TriggerNode("eye of c'thun claw tentacle spawned",
        { NextAction("eye of c'thun attack claw tentacle", ACTION_RAID) }));

    triggers.push_back(new TriggerNode("eye of c'thun ranged should spread",
        { NextAction("eye of c'thun spread ranged", ACTION_MOVE + 2) }));

    // Both phases spawn Eye Tentacles in rings around the room.
    triggers.push_back(new TriggerNode("c'thun eye tentacles spawned",
        { NextAction("c'thun attack nearest eye tentacle", ACTION_RAID) }));

    // Phase 2. The Giant Claw Tentacle submerges and reappears under someone else unless a tank
    // is in its melee range within ten seconds (boss_cthun.cpp:693).
    triggers.push_back(new TriggerNode("c'thun giant claw tentacle spawned",
        { NextAction("c'thun tank attack giant claw tentacle", ACTION_RAID + 2) }));

    // It chain casts the Eye's beam and, unlike the boss, can be stunned and interrupted.
    triggers.push_back(new TriggerNode("c'thun giant eye tentacle spawned",
        { NextAction("c'thun attack giant eye tentacle", ACTION_RAID + 1) }));

    triggers.push_back(new TriggerNode("c'thun body is weakened",
        { NextAction("c'thun attack body", ACTION_RAID + 3) }));

    triggers.push_back(new TriggerNode("c'thun bot in stomach with flesh tentacle",
        { NextAction("c'thun attack flesh tentacle", ACTION_RAID + 4) }));

    triggers.push_back(new TriggerNode("c'thun bot should leave stomach",
        { NextAction("c'thun leave stomach", ACTION_RAID + 4) }));

    triggers.push_back(new TriggerNode("c'thun ranged should spread",
        { NextAction("c'thun spread ranged", ACTION_MOVE + 2) }));
}

void RaidAq40Strategy::InitMultipliers(std::vector<Multiplier*>& multipliers)
{
    multipliers.push_back(new HuhuranDoNotDispelWyvernStingMultiplier(botAI));
    multipliers.push_back(new TwinEmperorsMeleeTargetMultiplier(botAI));
    multipliers.push_back(new CthunDoNotAttackCarapacedBodyMultiplier(botAI));
}
