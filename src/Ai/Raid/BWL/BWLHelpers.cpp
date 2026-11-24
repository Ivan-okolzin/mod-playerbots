/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#include "BWLHelpers.h"

#include "AiObjectContext.h"
#include "Creature.h"
#include "Group.h"
#include "InstanceScript.h"
#include "Spell.h"

namespace BlackwingLairHelpers
{
    Unit* GetEngagedChromaggus(Player* bot)
    {
        constexpr uint32 chromaggusEncounter = 6;  // DATA_CHROMAGGUS in blackwing_lair.h
        InstanceScript* instance = bot->GetInstanceScript();
        if (bot->GetMapId() != 469 || !instance || instance->GetBossState(chromaggusEncounter) != IN_PROGRESS)
            return nullptr;

        return instance->GetCreature(chromaggusEncounter);
    }

    bool ShouldHideFromBreath(Unit* boss, Player* bot)
    {
        if (!boss || !boss->GetVictim() || boss->GetVictim() == bot)
            return false;

        Spell* cast = boss->GetCurrentSpell(CURRENT_GENERIC_SPELL);
        if (!cast)
            return false;

        switch (static_cast<BlackwingLairSpells>(cast->GetSpellInfo()->Id))
        {
            case BlackwingLairSpells::SPELL_INCINERATE:
            case BlackwingLairSpells::SPELL_TIME_LAPSE:
            case BlackwingLairSpells::SPELL_CORROSIVE_ACID:
            case BlackwingLairSpells::SPELL_IGNITE_FLESH:
            case BlackwingLairSpells::SPELL_FROST_BURN:
                return true;
            default:
                return false;
        }
    }

    bool IsActiveSuppressionDeviceInRange(GameObject const* go, Player const* bot)
    {
        constexpr float suppressionDeviceInteractionDistance = 15.0f;
        return go &&
               go->GetEntry() == static_cast<uint32>(BlackwingLairGameObjects::GO_SUPPRESSION_DEVICE) &&
               go->GetDistance(bot) < suppressionDeviceInteractionDistance &&
               go->GetGoState() == GO_STATE_READY;
    }

    bool AreRazorgoreEggsAlive(PlayerbotAI* botAI)
    {
        GuidVector gos = botAI->GetAiObjectContext()->GetValue<GuidVector>("nearest game objects")->Get();
        for (auto const& guid : gos)
        {
            GameObject const* go = botAI->GetGameObject(guid);
            if (go && go->GetEntry() == static_cast<uint32>(BlackwingLairGameObjects::GO_BLACK_DRAGON_EGG))
                return true;
        }
        return false;
    }

    bool IsRazorgoreOffTank(Player* bot)
    {
        return PlayerbotAI::IsAssistTankOfIndex(bot, 0, true);
    }

    bool IsNonBABotNearPosition(Player const* bot, Position const& position, float distance)
    {
        Group const* group = bot->GetGroup();
        if (!group)
            return false;

        for (GroupReference const* gref = group->GetFirstMember(); gref; gref = gref->next())
        {
            Player const* p = gref->GetSource();
            if (!p || p == bot || !p->IsAlive() || p->GetMapId() != bot->GetMapId())
                continue;

            if (p->HasAura(static_cast<uint32>(BlackwingLairSpells::SPELL_BURNING_ADRENALINE)))
                continue;

            if (p->GetDistance2d(position.GetPositionX(), position.GetPositionY()) < distance)
                return true;
        }

        return false;
    }

    bool IsCorruptedWhelp(Unit const* unit)
    {
        if (!unit)
            return false;

        const uint32 entry = unit->GetEntry();
        return entry == static_cast<uint32>(BlackwingLairNPCs::NPC_CORRUPTED_RED_WHELP) ||
            entry == static_cast<uint32>(BlackwingLairNPCs::NPC_CORRUPTED_GREEN_WHELP) ||
            entry == static_cast<uint32>(BlackwingLairNPCs::NPC_CORRUPTED_BLUE_WHELP) ||
            entry == static_cast<uint32>(BlackwingLairNPCs::NPC_CORRUPTED_BRONZE_WHELP);
    }

    bool IsCorruptedTotemEntry(uint32 entry)
    {
        return entry == static_cast<uint32>(BlackwingLairNPCs::NPC_CORRUPTED_FIRE_NOVA_TOTEM) ||
            entry == static_cast<uint32>(BlackwingLairNPCs::NPC_CORRUPTED_STONESKIN_TOTEM) ||
            entry == static_cast<uint32>(BlackwingLairNPCs::NPC_CORRUPTED_HEALING_TOTEM) ||
            entry == static_cast<uint32>(BlackwingLairNPCs::NPC_CORRUPTED_WINDFURY_TOTEM);
    }

    bool IsCorruptedTotem(Unit const* unit)
    {
        return unit && IsCorruptedTotemEntry(unit->GetEntry());
    }

    Unit* FindCorruptedTotem(PlayerbotAI* botAI)
    {
        // Ranged take the nearest totem, melee only one they can already reach.
        Player* bot = botAI->GetBot();
        Unit* nearest = nullptr;
        float nearestDistance = 0.0f;
        for (ObjectGuid const guid : botAI->GetAiObjectContext()->GetValue<GuidVector>("attackers")->RefGet())
        {
            if (!IsCorruptedTotemEntry(guid.GetEntry()))
                continue;

            Unit* unit = botAI->GetUnit(guid);
            if (!unit || !unit->IsAlive() || (!bot->IsWithinMeleeRange(unit) && !PlayerbotAI::IsRanged(bot)))
                continue;

            float const distance = bot->GetExactDist(unit);
            if (!nearest || distance < nearestDistance)
            {
                nearest = unit;
                nearestDistance = distance;
            }
        }
        return nearest;
    }

    bool IsBoneConstruct(Unit const* unit)
    {
        return unit && unit->GetEntry() == static_cast<uint32>(BlackwingLairNPCs::NPC_BONE_CONSTRUCT);
    }

    bool HasBoneConstructAttacker(PlayerbotAI* botAI)
    {
        for (ObjectGuid const guid : botAI->GetAiObjectContext()->GetValue<GuidVector>("attackers")->RefGet())
        {
            if (guid.GetEntry() != static_cast<uint32>(BlackwingLairNPCs::NPC_BONE_CONSTRUCT))
                continue;

            Unit* unit = botAI->GetUnit(guid);
            if (unit && unit->IsAlive() && unit->IsInCombat())
                return true;
        }
        return false;
    }
}
