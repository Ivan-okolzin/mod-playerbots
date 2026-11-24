#!/usr/bin/env python3
"""audit.json + session_state.json -> progress.html (окно прогресса оркестровки)."""
import html
import json
import os

BASE = os.path.dirname(os.path.abspath(__file__))
audit = json.load(open(os.path.join(BASE, "audit.json"), encoding="utf-8"))
state = json.load(open(os.path.join(BASE, "session_state.json"), encoding="utf-8"))

LBL = {"good": "есть", "partial": "частично", "stub": "заглушка", "none": "нет",
       "disabled": "откл."}
ORDER = ["good", "partial", "stub", "disabled", "none"]

tot = {}
rows = []
for r in audit["raids"]:
    cnt = {}
    for b in r["bosses"]:
        cnt[b["status"]] = cnt.get(b["status"], 0) + 1
        tot[b["status"]] = tot.get(b["status"], 0) + 1
    rows.append((r, cnt))

total_bosses = sum(tot.values())
by_key = {w["raid"]: w for w in state["work"]}
e = html.escape


def bar(cnt, n):
    out = []
    for st in ORDER:
        if cnt.get(st):
            out.append('<span class="seg %s" style="flex:%d" title="%s: %d"></span>'
                       % (st, cnt[st], LBL[st], cnt[st]))
    return '<span class="bar">%s</span>' % "".join(out)


def counts(cnt):
    return " ".join('<span class="pill %s">%s %d</span>' % (st, LBL[st], cnt[st])
                    for st in ORDER if cnt.get(st))


raid_rows = []
for r, cnt in rows:
    w = by_key.get(r["key"])
    stage = ""
    if w:
        cls = {"готово": "done", "в работе": "live"}.get(w["state"], "wait")
        commit = (' <code>%s</code>' % e(w["commit"])) if w["commit"] else ""
        stage = ('<span class="state %s">%s</span><div class="sub">%s%s<br>%s</div>'
                 % (cls, e(w["state"]), e(w["branch"]), commit, e(w["note"])))
    raid_rows.append(
        '<tr><th scope="row"><span class="rk">%s</span><div class="sub">%s · карта %s · %s</div></th>'
        '<td class="num">%d</td><td>%s%s</td><td class="stage">%s</td></tr>'
        % (e(r["key"]), e(r["name_ru"]), r["map"], e(r["sizes"]), len(r["bosses"]),
           bar(cnt, len(r["bosses"])), counts(cnt), stage))

live = [w for w in state["work"] if w["state"] == "в работе"]
done = [w for w in state["work"] if w["state"] == "готово"]

cards = []
for w in state["work"]:
    cls = {"готово": "done", "в работе": "live"}.get(w["state"], "wait")
    cards.append(
        '<li class="card %s"><div class="chead"><span class="rk">%s</span>'
        '<span class="state %s">%s</span></div><div class="ctitle">%s</div>'
        '<div class="sub">%s</div><div class="meta">%s%s</div></li>'
        % (cls, e(w["raid"]), cls, e(w["state"]), e(w["title"]), e(w["note"]),
           e(w["branch"]), (' · ' + e(w["commit"])) if w["commit"] else ""))

page = """<title>Рейдовые тактики ботов</title>
<meta name="claude:viewport-fit-sides" content="cover">
<style>
/* Слева направо: сводка, затем конвейер агентов, затем таблица всех 23 рейдов. */
:root {
  --bg: #f4f2ee; --panel: #fffefb; --fg: #1b1a17; --muted: #6b675e; --line: #ded9cf;
  --good: #3f7d4e; --partial: #b8882a; --stub: #a4642c; --none: #8d3f3f; --disabled: #7a7a7a;
  --accent: #7a4b18;
  --font-head: "Space Grotesk", "Trebuchet MS", sans-serif;
  --font-body: "Inter", system-ui, sans-serif;
  --font-mono: ui-monospace, "SF Mono", Menlo, monospace;
}
@media (prefers-color-scheme: dark) {
  :root:not([data-theme="light"]) {
    --bg: #15161a; --panel: #1d1f24; --fg: #ece9e3; --muted: #9b968c; --line: #32343b;
    --good: #6fb783; --partial: #d9ad55; --stub: #cf8a4e; --none: #c96a6a; --disabled: #8b8b8b;
    --accent: #d9a86a; color-scheme: dark;
  }
}
:root[data-theme="dark"] {
  --bg: #15161a; --panel: #1d1f24; --fg: #ece9e3; --muted: #9b968c; --line: #32343b;
  --good: #6fb783; --partial: #d9ad55; --stub: #cf8a4e; --none: #c96a6a; --disabled: #8b8b8b;
  --accent: #d9a86a; color-scheme: dark;
}
body { background: var(--bg); color: var(--fg); font-family: var(--font-body);
  padding-left: max(16px, env(safe-area-inset-left, 0px));
  padding-right: max(16px, env(safe-area-inset-right, 0px));
  padding-block: 2rem 3rem; }
.wrap { max-width: 980px; margin: 0 auto; display: flex; flex-direction: column; gap: 2rem; }
h1 { font-family: var(--font-head); font-size: clamp(1.5rem, 4vw, 2.1rem); margin: 0;
  text-wrap: balance; letter-spacing: -0.01em; }
.lede { color: var(--muted); margin: 0.4rem 0 0; max-width: 62ch; line-height: 1.5; }
h2 { font-family: var(--font-head); font-size: 1.05rem; margin: 0 0 0.75rem;
  text-transform: uppercase; letter-spacing: 0.08em; color: var(--muted); }
.sum { display: flex; flex-wrap: wrap; gap: 0.5rem 1.25rem; align-items: baseline; }
.big { font-family: var(--font-head); font-size: 2.4rem; line-height: 1;
  font-variant-numeric: tabular-nums; }
.bar { display: flex; height: 10px; border-radius: 999px; overflow: hidden;
  background: var(--line); min-width: 120px; }
.bar.wide { height: 16px; margin: 0.9rem 0 0.6rem; }
.seg.good { background: var(--good) } .seg.partial { background: var(--partial) }
.seg.stub { background: var(--stub) } .seg.none { background: var(--none) }
.seg.disabled { background: var(--disabled) }
.pill { font-size: 0.78rem; white-space: nowrap; font-variant-numeric: tabular-nums;
  color: var(--muted) }
.pill::before { content: ""; display: inline-block; width: 7px; height: 7px; border-radius: 2px;
  margin-right: 0.35rem; vertical-align: 0.05em; }
.pill.good::before { background: var(--good) } .pill.partial::before { background: var(--partial) }
.pill.stub::before { background: var(--stub) } .pill.none::before { background: var(--none) }
.pill.disabled::before { background: var(--disabled) }
ul.cards { list-style: none; margin: 0; padding: 0; display: grid; gap: 0.75rem;
  grid-template-columns: repeat(auto-fill, minmax(220px, 1fr)); }
.card { background: var(--panel); border: 1px solid var(--line); border-radius: 10px;
  padding: 0.8rem 0.9rem; min-width: 0; }
.card.live { border-color: var(--accent); box-shadow: 0 0 0 1px var(--accent) inset }
.chead { display: flex; justify-content: space-between; align-items: center; gap: 0.5rem }
.rk { font-family: var(--font-mono); font-weight: 600; letter-spacing: 0.02em }
.ctitle { font-family: var(--font-head); margin-top: 0.35rem }
.sub { color: var(--muted); font-size: 0.82rem; line-height: 1.45; margin-top: 0.2rem }
.meta { font-family: var(--font-mono); font-size: 0.74rem; color: var(--muted);
  margin-top: 0.5rem }
.state { font-size: 0.72rem; text-transform: uppercase; letter-spacing: 0.07em;
  padding: 0.12rem 0.45rem; border-radius: 999px; border: 1px solid var(--line);
  white-space: nowrap }
.state.done { color: var(--good); border-color: var(--good) }
.state.live { color: var(--accent); border-color: var(--accent) }
.tablewrap { overflow-x: auto; border: 1px solid var(--line); border-radius: 10px;
  background: var(--panel) }
table { border-collapse: collapse; width: 100%; font-size: 0.88rem }
th, td { text-align: left; padding: 0.6rem 0.75rem; border-bottom: 1px solid var(--line);
  vertical-align: top }
thead th { font-size: 0.74rem; text-transform: uppercase; letter-spacing: 0.07em;
  color: var(--muted); font-weight: 600; white-space: nowrap }
tbody tr:last-child th, tbody tr:last-child td { border-bottom: 0 }
td.num { font-variant-numeric: tabular-nums; text-align: right; width: 1%; color: var(--muted) }
td.stage { width: 30% }
code { font-family: var(--font-mono); font-size: 0.95em }
footer { color: var(--muted); font-size: 0.82rem; line-height: 1.6 }
</style>
<link rel="stylesheet" href="https://fonts.googleapis.com/css2?family=Inter:wght@400;600&family=Space+Grotesk:wght@500;700&display=swap">
<div class="wrap">
  <header>
    <h1>Рейдовые тактики ботов</h1>
    <p class="lede">__NOTE__ Срез на __DATE__: покрытие __BOSSES__ энкаунтеров 23 рейдов
    3.3.5 в <code>mod-playerbots</code>. Статус боссу ставит аудит по числу подключённых
    триггеров с механиками: «есть» — четыре и больше, «частично» — от одного до трёх,
    «заглушка» — только вспомогательные, «нет» — ничего.</p>
  </header>

  <section>
    <h2>Сводка</h2>
    <div class="sum"><span class="big">__GOOD__</span><span class="pill">из __BOSSES__ боссов
      закрыты полностью</span><span class="pill">рейдов в работе: __LIVE__</span>
      <span class="pill">закрыто в этом конвейере: __DONE__</span></div>
    <span class="bar wide">__TOTBAR__</span>
    <div class="sum">__TOTPILLS__</div>
  </section>

  <section>
    <h2>Конвейер: один рейд — один агент</h2>
    <ul class="cards">__CARDS__</ul>
  </section>

  <section>
    <h2>Покрытие по рейдам</h2>
    <div class="tablewrap"><table>
      <thead><tr><th scope="col">Рейд</th><th scope="col">Боссов</th>
        <th scope="col">Покрытие</th><th scope="col">Этап</th></tr></thead>
      <tbody>__ROWS__</tbody>
    </table></div>
  </section>

  <footer>Код пишется против апстрима <code>mod-playerbots</code>, каждый рейд в своей ветке от
  <code>test-staging</code>, всё вместе — в <code>raid/all</code>. Проверки без сборки:
  <code>codestyle-cpp.py</code> и греп таблиц <code>creators</code>; в игре тактики пока не
  проверялись.</footer>
</div>
"""

page = (page
        .replace("__NOTE__", e(state["note"]))
        .replace("__DATE__", e(state["updated"]))
        .replace("__BOSSES__", str(total_bosses))
        .replace("__GOOD__", str(tot.get("good", 0)))
        .replace("__LIVE__", str(len(live)))
        .replace("__DONE__", str(len(done)))
        .replace("__TOTBAR__", "".join(
            '<span class="seg %s" style="flex:%d" title="%s: %d"></span>'
            % (st, tot[st], LBL[st], tot[st]) for st in ORDER if tot.get(st)))
        .replace("__TOTPILLS__", counts(tot))
        .replace("__CARDS__", "".join(cards))
        .replace("__ROWS__", "".join(raid_rows)))

out = os.path.join(BASE, "index.html")
open(out, "w", encoding="utf-8").write(page)
print("written", out, len(page), "bytes")
