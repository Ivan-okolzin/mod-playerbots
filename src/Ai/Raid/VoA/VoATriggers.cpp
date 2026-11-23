/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#include "VoATriggers.h"
#include "EncounterHelpers.h"
#include "EventMap.h"
#include "Object.h"
#include "PlayerbotAI.h"
#include "Playerbots.h"
#include "VoAHelpers.h"

using namespace EncounterHelpers;
using namespace VoAHelpers;

// Shared

bool VoABossShouldBeTankedTrigger::IsActiveInEncounter()
{
    if (!PlayerbotAI::IsMainTank(bot))
        return false;

    Unit* boss = FindThreatCreature(bot, _bossEntry);
    return IsAttackableNow(boss) && AI_VALUE(Unit*, "current target") != boss;
}

bool VoARangedShouldSpreadTrigger::IsActiveInEncounter()
{
    if (!PlayerbotAI::IsRanged(bot))
        return false;

    // Nothing to spread out of while the boss is not on this bot's threat list, and the player the
    // boss is hitting is the one place the raid cannot spread to anyway.
    Unit* boss = FindThreatCreature(bot, _bossEntry);
    if (!boss || boss->GetVictim() == bot)
        return false;

    return GetNearestPlayerInRadius(bot, SPREAD_DISTANCE) != nullptr;
}

bool VoAAddsSpawnedTrigger::IsActiveInEncounter()
{
    switch (_role)
    {
        case VoAAddRole::Tanks:
            // The main tank stays on the boss; the rest of the tanks take the adds.
            if (!PlayerbotAI::IsTank(bot) || PlayerbotAI::IsMainTank(bot))
                return false;
            break;
        case VoAAddRole::RangedDps:
            if (!PlayerbotAI::IsRangedDps(bot))
                return false;
            break;
    }

    Unit* add = GetNearestAttackableCachedUnit(botAI, _addsValue);
    return add && AI_VALUE(Unit*, "current target") != add;
}

bool VoABotNearAddTrigger::IsActiveInEncounter()
{
    return IsNearCachedUnit(botAI, _addsValue, _radius);
}

bool EmalonMarkBossTrigger::IsActive()
{
    // Only tank bot can mark target
    if (!PlayerbotAI::IsTank(bot))
    {
        return false;
    }

    // Check boss and it is alive
    Unit* boss = AI_VALUE2(Unit*, "find target", "emalon the storm watcher");
    if (!boss || !boss->IsAlive())
    {
        return false;
    }

    // Check if boss have skull mark
    Group* group = bot->GetGroup();
    int8 skullIndex = 7;  // Skull
    ObjectGuid currentSkullTarget = group->GetTargetIcon(skullIndex);
    if (currentSkullTarget == boss->GetGUID())
    {
        return false;
    }

    Unit* overchargedMinion = GetOverchargedMinion(botAI);
    if (overchargedMinion)
    {
        return false;
    }

    return true;
}

bool EmalonLightingNovaTrigger::IsActive()
{
    // Check boss and it is alive
    Unit* boss = AI_VALUE2(Unit*, "find target", "emalon the storm watcher");
    if (!boss || !boss->IsAlive())
    {
        return false;
    }

    // Tank dont need to move
    if (PlayerbotAI::IsTank(bot))
    {
        return false;
    }

    // Check if boss is casting Lightning Nova
    bool isCasting = boss->HasUnitState(UNIT_STATE_CASTING);
    bool isLightingNova = boss->FindCurrentSpellBySpellId(SPELL_LIGHTNING_NOVA_10_MAN) ||
                          boss->FindCurrentSpellBySpellId(SPELL_LIGHTNING_NOVA_25_MAN);
    return isCasting && isLightingNova;
}

bool EmalonOverchargeTrigger::IsActive()
{
    // Only tank bot can mark target
    if (!PlayerbotAI::IsTank(bot))
    {
        return false;
    }

    // Check boss and it is alive
    Unit* boss = AI_VALUE2(Unit*, "find target", "emalon the storm watcher");
    if (!boss || !boss->IsAlive())
    {
        return false;
    }

    Unit* overchargedMinion = GetOverchargedMinion(botAI);
    if (!overchargedMinion)
    {
        return false;
    }

    // Check if minion have skull mark
    Group* group = bot->GetGroup();
    int8 skullIndex = 7;  // Skull
    ObjectGuid currentSkullTarget = group->GetTargetIcon(skullIndex);
    if (currentSkullTarget == overchargedMinion->GetGUID())
    {
        return false;
    }

    return true;
}

bool EmalonFallFromFloorTrigger::IsActive()
{
    // Check boss and it is alive
    Unit* boss = AI_VALUE2(Unit*, "find target", "emalon the storm watcher");
    if (!boss || !boss->IsAlive())
    {
        return false;
    }

    // Check if bot is on the floor
    return bot->GetPositionZ() < 80.0f;
}

// Emalon the Storm Watcher

bool EmalonOverchargedMinionTrigger::IsActiveInEncounter()
{
    // The healers keep healing and the main tank keeps Emalon where he is: ten seconds of one
    // minion is not worth dropping either.
    if (PlayerbotAI::IsHeal(bot) || PlayerbotAI::IsMainTank(bot))
        return false;

    Unit* minion = GetOverchargedMinion(botAI);
    return minion && AI_VALUE(Unit*, "current target") != minion;
}

// Koralon the Flame Watcher

bool KoralonBurningBreathTrigger::IsActiveInEncounter()
{
    // The main tank holds him facing away from the raid and takes the breath himself; the melee
    // behind him are the ones with somewhere to go.
    if (PlayerbotAI::IsMainTank(bot) || !PlayerbotAI::IsMelee(bot))
        return false;

    Unit* koralon = FindThreatCreature(bot, Id(VoANpcs::NPC_KORALON));
    return IsBreathingFire(koralon) && IsInFrontOfBreath(bot, koralon);
}

// Toravon the Ice Watcher

bool ToravonBotPursuedByOrbTrigger::IsActiveInEncounter()
{
    return GetPursuingFrozenOrb(botAI) != nullptr;
}

bool ToravonBotInFreezingGroundTrigger::IsActiveInEncounter()
{
    return IsInHazard(botAI, TORAVON_FREEZING_GROUND_VALUE, FREEZING_GROUND_RADIUS);
}
