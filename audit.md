# Аудит рейдовых тактик mod-playerbots

Источник — `origin/raid/all@50081ef2d70eae8ffd26799032cf16fae67f5388`. Аудит рассчитан по исходникам рейдовых стратегий и `bosses.json`.
Дата: 2026-11-24.

Статусы: **есть** — 4+ механик подключено; **частично** — 1–3 механики; **заглушка** —
подключены только вспомогательные вещи (аура сопротивления, метка, падение с платформы);
**отключено** — объекты есть в коде, но закомментированы; **нет** — ничего.

Итог по 157 энкаунтерам 23 рейдов: **есть** — 94, **частично** — 60, **нет** — 3.


## Classic

### Molten Core (Огненные Недра), карта 409, 40, стратегия `moltencore`

| Босс | Статус | Подключённые триггеры |
|---|---|---|
| Lucifron | частично | `mc lucifron protectors spawned`, `mc lucifron shadow resistance`, `mc lucifron should be tanked` |
| Magmadar | частично | `mc magmadar bot in lava bomb`, `mc magmadar fire resistance`, `mc magmadar should be tanked`, `mc magmadar tremor` |
| Gehennas | частично | `mc gehennas bot in rain of fire`, `mc gehennas flamewakers spawned`, `mc gehennas shadow resistance`, `mc gehennas should be tanked` |
| Garr | частично | `mc garr fire resistance`, `mc garr firesworn spawned`, `mc garr should be tanked` |
| Shazzrah | частично | `mc shazzrah lost threat`, `mc shazzrah ranged`, `mc shazzrah should be tanked` |
| Baron Geddon | частично | `mc baron geddon fire resistance`, `mc baron geddon inferno`, `mc living bomb debuff` |
| Sulfuron Harbinger | частично | `mc sulfuron harbinger fire resistance`, `mc sulfuron harbinger priests spawned`, `mc sulfuron harbinger should be tanked` |
| Golemagg the Incinerator | есть | `mc golemagg fire resistance`, `mc golemagg is assist tank`, `mc golemagg is healer`, `mc golemagg is main tank`, `mc golemagg magma splash`, `mc golemagg mark boss` |
| Majordomo Executus | есть | `mc majordomo adds spawned`, `mc majordomo damage shield`, `mc majordomo lost threat`, `mc majordomo shadow resistance`, `mc majordomo should be tanked` |
| Ragnaros | есть | `mc ragnaros bot in lava burst`, `mc ragnaros fire resistance`, `mc ragnaros lost threat`, `mc ragnaros should be tanked`, `mc ragnaros sons of flame spawned` |

Общее и треш: `mc core hound mark`, `mc in lava`, `mc move from group`, `mc move from lava`

### Blackwing Lair (Логово Крыла Тьмы), карта 469, 40, стратегия `bwl`

| Босс | Статус | Подключённые триггеры |
|---|---|---|
| Razorgore the Untamed | частично | `bwl razorgore fire resistance`, `bwl razorgore not mind controlled` |
| Vaelastrasz the Corrupt | частично | `bwl vaelastrasz burning adrenaline`, `bwl vaelastrasz fire resistance`, `bwl vaelastrasz positioning` |
| Broodlord Lashlayer | частично | `bwl broodlord fire resistance`, `bwl broodlord ranged too close` |
| Firemaw | частично | `bwl firemaw fire resistance`, `bwl firemaw not victim` |
| Ebonroc | частично | `bwl ebonroc not victim`, `bwl ebonroc tank swap` |
| Flamegor | частично | `bwl flamegor fire resistance`, `bwl flamegor not victim` |
| Chromaggus | частично | `bwl chromaggus avoid breath`, `bwl chromaggus fire resistance` |
| Nefarian | частично | `bwl nefarian corrupted totem`, `bwl nefarian positioning`, `bwl nefarian wild magic` |

Общее и треш: `bwl affliction bronze`, `bwl check onyxia scale cloak`, `bwl death talon wyrmguard ranged`, `bwl death talon wyrmguard ranged move away`, `bwl death talon wyrmguard tank`, `bwl death talon wyrmguard tank move away`, `bwl suppression device`, `bwl turn off suppression device`, `bwl use hourglass sand`, `often`

### Zul'Gurub (Зул'Гуруб), карта 309, 20, стратегия `zulgurub`

| Босс | Статус | Подключённые триггеры |
|---|---|---|
| High Priest Venoxis | есть | `high priest venoxis bot in poison cloud`, `high priest venoxis lost threat`, `high priest venoxis serpents spawned`, `high priest venoxis should be tanked` |
| High Priestess Jeklik | есть | `high priestess jeklik bats spawned`, `high priestess jeklik bot in liquid fire`, `high priestess jeklik lost threat`, `high priestess jeklik should be tanked` |
| High Priestess Mar'li | частично | `high priestess mar'li lost threat`, `high priestess mar'li should be tanked`, `high priestess mar'li spawns hatched` |
| Bloodlord Mandokir | есть | `bloodlord mandokir bot is watched`, `bloodlord mandokir lost threat`, `bloodlord mandokir melee in whirlwind range`, `bloodlord mandokir ohgan should be tanked`, `bloodlord mandokir ohgan spawned`, `bloodlord mandokir should be tanked` |
| Edge of Madness (Gri'lek/Hazza'rah/Renataki/Wushoolay) | есть | `gri'lek bot is pursued`, `gri'lek lost threat`, `gri'lek should be tanked`, `hazza'rah illusions spawned`, `hazza'rah ranged should spread`, `hazza'rah should be tanked`, `renataki lost threat`, `renataki should be tanked`, `wushoolay bot in lightning cloud`, `wushoolay ranged should spread`, `wushoolay should be tanked` |
| High Priest Thekal | есть | `high priest thekal lost threat`, `high priest thekal should balance trio damage`, `high priest thekal should be tanked`, `high priest thekal tigers spawned`, `high priest thekal zealots should be tanked` |
| Gahz'ranka | частично | `gahz'ranka lost threat`, `gahz'ranka should be tanked` |
| High Priestess Arlokk | частично | `high priestess arlokk lost threat`, `high priestess arlokk prowlers spawned`, `high priestess arlokk should be tanked` |
| Jin'do the Hexxer | есть | `jin'do the hexxer brain wash totem spawned`, `jin'do the hexxer healing ward spawned`, `jin'do the hexxer hexed the tank`, `jin'do the hexxer shades spawned`, `jin'do the hexxer should be tanked` |
| Hakkar | есть | `hakkar attacking insane ally`, `hakkar lost threat`, `hakkar should be tanked`, `zg bot should pick up poisonous blood` |

Общее и треш: `zg move into poisonous cloud`, `zg no encounter in progress`, `zg reset encounter states`

### Ruins of Ahn'Qiraj (AQ20) (Руины Ан'Киража), карта 509, 20, стратегия `aq20`

| Босс | Статус | Подключённые триггеры |
|---|---|---|
| Kurinnaxx | частично | `kurinnaxx bot in sand trap`, `kurinnaxx main tank has mortal wound stacks`, `kurinnaxx should be tanked` |
| General Rajaxx | частично | `general rajaxx should be tanked` |
| Moam | частично | `moam mana fiends spawned`, `moam should be tanked` |
| Buru the Gorger | есть | `buru the gorger bot is fixated`, `buru the gorger egg should be killed`, `buru the gorger hatchlings spawned`, `buru the gorger should be tanked` |
| Ayamiss the Hunter | частично | `ayamiss the hunter larvae spawned`, `ayamiss the hunter should be tanked`, `ayamiss the hunter swarmers spawned` |
| Ossirian the Unscarred | есть | `ossirian the unscarred bot near sand vortex`, `ossirian the unscarred crystal should be used`, `ossirian the unscarred should be tanked`, `ossirian the unscarred tank should move to crystal` |

### Temple of Ahn'Qiraj (AQ40) (Храм Ан'Киража), карта 531, 40, стратегия `aq40`

| Босс | Статус | Подключённые триггеры |
|---|---|---|
| The Prophet Skeram | есть | `the prophet skeram attacking mind controlled ally`, `the prophet skeram images spawned`, `the prophet skeram ranged should spread`, `the prophet skeram should assign dps priority`, `the prophet skeram should be tanked` |
| Silithid Royalty (Vem / Lord Kri / Princess Yauj) | есть | `bug trio bot in poison cloud`, `bug trio brood spawned`, `bug trio should assign dps priority`, `bug trio targets should be tanked` |
| Battleguard Sartura | есть | `battleguard sartura melee in whirlwind range`, `battleguard sartura royal guards should be tanked`, `battleguard sartura should assign dps priority`, `battleguard sartura should be tanked` |
| Fankriss the Unyielding | есть | `fankriss the unyielding main tank has mortal wound stacks`, `fankriss the unyielding should be tanked`, `fankriss the unyielding spawns present`, `fankriss the unyielding worms spawned` |
| Viscidus | есть | `viscidus frozen`, `viscidus globs spawned`, `viscidus in frost phase`, `viscidus ranged should spread` |
| Princess Huhuran | частично | `princess huhuran bot in noxious poison`, `princess huhuran ranged should spread`, `princess huhuran should be tanked` |
| Twin Emperors (Vek'lor / Vek'nilash) | есть | `twin emperors bot in blizzard`, `twin emperors casters should attack vek'lor`, `twin emperors melee should attack vek'nilash`, `twin emperors should be tanked apart` |
| Ouro | есть | `ouro melee in front of boss`, `ouro ranged should spread`, `ouro scarabs spawned`, `ouro should be tanked`, `ouro submerged` |
| C'Thun | есть | `c'thun body is weakened`, `c'thun bot in stomach with flesh tentacle`, `c'thun bot should leave stomach`, `c'thun eye tentacles spawned`, `c'thun giant claw tentacle spawned`, `c'thun giant eye tentacle spawned`, `c'thun ranged should spread`, `eye of c'thun claw tentacle spawned`, `eye of c'thun dark glare incoming`, `eye of c'thun ranged should spread` |

Общее и треш: `aq40 no encounter in progress`, `aq40 reset encounter states`

### Onyxia's Lair (Логово Ониксии), карта 249, 10/25, стратегия `onyxia`

| Босс | Статус | Подключённые триггеры |
|---|---|---|
| Onyxia | есть | `ony avoid eggs`, `ony deep breath warning`, `ony fireball splash incoming`, `ony near tail`, `ony whelps spawn` |


## TBC

### Karazhan (Каражан), карта 532, 10, стратегия `karazhan`

| Босс | Статус | Подключённые триггеры |
|---|---|---|
| Attumen the Huntsman | частично | `attumen the huntsman phase one active`, `attumen the huntsman phase transition`, `attumen the huntsman phase two active` |
| Moroes | частично | `moroes should prioritize adds` |
| Maiden of Virtue | частично | `maiden of virtue boss engaged by tanks`, `maiden of virtue grounding totem consumes holy fire`, `maiden of virtue holy wrath deals chain damage` |
| Opera: The Wizard of Oz | частично | `wizard of oz need target priority`, `wizard of oz strawman is vulnerable to fire` |
| Opera: The Big Bad Wolf | частично | `big bad wolf boss engaged by tank`, `big bad wolf boss is chasing little red riding hood` |
| Opera: Romulo and Julianne | частично | `romulo and julianne both bosses revived` |
| The Curator | частично | `the curator astral flare spawned`, `the curator boss engaged by ranged`, `the curator boss engaged by tanks` |
| Terestian Illhoof | частично | `terestian illhoof should prioritize chains` |
| Shade of Aran | есть | `shade of aran arcane explosion is casting`, `shade of aran boss casts counterspell nearby`, `shade of aran conjured elementals summoned`, `shade of aran flame wreath is active` |
| Netherspite | есть | `netherspite blue beam is active`, `netherspite boss is banished`, `netherspite bot is not beam blocker`, `netherspite green beam is active`, `netherspite red beam is active`, `netherspite should manage timers and trackers` |
| Chess Event (Echo of Medivh) | нет | — |
| Prince Malchezaar | частично | `prince malchezaar boss engaged by tanks`, `prince malchezaar bot is enfeebled`, `prince malchezaar engaged by non-tanks` |
| Nightbane | есть | `nightbane boss engaged by tanks`, `nightbane boss is flying`, `nightbane bot went out of bounds`, `nightbane ground phase engaged by ranged`, `nightbane pets ignore collision to chase flying boss`, `nightbane should manage timers and trackers` |

Общее и треш: `julianne casting eternal affection`, `julianne interrupt eternal affection`, `karazhan bot is not in combat`, `karazhan enemies cast fear`, `karazhan reset encounter states`, `karazhan set tremor totem`, `mana warp is about to explode`, `mana warp stun creature before warp breach`

### Gruul's Lair (Логово Груула), карта 565, 25, стратегия `gruulslair`

| Босс | Статус | Подключённые триггеры |
|---|---|---|
| High King Maulgar | есть | `high king maulgar channeling whirlwind`, `high king maulgar hunter should misdirect`, `high king maulgar kiggler needs moonkin tank`, `high king maulgar krosh needs mage tank`, `high king maulgar should assign dps priority`, `high king maulgar should stand back from krosh`, `high king maulgar three ogres need melee tanks`, `high king maulgar wild fel stalker spawned`, `high king maulgar wild fel stalkers` |
| Gruul the Dragonkiller | есть | `gruul the dragonkiller bot in cave in`, `gruul the dragonkiller cave in`, `gruul the dragonkiller incoming shatter`, `gruul the dragonkiller ranged should spread`, `gruul the dragonkiller should be tanked` |

Общее и треш: `gruul's lair assign class roles`, `gruul's lair class roles should be assigned`, `gruul's lair no encounter in progress`, `gruul's lair reset encounter states`

### Magtheridon's Lair (Логово Магтеридона), карта 544, 25, стратегия `magtheridon`

| Босс | Статус | Подключённые триггеры |
|---|---|---|
| Magtheridon | есть | `mag burning abyssals`, `mag debris positions`, `magtheridon assist tanks should tank channelers`, `magtheridon burning abyssal spawned`, `magtheridon dps hold is active`, `magtheridon hunter should misdirect channelers`, `magtheridon incoming blast nova`, `magtheridon main tank should tank channelers`, `magtheridon no encounter in progress`, `magtheridon ranged should spread`, `magtheridon should assign dps priority`, `magtheridon should be tanked`, `magtheridon should manage timers and assignments`, `magtheridon standing in debris` |

### Serpentshrine Cavern (Логово Змея), карта 548, 25, стратегия `ssc`

| Босс | Статус | Подключённые триггеры |
|---|---|---|
| Hydross the Unstable | есть | `hydross the unstable dps hold is active`, `hydross the unstable ranged should spread in frost phase`, `hydross the unstable should be tanked by frost tank`, `hydross the unstable should be tanked by nature tank`, `hydross the unstable should manage phase timers`, `hydross the unstable should misdirect upon phase change` |
| The Lurker Below | есть | `ssc lurker guardian tanks`, `ssc lurker guardians`, `the lurker below guardians should be tanked`, `the lurker below melee cannot reach target`, `the lurker below melee in water`, `the lurker below ranged should spread`, `the lurker below should be tanked`, `the lurker below spout is active` |
| Leotheras the Blind | есть | `leotheras the blind channeling whirlwind`, `leotheras the blind dps hold is active`, `leotheras the blind hunter should misdirect demon form`, `leotheras the blind inner demon has awakened`, `leotheras the blind ranged should keep distance`, `leotheras the blind ranged should spread upon pull`, `leotheras the blind should focus boss in final phase`, `leotheras the blind should manage dps hold timers`, `leotheras the blind should separate boss from demon`, `leotheras the blind too many chaos blast stacks`, `leotheras the blind warlock should tank demon form`, `ssc leotheras`, `ssc shadow of leotheras` |
| Fathom-Lord Karathress | есть | `fathom-lord karathress hunter should misdirect`, `fathom-lord karathress pets should be held`, `fathom-lord karathress ranged should spread`, `fathom-lord karathress should assign dps priority`, `fathom-lord karathress should heal caribdis tank`, `fathom-lord karathress should manage dps timer`, `fathom-lord karathress stuck midair after cyclone`, `fathom-lord karathress targets should be tanked` |
| Morogrim Tidewalker | есть | `morogrim tidewalker hunter should misdirect`, `morogrim tidewalker ranged should stack`, `morogrim tidewalker should be tanked`, `morogrim tidewalker too far from boss` |
| Lady Vashj | есть | `lady vashj bot above the ground`, `lady vashj bot in toxic spores`, `lady vashj coilfang elite should be tanked`, `lady vashj coilfang strider should be tanked`, `lady vashj core passing chain member`, `lady vashj entangle on melee`, `lady vashj hunter should misdirect`, `lady vashj main tank needs grounding shaman`, `lady vashj melee near toxic spores`, `lady vashj out of sight in phase 3`, `lady vashj pet should switch target`, `lady vashj ranged reach blocked by toxic spores`, `lady vashj ranged should position in phase 3`, `lady vashj ranged should spread in phase 1`, `lady vashj shaman should ground shock blast`, `lady vashj should assign target priority`, `lady vashj should attack tainted elemental`, `lady vashj should be tanked`, `lady vashj should destroy tainted core`, `lady vashj should hold station in phase 2`, `lady vashj static charge on group member`, `lady vashj static charge on rogue`, `lady vashj station slots need holders`, `lady vashj tainted core looter`, `lady vashj tainted elemental needs looter`, `lady vashj tank is idle away from the middle`, `lady vashj tank needs fear ward`, `ssc toxic spores`, `ssc vashj adds` |

Общее и треш: `greyheart tidecaller mark water elemental totem`, `greyheart tidecaller water elemental totem spawned`, `ssc assign class roles`, `ssc class roles should be assigned`, `ssc no encounter in progress`, `ssc reset encounter states`, `ssc spitfire totem`, `ssc toxic pool`, `ssc water elemental totem`, `underbog colossus escape toxic pool`, `underbog colossus in toxic pool`

### Tempest Keep: The Eye (Крепость Бурь: Око), карта 550, 25, стратегия `tempestkeep`

| Босс | Статус | Подключённые триггеры |
|---|---|---|
| Al'ar | есть | `al'ar embers should be tanked`, `al'ar flies between platforms`, `al'ar hunter should misdirect`, `al'ar in phase 2`, `al'ar incoming flame quills`, `al'ar rising from the ashes`, `al'ar should assign non-tank target`, `al'ar should manage phase tracker`, `tk flame patches` |
| Void Reaver | есть | `void reaver arcane orb is incoming`, `void reaver knock away pulls aggro to non-tanks`, `void reaver ranged should stand back`, `void reaver should be tanked` |
| High Astromancer Solarian | частично | `high astromancer solarian should be tanked`, `high astromancer solarian solarium priests spawned`, `high astromancer solarian wrath of the astromancer` |
| Kael'thas Sunstrider | есть | `kael'thas sunstrider capernian should be tanked by warlock`, `kael'thas sunstrider chased by thaladred`, `kael'thas sunstrider has entered the fight`, `kael'thas sunstrider hunter should misdirect advisors`, `kael'thas sunstrider in gravity lapse phase`, `kael'thas sunstrider legendary axe casts whirlwind`, `kael'thas sunstrider legendary weapons are alive`, `kael'thas sunstrider legendary weapons are dead`, `kael'thas sunstrider legendary weapons are equipped`, `kael'thas sunstrider legendary weapons were lost`, `kael'thas sunstrider raid member is mind controlled`, `kael'thas sunstrider sanguinar or telonicus should be tanked`, `kael'thas sunstrider should assign advisor dps priority`, `kael'thas sunstrider should assign final phase target`, `kael'thas sunstrider should hold phase 3 positions`, `kael'thas sunstrider should manage advisor dps timer`, `kael'thas sunstrider should stand back from capernian`, `tk legendary weapons` |

Общее и треш: `crimson hand centurion cast polymorph`, `crimson hand centurion casts arcane flurry`, `tempest keep assign class roles`, `tempest keep class roles should be assigned`, `tempest keep clear stale falling flag`, `tempest keep no encounter in progress`, `tempest keep reset encounter states`, `tempest keep stuck falling`

### Battle for Mount Hyjal (Битва за Хиджал), карта 534, 25, стратегия `hyjal`

| Босс | Статус | Подключённые триггеры |
|---|---|---|
| Rage Winterchill | есть | `hyjal death and decay`, `rage winterchill hunter should misdirect`, `rage winterchill melee near death and decay`, `rage winterchill ranged in death and decay`, `rage winterchill ranged should spread`, `rage winterchill should be tanked` |
| Anetheron | есть | `anetheron hunter should misdirect`, `anetheron infernals pulse immolation`, `anetheron infernals should be tanked away`, `anetheron near inferno target`, `anetheron ranged should spread`, `anetheron should be tanked`, `anetheron should divide dps`, `anetheron targeted by infernal`, `hyjal infernals` |
| Kaz'rogal | есть | `kaz'rogal below mana threshold`, `kaz'rogal can split malevolent cleave damage`, `kaz'rogal hunter should misdirect`, `kaz'rogal hunter should preserve mana`, `kaz'rogal immunity no longer needed`, `kaz'rogal low on mana`, `kaz'rogal mark on mage or paladin`, `kaz'rogal ranged should avoid war stomp`, `kaz'rogal should be tanked`, `kaz'rogal warlock should manage mana` |
| Azgalor | есть | `azgalor bot is doomed`, `azgalor hunter should misdirect`, `azgalor melee near rain of fire`, `azgalor ranged in rain of fire`, `azgalor ranged should spread`, `azgalor should be tanked`, `azgalor should control doomguards`, `azgalor should divide dps`, `hyjal rain of fire` |
| Archimonde | есть | `archimonde casting air burst`, `archimonde hunter should misdirect`, `archimonde near doomfire`, `archimonde ranged should spread`, `archimonde shaman should protect against fear`, `archimonde should be tanked`, `archimonde stood in doomfire`, `hyjal doomfire trail` |

Общее и треш: `hyjal no encounter in progress`, `hyjal remove dangerous dot`, `hyjal reset encounter states`

### Black Temple (Чёрный храм), карта 564, 25, стратегия `blacktemple`

| Босс | Статус | Подключённые триггеры |
|---|---|---|
| High Warlord Naj'entus | есть | `high warlord naj'entus boss engaged by tanks`, `high warlord naj'entus boss has tidal shield`, `high warlord naj'entus casts needle spines`, `high warlord naj'entus player is impaled`, `high warlord naj'entus pulling boss` |
| Supremus | есть | `supremus boss engaged by ranged`, `supremus boss is fixated on bot`, `supremus need to manage phase timer`, `supremus pulling boss or changing phase`, `supremus volcano is nearby` |
| Shade of Akama | частично | `shade of akama focus target`, `shade of akama killing channelers starts phase 2` |
| Teron Gorefiend | есть | `teron gorefiend boss engaged by ranged`, `teron gorefiend boss engaged by tanks`, `teron gorefiend boss is casting shadow of death`, `teron gorefiend bot has shadow of death`, `teron gorefiend bot transformed into vengeful spirit`, `teron gorefiend pulling boss` |
| Gurtogg Bloodboil | есть | `gurtogg bloodboil boss casts bloodboil`, `gurtogg bloodboil boss engaged by tanks`, `gurtogg bloodboil bot has fel rage`, `gurtogg bloodboil need to manage phase timer`, `gurtogg bloodboil pulling boss` |
| Reliquary of Souls | есть | `reliquary of souls aggro resets upon phase change`, `reliquary of souls essence of desire casting deaden`, `reliquary of souls essence of desire has rune shield`, `reliquary of souls essence of suffering disables healing`, `reliquary of souls essence of suffering fixates on closest target` |
| Mother Shahraz | есть | `mother shahraz boss engaged by tanks`, `mother shahraz bots are linked by fatal attraction`, `mother shahraz pulling boss`, `mother shahraz sinister beam knocks back players`, `mother shahraz tanks are positioning boss` |
| The Illidari Council | есть | `illidari council darkshadow engaged by second assist tank`, `illidari council determining dps assignments`, `illidari council gathios casting judgement of command`, `illidari council gathios engaged by main tank`, `illidari council mage tank needs dedicated healer`, `illidari council malande engaged by first assist tank`, `illidari council need to manage dps timer`, `illidari council pets screw up the pull`, `illidari council pulling bosses`, `illidari council zerevor casts dangerous aoes`, `illidari council zerevor engaged by mage tank` |
| Illidan Stormrage | есть | `illidan stormrage boss casts flame crash in front of main tank`, `illidan stormrage boss deals splash damage`, `illidan stormrage boss is preparing to land`, `illidan stormrage boss spawns adds`, `illidan stormrage boss summoned flames of azzinoth`, `illidan stormrage boss transforms into demon`, `illidan stormrage bot has parasitic shadowfiend`, `illidan stormrage bot struck by dark barrage`, `illidan stormrage cheat`, `illidan stormrage grate is safe from flames`, `illidan stormrage maiev placed shadow trap`, `illidan stormrage need to clear hazards between phases`, `illidan stormrage need to manage dps timer and rti`, `illidan stormrage parasitic shadowfiends run wild`, `illidan stormrage pets die to fire`, `illidan stormrage tank needs aggro`, `illidan stormrage this expansion hates melee` |

Общее и треш: `black temple bot is not in combat`, `black temple erase timers and trackers`

### Zul'Aman (Зул'Аман), карта 568, 10, стратегия `zulaman`

| Босс | Статус | Подключённые триггеры |
|---|---|---|
| Nalorakk | частично | `nalorakk both forms should be tanked`, `nalorakk hunter should misdirect`, `nalorakk spread for surge` |
| Akil'zon | есть | `akil'zon electrical storm incoming`, `akil'zon hunter should misdirect`, `akil'zon should be tanked`, `akil'zon should track electrical storm`, `akil'zon spread for static disruption` |
| Jan'alai | есть | `jan'alai amani'shi hatchers spawned`, `jan'alai fire bombs`, `jan'alai hunter should misdirect`, `jan'alai is fire bombing`, `jan'alai should be tanked`, `jan'alai spread for flame breath` |
| Halazzi | есть | `halazzi hunter should misdirect`, `halazzi should be tanked`, `halazzi should focus dps`, `halazzi spirit lynx has appeared` |
| Hex Lord Malacrass | есть | `hex lord malacrass channeling whirlwind`, `hex lord malacrass freezing trap`, `hex lord malacrass freezing trap placed`, `hex lord malacrass hunter should misdirect`, `hex lord malacrass should prioritize adds` |
| Zul'jin | есть | `zul'jin channeling whirlwind in troll form`, `zul'jin creeping paralysis in bear form`, `zul'jin hunter should misdirect`, `zul'jin should be tanked`, `zul'jin spread for dragonhawk aoe`, `zul'jin summoning cyclones in eagle form` |

Общее и треш: `amani'shi medicine man mark ward`, `amani'shi medicine man summoned ward`, `zul'aman no encounter in progress`, `zul'aman reset encounter states`

### Sunwell Plateau (Плато Солнечного Колодца), карта 580, 25, стратегия `sunwell`

| Босс | Статус | Подключённые триггеры |
|---|---|---|
| Kalecgos / Sathrovarr | частично | `kalecgos bot in dragon realm`, `kalecgos bot in spectral realm` |
| Brutallus | есть | `brutallus bot has meteor slash`, `brutallus bot is burning`, `brutallus bot near burning ally`, `brutallus should be tanked` |
| Felmyst | есть | `felmyst attacking charmed ally`, `felmyst bot near vapor trail`, `felmyst breath incoming`, `felmyst ranged should spread`, `felmyst should be tanked`, `felmyst unyielding dead spawned` |
| Eredar Twins (Alythess / Sacrolash) | есть | `eredar twins casters should attack alythess`, `eredar twins melee should attack lady sacrolash`, `eredar twins ranged should spread`, `eredar twins should be tanked` |
| M'uru / Entropius | есть | `entropius bot near singularity`, `entropius should be tanked`, `m'uru adds spawned`, `m'uru bot in darkness`, `m'uru dark fiends spawned`, `m'uru should be tanked`, `m'uru void sentinel spawned` |
| Kil'jaeden | есть | `kil'jaeden bot in armageddon`, `kil'jaeden hands of the deceiver spawned`, `kil'jaeden ranged should spread`, `kil'jaeden shield orb spawned`, `kil'jaeden should be tanked`, `kil'jaeden sinister reflection spawned` |


## WotLK

### Naxxramas (Наксрамас), карта 533, 10/25, стратегия `naxx`

| Босс | Статус | Подключённые триггеры |
|---|---|---|
| Anub'Rekhan | частично | `anub'rekhan` |
| Grand Widow Faerlina | частично | `faerlina`, `faerlina follower present` |
| Maexxna | частично | `maexxna`, `maexxna web wrap present` |
| Noth the Plaguebringer | есть | `noth the plaguebringer balcony phase`, `noth the plaguebringer lost threat`, `noth the plaguebringer should be tanked`, `noth the plaguebringer skeletons should be tanked` |
| Heigan the Unclean | частично | `heigan melee`, `heigan ranged` |
| Loatheb | частично | `loatheb` |
| Instructor Razuvious | частично | `razuvious nontank`, `razuvious tank` |
| Gothik the Harvester | есть | `gothik the harvester lost threat`, `gothik the harvester should be tanked`, `gothik the harvester spectral adds should be tanked`, `gothik the harvester spectral adds spawned`, `gothik the harvester unrelenting adds should be tanked`, `gothik the harvester unrelenting adds spawned` |
| The Four Horsemen | частично | `four horsemen attractors`, `four horsemen except attractors` |
| Patchwerk | есть | `patchwerk lost threat`, `patchwerk non-melee in hateful strike range`, `patchwerk should be soaked`, `patchwerk should be tanked` |
| Grobbulus | есть | `grobbulus cloud`, `mutating injection melee`, `mutating injection ranged`, `mutating injection removed` |
| Gluth | частично | `gluth`, `gluth main tank mortal wound` |
| Thaddius | есть | `thaddius phase pet`, `thaddius phase pet lose aggro`, `thaddius phase thaddius`, `thaddius phase transition` — закомментировано строк: 2 |
| Sapphiron | частично | `sapphiron flight`, `sapphiron ground` |
| Kel'Thuzad | частично | `kel'thuzad` |

### The Obsidian Sanctum (Обсидиановое святилище), карта 615, 10/25, стратегия `wotlk-os`

| Босс | Статус | Подключённые триггеры |
|---|---|---|
| Sartharion | есть | `flame tsunami`, `sartharion dps`, `sartharion melee positioning`, `sartharion tank`, `twilight fissure` |
| Tenebron | частично | `twilight portal enter`, `twilight portal exit` |
| Shadron | нет | — |
| Vesperon | нет | — |

### The Eye of Eternity (Око Вечности), карта 616, 10/25, стратегия `wotlk-eoe`

| Босс | Статус | Подключённые триггеры |
|---|---|---|
| Malygos | есть | `drake combat`, `group flying`, `malygos`, `power spark` |

### Ulduar (Улдуар), карта 603, 10/25, стратегия `ulduar`

| Босс | Статус | Подключённые триггеры |
|---|---|---|
| Flame Leviathan | частично | `flame leviathan on vehicle`, `flame leviathan vehicle near` |
| Ignis the Furnace Master | есть | `ignis bot in scorched ground`, `ignis brittle construct should be killed`, `ignis fire resistance trigger`, `ignis iron construct should be tanked`, `ignis molten construct should be doused`, `ignis should be tanked` |
| Razorscale | есть | `razorscale avoid devouring flames`, `razorscale avoid sentinel`, `razorscale avoid whirlwind`, `razorscale fire resistance trigger`, `razorscale flying alone`, `razorscale fuse armor trigger`, `razorscale grounded`, `razorscale harpoon trigger` |
| XT-002 Deconstructor | есть | `xt-002 boombot spawned`, `xt-002 bot has gravity bomb`, `xt-002 bot in void zone`, `xt-002 bot near boombot`, `xt-002 heart exposed`, `xt-002 life spark spawned`, `xt-002 pummeller spawned`, `xt-002 ranged should spread`, `xt-002 scrapbot spawned`, `xt-002 should be tanked` |
| The Assembly of Iron | частично | `iron assembly lightning tendrils trigger`, `iron assembly overload trigger`, `iron assembly rune of power trigger` |
| Kologarn | есть | `kologarn attack dps target trigger`, `kologarn crunch armor trigger`, `kologarn eyebeam trigger`, `kologarn fall from floor trigger`, `kologarn mark dps target trigger`, `kologarn nature resistance trigger`, `kologarn rti target trigger`, `kologarn rubble slowdown trigger` |
| Auriaya | есть | `auriaya bot in seeping essence`, `auriaya fall from floor trigger`, `auriaya feral defender spawned`, `auriaya sanctum sentry should be killed`, `auriaya sentries spawned`, `auriaya should be tanked` |
| Hodir | частично | `hodir biting cold`, `hodir frost resistance trigger`, `hodir near snowpacked icicle`, `hodir player ice spawned` |
| Thorim | есть | `thorim arena positioning trigger`, `thorim fall from floor trigger`, `thorim frost resistance trigger`, `thorim gauntlet positioning trigger`, `thorim mark dps target trigger`, `thorim nature resistance trigger`, `thorim phase 2 positioning trigger`, `thorim unbalancing strike trigger` |
| Freya | есть | `freya fire resistance trigger`, `freya mark dps target trigger`, `freya move to healing spore trigger`, `freya nature resistance trigger`, `freya near nature bomb`, `freya strengthened iron roots spawned` |
| Mimiron | есть | `mimiron aerial command unit trigger`, `mimiron cheat trigger`, `mimiron fire resistance trigger`, `mimiron p3wx2 laser barrage trigger`, `mimiron phase 1 positioning trigger`, `mimiron phase 4 mark dps trigger`, `mimiron rapid burst trigger`, `mimiron rocket strike trigger`, `mimiron shock blast trigger` |
| General Vezax | есть | `vezax cheat trigger`, `vezax mark of the faceless trigger`, `vezax saronite animus spawned`, `vezax shadow crash trigger`, `vezax shadow resistance trigger` |
| Yogg-Saron | есть | `sara shadow resistance trigger`, `yogg-saron boss room movement cheat trigger`, `yogg-saron brain link trigger`, `yogg-saron death orb trigger`, `yogg-saron fall from floor trigger`, `yogg-saron guardian positioning trigger`, `yogg-saron illusion room trigger`, `yogg-saron lunatic gaze trigger`, `yogg-saron malady of the mind trigger`, `yogg-saron mark target trigger`, `yogg-saron move to enter portal trigger`, `yogg-saron move to exit portal trigger`, `yogg-saron ominous cloud cheat trigger`, `yogg-saron phase 3 positioning trigger`, `yogg-saron sanity trigger`, `yogg-saron shadow resistance trigger`, `yogg-saron use portal trigger` |
| Algalon the Observer | есть | `algalon big bang incoming`, `algalon bot near cosmic smash`, `algalon collapsing star should be killed`, `algalon constellation chasing bot`, `algalon dark matter spawned`, `algalon main tank has phase punch stacks`, `algalon should be tanked` |

### Trial of the Crusader (Испытание Крестоносца), карта 649, 10/25 + героик, стратегия `trialofthecrusader`

| Босс | Статус | Подключённые триггеры |
|---|---|---|
| Northrend Beasts: Gormok the Impaler | есть | `gormok the impaler bot is snobolled`, `gormok the impaler main tank has impale stacks`, `gormok the impaler should be tanked`, `gormok the impaler snobold on raid member` |
| Northrend Beasts: Acidmaw & Dreadscale | частично | `acidmaw and dreadscale bot in slime pool`, `acidmaw and dreadscale should be tanked` |
| Northrend Beasts: Icehowl | есть | `icehowl bot near arena wall`, `icehowl charge incoming`, `icehowl ranged should spread`, `icehowl should be tanked` |
| Lord Jaraxxus | есть | `lord jaraxxus bot in legion flame`, `lord jaraxxus demon spawned`, `lord jaraxxus ranged should spread`, `lord jaraxxus should be tanked` |
| Faction Champions | частично | `faction champions should focus target` |
| Twin Val'kyr (Fjola / Eydis) | есть | `twin val'kyr bot has no essence`, `twin val'kyr bot near opposite ball`, `twin val'kyr matching ball nearby`, `twin val'kyr pact incoming`, `twin val'kyr should be tanked` |
| Anub'arak | есть | `anub'arak bot near pursuing spike`, `anub'arak bot pursued by spike`, `anub'arak burrowers spawned`, `anub'arak frost sphere should be dropped`, `anub'arak scarabs spawned`, `anub'arak should be tanked` |

### Vault of Archavon (Крепость Аркавона), карта 624, 10/25, стратегия `voa`

| Босс | Статус | Подключённые триггеры |
|---|---|---|
| Archavon the Stone Watcher | частично | `archavon attacking non tank`, `archavon ranged should spread`, `archavon should be tanked` |
| Emalon the Storm Watcher | есть | `emalon fall from floor trigger`, `emalon lighting nova trigger`, `emalon mark boss trigger`, `emalon nature resistance trigger`, `emalon overcharge trigger`, `emalon overcharged minion should be killed`, `emalon ranged should spread`, `emalon should be tanked`, `emalon tempest minions spawned` |
| Koralon the Flame Watcher | частично | `koralon burning breath incoming`, `koralon fire resistance trigger`, `koralon ranged should spread`, `koralon should be tanked` |
| Toravon the Ice Watcher | есть | `toravon bot in freezing ground`, `toravon bot near frozen orb`, `toravon bot pursued by frozen orb`, `toravon frozen orbs spawned`, `toravon should be tanked` |

### Icecrown Citadel (Цитадель Ледяной Короны), карта 631, 10/25 + героик, стратегия `icc`

| Босс | Статус | Подключённые триггеры |
|---|---|---|
| Lord Marrowgar | частично | `icc lm` |
| Lady Deathwhisper | частично | `icc lady deathwhisper` |
| Gunship Battle | есть | `icc gunship cannon near`, `icc gunship rocket jump`, `icc gunship rocket pack setup`, `icc in cannon` |
| Deathbringer Saurfang | частично | `icc dbs` — зарегистрированы, но не подключены: `icc dbs main tank rune of blood` |
| Festergut | частично | `icc festergut avoid malleable goo`, `icc festergut group position`, `icc festergut spore` |
| Rotface | есть | `icc rotface avoid vile gas`, `icc rotface group position`, `icc rotface move away from explosion`, `icc rotface tank position` |
| Professor Putricide | есть | `icc putricide abomination`, `icc putricide gas cloud`, `icc putricide growing ooze puddle`, `icc putricide malleable goo`, `icc putricide mutated plague`, `icc putricide volatile ooze` |
| Blood Prince Council | есть | `icc bpc ball of flame`, `icc bpc empowered vortex`, `icc bpc keleseth tank`, `icc bpc kinetic bomb`, `icc bpc main tank` |
| Blood-Queen Lana'thel | частично | `icc bql group position`, `icc bql pact of darkfallen`, `icc bql vampiric bite` |
| Valithria Dreamwalker | есть | `icc valithria dream cloud`, `icc valithria group`, `icc valithria heal`, `icc valithria portal`, `icc valithria zombie kite` |
| Sindragosa | есть | `icc sindragosa blistering cold`, `icc sindragosa chilled to the bone`, `icc sindragosa frost beacon`, `icc sindragosa frost bomb`, `icc sindragosa group position`, `icc sindragosa hot`, `icc sindragosa mystic buffet`, `icc sindragosa unchained magic` |
| The Lich King | есть | `icc lich king adds`, `icc lich king necrotic plague`, `icc lich king shadow trap`, `icc lich king spirit bomb`, `icc lich king winter` |

Общее и треш: `icc avoid death and decay`, `icc cannon fire`, `icc dark reckoning`, `icc dogs`, `icc dogs tank position`, `icc rotting frost giant tank position`, `icc sister svalna`, `icc valkyre spear`

### The Ruby Sanctum (Рубиновое святилище), карта 724, 10/25 + героик, стратегия `rs`

| Босс | Статус | Подключённые триггеры |
|---|---|---|
| Baltharus the Warborn | есть | `rs baltharus avoid front`, `rs baltharus brand`, `rs baltharus healer position`, `rs baltharus tank position` |
| General Zarithrian | частично | `rs zarithrian adds`, `rs zarithrian tank` |
| Saviana Ragefire | есть | `rs saviana avoid front`, `rs saviana conflagration`, `rs saviana melee spread`, `rs saviana tank position` |
| Halion | есть | `rs halion add tank`, `rs halion adds`, `rs halion avoid cones`, `rs halion combustion`, `rs halion consumption`, `rs halion cutter`, `rs halion enter portal`, `rs halion heal consumption`, `rs halion meteor`, `rs halion p2 avoid cones`, `rs halion p2 tank position`, `rs halion start position`, `rs halion tank position` |

Общее и треш: `rs trash adds`, `rs trash assist tank`, `rs trash main tank`, `rs trash melee flank`, `rs trash ranged`

