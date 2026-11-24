/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#include "MCStrategy.h"
#include "MCHelpers.h"
#include "MCMultipliers.h"
#include "Playerbots.h"
#include "RtiTargetValue.h"
#include "Strategy.h"
#include <array>

using namespace MoltenCoreHelpers;

namespace
{

// Four bosses stand behind adds the raid has to clear first, and the pairs are the same shape:
// kill the adds, then the boss. Lucifron's Protectors charm a raid member every few seconds
// (SS 12119:0), Gehennas's Flamewakers stun and sunder the tanks (SS 11661:1, :2), Garr's Firesworn
// enrage him on every death and gain 300% damage if dragged more than 40 yards from him (BGA:139,
// :158), and Sulfuron's Priests heal the lowest-health creature within 60 yards (BSU:143), which
// makes the boss unkillable while they live.
struct McAddBoss
{
    uint32 bossEntry;
    uint32 addEntry;
};
constexpr std::array<McAddBoss, 4> ADD_BOSSES = {{
    { NPC_LUCIFRON, NPC_FLAMEWAKER_PROTECTOR },
    { NPC_GEHENNAS, NPC_FLAMEWAKER },
    { NPC_GARR, NPC_FIRESWORN },
    { NPC_SULFURON_HARBINGER, NPC_FLAMEWAKER_PRIEST },
}};

}

void RaidMcStrategy::InitTriggers(std::vector<TriggerNode*>& triggers)
{
    // Lucifron
    triggers.push_back(
        new TriggerNode("mc lucifron shadow resistance",
                        { NextAction("mc lucifron shadow resistance", ACTION_RAID) }));
    triggers.push_back(
        new TriggerNode("mc lucifron should be tanked",
                        { NextAction("mc lucifron main tank attack boss", ACTION_RAID + 1) }));
    // The two Protectors charm whoever they please while nobody holds them.
    triggers.push_back(
        new TriggerNode("mc lucifron protectors spawned",
                        { NextAction("mc lucifron tank attack nearest protector", ACTION_RAID + 2) }));

    // Magmadar
    triggers.push_back(
        new TriggerNode("mc magmadar tremor", { NextAction("tremor totem", ACTION_RAID + 2) }));
    triggers.push_back(
        new TriggerNode("mc magmadar fire resistance",
                        { NextAction("mc magmadar fire resistance", ACTION_RAID) }));
    triggers.push_back(
        new TriggerNode("mc magmadar should be tanked",
                        { NextAction("mc magmadar main tank attack boss", ACTION_RAID + 1) }));
    triggers.push_back(
        new TriggerNode("mc magmadar bot in lava bomb",
                        { NextAction("mc magmadar move out of lava bomb", ACTION_EMERGENCY + 7) }));

    // Gehennas
    triggers.push_back(
        new TriggerNode("mc gehennas shadow resistance",
                        { NextAction("mc gehennas shadow resistance", ACTION_RAID) }));
    triggers.push_back(
        new TriggerNode("mc gehennas should be tanked",
                        { NextAction("mc gehennas main tank attack boss", ACTION_RAID + 1) }));
    triggers.push_back(
        new TriggerNode("mc gehennas flamewakers spawned",
                        { NextAction("mc gehennas tank attack nearest flamewaker", ACTION_RAID + 2) }));
    triggers.push_back(
        new TriggerNode("mc gehennas bot in rain of fire",
                        { NextAction("mc gehennas move out of rain of fire", ACTION_EMERGENCY + 7) }));

    // Garr
    triggers.push_back(
        new TriggerNode("mc garr fire resistance",
                        { NextAction("mc garr fire resistance", ACTION_RAID) }));
    triggers.push_back(
        new TriggerNode("mc garr should be tanked",
                        { NextAction("mc garr main tank attack boss", ACTION_RAID + 1) }));
    // Held where they stand: a Firesworn dragged more than 40 yards from Garr gains 300% damage
    // (BGA:158).
    triggers.push_back(
        new TriggerNode("mc garr firesworn spawned",
                        { NextAction("mc garr tank attack nearest firesworn", ACTION_RAID + 2) }));

    // Baron Geddon
    triggers.push_back(
        new TriggerNode("mc baron geddon fire resistance",
                        { NextAction("mc baron geddon fire resistance", ACTION_RAID) }));
    triggers.push_back(
        new TriggerNode("mc living bomb debuff",
                        { NextAction("mc move from group", ACTION_RAID + 2) }));
    triggers.push_back(
        new TriggerNode("mc baron geddon inferno",
                        { NextAction("mc move from baron geddon", ACTION_RAID + 1) }));

    // Shazzrah
    triggers.push_back(
        new TriggerNode("mc shazzrah ranged",
                        { NextAction("mc shazzrah move away", ACTION_RAID) }));
    triggers.push_back(
        new TriggerNode("mc shazzrah should be tanked",
                        { NextAction("mc shazzrah main tank attack boss", ACTION_RAID + 1) }));
    // Gate of Shazzrah blinks him to a random ranged bot and wipes his threat list (BSH:148).
    triggers.push_back(
        new TriggerNode("mc shazzrah lost threat",
                        { NextAction("mc shazzrah taunt boss", ACTION_RAID + 3) }));

    // Sulfuron Harbinger
    // Alternatively, shadow resistance is also possible.
    triggers.push_back(
        new TriggerNode("mc sulfuron harbinger fire resistance",
                        { NextAction("mc sulfuron harbinger fire resistance", ACTION_RAID) }));
    triggers.push_back(
        new TriggerNode("mc sulfuron harbinger should be tanked",
                        { NextAction("mc sulfuron harbinger main tank attack boss", ACTION_RAID + 1) }));
    triggers.push_back(
        new TriggerNode("mc sulfuron harbinger priests spawned",
                        { NextAction("mc sulfuron harbinger tank attack nearest priest", ACTION_RAID + 2) }));

    // Golemagg the Incinerator
    triggers.push_back(
        new TriggerNode("mc golemagg fire resistance",
                        { NextAction("mc golemagg fire resistance", ACTION_RAID) }));
    triggers.push_back(
        new TriggerNode("mc golemagg mark boss",
                        { NextAction("mc golemagg mark boss", ACTION_RAID) }));
    triggers.push_back(
        new TriggerNode("mc golemagg is main tank",
                        { NextAction("mc golemagg main tank attack golemagg", ACTION_RAID) }));
    triggers.push_back(
        new TriggerNode("mc golemagg is assist tank",
                        { NextAction("mc golemagg assist tank attack core rager", ACTION_RAID) }));
    triggers.push_back(
        new TriggerNode("mc golemagg magma splash",
                        { NextAction("mc golemagg back off", ACTION_RAID + 1) }));
    triggers.push_back(
        new TriggerNode("mc golemagg is healer",
                        { NextAction("mc golemagg healer position", ACTION_RAID) }));

    // Majordomo Executus
    triggers.push_back(
        new TriggerNode("mc majordomo shadow resistance",
                        { NextAction("mc majordomo shadow resistance", ACTION_RAID) }));
    triggers.push_back(
        new TriggerNode("mc majordomo damage shield",
                        { NextAction("mc majordomo stop attack", ACTION_RAID + 1) }));
    triggers.push_back(
        new TriggerNode("mc majordomo should be tanked",
                        { NextAction("mc majordomo main tank attack boss", ACTION_RAID + 1) }));
    // Hate to Zero before each of his two teleports (BMJ:336, :345).
    triggers.push_back(
        new TriggerNode("mc majordomo lost threat",
                        { NextAction("mc majordomo taunt boss", ACTION_RAID + 3) }));
    // His eight adds are the encounter: it ends when the last one dies (BMJ:264).
    triggers.push_back(
        new TriggerNode("mc majordomo adds spawned",
                        { NextAction("mc majordomo tank attack nearest add", ACTION_RAID + 2) }));

    // Ragnaros
    triggers.push_back(
        new TriggerNode("mc ragnaros fire resistance",
                        { NextAction("mc ragnaros fire resistance", ACTION_RAID) }));
    triggers.push_back(
        new TriggerNode("mc ragnaros should be tanked",
                        { NextAction("mc ragnaros main tank attack boss", ACTION_RAID + 1) }));
    // He wipes his threat list on every submerge and picks a random target when he comes back
    // (BR:395, :447).
    triggers.push_back(
        new TriggerNode("mc ragnaros lost threat",
                        { NextAction("mc ragnaros taunt boss", ACTION_RAID + 3) }));
    // Eight Sons of Flame per submerge, and he stays under until the last of them is dead or 90
    // seconds have passed (BR:192, :408). Everyone but the healers goes for them.
    triggers.push_back(
        new TriggerNode("mc ragnaros sons of flame spawned",
                        { NextAction("mc ragnaros attack nearest son of flame", ACTION_RAID + 2) }));
    triggers.push_back(
        new TriggerNode("mc ragnaros bot in lava burst",
                        { NextAction("mc ragnaros move out of lava burst", ACTION_EMERGENCY + 7) }));

    // Trash
    triggers.push_back(
        new TriggerNode("mc core hound mark",
                        { NextAction("mc core hound mark", ACTION_RAID) }));

    // Anywhere in MC: escaping a lava pool outranks everything else.
    triggers.push_back(
        new TriggerNode("mc in lava",
                        { NextAction("mc move from lava", ACTION_RAID + 1) }));
}

void RaidMcStrategy::InitMultipliers(std::vector<Multiplier*>& multipliers)
{
    multipliers.push_back(new GarrDisableDpsAoeMultiplier(botAI));
    multipliers.push_back(new BaronGeddonAbilityMultiplier(botAI));
    multipliers.push_back(new GolemaggMultiplier(botAI));
    multipliers.push_back(new MajordomoReflectionMultiplier(botAI));
    multipliers.push_back(new McHazardChaseHoldMultiplier(
        botAI, "mc magmadar lava bomb chase hold", MAGMADAR_LAVA_BOMBS_VALUE, LAVA_BOMB_RADIUS));
    multipliers.push_back(new McHazardChaseHoldMultiplier(
        botAI, "mc gehennas rain of fire chase hold", GEHENNAS_RAIN_OF_FIRE_VALUE,
        RAIN_OF_FIRE_RADIUS));
    multipliers.push_back(new McHazardChaseHoldMultiplier(
        botAI, "mc ragnaros lava burst chase hold", RAGNAROS_LAVA_BURSTS_VALUE, LAVA_BURST_RADIUS));
}

void RaidMcStrategy::AppendTargetExclusions(GuidSet& exclusions, TargetValueExclusionType type)
{
    if (type == TargetValueExclusionType::TankTarget ||
        (type == TargetValueExclusionType::Aoe && PlayerbotAI::IsTank(botAI->GetBot())))
        return;

    // Damage into these is wasted: Core Ragers are unkillable while Golemagg
    // lives (full heal at 50%), and Majordomo cannot die; his encounter ends
    // when the eight adds are dead. Tanks still pick them up through their own
    // target selection.
    AiObjectContext* context = botAI->GetAiObjectContext();
    bool const golemaggAlive = AI_VALUE2(Unit*, "find target", "golemagg the incinerator") != nullptr;
    // The DPS target search skips the moon (crowd control) mark, so a moon-marked healer does not count.
    Group const* group = botAI->GetBot()->GetGroup();
    ObjectGuid const moonGuid = group ? group->GetTargetIcon(RtiTargetValue::moonIndex) : ObjectGuid::Empty;
    bool flamewakerHealerAlive = false;
    GuidVector flamewakerElites;
    // One slot per entry of ADD_BOSSES: the boss's guid, and whether any of its adds is still up.
    std::array<ObjectGuid, ADD_BOSSES.size()> addBossGuids = {};
    std::array<bool, ADD_BOSSES.size()> addBossHasAdds = {};
    for (ObjectGuid const guid : AI_VALUE(GuidVector, "attackers"))
    {
        Unit* unit = botAI->GetUnit(guid);
        if (!unit)
            continue;

        if ((golemaggAlive && unit->GetEntry() == NPC_CORE_RAGER) || unit->GetEntry() == NPC_MAJORDOMO_EXECUTUS)
            exclusions.insert(guid);
        else if (unit->GetEntry() == NPC_FLAMEWAKER_HEALER && unit->IsAlive() && guid != moonGuid)
            flamewakerHealerAlive = true;
        else if (unit->GetEntry() == NPC_FLAMEWAKER_ELITE)
            flamewakerElites.push_back(guid);

        for (size_t i = 0; i < ADD_BOSSES.size(); ++i)
        {
            if (unit->GetEntry() == ADD_BOSSES[i].bossEntry)
                addBossGuids[i] = guid;
            else if (unit->GetEntry() == ADD_BOSSES[i].addEntry && unit->IsAlive())
                addBossHasAdds[i] = true;
        }
    }

    // Majordomo's healers first: they heal the elites and each other.
    if (type == TargetValueExclusionType::DpsTarget && flamewakerHealerAlive)
        exclusions.insert(flamewakerElites.begin(), flamewakerElites.end());

    // Adds before the boss on the four add bosses. Excluding the boss is enough to turn the raid
    // around: "dps target" picks an add instead, and "not dps target active" switches to it.
    if (type == TargetValueExclusionType::DpsTarget)
    {
        for (size_t i = 0; i < ADD_BOSSES.size(); ++i)
        {
            if (addBossHasAdds[i] && !addBossGuids[i].IsEmpty())
                exclusions.insert(addBossGuids[i]);
        }
    }
}
