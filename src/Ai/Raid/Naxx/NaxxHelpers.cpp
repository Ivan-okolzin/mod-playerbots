/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#include "NaxxHelpers.h"
#include "Creature.h"
#include "GameObject.h"
#include "Playerbots.h"
#include "ThreatManager.h"
#include <algorithm>
#include <limits>
#include <list>

namespace NaxxHelpers
{

bool HasRole(Player* bot, NaxxRole role)
{
    switch (role)
    {
        case NaxxRole::MainTank:
            return PlayerbotAI::IsMainTank(bot);
        case NaxxRole::Tanks:
            return PlayerbotAI::IsTank(bot);
        case NaxxRole::AssistTanks:
            return PlayerbotAI::IsAssistTank(bot);
        case NaxxRole::Dps:
            return PlayerbotAI::IsDps(bot) && !PlayerbotAI::IsTank(bot) && !PlayerbotAI::IsHeal(bot);
    }

    return false;
}

Unit* FindThreatCreature(Player* bot, uint32 entry)
{
    for (auto const& [guid, ref] : bot->GetThreatMgr().GetThreatenedByMeList())
    {
        if (guid.GetEntry() != entry)
            continue;

        Unit* unit = ref->GetOwner();
        if (unit && unit->IsInWorld() && unit->IsAlive())
            return unit;
    }

    return nullptr;
}

GuidVector FindCreatureGuids(Player* bot, std::vector<uint32> const& entries, float radius)
{
    GuidVector guids;
    for (uint32 const entry : entries)
    {
        std::list<Creature*> creatures;
        bot->GetCreatureListWithEntryInGrid(creatures, entry, radius);
        for (Creature* creature : creatures)
        {
            if (creature && creature->IsAlive())
                guids.push_back(creature->GetGUID());
        }
    }

    std::sort(guids.begin(), guids.end());
    return guids;
}

std::vector<Unit*> GetCachedUnits(PlayerbotAI* botAI, char const* value)
{
    GuidVector const& guids = botAI->GetAiObjectContext()->GetValue<GuidVector>(value)->RefGet();

    std::vector<Unit*> units;
    units.reserve(guids.size());
    for (ObjectGuid const guid : guids)
    {
        Unit* unit = botAI->GetUnit(guid);
        if (unit && unit->IsAlive())
            units.push_back(unit);
    }

    return units;
}

Unit* GetNearestCachedUnit(PlayerbotAI* botAI, char const* value)
{
    Player* bot = botAI->GetBot();
    Unit* nearest = nullptr;
    float nearestDistance = std::numeric_limits<float>::max();
    for (Unit* unit : GetCachedUnits(botAI, value))
    {
        float const distance = bot->GetExactDist(unit);
        if (distance < nearestDistance)
        {
            nearest = unit;
            nearestDistance = distance;
        }
    }

    return nearest;
}

bool IsUnassailable(Unit* unit)
{
    return !unit || unit->HasUnitFlag(UNIT_FLAG_NOT_SELECTABLE) ||
        unit->HasUnitFlag(UNIT_FLAG_NON_ATTACKABLE);
}

bool IsBossOnNonTank(Unit* boss)
{
    if (!boss)
        return false;

    Unit* victim = boss->GetVictim();
    if (!victim || !victim->IsPlayer())
        return false;

    return !PlayerbotAI::IsTank(victim->ToPlayer());
}

bool IsBossEngageable(PlayerbotAI* botAI, Unit* boss)
{
    if (IsUnassailable(boss))
        return false;

    if (boss->GetEntry() != Id(NaxxNpcs::NPC_GOTHIK))
        return true;

    return !IsGothikWavePhase(boss) && IsReachableAcrossGothikGate(botAI, boss);
}

bool IsGameObjectOpen(Player* bot, uint32 entry, float radius)
{
    std::list<GameObject*> objects;
    bot->GetGameObjectListWithEntryInGrid(objects, entry, radius);
    for (GameObject* object : objects)
    {
        if (object && object->isSpawned() && object->GetGoState() == GO_STATE_ACTIVE)
            return true;
    }

    return false;
}

// Noth the Plaguebringer

bool IsNothOnBalcony(Unit* noth)
{
    return noth && noth->HasUnitFlag(UNIT_FLAG_NOT_SELECTABLE);
}

// Gothik the Harvester

bool IsOnLiveSide(WorldObject const* who)
{
    return who && who->GetPositionY() < GOTHIK_GATE_Y;
}

bool IsGothikGateOpen(PlayerbotAI* botAI)
{
    return botAI->GetAiObjectContext()->GetValue<bool>(GOTHIK_GATE_OPEN_VALUE)->Get();
}

bool IsReachableAcrossGothikGate(PlayerbotAI* botAI, WorldObject const* who)
{
    if (!who)
        return false;

    return IsOnLiveSide(botAI->GetBot()) == IsOnLiveSide(who) || IsGothikGateOpen(botAI);
}

Unit* GetNearestReachableGothikAdd(PlayerbotAI* botAI, char const* value)
{
    Player* bot = botAI->GetBot();
    Unit* nearest = nullptr;
    float nearestDistance = std::numeric_limits<float>::max();
    for (Unit* add : GetCachedUnits(botAI, value))
    {
        if (IsUnassailable(add) || !IsReachableAcrossGothikGate(botAI, add))
            continue;

        float const distance = bot->GetExactDist(add);
        if (distance < nearestDistance)
        {
            nearest = add;
            nearestDistance = distance;
        }
    }

    return nearest;
}

bool IsGothikWavePhase(Unit* gothik)
{
    return gothik && gothik->HasUnitFlag(UNIT_FLAG_DISABLE_MOVE);
}

}  // namespace NaxxHelpers
