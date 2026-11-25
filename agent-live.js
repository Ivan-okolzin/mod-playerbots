(() => {
  const el = id => document.getElementById(id);
  const api = 'https://api.github.com/repos/Ivan-okolzin/mod-playerbots/actions';
  let busy = false;
  let lastCI = '';
  let lastRead = '';
  const now = () => new Date().toLocaleTimeString();
  const minutes = time => Math.max(0, Math.floor((Date.now() - Date.parse(time)) / 60000));
  async function read(url) {
    const response = await fetch(url, {cache: 'no-store', signal: AbortSignal.timeout(15000)});
    if (!response.ok) throw Error('HTTP ' + response.status);
    return response.json();
  }
  async function refresh() {
    if (busy || location.hash !== '#agents' || document.hidden) return;
    busy = true;
    try {
      const state = await read('agent-live.json');
      lastRead = now();
      el('live-check').textContent = 'Сведения об агентах получены в ' + lastRead;
      el('live-agents').replaceChildren(...state.agents.map(agent => {
        const row = document.createElement('li');
        const age = minutes(agent.time);
        row.textContent = [agent.name, agent.task, agent.event, age + ' мин назад'].join(' · ');
        if (agent.active && age >= 10) {
          row.append(' · Нет свежего подтверждения');
          row.style.borderLeft = '4px solid #eab308';
        }
        return row;
      }));
      el('live-release').textContent = 'Модуль ' + state.module.slice(0,8) + ' · ' +
        (state.installed === state.module ? 'Готово на ASUS' : 'Последняя подтверждённая версия ASUS ' + (state.installed || 'неизвестна').slice(0,8));
      try {
        const runs = await read(api + '/workflows/windows_runtime.yml/runs?per_page=1&head_sha=' + encodeURIComponent(state.workflow));
        const run = runs.workflow_runs[0];
        const ci = el('live-ci');
        if (run) {
          const jobs = await read(api + '/runs/' + run.id + '/jobs');
          const step = jobs.jobs.flatMap(job => job.steps || []).find(step => step.status === 'in_progress');
          const link = document.createElement('a');
          link.href = run.html_url;
          link.textContent = 'Журнал #' + run.run_number;
          ci.replaceChildren(link, ' · ' + (run.conclusion || run.status) +
            (step ? ' · ' + step.name + ' · ' + minutes(step.started_at) + ' мин' : ''));
        } else ci.textContent = 'Ожидаем запуск для этой ревизии';
        lastCI = now();
        ci.append(' · GitHub ответил в ' + lastCI);
      } catch (error) {
        el('live-ci').textContent = 'GitHub недоступен · ' + error.message + (lastCI ? ' · последний ответ ' + lastCI : '');
      }
    } catch (error) {
      el('live-check').textContent = 'Сведения недоступны · ' + error.message + (lastRead ? ' · последний ответ ' + lastRead : '');
    } finally { busy = false; }
  }
  refresh();
  setInterval(refresh, 60000);
  addEventListener('hashchange', refresh);
  document.addEventListener('visibilitychange', refresh);
})();
