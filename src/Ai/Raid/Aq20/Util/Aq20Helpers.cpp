/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#include "Aq20Helpers.h"
#include "Creature.h"
#include "GameObject.h"
#include "ObjectAccessor.h"
#include "Playerbots.h"
#include "SpellAuras.h"
#include "ThreatManager.h"
#include <algorithm>
#include <cmath>
#include <limits>
#include <list>

namespace Aq20Helpers
{

namespace
{

// A crystal rolls one of these five on Ossirian (OSS:344), so the raid cannot know in advance
// which one is on him.
constexpr uint32 OSSIRIAN_WEAKNESSES[] = {
    Id(Aq20Spells::SPELL_FIRE_WEAKNESS), Id(Aq20Spells::SPELL_FROST_WEAKNESS),
    Id(Aq20Spells::SPELL_NATURE_WEAKNESS), Id(Aq20Spells::SPELL_ARCANE_WEAKNESS),
    Id(Aq20Spells::SPELL_SHADOW_WEAKNESS)};

// Milliseconds left on the shortest weakness currently on Ossirian, or a very large number when
// none is on him at all.
int32 GetWeaknessTimeRemaining(Unit* ossirian)
{
    int32 remaining = std::numeric_limits<int32>::max();
    for (uint32 const weakness : OSSIRIAN_WEAKNESSES)
    {
        Aura* aura = ossirian->GetAura(weakness);
        if (!aura)
            continue;

        int32 const duration = aura->GetDuration();
        if (duration < remaining)
            remaining = duration;
    }

    return remaining;
}

// Rings around the bot, searched outwards, for the first point clear of every hazard.
template <typename Fn>
bool FindPositionAwayFrom(Player* bot, Fn isSafeAt, Position& outPos)
{
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

            if (isSafeAt(x, y))
            {
                outPos = Position(x, y, bot->GetPositionZ());
                return true;
            }
        }
    }

    return false;
}

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

GuidVector FindGameObjectGuids(Player* bot, std::vector<uint32> const& entries, float radius)
{
    GuidVector guids;
    for (uint32 const entry : entries)
    {
        std::list<GameObject*> gameObjects;
        bot->GetGameObjectListWithEntryInGrid(gameObjects, entry, radius);
        for (GameObject* gameObject : gameObjects)
        {
            if (gameObject && gameObject->IsInWorld())
                guids.push_back(gameObject->GetGUID());
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

    return FindPositionAwayFrom(botAI->GetBot(), [&hazards, radius](float x, float y)
    {
        for (Unit* hazard : hazards)
        {
            if (hazard->GetExactDist2d(x, y) <= radius)
                return false;
        }

        return true;
    }, outPos);
}

std::vector<GameObject*> GetCachedGameObjects(PlayerbotAI* botAI, char const* value)
{
    GuidVector const& guids = botAI->GetAiObjectContext()->GetValue<GuidVector>(value)->RefGet();

    Player* bot = botAI->GetBot();
    std::vector<GameObject*> gameObjects;
    gameObjects.reserve(guids.size());
    for (ObjectGuid const guid : guids)
    {
        GameObject* gameObject = ObjectAccessor::GetGameObject(*bot, guid);
        if (gameObject && gameObject->IsInWorld())
            gameObjects.push_back(gameObject);
    }

    return gameObjects;
}

bool IsNearCachedGameObject(PlayerbotAI* botAI, char const* value, float radius)
{
    Player* bot = botAI->GetBot();
    for (GameObject* gameObject : GetCachedGameObjects(botAI, value))
    {
        if (bot->GetExactDist2d(gameObject) < radius)
            return true;
    }

    return false;
}

bool FindPositionAwayFromCachedGameObjects(
    PlayerbotAI* botAI, char const* value, float radius, Position& outPos)
{
    std::vector<GameObject*> const hazards = GetCachedGameObjects(botAI, value);
    if (hazards.empty())
        return false;

    return FindPositionAwayFrom(botAI->GetBot(), [&hazards, radius](float x, float y)
    {
        for (GameObject* hazard : hazards)
        {
            if (hazard->GetExactDist2d(x, y) <= radius)
                return false;
        }

        return true;
    }, outPos);
}

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

bool IsMoamInStonePhase(Unit* moam)
{
    return moam && moam->HasAura(Id(Aq20Spells::SPELL_ENERGIZE));
}

bool IsBuruInEggPhase(Unit* buru)
{
    return buru && buru->HasAura(Id(Aq20Spells::SPELL_THORNS));
}

bool IsFixatedByBuru(Player* bot)
{
    Unit* buru = FindThreatCreature(bot, Id(Aq20Npcs::NPC_BURU));
    if (!IsBuruInEggPhase(buru))
        return false;

    return buru->GetVictim() == bot;
}

Unit* GetBuruTargetEgg(PlayerbotAI* botAI)
{
    Player* bot = botAI->GetBot();
    Unit* buru = FindThreatCreature(bot, Id(Aq20Npcs::NPC_BURU));
    if (!IsBuruInEggPhase(buru))
        return nullptr;

    Unit* target = nullptr;
    float targetDistance = EGG_EXPLOSION_REACH;
    for (Unit* egg : GetCachedUnits(botAI, BURU_EGGS_VALUE))
    {
        if (!IsAttackableNow(egg))
            continue;

        float const distance = buru->GetExactDist(egg);
        if (distance < targetDistance)
        {
            target = egg;
            targetDistance = distance;
        }
    }

    return target;
}

Unit* GetNearestBuruEgg(PlayerbotAI* botAI)
{
    Unit* buru = FindThreatCreature(botAI->GetBot(), Id(Aq20Npcs::NPC_BURU));
    if (!IsBuruInEggPhase(buru))
        return nullptr;

    return GetNearestAttackableCachedUnit(botAI, BURU_EGGS_VALUE);
}

bool IsAyamissInAirPhase(Unit* ayamiss)
{
    return ayamiss && ayamiss->IsLevitating();
}

bool CanTankAyamiss(Unit* ayamiss)
{
    Creature* boss = ayamiss ? ayamiss->ToCreature() : nullptr;
    return IsAttackableNow(boss) && !IsAyamissInAirPhase(boss) && boss->HasReactState(REACT_AGGRESSIVE);
}

GameObject* GetUsableOssirianCrystal(PlayerbotAI* botAI)
{
    Player* bot = botAI->GetBot();
    GameObject* nearest = nullptr;
    float nearestDistance = std::numeric_limits<float>::max();
    for (GameObject* crystal : GetCachedGameObjects(botAI, OSSIRIAN_CRYSTALS_VALUE))
    {
        // The script clears the flag on every crystal it spawns (OSS:134, :232), so a crystal
        // carrying it has been clicked already.
        if (crystal->HasGameObjectFlag(GO_FLAG_IN_USE))
            continue;

        float const distance = bot->GetExactDist(crystal);
        if (distance < nearestDistance)
        {
            nearest = crystal;
            nearestDistance = distance;
        }
    }

    return nearest;
}

bool IsOssirianCrystalDue(Unit* ossirian, uint32 leadTimeMs)
{
    if (!ossirian)
        return false;

    if (ossirian->HasAura(Id(Aq20Spells::SPELL_STRENGTH_OF_OSSIRIAN)))
        return true;

    return GetWeaknessTimeRemaining(ossirian) < static_cast<int32>(leadTimeMs);
}

}
