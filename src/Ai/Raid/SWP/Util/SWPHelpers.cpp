/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#include "SWPHelpers.h"
#include "Creature.h"
#include "InstanceScript.h"
#include "Playerbots.h"
#include "ThreatManager.h"
#include <algorithm>
#include <cmath>
#include <limits>
#include <list>

namespace SwpHelpers
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

Unit* GetCachedUnitOfIndex(PlayerbotAI* botAI, char const* value, uint8 index)
{
    std::vector<Unit*> const units = GetCachedUnits(botAI, value);
    return index < units.size() ? units[index] : nullptr;
}

bool IsNearCachedUnit(PlayerbotAI* botAI, char const* value, float radius)
{
    Player* bot = botAI->GetBot();
    for (Unit* unit : GetCachedUnits(botAI, value))
    {
        if (bot->GetExactDist2d(unit) < radius)
            return true;
    }

    return false;
}

bool FindPositionAwayFromCachedUnits(
    PlayerbotAI* botAI, char const* value, float radius, Position& outPos)
{
    std::vector<Unit*> const hazards = GetCachedUnits(botAI, value);
    if (hazards.empty())
        return false;

    Player* bot = botAI->GetBot();

    constexpr float minSearchRadius = 2.0f;
    constexpr float distanceStep = 2.0f;
    constexpr uint8 numDistSteps = 12;
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
            for (Unit* hazard : hazards)
            {
                if (hazard->GetExactDist2d(x, y) <= radius)
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

Unit* GetKalecgosRealmTarget(Player* bot, bool spectral)
{
    if (bot->GetMapId() != SWP_MAP_ID || PlayerbotAI::IsHeal(bot) || spectral != IsInSpectralRealm(bot))
        return nullptr;

    // Instance data keys from sunwell_plateau.h. A newly teleported player can have no threat yet.
    constexpr uint32 dataKalecgos = 0;
    constexpr uint32 dataSathrovarr = 10;
    InstanceScript* instance = bot->GetInstanceScript();
    if (!instance || instance->GetBossState(dataKalecgos) != IN_PROGRESS)
        return nullptr;

    Creature* boss = instance->GetCreature(spectral ? dataSathrovarr : dataKalecgos);
    return boss && bot->IsValidAttackTarget(boss) ? boss : nullptr;
}

bool IsInSpectralRealm(Player* bot)
{
    return bot->HasAura(Id(SwpSpells::SPELL_SPECTRAL_REALM)) ||
        bot->GetPositionZ() < SPECTRAL_REALM_Z_CEILING;
}

bool IsBurning(Unit* unit)
{
    return unit && unit->HasAura(Id(SwpSpells::SPELL_BURN_DAMAGE));
}

}
