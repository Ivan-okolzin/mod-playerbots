/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#include "VoAHelpers.h"
#include "Creature.h"
#include "EncounterHelpers.h"
#include "Playerbots.h"
#include "SpellAuras.h"
#include "ThreatManager.h"
#include <algorithm>
#include <cmath>
#include <limits>
#include <list>

namespace VoAHelpers
{

// Bosses and adds

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

bool IsAttackableNow(Unit* unit)
{
    return unit && !unit->HasUnitFlag(UNIT_FLAG_NOT_SELECTABLE) &&
        !unit->HasUnitFlag(UNIT_FLAG_NON_ATTACKABLE);
}

Unit* GetNearestAttackableCachedUnit(PlayerbotAI* botAI, char const* value)
{
    Player* bot = botAI->GetBot();
    Unit* nearest = nullptr;
    float nearestDistance = std::numeric_limits<float>::max();
    for (Unit* unit : GetCachedUnits(botAI, value))
    {
        if (!IsAttackableNow(unit))
            continue;

        float const distance = bot->GetExactDist(unit);
        if (distance < nearestDistance)
        {
            nearest = unit;
            nearestDistance = distance;
        }
    }

    return nearest;
}

// Creature hazards

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

namespace
{

// One ring search shared by the creature hazards and the ground hazards: the rings grow outwards
// from the bot, so the first point that clears every hazard is also the nearest one.
template <typename HazardList, typename DistanceToHazard>
bool FindSafeRingPosition(
    Player* bot, HazardList const& hazards, float radius, DistanceToHazard distance,
    Position& outPos)
{
    if (hazards.empty())
        return false;

    constexpr float minSearchRadius = 2.0f;
    constexpr float distanceStep = 2.0f;
    constexpr uint8 numDistSteps = 12;
    constexpr uint8 numAngles = 24;
    constexpr float angleStep = 2.0f * static_cast<float>(M_PI) / numAngles;

    for (uint8 i = 0; i <= numDistSteps; ++i)
    {
        float const ring = minSearchRadius + i * distanceStep;
        for (uint8 j = 0; j < numAngles; ++j)
        {
            float const angle = j * angleStep;
            float const x = bot->GetPositionX() + ring * std::cos(angle);
            float const y = bot->GetPositionY() + ring * std::sin(angle);

            bool safe = true;
            for (auto const& hazard : hazards)
            {
                if (distance(hazard, x, y) <= radius)
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

}

bool FindPositionAwayFromCachedUnits(
    PlayerbotAI* botAI, char const* value, float radius, Position& outPos)
{
    return FindSafeRingPosition(
        botAI->GetBot(), GetCachedUnits(botAI, value), radius,
        [](Unit* hazard, float x, float y) { return hazard->GetExactDist2d(x, y); }, outPos);
}

// Ground hazards left by a spell rather than by a creature

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
    return FindSafeRingPosition(
        botAI->GetBot(), GetCachedHazardPositions(botAI, value), radius,
        [](Position const& hazard, float x, float y) { return hazard.GetExactDist2d(x, y); },
        outPos);
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

// Emalon the Storm Watcher

Unit* GetOverchargedMinion(PlayerbotAI* botAI)
{
    for (Unit* minion : GetCachedUnits(botAI, EMALON_MINIONS_VALUE))
    {
        if (IsAttackableNow(minion) && minion->HasAura(Id(VoASpells::SPELL_OVERCHARGED)))
            return minion;
    }

    return nullptr;
}

// Koralon the Flame Watcher

bool IsBreathingFire(Unit* koralon)
{
    if (!koralon || !koralon->HasUnitState(UNIT_STATE_CASTING))
        return false;

    return koralon->FindCurrentSpellBySpellId(Id(VoASpells::SPELL_BURNING_BREATH)) != nullptr;
}

bool IsInFrontOfBreath(Player* bot, Unit* koralon)
{
    if (!koralon || bot->GetExactDist(koralon) > BURNING_BREATH_REACH)
        return false;

    return koralon->HasInArc(2.0f * BURNING_BREATH_HALF_ARC, bot);
}

// Toravon the Ice Watcher

Unit* GetPursuingFrozenOrb(PlayerbotAI* botAI)
{
    Player* bot = botAI->GetBot();
    for (Unit* orb : GetCachedUnits(botAI, TORAVON_FROZEN_ORBS_VALUE))
    {
        if (orb->GetVictim() == bot)
            return orb;
    }

    return nullptr;
}

}
