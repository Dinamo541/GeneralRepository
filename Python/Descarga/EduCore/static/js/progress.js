/* ============================================================
   EDUcore - GESTIÓN DE PROGRESO
   ============================================================ */

/**
 * Obtiene todas las lecciones visitadas del localStorage
 */
function getLeccionesVisitadas() {
    try {
        return JSON.parse(localStorage.getItem('leccionesVisitadas') || '{}');
    } catch (e) {
        return {};
    }
}

/**
 * Guarda las lecciones visitadas en localStorage
 */
function saveLeccionesVisitadas(data) {
    localStorage.setItem('leccionesVisitadas', JSON.stringify(data));
}

/**
 * Marca una lección como visitada
 */
function marcarLeccionVisitada(url) {
    console.log('📌 Marcando lección como visitada:', url);

    var lecciones = getLeccionesVisitadas();
    lecciones[url] = true;
    saveLeccionesVisitadas(lecciones);

    // Actualizar progreso
    actualizarTodasLasBarras();
}

/**
 * Actualiza todas las barras de progreso en la página
 */
function actualizarTodasLasBarras() {
    console.log('📊 Actualizando barras de progreso...');

    var lecciones = getLeccionesVisitadas();

    // Buscar todos los temas (.topic-item)
    document.querySelectorAll('.topic-item').forEach(function (topic) {
        var lessonItems = topic.querySelectorAll('.lesson-item');
        var totalLessons = lessonItems.length;
        var completedLessons = 0;

        lessonItems.forEach(function (lesson) {
            var link = lesson.querySelector('a');
            if (link) {
                var href = link.getAttribute('href');
                if (lecciones[href]) {
                    completedLessons++;
                }
            }
        });

        // Buscar la barra de progreso dentro del tema
        var progressBar = topic.querySelector('.topic-progress-bar');
        var progressText = topic.querySelector('.topic-progress-text');

        if (progressBar) {
            var pct = totalLessons > 0 ? Math.round((completedLessons / totalLessons) * 100) : 0;
            progressBar.style.width = pct + '%';
            /*progressBar.textContent = pct + '%';*/
            console.log('  📊 Progreso:', pct + '% (' + completedLessons + '/' + totalLessons + ')');
        }

        if (progressText) {
            var pct = totalLessons > 0 ? Math.round((completedLessons / totalLessons) * 100) : 0;
            progressText.textContent = pct + '% completado';
        }
    });
}

// ============================================================
// EXPORTAR FUNCIONES AL ÁMBITO GLOBAL
// ============================================================
window.getLeccionesVisitadas = getLeccionesVisitadas;
window.saveLeccionesVisitadas = saveLeccionesVisitadas;
window.marcarLeccionVisitada = marcarLeccionVisitada;
window.actualizarTodasLasBarras = actualizarTodasLasBarras;

console.log('📊 Módulo de progreso cargado');