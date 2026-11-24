/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#include "BWLMultipliers.h"
#include "BWLActions.h"
#include "BWLHelpers.h"
#include "ChooseTargetActions.h"
#include "GenericSpellActions.h"
#include "HunterActions.h"
#include "Playerbots.h"
#include "ReachTargetActions.h"
#include "Strategy.h"

using namespace BlackwingLairHelpers;

static constexpr float VAELASTRASZ_BA_SAFE_DISTANCE = 20.0f;
static constexpr float VAELASTRASZ_BA_BOSS_DISTANCE = 30.0f;

float ChromaggusMultiplier::GetValue(Action* action)
{
    Unit* boss = GetEngagedChromaggus(bot);
    if (!boss || !boss->GetVictim())
        return 1.0f;

    // Hold cover until the breath finishes, including when the current DPS target changes.
    if (dynamic_cast<MovementAction*>(action) && ShouldHideFromBreath(boss, bot) && !boss->IsWithinLOSInMap(bot))
        return 0.0f;

    auto* cast = dynamic_cast<CastSpellAction*>(action);
    if (!cast)
        return 1.0f;

    if (dynamic_cast<CastCureSpellAction*>(cast) || dynamic_cast<CurePartyMemberAction*>(cast))
    {
        Unit* target = cast->GetTarget();
        if (!target)
            return 1.0f;

        // The fifth distinct affliction causes Chromatic Mutation immediately.
        constexpr uint32 afflictions[] = {23153, 23154, 23155, 23169, 23170};
        unsigned count = 0;
        for (uint32 affliction : afflictions)
            if (target->HasAura(affliction))
                ++count;

        return count >= 3 ? (ACTION_RAID + 1) / ACTION_DISPEL : 1.0f;
    }

    if (AI_VALUE(Unit*, "current target") != boss || cast->GetTarget() != boss)
        return 1.0f;

    SpellInfo const* info = sSpellMgr->GetSpellInfo(AI_VALUE2(uint32, "spell id", cast->getSpell()));
    if (!info || !info->HasEffect(SPELL_EFFECT_SCHOOL_DAMAGE))
        return 1.0f;

    // Prefer a matching damage school without blocking single-school rotations.
    static constexpr SpellSchoolMask schools[] = {SPELL_SCHOOL_MASK_FIRE, SPELL_SCHOOL_MASK_FROST,
                                                  SPELL_SCHOOL_MASK_SHADOW, SPELL_SCHOOL_MASK_NATURE,
                                                  SPELL_SCHOOL_MASK_ARCANE};
    constexpr uint32 firstShield = 22277;
    for (uint32 i = 0; i < std::size(schools); ++i)
        if ((info->GetSchoolMask() & schools[i]) && boss->HasAura(firstShield + i))
            return 1.1f;

    return 1.0f;
}

float RazorgoreTankMultiplier::GetValue(Action* action)
{
    if (!PlayerbotAI::IsTank(bot))
        return 1.0f;

    Unit* boss = AI_VALUE2(Unit*, "find target", "razorgore the untamed");
    if (!boss)
        return 1.0f;

    if (AreRazorgoreEggsAlive(botAI))
    {
        // Off-tank picks up boss, blocks TankAssistAction to avoid changing targets
        if (IsRazorgoreOffTank(bot) && bot->GetVictim() != nullptr && dynamic_cast<TankAssistAction*>(action))
            return 0.0f;
        return 1.0f;
    }

    // All eggs destroyed. Tanks not targeted by the boss don't run into the Cleave.
    if (boss->GetVictim() != bot && dynamic_cast<TankFaceAction*>(action))
        return 0.0f;
    return 1.0f;
}

float VaelastraszTankMultiplier::GetValue(Action* action)
{
    if (!PlayerbotAI::IsTank(bot))
        return 1.0f;

    Unit* boss = AI_VALUE2(Unit*, "find target", "vaelastrasz the corrupt");
    if (!boss)
        return 1.0f;

    // Stay at rear flank position and don't move in front of the boss.
    if (dynamic_cast<TankFaceAction*>(action))
    {
        Unit* victim = boss->GetVictim();
        Player* victimPlayer = victim ? victim->ToPlayer() : nullptr;
        if (victim != bot && victimPlayer && PlayerbotAI::IsTank(victimPlayer))
            return 0.0f;
    }

    return 1.0f;
}

float VaelastraszBurningAdrenalineMultiplier::GetValue(Action* action)
{
    if (bot->HasAura(static_cast<uint32>(BlackwingLairSpells::SPELL_BURNING_ADRENALINE)))
    {
        if (dynamic_cast<MovementAction*>(action))
        {
            if (dynamic_cast<BwlVaelastraszMoveAwayAction*>(action))
            {
                // Allow movement when boss is dead or bot was knocked away
                Unit* boss = AI_VALUE2(Unit*, "find target", "vaelastrasz the corrupt");
                if (!boss || !boss->IsAlive() || bot->GetDistance2d(boss) > VAELASTRASZ_BA_BOSS_DISTANCE)
                    return 1.0f;
            }

            // Block ALL other movement once bot is far enough from non-BA bots
            if (!IsNonBABotNearPosition(bot, bot->GetPosition(), VAELASTRASZ_BA_SAFE_DISTANCE) ||
                !dynamic_cast<BwlVaelastraszMoveAwayAction*>(action))
                return 0.0f;
        }
        // Also block charge actions
        if (dynamic_cast<CastReachTargetSpellAction*>(action))
            return 0.0f;
    }

    return 1.0f;
}

float NefarianCorruptedHealingMultiplier::GetValue(Action* action)
{
    // Priest call: a holy heal that is not a heal-over-time puts a damage-over-time effect on its target instead.
    if (bot->getClass() != CLASS_PRIEST ||
        !bot->HasAura(static_cast<uint32>(BlackwingLairSpells::SPELL_CORRUPTED_HEALING)))
        return 1.0f;

    auto* spellAction = dynamic_cast<CastSpellAction*>(action);
    if (!spellAction)
        return 1.0f;

    static std::unordered_set<std::string> const directHeals = {
        "lesser heal", "heal", "greater heal", "flash heal", "binding heal", "penance", "prayer of healing",
        "circle of healing", "prayer of mending", "desperate prayer", "divine hymn", "holy nova"};
    std::string const spell = spellAction->getSpell();
    if (directHeals.count(spell))
        return 0.0f;

    // Empowered Renew adds an instant direct heal to Renew.
    if (spell == "renew" && (bot->HasAura(static_cast<uint32>(BlackwingLairSpells::SPELL_EMPOWERED_RENEW_R1)) ||
                             bot->HasAura(static_cast<uint32>(BlackwingLairSpells::SPELL_EMPOWERED_RENEW_R2)) ||
                             bot->HasAura(static_cast<uint32>(BlackwingLairSpells::SPELL_EMPOWERED_RENEW_R3))))
        return 0.0f;

    // The glyph adds a direct heal to the shield.
    if (spell == "power word: shield" &&
        bot->HasAura(static_cast<uint32>(BlackwingLairSpells::SPELL_GLYPH_OF_POWER_WORD_SHIELD)))
        return 0.0f;

    return 1.0f;
}

float NefarianCorruptedTotemMultiplier::GetValue(Action* action)
{
    // Keeps DPS on a corrupted totem until it dies instead of switching back to the dps, AoE or RTI target.
    if ((!dynamic_cast<DpsAssistAction*>(action) && !dynamic_cast<DpsAoeAction*>(action) &&
         !dynamic_cast<AttackRtiTargetAction*>(action)) ||
        !PlayerbotAI::IsDps(bot))
        return 1.0f;

    Unit* target = AI_VALUE(Unit*, "current target");
    return target && target->IsAlive() && IsCorruptedTotem(target) ? 0.0f : 1.0f;
}
