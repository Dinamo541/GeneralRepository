/* ============================================================
   EDUcore - FUNCIONES PARA PÁGINAS DE CURSOS
   ============================================================ */

/**
 * Inicializa el buscador de lecciones
 */
function initLessonSearch() {
    var searchInput = document.getElementById('searchLessons');
    var topicItems = document.querySelectorAll('.topic-item');
    var noResults = document.getElementById('noResults');

    if (!searchInput) return;

    searchInput.addEventListener('input', function () {
        var query = this.value.toLowerCase().trim();
        var hasResults = false;

        topicItems.forEach(function (topic) {
            var topicHasMatch = false;
            var lessons = topic.querySelectorAll('.lesson-item');

            lessons.forEach(function (lesson) {
                var lessonText = lesson.dataset.lesson || '';
                var match = lessonText.includes(query);

                if (query === '' || match) {
                    lesson.style.display = '';
                    topicHasMatch = true;
                } else {
                    lesson.style.display = 'none';
                }
            });

            if (query === '' || topicHasMatch) {
                topic.style.display = '';
                hasResults = true;
            } else {
                topic.style.display = 'none';
            }
        });

        if (noResults) {
            noResults.style.display = hasResults ? 'none' : 'block';
        }
    });
}

/**
 * Inicializa la página del curso
 */
function initCoursePage() {
    console.log('📚 Página de curso inicializada');

    // Inicializar buscador
    initLessonSearch();

    // Actualizar progreso
    if (typeof window.actualizarTodasLasBarras === 'function') {
        window.actualizarTodasLasBarras();
    }
}

// ============================================================
// EXPORTAR FUNCIONES AL ÁMBITO GLOBAL
// ============================================================
window.initCoursePage = initCoursePage;
window.initLessonSearch = initLessonSearch;