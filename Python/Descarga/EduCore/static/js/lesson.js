/* ============================================================
   EDUcore - FUNCIONES PARA PÁGINAS DE LECCIÓN
   ============================================================ */

/**
 * Inicializa el procesamiento de fórmulas matemáticas con MathJax
 */
function initMathJax() {
    if (window.MathJax && MathJax.typesetPromise) {
        MathJax.typesetPromise()
            .then(function () {
                console.log('✅ Fórmulas matemáticas renderizadas');
            })
            .catch(function (err) {
                console.log('⚠️ Error en fórmulas:', err);
            });
    }
}

/**
 * Inicializa la página de lección
 */
function initLessonPage() {
    console.log('📖 Página de lección inicializada');

    // Procesar fórmulas matemáticas
    initMathJax();

    // Marcar lección como visitada
    var currentPath = window.location.pathname;
    if (typeof window.marcarLeccionVisitada === 'function') {
        window.marcarLeccionVisitada(currentPath);
    } else {
        console.warn('⚠️ marcarLeccionVisitada no está disponible');
    }
}

// ============================================================
// EXPORTAR FUNCIONES AL ÁMBITO GLOBAL
// ============================================================
window.initLessonPage = initLessonPage;
window.initMathJax = initMathJax;