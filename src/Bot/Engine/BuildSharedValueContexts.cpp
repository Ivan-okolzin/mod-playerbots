/*
 * This file is part of the mod-playerbots module for AzerothCore. See AUTHORS file for Copyright
 * information; released under GNU GPL v2 license, redistribute/modify under version 2 of the License,
 * or (at your option) any later version.
 */

#include "AiObjectContext.h"
#include "Aq20ValueContext.h"
#include "Aq40ValueContext.h"
#include "GDValueContext.h"
#include "GruulValueContext.h"
#include "HyjalValueContext.h"
#include "MCValueContext.h"
#include "MagValueContext.h"
#include "MechValueContext.h"
#include "MgTValueContext.h"
#include "NaxxValueContext.h"
#include "SSCValueContext.h"
#include "CrusaderValueContext.h"
#include "SWPValueContext.h"
#include "TKValueContext.h"
#include "UBValueContext.h"
#include "UldValueContext.h"
#include "VoAValueContext.h"
#include "ZAValueContext.h"
#include "ZGValueContext.h"
#include "ValueContext.h"

void AiObjectContext::BuildSharedValueContexts(
    SharedNamedObjectContextList<UntypedValue>& valueContexts)
{
    valueContexts.Add(new ValueContext());
    valueContexts.Add(new RaidAq20ValueContext());
    valueContexts.Add(new RaidAq40ValueContext());
    valueContexts.Add(new RaidZulGurubValueContext());
    valueContexts.Add(new RaidGruulsLairValueContext());
    valueContexts.Add(new RaidHyjalValueContext());
    valueContexts.Add(new RaidMagtheridonValueContext());
    valueContexts.Add(new RaidMcValueContext());
    valueContexts.Add(new RaidSscValueContext());
    valueContexts.Add(new RaidSwpValueContext());
    valueContexts.Add(new RaidCrusaderValueContext());
    valueContexts.Add(new RaidNaxxValueContext());
    valueContexts.Add(new RaidTempestKeepValueContext());
    valueContexts.Add(new RaidUlduarValueContext());
    valueContexts.Add(new RaidVoAValueContext());
    valueContexts.Add(new RaidZulAmanValueContext());
    valueContexts.Add(new TbcDungeonMechValueContext());
    valueContexts.Add(new TbcDungeonMgTValueContext());
    valueContexts.Add(new TbcDungeonUnderbogValueContext());
    valueContexts.Add(new WotlkDungeonGDValueContext());
}
