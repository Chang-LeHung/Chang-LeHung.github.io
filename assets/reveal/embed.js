// Each embedded deck owns its navigation and fullscreen lifecycle.
document.querySelectorAll('.slide-embed').forEach(function (el) {
  el.tabIndex = 0;
  var pdf = el.classList.contains('pdf');
  var natural = {
    width: +el.dataset.width || 1024,
    height: +el.dataset.height || 768,
    margin: 0, maxScale: 10,
  };
  var deck = new Reveal(el, Object.assign({
    embedded: true, hash: false,
    slideNumber: 'c/t', controlsTutorial: false, progress: false,
    center: false, transition: 'none', keyboard: !pdf,
    keyboardCondition: 'focused',
    navigationMode: pdf ? 'linear' : 'default', controlsLayout: 'bottom-right',
    // Dragging across PDF text must select text, not swipe the slide.
    touch: !pdf,
  }, natural));

  el.addEventListener('pointerdown', function (event) {
    if (!event.target.closest('button, a, input, textarea, select')) {
      el.focus({ preventScroll: true });
    }
  });

  function fitText() {
    var sec = deck.getCurrentSlide();
    if (!sec) return;
    var spans = Array.from(sec.querySelectorAll('.pdf-text span'));
    // Preserve percentage widths so fullscreen/resizing cannot freeze text at
    // an old pixel size. Read all target widths before changing any styles.
    spans.forEach(function (s) {
      if (!s.dataset.width) s.dataset.width = s.style.width;
      s.style.width = s.dataset.width;
      s.style.transform = '';
    });
    var want = spans.map(function (s) { return s.getBoundingClientRect().width; });
    spans.forEach(function (s) { s.style.width = 'auto'; });
    var have = spans.map(function (s) { return s.getBoundingClientRect().width; });
    spans.forEach(function (s, i) {
      if (have[i] > 0) s.style.transform = 'scaleX(' + want[i] / have[i] + ')';
    });
  }
  deck.on('slidechanged', function () {
    fitText();
    // Clicking Reveal's arrows leaves focus on a button. Keep subsequent
    // arrow keys with this deck, rather than the surrounding article.
    if (el.contains(document.activeElement)) el.focus({ preventScroll: true });
  });

  function toggle() {
    var action = document.fullscreenElement === el
      ? document.exitFullscreen() : el.requestFullscreen && el.requestFullscreen();
    if (action && action.catch) action.catch(function (error) { console.warn(error); });
  }
  var button = document.createElement('button');
  button.className = 'slide-full';
  button.type = 'button';
  button.setAttribute('aria-label', 'Full screen');
  button.innerHTML = '<svg viewBox="0 0 16 16" width="16" height="16" fill="none" stroke="currentColor" stroke-width="1.6"><path d="M2 6V2h4M10 2h4v4M14 10v4h-4M6 14H2v-4"/></svg>';
  button.addEventListener('click', function () { toggle(); el.focus({ preventScroll: true }); });
  el.appendChild(button);

  document.addEventListener('keydown', function (event) {
    var full = document.fullscreenElement;
    var active = full ? full === el : el.contains(document.activeElement);
    if (!active || event.ctrlKey || event.metaKey || event.altKey ||
        event.target.closest('input, textarea, select, [contenteditable="true"]')) return;
    var next = ['ArrowRight', 'ArrowDown', 'PageDown', ' '].includes(event.key);
    var prev = ['ArrowLeft', 'ArrowUp', 'PageUp'].includes(event.key);
    if (pdf && (next || prev || event.key === 'Home' || event.key === 'End')) {
      event.preventDefault(); event.stopImmediatePropagation();
      if (next) deck.next();
      else if (prev) deck.prev();
      else deck.slide(event.key === 'Home' ? 0 : deck.getHorizontalSlides().length - 1);
    } else if (event.key.toLowerCase() === 'f') {
      event.preventDefault(); event.stopImmediatePropagation(); toggle();
    }
  }, true);

  function layout() {
    deck.layout();
    fitText();
  }
  var wasFull = false;
  document.addEventListener('fullscreenchange', function () {
    var full = document.fullscreenElement === el;
    if (!full && !wasFull) return;
    wasFull = full;
    // Keep the natural stage coordinates: changing them during slidechanged
    // used to reset/reconfigure navigation after every single PDF page.
    deck.configure(Object.assign({}, natural, { margin: full && !pdf ? 0.04 : 0 }));
    el.focus({ preventScroll: true });
    requestAnimationFrame(layout);
  });
  window.addEventListener('resize', function () { requestAnimationFrame(layout); });
  deck.initialize().then(function () {
    layout();
    document.fonts.ready.then(layout);
  });
});
