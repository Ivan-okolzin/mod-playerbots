/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#include "RaidTrash.h"

#include "CombatManager.h"
#include "EncounterHelpers.h"
#include "GenericSpellActions.h"
#include "InstanceScript.h"
#include "Map.h"
#include "Pet.h"
#include "Playerbots.h"
#include "RtiTargetValue.h"
#include "Spell.h"
#include "SpellMgr.h"
#include <algorithm>
#include <map>

namespace RaidTrash
{
namespace
{
constexpr float TANK_SPACING = 12.0f;

bool IsProtected(Pack const& pack, Unit* target)
{
    return target && pack.protectedTargets.count(target->GetGUID());
}

Pack const& GetPack(PlayerbotAI* ai)
{
    return ai->GetAiObjectContext()->GetValue<Pack>("raid trash pack")->RefGet();
}

void CollectPack(Player* bot, Player* member, std::map<ObjectGuid, Unit*>& mobs, Pack& pack)
{
    if (!member || !member->IsAlive() || !bot->IsWithinDistInMap(member, sPlayerbotAIConfig.SightDistance))
        return;

    // A live cast is its own reservation. Interrupts and failed casts release it automatically.
    if (Spell* cast = member->GetCurrentSpell(CURRENT_GENERIC_SPELL))
        if (cast->m_spellInfo->GetSpellSpecific() == SPELL_SPECIFIC_MAGE_POLYMORPH)
            pack.protectedTargets.insert(cast->m_targets.GetUnitTargetGUID());

    for (auto const& [guid, combat] : member->GetCombatManager().GetPvECombatRefs())
    {
        Unit* enemy = combat->GetOther(member);
        Creature* creature = enemy->ToCreature();
        if (creature && (creature->IsDungeonBoss() || creature->isWorldBoss()))
        {
            pack.bossEngaged = true;
            return;
        }
        if (creature && creature->IsAlive() &&
            bot->IsValidAttackTarget(creature) && bot->IsWithinDistInMap(creature, sPlayerbotAIConfig.SightDistance))
            mobs.emplace(guid, creature);
    }
}

bool InRange(PlayerbotAI* ai, GuidSet const& targets, Unit* center, float range)
{
    if (!center)
        return false;
    for (ObjectGuid guid : targets)
        if (Unit* target = ai->GetUnit(guid))
            if (center->IsWithinDistInMap(target, range))
                return true;
    return false;
}

bool HitsProtected(PlayerbotAI* ai, Pack const& pack, SpellInfo const* info, Unit* target,
    Position const* destination, bool areaThreat)
{
    Player* bot = ai->GetBot();
    auto hitsDestination = [&](float radius)
    {
        if (!destination)
            return InRange(ai, pack.protectedTargets, target, radius);
        for (ObjectGuid guid : pack.protectedTargets)
            if (Unit* unit = ai->GetUnit(guid); unit && unit->GetDistance(*destination) <= radius)
                return true;
        return false;
    };
    // These self buffs trigger damage through secondary spells.
    uint32 first = info->GetFirstRankSpell()->Id;
    if (first == 48505) // Starfall
        return InRange(ai, pack.protectedTargets, bot, 40.0f);
    if (first == 13877 || first == 12328) // Blade Flurry, Sweeping Strikes
        return InRange(ai, pack.protectedTargets, bot, 8.0f);
    switch (first)
    {
        case 8190:  // Magma Totem
        case 13813: // Explosive Trap
            return InRange(ai, pack.protectedTargets, bot, 10.0f);
        case 1535:  // Fire Nova originates at the active fire totem
            return InRange(ai, pack.protectedTargets, ai->GetUnit(bot->m_SummonSlot[SUMMON_SLOT_TOTEM_FIRE]), 10.0f);
        case 44457: // Living Bomb
        case 27243: // Seed of Corruption
        case 48045: // Mind Sear
            return InRange(ai, pack.protectedTargets, target, 15.0f);
        default:
            break;
    }
    if (info->IsPositive() || info->GetSpellSpecific() == SPELL_SPECIFIC_MAGE_POLYMORPH)
        return false;

    if (IsProtected(pack, target))
        return true;

    for (auto const& effect : info->Effects)
    {
        if (!effect.IsEffect())
            continue;
        // Chain spells and melee cleaves can jump beyond their initial target.
        if (effect.ChainTarget > 1 && InRange(ai, pack.protectedTargets, target, 12.5f * (effect.ChainTarget - 1)))
            return true;
        for (auto const& implicit : {effect.TargetA, effect.TargetB})
        {
            if (!implicit.IsArea())
                continue;
            auto ref = implicit.GetReferenceType();
            if (ref == TARGET_REFERENCE_TYPE_DEST && hitsDestination(effect.CalcRadius(bot)))
                return true;
            Unit* center = ref == TARGET_REFERENCE_TYPE_CASTER || ref == TARGET_REFERENCE_TYPE_SRC ? bot : target;
            if (ref != TARGET_REFERENCE_TYPE_DEST && InRange(ai, pack.protectedTargets, center, effect.CalcRadius(bot)))
                return true;
        }
    }

    // Some weapon, glyph and ground effects have no area selector on the cast itself.
    if (areaThreat || first == 845 || first == 6807 || (info->IsChanneled() && (info->Targets & TARGET_FLAG_DEST_LOCATION)))
    {
        if (info->Targets & TARGET_FLAG_DEST_LOCATION)
            return hitsDestination(sPlayerbotAIConfig.AoeRadius);
        return InRange(ai, pack.protectedTargets, bot, sPlayerbotAIConfig.AoeRadius);
    }
    return false;
}

bool UnsafeCast(PlayerbotAI* ai, Pack const& pack, CurrentSpellTypes slot)
{
    Spell* cast = ai->GetBot()->GetCurrentSpell(slot);
    if (!cast || pack.protectedTargets.empty())
        return false;
    return HitsProtected(ai, pack, cast->m_spellInfo, cast->m_targets.GetUnitTarget(),
        cast->m_targets.HasDst() ? cast->m_targets.GetDstPos() : nullptr, false);
}

bool NeedsRelease(PlayerbotAI* ai, Pack const& pack)
{
    Player* bot = ai->GetBot();
    return UnsafeCast(ai, pack, CURRENT_GENERIC_SPELL) || UnsafeCast(ai, pack, CURRENT_CHANNELED_SPELL) ||
        IsProtected(pack, ai->GetAiObjectContext()->GetValue<Unit*>("current target")->Get()) ||
        IsProtected(pack, bot->GetVictim()) || (bot->GetPet() && IsProtected(pack, bot->GetPet()->GetVictim()));
}
}

bool IsActive(Player* bot)
{
    if (!bot->IsInCombat() || !bot->GetGroup() || !bot->GetMap() || !bot->GetMap()->IsRaid())
        return false;
    InstanceScript* instance = bot->GetInstanceScript();
    if (!instance || instance->IsEncounterInProgress())
        return false;
    PlayerbotAI* ai = GET_PLAYERBOT_AI(bot);
    return ai && !GetPack(ai).bossEngaged;
}

Pack PackValue::Calculate()
{
    Pack pack;
    Group* group = bot->GetGroup();
    if (!group)
        return pack;

    std::map<ObjectGuid, Unit*> mobs;
    for (GroupReference* ref = group->GetFirstMember(); ref; ref = ref->next())
    {
        CollectPack(bot, ref->GetSource(), mobs, pack);
        if (pack.bossEngaged)
            return pack;
    }

    // Nearby CC remains visible even when the target drops out of the attackers list.
    for (ObjectGuid guid : AI_VALUE(GuidVector, "possible targets no los"))
        if (Unit* unit = botAI->GetUnit(guid))
            if (unit->IsPolymorphed() || unit->HasBreakableByDamageCrowdControlAura())
                pack.protectedTargets.insert(guid);
    for (auto const& [guid, mob] : mobs)
        if (mob->IsPolymorphed() || mob->HasBreakableByDamageCrowdControlAura())
            pack.protectedTargets.insert(guid);
    for (ObjectGuid guid : pack.protectedTargets)
        mobs.erase(guid);

    if (mobs.empty() || (!PlayerbotAI::IsMainTank(bot) && !PlayerbotAI::IsAssistTank(bot)))
        return pack;

    std::vector<Player*> tanks;
    if (Player* main = EncounterHelpers::GetGroupMainTank(bot);
        main && bot->IsWithinDistInMap(main, sPlayerbotAIConfig.SightDistance))
        tanks.push_back(main);
    for (uint8 index = 0; Player* assist = EncounterHelpers::GetGroupAssistTank(bot, index); ++index)
        if (bot->IsWithinDistInMap(assist, sPlayerbotAIConfig.SightDistance))
            tanks.push_back(assist);
    if (std::find(tanks.begin(), tanks.end(), bot) == tanks.end())
        return pack;

    Player* main = tanks.front();
    // Reserve the skull or MT's current enemy first. Keep existing tank victims,
    // then divide loose enemies among off-tanks in stable GUID order.
    auto focus = mobs.find(group->GetTargetIcon(RtiTargetValue::skullIndex));
    if (focus == mobs.end() && main->GetVictim())
        focus = mobs.find(main->GetVictim()->GetGUID());
    if (focus == mobs.end())
        focus = mobs.begin();

    std::vector<size_t> load(tanks.size());
    std::map<ObjectGuid, Player*> owners;
    owners[focus->first] = main;
    ++load[0];
    for (auto const& [guid, mob] : mobs)
    {
        auto held = std::find(tanks.begin(), tanks.end(), mob->GetVictim());
        if (guid != focus->first && held != tanks.end() && (*held != main || tanks.size() == 1))
        {
            owners[guid] = *held;
            ++load[held - tanks.begin()];
        }
    }
    Unit* choice = nullptr;
    for (auto const& [guid, mob] : mobs)
    {
        Player*& owner = owners[guid];
        if (!owner)
        {
            auto slot = std::min_element(load.begin() + (tanks.size() > 1), load.end());
            owner = tanks[slot - load.begin()];
            ++*slot;
        }
        if (owner != bot)
            pack.otherTanksTargets.insert(guid);
        else if (bot == main && guid == focus->first)
            choice = mob;
        else if (!choice || (bot != main && choice->GetVictim() == bot && mob->GetVictim() != bot))
            choice = mob;
    }
    if (!choice)
        return pack;
    pack.tankTarget = choice->GetGUID();
    if (choice->GetVictim() == bot && bot->IsWithinMeleeRange(choice))
    {
        Unit* closest = nullptr;
        auto consider = [&](Unit* unit)
        {
            if (unit && bot->IsWithinDistInMap(unit, TANK_SPACING) &&
                (!closest || bot->GetDistance(unit) < bot->GetDistance(closest)))
                closest = unit;
        };
        for (ObjectGuid guid : pack.protectedTargets)
            consider(botAI->GetUnit(guid));
        for (Player* tank : tanks)
        {
            if (tank == bot)
                break;
            if (tank->GetVictim() && tank->GetVictim()->GetVictim() == tank)
                consider(tank);
        }
        if (closest)
            pack.spaceFrom = closest->GetGUID();
    }
    return pack;
}

bool ManageTrigger::IsActive()
{
    if (!RaidTrash::IsActive(bot))
        return false;
    Pack const& pack = GetPack(botAI);
    return NeedsRelease(botAI, pack) || pack.spaceFrom ||
        (pack.tankTarget && (!bot->GetVictim() || bot->GetVictim()->GetGUID() != pack.tankTarget));
}

bool ManageAction::Execute(Event)
{
    if (!RaidTrash::IsActive(bot))
        return false;
    context->GetValue<Pack>("raid trash pack")->Reset();
    Pack const& pack = GetPack(botAI);
    if (pack.bossEngaged)
        return false;
    bool released = NeedsRelease(botAI, pack);
    if (released)
    {
        for (auto slot : {CURRENT_GENERIC_SPELL, CURRENT_CHANNELED_SPELL})
            if (UnsafeCast(botAI, pack, slot))
                bot->InterruptSpell(slot);
        if (Pet* pet = bot->GetPet(); pet && IsProtected(pack, pet->GetVictim()))
            pet->AttackStop();
        if (IsProtected(pack, bot->GetVictim()) || IsProtected(pack, AI_VALUE(Unit*, "current target")))
        {
            bot->InterruptSpell(CURRENT_AUTOREPEAT_SPELL);
            bot->AttackStop();
            context->GetValue<Unit*>("current target")->Set(nullptr);
            bot->SetSelection(ObjectGuid::Empty);
        }
    }
    if (Unit* target = botAI->GetUnit(pack.tankTarget))
    {
        if (target->IsAlive() && !target->IsPolymorphed() && !target->HasBreakableByDamageCrowdControlAura() &&
            bot->GetVictim() != target)
            return Attack(target);
        if (Unit* obstacle = botAI->GetUnit(pack.spaceFrom); obstacle && bot->IsWithinDistInMap(obstacle, TANK_SPACING))
            return MoveAway(obstacle, TANK_SPACING + 2.0f - bot->GetDistance(obstacle));
    }
    return released;
}

float ProtectMultiplier::GetValue(Action* action)
{
    if (!RaidTrash::IsActive(bot))
        return 1.0f;
    Pack const& pack = GetPack(botAI);
    if (pack.protectedTargets.empty() && pack.otherTanksTargets.empty())
        return 1.0f;
    if (auto* cast = dynamic_cast<CastSpellAction*>(action))
    {
        if (!pack.protectedTargets.empty() && !dynamic_cast<CastHealingSpellAction*>(cast))
        {
            uint32 id = AI_VALUE2(uint32, "spell id", cast->getSpell());
            SpellInfo const* info = sSpellMgr->GetSpellInfo(id);
            bool areaThreat = cast->getThreatType() == Action::ActionThreatType::Aoe ||
                EncounterHelpers::IsAoeThreatAction(bot, action);
            if (info && HitsProtected(botAI, pack, info, cast->GetTarget(), nullptr, areaThreat))
                return 0.0f;
        }
        if (!pack.otherTanksTargets.empty() && EncounterHelpers::IsTauntAction(bot, action))
        {
            Unit* target = cast->GetTarget();
            if (target && pack.otherTanksTargets.count(target->GetGUID()))
                return 0.0f;
            if (cast->getSpell() == "righteous defense")
            {
                for (ObjectGuid guid : pack.otherTanksTargets)
                    if (Unit* mob = botAI->GetUnit(guid); target && mob && mob->GetVictim() == target)
                        return 0.0f;
            }
            if ((cast->getSpell() == "challenging roar" || cast->getSpell() == "challenging shout") &&
                InRange(botAI, pack.otherTanksTargets, bot, 10.0f))
                return 0.0f;
        }
    }
    if (dynamic_cast<AttackAction*>(action) && !dynamic_cast<ManageAction*>(action))
        if (Unit* target = action->GetTarget(); IsProtected(pack, target) ||
            (target && pack.otherTanksTargets.count(target->GetGUID())))
            return 0.0f;
    return 1.0f;
}
}

void RaidTrashStrategy::AppendTargetExclusions(GuidSet& exclusions, TargetValueExclusionType type)
{
    if (!RaidTrash::IsActive(botAI->GetBot()))
        return;
    auto const& pack = RaidTrash::GetPack(botAI);
    exclusions.insert(pack.protectedTargets.begin(), pack.protectedTargets.end());
    if (type == TargetValueExclusionType::TankTarget)
        exclusions.insert(pack.otherTanksTargets.begin(), pack.otherTanksTargets.end());
}

void RaidTrashStrategy::InitTriggers(std::vector<TriggerNode*>& triggers)
{
    triggers.push_back(new TriggerNode("manage raid trash", { NextAction("manage raid trash", ACTION_RAID + 1) }));
}

void RaidTrashStrategy::InitMultipliers(std::vector<Multiplier*>& multipliers)
{
    multipliers.push_back(new RaidTrash::ProtectMultiplier(botAI));
}
