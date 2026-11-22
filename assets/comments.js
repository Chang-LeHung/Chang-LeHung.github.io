// Optional GitHub comments (giscus or utterances), loaded only when the reader
// approaches the section.  Nothing here runs on a site without [comments].
(function () {
  var mount = document.querySelector('.comments-mount');
  if (!mount) return;
  var provider = mount.dataset.provider;
  var loaded = false;
  var failedOnce = false;
  var watcher = null;

  function status(text, link) {
    var line = document.createElement('p');
    line.className = 'comments-status';
    line.textContent = text;
    if (link) {
      var anchor = document.createElement('a');
      anchor.href = mount.dataset.link;
      anchor.textContent = mount.dataset.linkText || mount.dataset.link;
      line.appendChild(document.createTextNode(' '));
      line.appendChild(anchor);
    }
    return line;
  }

  function failed() {
    if (failedOnce) return;
    failedOnce = true;
    if (watcher) {
      watcher.disconnect();
      watcher = null;
    }
    mount.replaceChildren(status(mount.dataset.failed || 'Comments failed to load.', true));
  }

  function load() {
    if (loaded) return;
    loaded = true;
    var pending = status(mount.dataset.loading || 'Loading comments…');
    mount.replaceChildren(pending);
    var script = document.createElement('script');
    script.async = true;
    script.src = provider === 'utterances'
      ? 'https://utteranc.es/client.js'
      : 'https://giscus.app/client.js';
    script.setAttribute('crossorigin', 'anonymous');
    if (provider === 'utterances') {
      script.setAttribute('repo', mount.dataset.repo);
      script.setAttribute('issue-term', mount.dataset.mapping);
      script.setAttribute('theme', mount.dataset.theme);
    } else {
      script.setAttribute('data-repo', mount.dataset.repo);
      script.setAttribute('data-repo-id', mount.dataset.repoId);
      script.setAttribute('data-category', mount.dataset.category);
      script.setAttribute('data-category-id', mount.dataset.categoryId);
      script.setAttribute('data-mapping', mount.dataset.mapping);
      if (mount.dataset.term) script.setAttribute('data-term', mount.dataset.term);
      script.setAttribute('data-strict', '0');
      script.setAttribute('data-reactions-enabled', mount.dataset.reactions || '1');
      script.setAttribute('data-emit-metadata', '0');
      script.setAttribute('data-input-position', 'bottom');
      script.setAttribute('data-theme', mount.dataset.theme);
      script.setAttribute('data-lang', mount.dataset.lang || 'en');
    }
    script.addEventListener('error', failed);
    // Drop the placeholder once the widget has put its frame in place; keep it
    // on screen while the request is in flight so the space is not blank.
    var observer = new MutationObserver(function () {
      if (mount.querySelector('iframe')) {
        if (pending.parentNode === mount) pending.remove();
        observer.disconnect();
        watcher = null;
      }
    });
    watcher = observer;
    observer.observe(mount, { childList: true, subtree: true });
    mount.appendChild(script);
    setTimeout(function () {
      if (!mount.querySelector('iframe')) failed();
    }, 10000);
  }

  if (!('IntersectionObserver' in window)) {
    load();
    return;
  }
  var observer = new IntersectionObserver(function (entries) {
    if (entries.some(function (entry) { return entry.isIntersecting; })) {
      observer.disconnect();
      load();
    }
  }, { rootMargin: '400px 0px' });
  observer.observe(mount);
})();
