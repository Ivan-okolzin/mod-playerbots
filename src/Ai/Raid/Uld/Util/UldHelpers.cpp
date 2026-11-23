/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#include "UldHelpers.h"
#include "Creature.h"
#include "EncounterHelpers.h"
#include "Playerbots.h"
#include "SpellAuras.h"
#include "ThreatManager.h"
#include <algorithm>
#include <cmath>
#include <limits>
#include <list>

namespace UldHelpers
{

namespace
{

bool HasAnyAura(Unit* unit, std::vector<uint32> const& spellIds)
{
    if (!unit)
        return false;

    for (uint32 const spellId : spellIds)
    {
        if (unit->HasAura(spellId))
            return true;
    }

    return false;
}

Unit* GetNearestCachedUnitIf(
    PlayerbotAI* botAI, char const* value, bool (*predicate)(Unit*))
{
    Player* bot = botAI->GetBot();
    Unit* nearest = nullptr;
    float nearestDistance = std::numeric_limits<float>::max();
    for (Unit* unit : GetCachedUnits(botAI, value))
    {
        if (!predicate(unit))
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

bool IsActiveConstruct(Unit* construct)
{
    return IsAttackableNow(construct);
}

bool IsBrittle(Unit* construct)
{
    return IsAttackableNow(construct) && IsConstructBrittle(construct);
}

}

// Bosses and adds

Unit* FindThreatCreature(Player* bot, std::vector<uint32> const& entries)
{
    for (auto const& [guid, ref] : bot->GetThreatMgr().GetThreatenedByMeList())
    {
        if (std::find(entries.begin(), entries.end(), guid.GetEntry()) == entries.end())
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

bool IsAttackableNow(Unit* unit)
{
    return unit && !unit->HasUnitFlag(UNIT_FLAG_NOT_SELECTABLE) &&
        !unit->HasUnitFlag(UNIT_FLAG_NON_ATTACKABLE);
}

Unit* GetNearestAttackableCachedUnit(PlayerbotAI* botAI, char const* value)
{
    return GetNearestCachedUnitIf(botAI, value, &IsAttackableNow);
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

bool FindPositionAwayFromCachedUnits(
    PlayerbotAI* botAI, char const* value, float radius, Position& outPos)
{
    std::vector<Unit*> const hazards = GetCachedUnits(botAI, value);
    if (hazards.empty())
        return false;

    Player* bot = botAI->GetBot();

    // The rings grow outwards from the bot, so the first point that clears every hazard is also
    // the nearest one.
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

uint8 GetAuraStacks(Unit* unit, uint32 spellId)
{
    if (!unit)
        return 0;

    Aura* aura = unit->GetAura(spellId);
    return aura ? aura->GetStackAmount() : 0;
}

// XT-002 Deconstructor

Unit* GetExposedHeart(PlayerbotAI* botAI)
{
    return GetNearestAttackableCachedUnit(botAI, XT002_HEARTS_VALUE);
}

bool HasGravityBomb(Player* bot)
{
    return HasAnyAura(
        bot, { Id(UldSpells::SPELL_GRAVITY_BOMB), Id(UldSpells::SPELL_GRAVITY_BOMB_25) });
}

// Ignis the Furnace Master

Unit* GetNearestActiveConstruct(PlayerbotAI* botAI)
{
    return GetNearestCachedUnitIf(botAI, IGNIS_CONSTRUCTS_VALUE, &IsActiveConstruct);
}

bool IsConstructMolten(Unit* construct)
{
    return HasAnyAura(construct, { Id(UldSpells::SPELL_MOLTEN) });
}

bool IsConstructBrittle(Unit* construct)
{
    return HasAnyAura(
        construct, { Id(UldSpells::SPELL_BRITTLE), Id(UldSpells::SPELL_BRITTLE_25) });
}

Unit* GetBrittleConstruct(PlayerbotAI* botAI)
{
    return GetNearestCachedUnitIf(botAI, IGNIS_CONSTRUCTS_VALUE, &IsBrittle);
}

Unit* GetHeldMoltenConstruct(PlayerbotAI* botAI)
{
    Player* bot = botAI->GetBot();
    for (Unit* construct : GetCachedUnits(botAI, IGNIS_CONSTRUCTS_VALUE))
    {
        if (!IsAttackableNow(construct) || !IsConstructMolten(construct))
            continue;

        // Already Brittle constructs are left where they are: the raid kills them on the spot.
        if (IsConstructBrittle(construct))
            continue;

        if (construct->GetVictim() == bot)
            return construct;
    }

    return nullptr;
}

Unit* GetNearestWaterTrigger(PlayerbotAI* botAI)
{
    return GetNearestCachedUnit(botAI, IGNIS_WATER_TRIGGERS_VALUE);
}

// Algalon the Observer

bool IsBigBangIncoming(Unit* algalon)
{
    if (!algalon || !algalon->HasUnitState(UNIT_STATE_CASTING))
        return false;

    return algalon->FindCurrentSpellBySpellId(Id(UldSpells::SPELL_BIG_BANG)) != nullptr ||
        algalon->FindCurrentSpellBySpellId(Id(UldSpells::SPELL_BIG_BANG_25)) != nullptr;
}

Unit* GetNearestBlackHole(PlayerbotAI* botAI)
{
    return GetNearestCachedUnit(botAI, ALGALON_BLACK_HOLES_VALUE);
}

Unit* GetChasingConstellation(PlayerbotAI* botAI)
{
    Player* bot = botAI->GetBot();
    for (Unit* constellation : GetCachedUnits(botAI, ALGALON_CONSTELLATIONS_VALUE))
    {
        // A Constellation is passive and untargetable until Algalon calls it (BAL:1044-1057).
        if (!IsAttackableNow(constellation))
            continue;

        if (constellation->GetVictim() == bot)
            return constellation;
    }

    return nullptr;
}

}
