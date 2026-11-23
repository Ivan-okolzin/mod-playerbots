/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#include "CrusaderStrategy.h"
#include "CrusaderMultipliers.h"
#include "Playerbots.h"

void RaidCrusaderStrategy::InitTriggers(std::vector<TriggerNode*>& triggers)
{
    //
    // Northrend Beasts: Gormok the Impaler
    //
    triggers.push_back(new TriggerNode("gormok the impaler should be tanked",
        { NextAction("gormok the impaler main tank attack boss", ACTION_RAID + 1) }));

    // A Snobold rides a raid member and silences it; both the carrier and the ranged go for it.
    triggers.push_back(new TriggerNode("gormok the impaler snobold on raid member",
        { NextAction("gormok the impaler attack nearest snobold", ACTION_RAID + 2) }));

    triggers.push_back(new TriggerNode("gormok the impaler bot is snobolled",
        { NextAction("gormok the impaler attack nearest snobold", ACTION_RAID + 2) }));

    triggers.push_back(new TriggerNode("gormok the impaler main tank has impale stacks",
        { NextAction("gormok the impaler tank swap", ACTION_RAID + 3) }));

    //
    // Northrend Beasts: Acidmaw and Dreadscale
    //
    triggers.push_back(new TriggerNode("acidmaw and dreadscale should be tanked",
        { NextAction("acidmaw and dreadscale assign tanks", ACTION_RAID + 1) }));

    triggers.push_back(new TriggerNode("acidmaw and dreadscale bot in slime pool",
        { NextAction("acidmaw and dreadscale move away from slime pool", ACTION_EMERGENCY + 7) }));

    //
    // Northrend Beasts: Icehowl
    //
    triggers.push_back(new TriggerNode("icehowl should be tanked",
        { NextAction("icehowl main tank attack boss", ACTION_RAID + 1) }));

    // Trample kills whoever the charge runs through, and it is aimed down the lane the stalker
    // stands in.
    triggers.push_back(new TriggerNode("icehowl charge incoming",
        { NextAction("icehowl move out of charge path", ACTION_EMERGENCY + 7) }));

    triggers.push_back(new TriggerNode("icehowl bot near arena wall",
        { NextAction("icehowl move away from arena wall", ACTION_MOVE + 3) }));

    triggers.push_back(new TriggerNode("icehowl ranged should spread",
        { NextAction("icehowl spread ranged", ACTION_MOVE + 2) }));

    //
    // Lord Jaraxxus
    //
    triggers.push_back(new TriggerNode("lord jaraxxus should be tanked",
        { NextAction("lord jaraxxus main tank attack boss", ACTION_RAID + 1) }));

    triggers.push_back(new TriggerNode("lord jaraxxus bot in legion flame",
        { NextAction("lord jaraxxus move away from legion flame", ACTION_EMERGENCY + 7) }));

    // Mistress of Pain and the Felflame Infernals both beat on whoever they land next to, so the
    // tanks take them off the raid.
    triggers.push_back(new TriggerNode("lord jaraxxus demon spawned",
        { NextAction("lord jaraxxus tank attack nearest demon", ACTION_RAID + 2) }));

    triggers.push_back(new TriggerNode("lord jaraxxus ranged should spread",
        { NextAction("lord jaraxxus spread ranged", ACTION_MOVE + 2) }));

    //
    // Faction Champions
    //
    triggers.push_back(new TriggerNode("faction champions should focus target",
        { NextAction("faction champions attack focus target", ACTION_RAID + 2) }));

    //
    // Twin Val'kyr
    //
    // Nothing else in this fight works without an essence, so it outranks holding a boss.
    triggers.push_back(new TriggerNode("twin val'kyr bot has no essence",
        { NextAction("twin val'kyr take essence", ACTION_RAID + 5) }));

    triggers.push_back(new TriggerNode("twin val'kyr should be tanked",
        { NextAction("twin val'kyr assign tanks", ACTION_RAID + 1) }));

    triggers.push_back(new TriggerNode("twin val'kyr pact incoming",
        { NextAction("twin val'kyr attack pacting twin", ACTION_RAID + 4) }));

    triggers.push_back(new TriggerNode("twin val'kyr bot near opposite ball",
        { NextAction("twin val'kyr move away from ball", ACTION_EMERGENCY + 7) }));

    triggers.push_back(new TriggerNode("twin val'kyr matching ball nearby",
        { NextAction("twin val'kyr collect matching ball", ACTION_MOVE + 2) }));

    //
    // Anub'arak
    //
    triggers.push_back(new TriggerNode("anub'arak should be tanked",
        { NextAction("anub'arak main tank attack boss", ACTION_RAID + 1) }));

    // Permafrost is the only thing that stops the spike; outrunning it is what is left until a
    // Frost Sphere has been brought down.
    triggers.push_back(new TriggerNode("anub'arak bot pursued by spike",
        { NextAction("anub'arak flee to permafrost", ACTION_EMERGENCY + 7),
          NextAction("anub'arak flee from spike", ACTION_EMERGENCY + 6) }));

    triggers.push_back(new TriggerNode("anub'arak bot near pursuing spike",
        { NextAction("anub'arak move away from spike", ACTION_EMERGENCY + 7) }));

    triggers.push_back(new TriggerNode("anub'arak frost sphere should be dropped",
        { NextAction("anub'arak shoot down frost sphere", ACTION_RAID + 3) }));

    triggers.push_back(new TriggerNode("anub'arak burrowers spawned",
        { NextAction("anub'arak attack nearest burrower", ACTION_RAID + 2) }));

    triggers.push_back(new TriggerNode("anub'arak scarabs spawned",
        { NextAction("anub'arak attack nearest scarab", ACTION_RAID) }));
}

void RaidCrusaderStrategy::InitMultipliers(std::vector<Multiplier*>& multipliers)
{
    multipliers.push_back(new FactionChampionsFocusTargetMultiplier(botAI));
    multipliers.push_back(new ValkyrPactTargetMultiplier(botAI));
}
