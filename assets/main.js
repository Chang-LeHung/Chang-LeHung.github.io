// Native navigation with non-blocking feedback; no router or content replacement.
(function () {
  document.addEventListener('click', function (event) {
    if (!(event.target instanceof Element)) return;
    var link = event.target.closest('a[href]');
    if (!link || event.defaultPrevented || event.button !== 0 ||
        event.metaKey || event.ctrlKey || event.shiftKey || event.altKey ||
        link.hasAttribute('download') || (link.target && link.target !== '_self')) return;
    var url = new URL(link.href, location.href);
    // Anchors, feeds, downloads, mail and external tabs keep their native feedback.
    if (url.origin !== location.origin || !/(\/|\.html)$/.test(url.pathname) ||
        (url.pathname === location.pathname && url.search === location.search)) return;
    if (window.bellpressLoading) window.bellpressLoading.start();
  });

  document.addEventListener('click', function (event) {
    if (!(event.target instanceof Element)) return;
    var button = event.target.closest('.code-copy');
    if (!button || button.dataset.copyBusy) return;
    var block = button.closest('.code-block');
    var code = block && block.querySelector('code');
    if (!code) return;
    var label = button.dataset.copyLabel || button.textContent;
    button.dataset.copyLabel = label;
    button.dataset.copyBusy = 'true';
    button.setAttribute('aria-busy', 'true');
    button.textContent = button.dataset.copyWaiting || 'Copying';
    var settled = false;
    function complete(ok) {
      if (settled) return;
      settled = true;
      clearTimeout(timeout);
      button.removeAttribute('aria-busy');
      button.textContent = ok ? (button.dataset.copyDone || 'Copied') : (button.dataset.copyFailed || 'Failed');
      setTimeout(function () {
        button.textContent = label;
        delete button.dataset.copyBusy;
      }, 1600);
    }
    var timeout = setTimeout(function () { complete(false); }, 5000);
    if (navigator.clipboard && navigator.clipboard.writeText) {
      navigator.clipboard.writeText(code.textContent).then(function () { complete(true); }, function () { complete(false); });
    } else {
      complete(false);
    }
  });
})();
