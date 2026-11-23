/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#include "Aq40Triggers.h"
#include "Aq40Helpers.h"
#include "EncounterHelpers.h"
#include "Playerbots.h"
#include "ThreatHelpers.h"

using namespace Aq40Helpers;
using namespace EncounterHelpers;

// Shared

bool Aq40NoEncounterInProgressTrigger::IsActive()
{
    return !IsEncounterInProgress(bot, AQ40_MAP_ID);
}

bool Aq40BossShouldBeTankedTrigger::IsActiveInEncounter()
{
    if (!PlayerbotAI::IsMainTank(bot))
        return false;

    return AI_VALUE2(Unit*, "find target", _bossName) != nullptr;
}

bool Aq40RangedShouldSpreadTrigger::IsActiveInEncounter()
{
    if (!PlayerbotAI::IsRanged(bot))
        return false;

    Unit* boss = AI_VALUE2(Unit*, "find target", _bossName);
    if (!boss || boss->GetVictim() == bot)
        return false;

    if (bot->GetExactDist(boss) < _distanceFromBoss)
        return true;

    return GetNearestPlayerInRadius(bot, SPREAD_DISTANCE) != nullptr;
}

bool Aq40BotInHazardTrigger::IsActiveInEncounter()
{
    bool bossFound = false;
    for (std::string const& bossName : _bossNames)
    {
        if (FindThreatTarget(bot, bossName))
        {
            bossFound = true;
            break;
        }
    }

    if (!bossFound)
        return false;

    return IsInHazard(botAI, _hazardValue, _radius);
}

bool Aq40AddsSpawnedTrigger::IsActiveInEncounter()
{
    switch (_role)
    {
        case Aq40AddRole::MeleeAndTanks:
            if (!PlayerbotAI::IsMelee(bot) && !PlayerbotAI::IsTank(bot))
                return false;
            break;
        case Aq40AddRole::AssistTanks:
            if (!PlayerbotAI::IsAssistTank(bot))
                return false;
            break;
        case Aq40AddRole::Tanks:
            if (!PlayerbotAI::IsTank(bot))
                return false;
            break;
        case Aq40AddRole::RangedDps:
            if (!PlayerbotAI::IsRangedDps(bot))
                return false;
            break;
        case Aq40AddRole::Everyone:
            if (PlayerbotAI::IsHeal(bot))
                return false;
            break;
    }

    Unit* add = GetNearestCachedUnit(botAI, _addsValue);
    return add && AI_VALUE(Unit*, "current target") != add;
}

// The Prophet Skeram

bool SkeramShouldBeTankedTrigger::IsActiveInEncounter()
{
    if (!PlayerbotAI::IsMainTank(bot))
        return false;

    return GetRealSkeram(botAI) != nullptr;
}

bool SkeramImagesSpawnedTrigger::IsActiveInEncounter()
{
    if (!PlayerbotAI::IsAssistTankOfIndex(bot, 0, true) &&
        !PlayerbotAI::IsAssistTankOfIndex(bot, 1, true))
    {
        return false;
    }

    return !GetSkeramImages(botAI).empty();
}

bool SkeramShouldAssignDpsPriorityTrigger::IsActiveInEncounter()
{
    if (PlayerbotAI::IsTank(bot) || PlayerbotAI::IsHeal(bot))
        return false;

    Unit* skeram = GetRealSkeram(botAI);
    return skeram && AI_VALUE(Unit*, "current target") != skeram;
}

// True Fulfillment turns a raid member hostile, and the bots' own target selection happily picks
// that player up. The ally has to be left alone: killing him is a death the raid does not need.
bool SkeramAttackingMindControlledAllyTrigger::IsActiveInEncounter()
{
    Unit* target = AI_VALUE(Unit*, "current target");
    if (!target || !target->IsPlayer())
        return false;

    return target->HasAura(Id(Aq40Spells::SPELL_TRUE_FULFILLMENT));
}

// Silithid Royalty

bool BugTrioTargetsShouldBeTankedTrigger::IsActiveInEncounter()
{
    if (!PlayerbotAI::IsTank(bot))
        return false;

    return FindThreatTarget(bot, VEM_NAME) || FindThreatTarget(bot, LORD_KRI_NAME) ||
        FindThreatTarget(bot, PRINCESS_YAUJ_NAME);
}

bool BugTrioShouldAssignDpsPriorityTrigger::IsActiveInEncounter()
{
    if (PlayerbotAI::IsTank(bot) || PlayerbotAI::IsHeal(bot))
        return false;

    Unit* killTarget = GetBugTrioKillTarget(botAI);
    return killTarget && AI_VALUE(Unit*, "current target") != killTarget;
}

// Battleguard Sartura

bool SarturaRoyalGuardsShouldBeTankedTrigger::IsActiveInEncounter()
{
    if (!FindThreatTarget(bot, SARTURA_NAME))
        return false;

    for (uint8 index = 0; index < 2; ++index)
    {
        if (PlayerbotAI::IsAssistTankOfIndex(bot, index, true) &&
            GetCachedUnitOfIndex(botAI, ROYAL_GUARDS_VALUE, index))
        {
            return true;
        }
    }

    return false;
}

// Sartura and her Guards are immune to stuns while whirlwinding and switch target every few
// seconds, so melee step out instead of trying to hold them.
bool SarturaMeleeInWhirlwindRangeTrigger::IsActiveInEncounter()
{
    if (!PlayerbotAI::IsMelee(bot) || PlayerbotAI::IsTank(bot))
        return false;

    Unit* sartura = FindThreatTarget(bot, SARTURA_NAME);
    if (sartura && sartura->HasAura(Id(Aq40Spells::SPELL_WHIRLWIND)) &&
        bot->GetExactDist(sartura) < WHIRLWIND_ESCAPE_DISTANCE)
    {
        return true;
    }

    for (Unit* guard : GetCachedUnits(botAI, ROYAL_GUARDS_VALUE))
    {
        if (guard->HasAura(Id(Aq40Spells::SPELL_GUARD_WHIRLWIND)) &&
            bot->GetExactDist(guard) < WHIRLWIND_ESCAPE_DISTANCE)
        {
            return true;
        }
    }

    return false;
}

bool SarturaShouldAssignDpsPriorityTrigger::IsActiveInEncounter()
{
    if (PlayerbotAI::IsTank(bot) || PlayerbotAI::IsHeal(bot))
        return false;

    if (!FindThreatTarget(bot, SARTURA_NAME))
        return false;

    Unit* guard = GetNearestCachedUnit(botAI, ROYAL_GUARDS_VALUE);
    return guard && AI_VALUE(Unit*, "current target") != guard;
}

// Fankriss the Unyielding

bool FankrissMainTankMortalWoundStacksTrigger::IsActiveInEncounter()
{
    if (!PlayerbotAI::IsAssistTankOfIndex(bot, 0, true))
        return false;

    Unit* fankriss = FindThreatTarget(bot, FANKRISS_NAME);
    if (!fankriss)
        return false;

    Unit* mainTank = AI_VALUE(Unit*, "main tank");
    if (!mainTank || fankriss->GetVictim() != mainTank)
        return false;

    return GetAuraStacks(mainTank, Id(Aq40Spells::SPELL_MORTAL_WOUND)) >=
        MORTAL_WOUND_SWAP_STACKS;
}

// Viscidus

bool ViscidusInFrostPhaseTrigger::IsActiveInEncounter()
{
    if (!GetCheapestFrostSpell(bot))
        return false;

    Unit* viscidus = FindThreatTarget(bot, VISCIDUS_NAME);
    if (!viscidus || IsViscidusFrozen(viscidus))
        return false;

    // While the Globs are out there is nothing left to freeze.
    return GetCachedUnits(botAI, VISCIDUS_GLOBS_VALUE).empty();
}

// Twin Emperors

bool TwinEmperorsShouldBeTankedApartTrigger::IsActiveInEncounter()
{
    if (PlayerbotAI::IsMainTank(bot))
        return FindThreatTarget(bot, VEKNILASH_NAME) != nullptr;

    if (PlayerbotAI::IsAssistTankOfIndex(bot, 0, true))
        return FindThreatTarget(bot, VEKLOR_NAME) != nullptr;

    return false;
}

bool TwinEmperorsMeleeShouldAttackVeknilashTrigger::IsActiveInEncounter()
{
    if (!PlayerbotAI::IsMelee(bot) || PlayerbotAI::IsTank(bot))
        return false;

    Unit* veknilash = FindThreatTarget(bot, VEKNILASH_NAME);
    return veknilash && AI_VALUE(Unit*, "current target") != veknilash;
}

bool TwinEmperorsCastersShouldAttackVeklorTrigger::IsActiveInEncounter()
{
    if (!PlayerbotAI::IsRangedDps(bot))
        return false;

    Unit* veklor = FindThreatTarget(bot, VEKLOR_NAME);
    return veklor && AI_VALUE(Unit*, "current target") != veklor;
}

// C'Thun

bool CthunBotInDarkGlarePathTrigger::IsActiveInEncounter()
{
    Unit* eye = GetCthunEye(botAI);
    if (!IsEyeCastingDarkGlare(eye))
        return false;

    return eye->HasInLine(bot, DARK_GLARE_LINE_WIDTH);
}

bool CthunBodyWeakenedTrigger::IsActiveInEncounter()
{
    // Tanks keep the Giant Claw Tentacle: it kills whoever it reaches while the raid burns the
    // body, and the body itself never swings at anyone.
    if (PlayerbotAI::IsTank(bot) || PlayerbotAI::IsHeal(bot))
        return false;

    if (IsInCthunStomach(bot))
        return false;

    Unit* body = GetCthunBody(botAI);
    if (!IsCthunBodyWeakened(body))
        return false;

    return AI_VALUE(Unit*, "current target") != body;
}

bool CthunFleshTentacleInStomachTrigger::IsActiveInEncounter()
{
    if (!IsInCthunStomach(bot))
        return false;

    Unit* tentacle = GetNearestCachedUnit(botAI, CTHUN_FLESH_TENTACLES_VALUE);
    return tentacle && AI_VALUE(Unit*, "current target") != tentacle;
}

bool CthunShouldLeaveStomachTrigger::IsActiveInEncounter()
{
    if (!IsInCthunStomach(bot))
        return false;

    if (GetNearestCachedUnit(botAI, CTHUN_FLESH_TENTACLES_VALUE))
        return false;

    return bot->GetExactDist2d(CTHUN_STOMACH_EXIT) > CTHUN_STOMACH_EXIT_ARRIVAL_DISTANCE;
}

bool CthunRangedShouldSpreadTrigger::IsActiveInEncounter()
{
    return !IsInCthunStomach(bot) && Aq40RangedShouldSpreadTrigger::IsActiveInEncounter();
}

// Ouro

// Sweep and Sand Blast both come out of his front, and Sand Blast wipes the threat of everyone it
// hits, so only the tank stands there.
bool OuroMeleeInFrontOfBossTrigger::IsActiveInEncounter()
{
    if (!PlayerbotAI::IsMelee(bot) || PlayerbotAI::IsTank(bot))
        return false;

    Unit* ouro = FindThreatTarget(bot, OURO_NAME);
    if (!ouro || ouro->GetVictim() == bot)
        return false;

    return ouro->HasInArc(OURO_FRONT_ARC, bot) && bot->IsWithinMeleeRange(ouro);
}

// He despawns while submerged and comes back out of one of his Dirt Mounds, so a mound is where
// nobody wants to be standing.
bool OuroSubmergedTrigger::IsActiveInEncounter()
{
    for (Unit* mound : GetCachedUnits(botAI, DIRT_MOUNDS_VALUE))
    {
        if (bot->GetExactDist2d(mound) < DIRT_MOUND_RADIUS)
            return true;
    }

    return false;
}
