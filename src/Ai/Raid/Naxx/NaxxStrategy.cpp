/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#include "NaxxStrategy.h"
#include "EncounterHelpers.h"
#include "NaxxHelpers.h"
#include "NaxxMultipliers.h"
#include "Playerbots.h"

void RaidNaxxStrategy::InitTriggers(std::vector<TriggerNode*>& triggers)
{
    // Grobbulus
    triggers.push_back(new TriggerNode("mutating injection melee",
        { NextAction("grobbulus move away", ACTION_RAID + 2) }
    ));

    triggers.push_back(new TriggerNode("mutating injection ranged",
        { NextAction("grobbulus go behind the boss", ACTION_RAID + 2) }
    ));

    triggers.push_back(new TriggerNode("mutating injection removed",
        { NextAction("grobbulus move center", ACTION_RAID + 1) }
    ));

    triggers.push_back(new TriggerNode("grobbulus cloud",
        { NextAction("rotate grobbulus", ACTION_RAID + 1) }
    ));

    // Heigan the Unclean
    triggers.push_back(new TriggerNode("heigan melee",
        { NextAction("heigan dance melee", ACTION_RAID + 1) }
    ));

    triggers.push_back(new TriggerNode("heigan ranged",
        { NextAction("heigan dance ranged", ACTION_RAID + 1) }
    ));

    // Kel'Thuzad
    triggers.push_back(
        new TriggerNode("kel'thuzad",
        {
            NextAction("kel'thuzad position", ACTION_RAID + 2),
            NextAction("kel'thuzad choose target", ACTION_RAID + 1)
        })
    );

    // Anub'Rekhan
    triggers.push_back(new TriggerNode("anub'rekhan",
        {
            NextAction("anub'rekhan position", ACTION_RAID + 2),
            NextAction("anub'rekhan choose target", ACTION_RAID + 1)
        }
    ));

     // Grand Widow Faerlina
     triggers.push_back(new TriggerNode("faerlina",
        { NextAction("avoid aoe", ACTION_RAID + 1) }
    ));

    // Maexxna
    triggers.push_back(
        new TriggerNode("maexxna",
        {
            NextAction("rear flank", ACTION_RAID + 1),
            NextAction("avoid aoe", ACTION_RAID + 1)
        })
    );

    triggers.push_back(new TriggerNode("maexxna web wrap present",
        { NextAction("maexxna free web wrap", ACTION_RAID + 2) }
    ));

    triggers.push_back(new TriggerNode("faerlina follower present",
        { NextAction("faerlina attack follower", ACTION_RAID + 2) }
    ));

    // Noth the Plaguebringer
    triggers.push_back(new TriggerNode("noth the plaguebringer should be tanked",
        { NextAction("noth the plaguebringer attack boss", ACTION_RAID + 1) }
    ));

    // Noth blinks away from his tank and drops his threat list every 30s in the 25 man version.
    triggers.push_back(new TriggerNode("noth the plaguebringer lost threat",
        { NextAction("taunt spell", ACTION_RAID + 3) }
    ));

    triggers.push_back(new TriggerNode("noth the plaguebringer skeletons should be tanked",
        { NextAction("noth the plaguebringer attack nearest skeleton", ACTION_RAID + 2) }
    ));

    // While he is on the balcony the waves are the whole fight.
    triggers.push_back(new TriggerNode("noth the plaguebringer balcony phase",
        { NextAction("noth the plaguebringer attack nearest skeleton", ACTION_RAID + 1) }
    ));

    // Gothik the Harvester
    triggers.push_back(new TriggerNode("gothik the harvester should be tanked",
        { NextAction("gothik the harvester attack boss", ACTION_RAID + 1) }
    ));

    // He drops his whole threat list every time he teleports between the two halves of the room.
    triggers.push_back(new TriggerNode("gothik the harvester lost threat",
        { NextAction("taunt spell", ACTION_RAID + 3) }
    ));

    triggers.push_back(new TriggerNode("gothik the harvester unrelenting adds should be tanked",
        { NextAction("gothik the harvester attack nearest unrelenting add", ACTION_RAID + 2) }
    ));

    triggers.push_back(new TriggerNode("gothik the harvester unrelenting adds spawned",
        { NextAction("gothik the harvester attack nearest unrelenting add", ACTION_RAID + 1) }
    ));

    triggers.push_back(new TriggerNode("gothik the harvester spectral adds should be tanked",
        { NextAction("gothik the harvester attack nearest spectral add", ACTION_RAID + 2) }
    ));

    triggers.push_back(new TriggerNode("gothik the harvester spectral adds spawned",
        { NextAction("gothik the harvester attack nearest spectral add", ACTION_RAID + 1) }
    ));

    // Patchwerk
    triggers.push_back(new TriggerNode("patchwerk should be tanked",
        { NextAction("patchwerk attack boss", ACTION_RAID + 1) }
    ));

    // Every Hateful Strike hands 500 threat to whoever it hits, which is how the boss changes hands.
    triggers.push_back(new TriggerNode("patchwerk lost threat",
        { NextAction("taunt spell", ACTION_RAID + 3) }
    ));

    // The assist tanks have to be inside melee range to be the ones the strike picks.
    triggers.push_back(new TriggerNode("patchwerk should be soaked",
        { NextAction("patchwerk attack boss", ACTION_RAID + 1) }
    ));

    triggers.push_back(new TriggerNode("patchwerk non-melee in hateful strike range",
        { NextAction("patchwerk back off from boss", ACTION_RAID + 2) }
    ));

    // Thaddius
    triggers.push_back(new TriggerNode("thaddius phase pet",
        { NextAction("thaddius attack nearest pet", ACTION_RAID + 1) }
    ));

    triggers.push_back(new TriggerNode("thaddius phase pet lose aggro",
        { NextAction("taunt spell", ACTION_RAID + 2) }
    ));

    triggers.push_back(new TriggerNode("thaddius phase transition",
        { NextAction("thaddius move to platform", ACTION_RAID + 1) }
    ));

    triggers.push_back(new TriggerNode("thaddius phase thaddius",
        { NextAction("thaddius move polarity", ACTION_RAID + 1) }
    ));

    // Instructor Razuvious
    triggers.push_back(new TriggerNode("razuvious tank",
        { NextAction("razuvious use obedience crystal", ACTION_RAID + 1) }
    ));

    triggers.push_back(new TriggerNode("razuvious nontank",
        { NextAction("razuvious target", ACTION_RAID + 1) }
    ));

    // four horsemen
    triggers.push_back(new TriggerNode("four horsemen attractors",
        { NextAction("four horsemen attract alternatively", ACTION_RAID + 1) }
    ));

    triggers.push_back(new TriggerNode("four horsemen except attractors",
        { NextAction("four horsemen attack in order", ACTION_RAID + 1) }
    ));

    // sapphiron
    triggers.push_back(new TriggerNode("sapphiron ground",
        { NextAction("sapphiron ground position", ACTION_RAID + 1) }
    ));

    triggers.push_back(new TriggerNode("sapphiron flight",
        { NextAction("sapphiron flight position", ACTION_RAID + 1) }
    ));

    // Gluth
    triggers.push_back(
        new TriggerNode("gluth",
        {
            NextAction("gluth choose target", ACTION_RAID + 1),
            NextAction("gluth position", ACTION_RAID + 1),
            NextAction("gluth slowdown", ACTION_RAID)
        })
    );

    triggers.push_back(new TriggerNode("gluth main tank mortal wound",
        { NextAction("taunt spell", ACTION_RAID + 1) }
    ));

    // Loatheb
    triggers.push_back(
        new TriggerNode("loatheb",
        {
            NextAction("loatheb position", ACTION_RAID + 1),
            NextAction("loatheb choose target", ACTION_RAID + 1)
        })
    );

}

void RaidNaxxStrategy::InitMultipliers(std::vector<Multiplier*>& multipliers)
{
    multipliers.push_back(new GrobbulusMultiplier(botAI));
    multipliers.push_back(new HeiganDanceMultiplier(botAI));
    multipliers.push_back(new LoathebGenericMultiplier(botAI));
    multipliers.push_back(new ThaddiusGenericMultiplier(botAI));
    multipliers.push_back(new SapphironGenericMultiplier(botAI));
    multipliers.push_back(new InstructorRazuviousGenericMultiplier(botAI));
    multipliers.push_back(new KelthuzadGenericMultiplier(botAI));
    multipliers.push_back(new AnubrekhanGenericMultiplier(botAI));
    multipliers.push_back(new FourHorsemenGenericMultiplier(botAI));
    multipliers.push_back(new NaxxDoNotAttackUnengageableBossMultiplier(
        botAI, "noth the plaguebringer do not attack from the balcony",
        NaxxHelpers::Id(NaxxHelpers::NaxxNpcs::NPC_NOTH)));
    multipliers.push_back(new NaxxDoNotAttackUnengageableBossMultiplier(
        botAI, "gothik the harvester do not attack unreachable boss",
        NaxxHelpers::Id(NaxxHelpers::NaxxNpcs::NPC_GOTHIK)));
    multipliers.push_back(new GluthGenericMultiplier(botAI));
}

// Target selection is what puts a bot on a boss in the first place, so the two bosses that spend
// part of their fight out of reach are taken out of it for as long as they are.
void RaidNaxxStrategy::AppendTargetExclusions(GuidSet& exclusions, TargetValueExclusionType /*type*/)
{
    Player* bot = botAI->GetBot();
    if (!EncounterHelpers::IsEncounterInProgress(bot, NAXX_MAP_ID))
        return;

    for (uint32 const entry : { NaxxHelpers::Id(NaxxHelpers::NaxxNpcs::NPC_NOTH),
                                NaxxHelpers::Id(NaxxHelpers::NaxxNpcs::NPC_GOTHIK) })
    {
        Unit* boss = NaxxHelpers::FindThreatCreature(bot, entry);
        if (boss && !NaxxHelpers::IsBossEngageable(botAI, boss))
            exclusions.insert(boss->GetGUID());
    }
}
