// Site search: a static JSON index, filtered in the browser.
// Plain substring matching over title, tags, summary and body text; every term
// must appear somewhere.  No stemmer, no dependency, no request until typed.
(function () {
  var script = document.currentScript;
  var index = [];
  var pending = null;
  var ready = false;
  var revision = 0;
  var input = document.getElementById('q');
  var status = document.getElementById('status');
  var list = document.getElementById('results');
  if (!script || !input || !list) return;

  var tplCount = script.dataset.tplCount || '{n} results';
  var tplEmpty = script.dataset.tplEmpty || 'Nothing matched.';
  var tplHint = script.dataset.tplHint || 'Type to search.';
  var tplLoading = script.dataset.tplLoading || 'Loading search index…';
  var tplError = script.dataset.tplError || 'Search failed to load. Type again to retry.';

  function load() {
    if (ready) return Promise.resolve();
    if (pending) return pending;
    var controller = new AbortController();
    var timeout = setTimeout(function () { controller.abort(); }, 10000);
    pending = fetch(script.dataset.index, { signal: controller.signal })
      .then(function (r) {
        if (!r.ok) throw new Error('Search index: ' + r.status);
        return r.json();
      })
      .then(function (data) {
        if (!Array.isArray(data)) throw new Error('Invalid search index');
        index = data;
        ready = true;
      })
      .finally(function () { clearTimeout(timeout); pending = null; });
    return pending;
  }

  function terms(q) {
    return q.toLowerCase().split(/\s+/).filter(Boolean);
  }

  function haystack(entry) {
    return (entry.title + ' ' + entry.tags.join(' ') + ' ' +
            entry.summary + ' ' + entry.text).toLowerCase();
  }

  function escapeHtml(s) {
    return s.replace(/[&<>"]/g, function (c) {
      return { '&': '&amp;', '<': '&lt;', '>': '&gt;', '"': '&quot;' }[c];
    });
  }

  function snippet(entry, words) {
    var text = entry.summary || entry.text;
    var lower = text.toLowerCase();
    for (var i = 0; i < words.length; i++) {
      var at = lower.indexOf(words[i]);
      if (at > 60) { text = '…' + text.slice(at - 40); break; }
      if (at >= 0) break;
    }
    return text.length > 160 ? text.slice(0, 160) + '…' : text;
  }

  function render(q) {
    var words = terms(q);
    list.innerHTML = '';
    if (!words.length) { status.textContent = tplHint; return; }
    var found = index.filter(function (entry) {
      var hay = haystack(entry);
      return words.every(function (w) { return hay.indexOf(w) >= 0; });
    });
    status.textContent = found.length
      ? tplCount.replace('{n}', found.length)
      : tplEmpty;
    found.forEach(function (entry) {
      var li = document.createElement('li');
      var tags = entry.tags.map(function (tag) {
        return '<span class="search-tag">' + escapeHtml(tag) + '</span>';
      }).join('');
      li.innerHTML =
        '<a href="' + entry.url + '">' + escapeHtml(entry.title) + '</a>' +
        '<span class="search-meta">' + escapeHtml(entry.date) + tags + '</span>' +
        '<span class="search-snippet">' + escapeHtml(snippet(entry, words)) + '</span>';
      list.appendChild(li);
    });
  }

  function run() {
    var current = ++revision;
    if (!input.value.trim()) {
      list.removeAttribute('aria-busy');
      status.classList.remove('is-loading');
      render('');
      return;
    }
    if (!ready) {
      status.textContent = tplLoading;
      status.classList.add('is-loading');
      list.setAttribute('aria-busy', 'true');
    }
    load().then(function () {
      if (current !== revision) return;
      render(input.value);
    }).catch(function () {
      if (current !== revision) return;
      status.textContent = tplError;
    }).finally(function () {
      if (current !== revision) return;
      status.classList.remove('is-loading');
      list.removeAttribute('aria-busy');
    });
  }

  var initial = new URLSearchParams(location.search).get('q') || '';
  input.value = initial;
  if (initial) run();

  var timer = null;
  function schedule(event) {
    ++revision;
    clearTimeout(timer);
    if (event && event.isComposing) {
      status.classList.remove('is-loading');
      list.removeAttribute('aria-busy');
      return;
    }
    timer = setTimeout(function () {
      run();
      var q = input.value.trim();
      history.replaceState(null, '', q ? '?q=' + encodeURIComponent(q) : location.pathname);
    }, 120);
  }
  input.addEventListener('input', schedule);
  input.addEventListener('compositionend', schedule);
  if (input.form) input.form.addEventListener('submit', function (event) {
    event.preventDefault();
    schedule();
  });
  input.focus({ preventScroll: true });
})();
