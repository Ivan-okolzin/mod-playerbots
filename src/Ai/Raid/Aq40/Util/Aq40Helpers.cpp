/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#include "Aq40Helpers.h"
#include "Creature.h"
#include "Playerbots.h"
#include "SpellAuras.h"
#include "ThreatHelpers.h"
#include <algorithm>
#include <cmath>
#include <limits>
#include <list>

namespace Aq40Helpers
{

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

bool IsSkeramImage(Unit* unit)
{
    return unit && unit->IsSummon();
}

Unit* GetRealSkeram(PlayerbotAI* botAI)
{
    for (Unit* copy : GetCachedUnits(botAI, SKERAM_COPIES_VALUE))
    {
        if (!IsSkeramImage(copy))
            return copy;
    }

    return nullptr;
}

std::vector<Unit*> GetSkeramImages(PlayerbotAI* botAI)
{
    std::vector<Unit*> images;
    for (Unit* copy : GetCachedUnits(botAI, SKERAM_COPIES_VALUE))
    {
        if (IsSkeramImage(copy))
            images.push_back(copy);
    }

    return images;
}

Unit* GetBugTrioKillTarget(PlayerbotAI* botAI)
{
    Player* bot = botAI->GetBot();
    if (Unit* kri = FindThreatTarget(bot, LORD_KRI_NAME))
        return kri;

    if (Unit* yauj = FindThreatTarget(bot, PRINCESS_YAUJ_NAME))
        return yauj;

    return FindThreatTarget(bot, VEM_NAME);
}

char const* GetCheapestFrostSpell(Player* bot)
{
    switch (bot->getClass())
    {
        case CLASS_MAGE:
            return "ice lance";
        case CLASS_SHAMAN:
            return "frost shock";
        case CLASS_DEATH_KNIGHT:
            return "icy touch";
        default:
            return nullptr;
    }
}

bool IsViscidusFrozen(Unit* viscidus)
{
    return viscidus && viscidus->HasAura(Id(Aq40Spells::SPELL_VISCIDUS_FREEZE));
}

// C'Thun

Unit* GetCthunEye(PlayerbotAI* botAI)
{
    return FindThreatTarget(botAI->GetBot(), CTHUN_EYE_NAME);
}

Unit* GetCthunBody(PlayerbotAI* botAI)
{
    return FindThreatTarget(botAI->GetBot(), CTHUN_NAME);
}

bool IsEyeCastingDarkGlare(Unit* eye)
{
    if (!eye)
        return false;

    return eye->HasAura(Id(Aq40Spells::SPELL_RED_COLORATION)) ||
        eye->HasAura(Id(Aq40Spells::SPELL_FREEZE_ANIM));
}

// The body is flagged unattackable for the whole of phase 1 and is given Carapace half a second
// into phase 2 (boss_cthun.cpp:362, :383), so both tests together are also the phase gate.
bool IsCthunBodyWeakened(Unit* body)
{
    if (!body || body->HasUnitFlag(UNIT_FLAG_NOT_SELECTABLE) ||
        body->HasUnitFlag(UNIT_FLAG_NON_ATTACKABLE))
    {
        return false;
    }

    return !body->HasAura(Id(Aq40Spells::SPELL_CARAPACE_OF_CTHUN));
}

bool IsInCthunStomach(Player* bot)
{
    return bot->HasAura(Id(Aq40Spells::SPELL_DIGESTIVE_ACID)) ||
        bot->GetPositionZ() < CTHUN_STOMACH_Z_CEILING;
}

float NormalizeAngleDelta(float angle)
{
    constexpr float fullCircle = 2.0f * static_cast<float>(M_PI);
    while (angle > static_cast<float>(M_PI))
        angle -= fullCircle;

    while (angle <= -static_cast<float>(M_PI))
        angle += fullCircle;

    return angle;
}

// The script picks the sweep's direction at random for every Dark Glare and puts it nowhere a
// player could read it (boss_cthun.cpp:267, :280), so it is derived from how the Eye's
// orientation changes between two samples.
float DarkGlareSweepSampler::Sample(PlayerbotAI* botAI)
{
    Unit* eye = GetCthunEye(botAI);
    if (!IsEyeCastingDarkGlare(eye))
    {
        lastAngle.reset();
        sweep = 0.0f;
        return sweep;
    }

    float const angle = eye->GetOrientation();
    if (lastAngle)
    {
        float const delta = NormalizeAngleDelta(angle - *lastAngle);
        if (std::fabs(delta) > DARK_GLARE_SWEEP_EPSILON)
            sweep = delta > 0.0f ? 1.0f : -1.0f;
    }

    lastAngle = angle;
    return sweep;
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

}
