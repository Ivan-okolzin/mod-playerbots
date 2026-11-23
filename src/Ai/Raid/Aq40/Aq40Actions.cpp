/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#include "Aq40Actions.h"
#include "Aq40Helpers.h"
#include "EncounterHelpers.h"
#include "Playerbots.h"
#include "RtiTargetValue.h"
#include "ThreatHelpers.h"
#include <algorithm>
#include <cmath>

using namespace Aq40Helpers;
using namespace EncounterHelpers;

// Shared

bool Aq40ResetEncounterStatesAction::Execute(Event /*event*/)
{
    return ClearStrategyTargetIcon(
        bot, RtiTargetValue::skullIndex,
        { Id(Aq40Npcs::NPC_SKERAM), Id(Aq40Npcs::NPC_VEM), Id(Aq40Npcs::NPC_LORD_KRI),
          Id(Aq40Npcs::NPC_PRINCESS_YAUJ), Id(Aq40Npcs::NPC_SARTURA_ROYAL_GUARD) });
}

bool Aq40MainTankAttackBossAction::Execute(Event /*event*/)
{
    Unit* boss = AI_VALUE2(Unit*, "find target", _bossName);
    if (!boss)
        return false;

    return AI_VALUE(Unit*, "current target") != boss && Attack(boss);
}

bool Aq40SpreadRangedAction::Execute(Event /*event*/)
{
    Unit* boss = AI_VALUE2(Unit*, "find target", _bossName);
    if (!boss)
        return false;

    constexpr uint32 minInterval = 0;
    if (bot->GetExactDist(boss) < _distanceFromBoss &&
        FleePosition(boss->GetPosition(), _distanceFromBoss, minInterval))
    {
        return true;
    }

    Player* nearestPlayer = GetNearestPlayerInRadius(bot, SPREAD_DISTANCE);
    return nearestPlayer && FleePosition(nearestPlayer->GetPosition(), SPREAD_DISTANCE);
}

bool Aq40MoveOutOfHazardAction::Execute(Event /*event*/)
{
    Position safePos;
    if (!FindPositionOutsideHazards(botAI, _hazardValue, _radius, safePos))
        return false;

    bot->CastStop();
    return MoveTo(
        AQ40_MAP_ID, safePos.GetPositionX(), safePos.GetPositionY(), bot->GetPositionZ(), false,
        false, false, false, MovementPriority::MOVEMENT_FORCED, true, false);
}

bool Aq40AttackNearestAddAction::Execute(Event /*event*/)
{
    Unit* add = GetNearestCachedUnit(botAI, _addsValue);
    if (!add)
        return false;

    return AI_VALUE(Unit*, "current target") != add && Attack(add);
}

// The Prophet Skeram

bool SkeramMainTankAttackBossAction::Execute(Event /*event*/)
{
    Unit* skeram = GetRealSkeram(botAI);
    if (!skeram)
        return false;

    return AI_VALUE(Unit*, "current target") != skeram && Attack(skeram);
}

bool SkeramAssistTankAttackImageAction::Execute(Event /*event*/)
{
    std::vector<Unit*> const images = GetSkeramImages(botAI);
    if (images.empty())
        return false;

    uint8 const index = PlayerbotAI::IsAssistTankOfIndex(bot, 0, true) ? 0 : 1;
    Unit* image = index < images.size() ? images[index] : images.back();

    return AI_VALUE(Unit*, "current target") != image && Attack(image);
}

bool SkeramAssignDpsPriorityAction::Execute(Event /*event*/)
{
    Unit* skeram = GetRealSkeram(botAI);
    if (!skeram)
        return false;

    if (AI_VALUE(Unit*, "current target") != skeram)
        return Attack(skeram);

    return MarkTargetWithSkull(bot, skeram);
}

bool SkeramStopAttackingMindControlledAllyAction::Execute(Event /*event*/)
{
    Unit* target = AI_VALUE(Unit*, "current target");
    if (!target)
        return false;

    bool acted = StopAttackingTarget(bot, *target);

    if (Unit* skeram = GetRealSkeram(botAI))
        acted = SelectTarget(botAI, skeram) || acted;

    return acted;
}

// Silithid Royalty

// The main tank takes Vem, who is the last to die, so the raid's longest-lived target stays on
// the most solid tank.
bool BugTrioAssignTanksAction::Execute(Event /*event*/)
{
    char const* bossName = nullptr;
    if (PlayerbotAI::IsMainTank(bot))
        bossName = VEM_NAME;
    else if (PlayerbotAI::IsAssistTankOfIndex(bot, 0, true))
        bossName = LORD_KRI_NAME;
    else if (PlayerbotAI::IsAssistTankOfIndex(bot, 1, true))
        bossName = PRINCESS_YAUJ_NAME;

    if (!bossName)
        return false;

    Unit* boss = FindThreatTarget(bot, bossName);
    if (!boss)
        return false;

    return AI_VALUE(Unit*, "current target") != boss && Attack(boss);
}

bool BugTrioAssignDpsPriorityAction::Execute(Event /*event*/)
{
    Unit* killTarget = GetBugTrioKillTarget(botAI);
    if (!killTarget)
        return false;

    if (AI_VALUE(Unit*, "current target") != killTarget)
        return Attack(killTarget);

    return MarkTargetWithSkull(bot, killTarget);
}

// Battleguard Sartura

bool SarturaAssistTankAttackGuardAction::Execute(Event /*event*/)
{
    uint8 const index = PlayerbotAI::IsAssistTankOfIndex(bot, 0, true) ? 0 : 1;
    Unit* guard = GetCachedUnitOfIndex(botAI, ROYAL_GUARDS_VALUE, index);
    if (!guard)
        return false;

    return AI_VALUE(Unit*, "current target") != guard && Attack(guard);
}

bool SarturaMeleeBackOffAction::Execute(Event /*event*/)
{
    Unit* whirlwinding = nullptr;

    Unit* sartura = FindThreatTarget(bot, SARTURA_NAME);
    if (sartura && sartura->HasAura(Id(Aq40Spells::SPELL_WHIRLWIND)))
        whirlwinding = sartura;

    if (!whirlwinding)
    {
        for (Unit* guard : GetCachedUnits(botAI, ROYAL_GUARDS_VALUE))
        {
            if (guard->HasAura(Id(Aq40Spells::SPELL_GUARD_WHIRLWIND)) &&
                bot->GetExactDist(guard) < WHIRLWIND_ESCAPE_DISTANCE)
            {
                whirlwinding = guard;
                break;
            }
        }
    }

    if (!whirlwinding)
        return false;

    constexpr uint32 minInterval = 0;
    return FleePosition(whirlwinding->GetPosition(), WHIRLWIND_ESCAPE_DISTANCE, minInterval);
}

bool SarturaAssignDpsPriorityAction::Execute(Event /*event*/)
{
    Unit* guard = GetNearestCachedUnit(botAI, ROYAL_GUARDS_VALUE);
    if (!guard)
        return false;

    if (AI_VALUE(Unit*, "current target") != guard)
        return Attack(guard);

    return MarkTargetWithSkull(bot, guard);
}

// Fankriss the Unyielding

bool FankrissTankSwapAction::Execute(Event /*event*/)
{
    Unit* fankriss = FindThreatTarget(bot, FANKRISS_NAME);
    if (!fankriss)
        return false;

    if (AI_VALUE(Unit*, "current target") != fankriss && !Attack(fankriss))
        return false;

    return CastTankTaunt(botAI, fankriss);
}

// Viscidus

bool ViscidusCastFrostSpellAction::Execute(Event /*event*/)
{
    char const* frostSpell = GetCheapestFrostSpell(bot);
    if (!frostSpell)
        return false;

    Unit* viscidus = FindThreatTarget(bot, VISCIDUS_NAME);
    if (!viscidus)
        return false;

    return botAI->CanCastSpell(frostSpell, viscidus) && botAI->CastSpell(frostSpell, viscidus);
}

// Twin Emperors

bool TwinEmperorsTankPositionBossAction::Execute(Event /*event*/)
{
    bool const isMainTank = PlayerbotAI::IsMainTank(bot);
    char const* twinName = isMainTank ? VEKNILASH_NAME : VEKLOR_NAME;
    char const* otherName = isMainTank ? VEKLOR_NAME : VEKNILASH_NAME;
    Position const& station = isMainTank ? VEKNILASH_STATION : VEKLOR_STATION;

    Unit* twin = FindThreatTarget(bot, twinName);
    if (!twin)
        return false;

    if (AI_VALUE(Unit*, "current target") != twin)
        return Attack(twin);

    if (twin->GetVictim() != bot)
        return false;

    // They only need separating when they are within healing range of each other.
    Unit* other = FindThreatTarget(bot, otherName);
    if (other && twin->GetExactDist(other) > TWIN_SEPARATION_DISTANCE)
        return false;

    constexpr float arrivalDist = 5.0f;
    float moveX;
    float moveY;
    bool backwards;
    if (!GetStepToPosition(bot, station, arrivalDist, nullptr, moveX, moveY, backwards))
        return false;

    return MoveTo(
        AQ40_MAP_ID, moveX, moveY, bot->GetPositionZ(), false, false, false, false,
        MovementPriority::MOVEMENT_COMBAT, true, backwards);
}

bool TwinEmperorsSwitchTargetAction::Execute(Event /*event*/)
{
    Unit* twin = FindThreatTarget(bot, _bossName);
    if (!twin)
        return false;

    return AI_VALUE(Unit*, "current target") != twin && Attack(twin);
}

// C'Thun

// The beam sweeps half a circle in one direction, so the safe ground is the arc it has already
// passed: the bot circles the Eye against the sweep, which also takes it out of the line it is
// standing in. Until two samples have told the direction apart, it just leaves the line.
bool CthunMoveOutOfDarkGlareAction::Execute(Event /*event*/)
{
    Unit* eye = GetCthunEye(botAI);
    if (!IsEyeCastingDarkGlare(eye))
        return false;

    float const botAngle = eye->GetAngle(bot);
    float sweep = AI_VALUE(float, CTHUN_DARK_GLARE_SWEEP_VALUE);
    if (sweep == 0.0f)
    {
        float const offset = NormalizeAngleDelta(botAngle - eye->GetOrientation());
        sweep = offset < 0.0f ? 1.0f : -1.0f;
    }

    float const radius = std::max(eye->GetExactDist2d(bot), DARK_GLARE_MIN_RADIUS);
    float const safeAngle = botAngle - sweep * DARK_GLARE_DODGE_ANGLE;
    float const safeX = eye->GetPositionX() + radius * std::cos(safeAngle);
    float const safeY = eye->GetPositionY() + radius * std::sin(safeAngle);

    float stepX;
    float stepY;
    float stepZ;
    if (!CanTakeStepTowards(bot, safeX, safeY, DARK_GLARE_STEP_DISTANCE, stepX, stepY, stepZ))
        return false;

    bot->CastStop();
    return MoveTo(
        AQ40_MAP_ID, stepX, stepY, stepZ, false, false, false, false,
        MovementPriority::MOVEMENT_FORCED, true, false);
}

bool CthunAttackBodyAction::Execute(Event /*event*/)
{
    Unit* body = GetCthunBody(botAI);
    if (!IsCthunBodyWeakened(body))
        return false;

    return AI_VALUE(Unit*, "current target") != body && Attack(body);
}

// The core spits a player out of the stomach only from areatrigger 4033, and only while the Exit
// Trigger creature (15800) stands within ten yards of it (boss_cthun.cpp:874). No AzerothCore
// world database spawns that creature, so walking onto the trigger is the right move but, on an
// unpatched database, does not actually get the bot out. See AQ40/PLAN.md.
bool CthunLeaveStomachAction::Execute(Event /*event*/)
{
    float moveX;
    float moveY;
    bool backwards;
    if (!GetStepToPosition(
            bot, CTHUN_STOMACH_EXIT, CTHUN_STOMACH_EXIT_ARRIVAL_DISTANCE, nullptr, moveX, moveY,
            backwards))
    {
        return false;
    }

    return MoveTo(
        AQ40_MAP_ID, moveX, moveY, bot->GetPositionZ(), false, false, false, false,
        MovementPriority::MOVEMENT_COMBAT, true, backwards);
}

// Ouro

bool OuroSpreadFromDirtMoundsAction::Execute(Event /*event*/)
{
    Unit* mound = GetNearestCachedUnit(botAI, DIRT_MOUNDS_VALUE);
    if (!mound)
        return false;

    constexpr uint32 minInterval = 0;
    return FleePosition(mound->GetPosition(), DIRT_MOUND_RADIUS, minInterval);
}
