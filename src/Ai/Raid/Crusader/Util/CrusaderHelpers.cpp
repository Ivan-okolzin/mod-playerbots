/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#include "CrusaderHelpers.h"
#include "Creature.h"
#include "EncounterHelpers.h"
#include "Playerbots.h"
#include "Spell.h"
#include "SpellAuras.h"
#include "SpellInfo.h"
#include "ThreatManager.h"
#include <algorithm>
#include <cmath>
#include <limits>
#include <list>

using namespace EncounterHelpers;

namespace CrusaderHelpers
{

namespace
{

constexpr uint8 NOT_A_CHAMPION = 0xFF;

// Kill order of the Faction Champions, lowest first. The healers have to go before anything else
// can be held down, and among them the ones whose heals are hardest to interrupt come first;
// after them the casters, and the melee last, because they are the ones the raid can outlast.
uint8 GetFactionChampionPriority(uint32 entry)
{
    switch (entry)
    {
        case Id(CrusaderNpcs::NPC_HORDE_SHAMAN_RESTORATION):
        case Id(CrusaderNpcs::NPC_ALLIANCE_SHAMAN_RESTORATION):
            return 0;
        case Id(CrusaderNpcs::NPC_HORDE_PALADIN_HOLY):
        case Id(CrusaderNpcs::NPC_ALLIANCE_PALADIN_HOLY):
            return 1;
        case Id(CrusaderNpcs::NPC_HORDE_PRIEST_DISCIPLINE):
        case Id(CrusaderNpcs::NPC_ALLIANCE_PRIEST_DISCIPLINE):
            return 2;
        case Id(CrusaderNpcs::NPC_HORDE_DRUID_RESTORATION):
        case Id(CrusaderNpcs::NPC_ALLIANCE_DRUID_RESTORATION):
            return 3;
        case Id(CrusaderNpcs::NPC_HORDE_WARLOCK):
        case Id(CrusaderNpcs::NPC_ALLIANCE_WARLOCK):
            return 4;
        case Id(CrusaderNpcs::NPC_HORDE_MAGE):
        case Id(CrusaderNpcs::NPC_ALLIANCE_MAGE):
            return 5;
        case Id(CrusaderNpcs::NPC_HORDE_PRIEST_SHADOW):
        case Id(CrusaderNpcs::NPC_ALLIANCE_PRIEST_SHADOW):
            return 6;
        case Id(CrusaderNpcs::NPC_HORDE_DRUID_BALANCE):
        case Id(CrusaderNpcs::NPC_ALLIANCE_DRUID_BALANCE):
            return 7;
        case Id(CrusaderNpcs::NPC_HORDE_HUNTER):
        case Id(CrusaderNpcs::NPC_ALLIANCE_HUNTER):
            return 8;
        case Id(CrusaderNpcs::NPC_HORDE_ROGUE):
        case Id(CrusaderNpcs::NPC_ALLIANCE_ROGUE):
            return 9;
        case Id(CrusaderNpcs::NPC_HORDE_DEATH_KNIGHT):
        case Id(CrusaderNpcs::NPC_ALLIANCE_DEATH_KNIGHT):
            return 10;
        case Id(CrusaderNpcs::NPC_HORDE_SHAMAN_ENHANCEMENT):
        case Id(CrusaderNpcs::NPC_ALLIANCE_SHAMAN_ENHANCEMENT):
            return 11;
        case Id(CrusaderNpcs::NPC_HORDE_PALADIN_RETRIBUTION):
        case Id(CrusaderNpcs::NPC_ALLIANCE_PALADIN_RETRIBUTION):
            return 12;
        case Id(CrusaderNpcs::NPC_HORDE_WARRIOR):
        case Id(CrusaderNpcs::NPC_ALLIANCE_WARRIOR):
            return 13;
        default:
            break;
    }

    return NOT_A_CHAMPION;
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

Unit* GetNearestCachedUnitOfEntry(PlayerbotAI* botAI, char const* value, uint32 entry)
{
    Player* bot = botAI->GetBot();
    Unit* nearest = nullptr;
    float nearestDistance = std::numeric_limits<float>::max();
    for (Unit* unit : GetCachedUnits(botAI, value))
    {
        if (unit->GetEntry() != entry)
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

bool IsSnobolled(PlayerbotAI* botAI, Player* bot)
{
    if (bot->HasAura(Id(CrusaderSpells::SPELL_SNOBOLLED)))
        return true;

    for (Unit* snobold : GetCachedUnits(botAI, GORMOK_SNOBOLDS_VALUE))
    {
        if (snobold->GetVictim() == bot)
            return true;
    }

    return false;
}

Unit* GetNearestLatchedSnobold(PlayerbotAI* botAI)
{
    Player* bot = botAI->GetBot();
    Unit* nearest = nullptr;
    float nearestDistance = std::numeric_limits<float>::max();
    for (Unit* snobold : GetCachedUnits(botAI, GORMOK_SNOBOLDS_VALUE))
    {
        Unit* carrier = snobold->GetVehicleBase();
        if ((carrier && !carrier->IsPlayer()) || !IsAttackableNow(snobold))
            continue;

        float const distance = bot->GetExactDist(snobold);
        if (distance < nearestDistance)
        {
            nearest = snobold;
            nearestDistance = distance;
        }
    }

    return nearest;
}

bool IsWormMobile(Unit* worm)
{
    if (!worm)
        return false;

    uint32 const mobileModel = worm->GetEntry() == Id(CrusaderNpcs::NPC_ACIDMAW) ?
        Id(CrusaderModels::MODEL_ACIDMAW_MOBILE) : Id(CrusaderModels::MODEL_DREADSCALE_MOBILE);

    return worm->GetDisplayId() == mobileModel;
}

bool IsWormSubmerged(Unit* worm)
{
    return worm && worm->HasUnitFlag(UNIT_FLAG_NOT_SELECTABLE);
}

bool HasParalyticToxin(Unit* unit)
{
    if (!unit)
        return false;

    return unit->HasAura(Id(CrusaderSpells::SPELL_PARALYTIC_TOXIN)) ||
        unit->HasAura(Id(CrusaderSpells::SPELL_PARALYTIC_TOXIN_25)) ||
        unit->HasAura(Id(CrusaderSpells::SPELL_PARALYTIC_TOXIN_10H)) ||
        unit->HasAura(Id(CrusaderSpells::SPELL_PARALYTIC_TOXIN_25H));
}

Unit* GetAssignedWorm(PlayerbotAI* botAI)
{
    Player* bot = botAI->GetBot();
    bool const isMainTank = PlayerbotAI::IsMainTank(bot);
    if (!isMainTank && !PlayerbotAI::IsAssistTankOfIndex(bot, 0, true))
        return nullptr;

    Unit* acidmaw = FindThreatCreature(bot, Id(CrusaderNpcs::NPC_ACIDMAW));
    Unit* dreadscale = FindThreatCreature(bot, Id(CrusaderNpcs::NPC_DREADSCALE));
    if (!acidmaw || !dreadscale)
    {
        // Keep the surviving worm on its tank after its partner dies.
        Unit* alone = acidmaw ? acidmaw : dreadscale;
        if (!alone || IsWormSubmerged(alone))
            return nullptr;

        Player* partner = isMainTank ? GetGroupAssistTank(bot, 0) : GetGroupMainTank(bot);
        if (partner && partner->IsAlive() && alone->GetVictim() == partner)
            return nullptr;

        return alone;
    }

    Unit* mobile = IsWormMobile(acidmaw) ? acidmaw : dreadscale;
    Unit* stationary = mobile == acidmaw ? dreadscale : acidmaw;

    // Paralytic Toxin ends in Paralysis and nothing in this core takes it off (BNB:950), so the
    // tank carrying it hands the biting worm over and takes the one that only spits.
    Player* mainTank = GetGroupMainTank(bot);
    Player* assistTank = GetGroupAssistTank(bot, 0);
    bool const mainTankTakesMobile =
        !(HasParalyticToxin(mainTank) && !HasParalyticToxin(assistTank));

    Unit* assigned = (isMainTank == mainTankTakesMobile) ? mobile : stationary;
    return IsWormSubmerged(assigned) ? nullptr : assigned;
}

bool IsIcehowlCharging(Unit* icehowl)
{
    return icehowl && !icehowl->GetVictim();
}

bool IsFactionChampion(uint32 entry)
{
    return GetFactionChampionPriority(entry) != NOT_A_CHAMPION;
}

Unit* FindFactionChampionFocus(Player* bot)
{
    Unit* focus = nullptr;
    uint8 focusPriority = NOT_A_CHAMPION;
    uint32 focusHealth = 0;

    for (auto const& [guid, ref] : bot->GetThreatMgr().GetThreatenedByMeList())
    {
        uint8 const priority = GetFactionChampionPriority(guid.GetEntry());
        if (priority == NOT_A_CHAMPION)
            continue;

        Unit* champion = ref->GetOwner();
        if (!champion || !champion->IsInWorld() || !champion->IsAlive())
            continue;

        if (champion->HasAura(Id(CrusaderSpells::SPELL_DIVINE_SHIELD)))
            continue;

        uint32 const health = champion->GetHealth();
        bool const better = !focus || priority < focusPriority ||
            (priority == focusPriority && health < focusHealth);
        if (!better)
            continue;

        focus = champion;
        focusPriority = priority;
        focusHealth = health;
    }

    return focus;
}

CrusaderEssence GetEssence(Player* bot)
{
    if (bot->HasAura(Id(CrusaderSpells::SPELL_LIGHT_ESSENCE)) ||
        bot->HasAura(Id(CrusaderSpells::SPELL_LIGHT_ESSENCE_25)) ||
        bot->HasAura(Id(CrusaderSpells::SPELL_LIGHT_ESSENCE_10H)) ||
        bot->HasAura(Id(CrusaderSpells::SPELL_LIGHT_ESSENCE_25H)))
    {
        return CrusaderEssence::Light;
    }

    if (bot->HasAura(Id(CrusaderSpells::SPELL_DARK_ESSENCE)) ||
        bot->HasAura(Id(CrusaderSpells::SPELL_DARK_ESSENCE_25)) ||
        bot->HasAura(Id(CrusaderSpells::SPELL_DARK_ESSENCE_10H)) ||
        bot->HasAura(Id(CrusaderSpells::SPELL_DARK_ESSENCE_25H)))
    {
        return CrusaderEssence::Dark;
    }

    return CrusaderEssence::None;
}

CrusaderEssence GetAssignedEssence(Player* bot)
{
    // Each tank takes the colour of the twin it holds, so her melee and her spike land on the
    // essence that absorbs them.
    if (PlayerbotAI::IsMainTank(bot))
        return CrusaderEssence::Light;

    if (PlayerbotAI::IsAssistTankOfIndex(bot, 0, true))
        return CrusaderEssence::Dark;

    // Everyone else splits in half by GUID, which every bot can work out for itself and which
    // does not change when somebody dies.
    return (bot->GetGUID().GetRawValue() & 1) ? CrusaderEssence::Light : CrusaderEssence::Dark;
}

bool IsCastingHeal(Unit* unit)
{
    if (!unit)
        return false;

    Spell* cast = unit->GetCurrentSpell(CURRENT_GENERIC_SPELL);
    if (cast && cast->GetSpellInfo() && cast->GetSpellInfo()->IsPositive())
        return true;

    Spell* channel = unit->GetCurrentSpell(CURRENT_CHANNELED_SPELL);
    return channel && channel->GetSpellInfo() && channel->GetSpellInfo()->IsPositive();
}

char const* GetBallValue(Player* bot, bool matching)
{
    CrusaderEssence const essence = GetEssence(bot);
    if (essence == CrusaderEssence::None)
        return nullptr;

    bool const light = (essence == CrusaderEssence::Light) == matching;
    return light ? VALKYR_LIGHT_BALLS_VALUE : VALKYR_DARK_BALLS_VALUE;
}

Unit* GetPactingTwin(PlayerbotAI* botAI)
{
    Player* bot = botAI->GetBot();
    Unit* fjola = FindThreatCreature(bot, Id(CrusaderNpcs::NPC_FJOLA_LIGHTBANE));
    if (IsCastingHeal(fjola))
        return fjola;

    Unit* eydis = FindThreatCreature(bot, Id(CrusaderNpcs::NPC_EYDIS_DARKBANE));
    return IsCastingHeal(eydis) ? eydis : nullptr;
}

bool IsAnubarakSubmerged(Unit* anubarak)
{
    if (!anubarak)
        return false;

    return anubarak->HasUnitFlag(UNIT_FLAG_NOT_SELECTABLE) ||
        anubarak->HasAura(Id(CrusaderSpells::SPELL_ANUBARAK_SUBMERGE));
}

bool IsPursuedBySpike(PlayerbotAI* botAI, Player* bot)
{
    if (bot->HasAura(Id(CrusaderSpells::SPELL_PURSUING_SPIKE_MARK)))
        return true;

    for (Unit* spike : GetCachedUnits(botAI, ANUBARAK_SPIKES_VALUE))
    {
        if (spike->GetVictim() == bot)
            return true;
    }

    return false;
}

Unit* GetNearestPermafrost(PlayerbotAI* botAI)
{
    Player* bot = botAI->GetBot();
    Unit* nearest = nullptr;
    float nearestDistance = std::numeric_limits<float>::max();
    for (Unit* sphere : GetCachedUnits(botAI, ANUBARAK_FROST_SPHERES_VALUE))
    {
        if (std::fabs(sphere->GetPositionZ() - bot->GetPositionZ()) > PERMAFROST_REACH)
            continue;

        float const distance = bot->GetExactDist2d(sphere);
        if (distance < nearestDistance)
        {
            nearest = sphere;
            nearestDistance = distance;
        }
    }

    return nearest;
}

Unit* GetNearestHoveringFrostSphere(PlayerbotAI* botAI)
{
    Player* bot = botAI->GetBot();
    Unit* nearest = nullptr;
    float nearestDistance = std::numeric_limits<float>::max();
    for (Unit* sphere : GetCachedUnits(botAI, ANUBARAK_FROST_SPHERES_VALUE))
    {
        if (sphere->GetPositionZ() - bot->GetPositionZ() <= PERMAFROST_REACH)
            continue;

        float const distance = bot->GetExactDist2d(sphere);
        if (distance < nearestDistance)
        {
            nearest = sphere;
            nearestDistance = distance;
        }
    }

    return nearest;
}

}
