/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#include "ZGHelpers.h"
#include "Creature.h"
#include "GameObject.h"
#include "Playerbots.h"
#include "ThreatManager.h"
#include <algorithm>
#include <cmath>
#include <limits>
#include <list>

namespace ZulGurubHelpers
{

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

GuidVector FindCreatureGuids(
    Player* bot, std::vector<uint32> const& entries, float radius, bool summonsOnly)
{
    GuidVector guids;
    for (uint32 const entry : entries)
    {
        std::list<Creature*> creatures;
        bot->GetCreatureListWithEntryInGrid(creatures, entry, radius);
        for (Creature* creature : creatures)
        {
            if (!creature || !creature->IsAlive())
                continue;

            if (summonsOnly && !creature->IsSummon())
                continue;

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

Unit* GetCachedUnitOfEntry(PlayerbotAI* botAI, char const* value, uint32 entry)
{
    for (Unit* unit : GetCachedUnits(botAI, value))
    {
        if (unit->GetEntry() == entry)
            return unit;
    }

    return nullptr;
}

bool IsUnassailable(Unit* unit)
{
    return !unit || unit->HasUnitFlag(UNIT_FLAG_NOT_SELECTABLE) ||
        unit->HasUnitFlag(UNIT_FLAG_NON_ATTACKABLE);
}

// Ground hazards

// Jeklik's bombs land as trap objects rather than as spell areas (BJE:410 summons 180125), so
// this is the game object counterpart of EncounterHelpers::GetDynamicObjectPositions.
std::vector<Position> FindGameObjectPositions(Player* bot, uint32 entry, float radius)
{
    std::list<GameObject*> objects;
    bot->GetGameObjectListWithEntryInGrid(objects, entry, radius);

    std::vector<Position> positions;
    positions.reserve(objects.size());
    for (GameObject* object : objects)
    {
        if (object && object->isSpawned())
            positions.push_back(object->GetPosition());
    }

    return positions;
}

std::vector<Position> const& GetCachedHazardPositions(PlayerbotAI* botAI, char const* value)
{
    return botAI->GetAiObjectContext()->GetValue<std::vector<Position>>(value)->RefGet();
}

bool IsInHazard(PlayerbotAI* botAI, char const* value, float radius)
{
    Player* bot = botAI->GetBot();
    for (Position const& position : GetCachedHazardPositions(botAI, value))
    {
        if (bot->GetExactDist2d(position) < radius)
            return true;
    }

    return false;
}

bool FindPositionOutsideHazards(
    PlayerbotAI* botAI, char const* value, float radius, Position& outPos)
{
    std::vector<Position> const& hazards = GetCachedHazardPositions(botAI, value);
    if (hazards.empty())
        return false;

    Player* bot = botAI->GetBot();

    constexpr float minSearchRadius = 2.0f;
    constexpr float distanceStep = 2.0f;
    constexpr uint8 numDistSteps = 10;
    constexpr uint8 numAngles = 24;
    constexpr float angleStep = 2.0f * static_cast<float>(M_PI) / numAngles;

    for (uint8 i = 0; i <= numDistSteps; ++i)
    {
        float const distance = minSearchRadius + i * distanceStep;
        for (uint8 j = 0; j < numAngles; ++j)
        {
            float const angle = j * angleStep;
            float const x = bot->GetPositionX() + distance * std::cos(angle);
            float const y = bot->GetPositionY() + distance * std::sin(angle);

            bool safe = true;
            for (Position const& hazard : hazards)
            {
                if (hazard.GetExactDist2d(x, y) <= radius)
                {
                    safe = false;
                    break;
                }
            }

            if (safe)
            {
                outPos = Position(x, y, bot->GetPositionZ());
                return true;
            }
        }
    }

    return false;
}

// Tanking

bool CastTankTaunt(PlayerbotAI* botAI, Unit* target)
{
    if (!target)
        return false;

    char const* taunt = nullptr;
    switch (botAI->GetBot()->getClass())
    {
        case CLASS_DEATH_KNIGHT:
            taunt = "dark command";
            break;
        case CLASS_DRUID:
            taunt = "growl";
            break;
        case CLASS_PALADIN:
            taunt = "hand of reckoning";
            break;
        case CLASS_WARRIOR:
            taunt = "taunt";
            break;
        default:
            return false;
    }

    return botAI->CanCastSpell(taunt, target) && botAI->CastSpell(taunt, target);
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

// High Priest Thekal

bool IsThekalTrioFight(PlayerbotAI* botAI)
{
    return GetCachedUnitOfEntry(botAI, THEKAL_TRIO_VALUE, Id(ZulGurubNpcs::NPC_ZEALOT_LORKHAN)) ||
        GetCachedUnitOfEntry(botAI, THEKAL_TRIO_VALUE, Id(ZulGurubNpcs::NPC_ZEALOT_ZATH));
}

Unit* GetThekalTrioFocus(PlayerbotAI* botAI)
{
    // Thekal alone is the tiger phase, which the ordinary tank and dps objects already cover.
    if (!IsThekalTrioFight(botAI))
        return nullptr;

    Unit* focus = nullptr;
    for (Unit* candidate : GetCachedUnits(botAI, THEKAL_TRIO_VALUE))
    {
        if (IsUnassailable(candidate))
            continue;

        if (!focus || candidate->GetHealthPct() > focus->GetHealthPct())
            focus = candidate;
    }

    return focus;
}

}  // namespace ZulGurubHelpers
