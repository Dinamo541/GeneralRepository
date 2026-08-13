/* ============================================================
   CURSO: LÓGICA Y ALGORITMOS COMPUTACIONALES (TDC400)
   ============================================================ */

var logicCourseInitialized = false;

/**
 * Inicializa todas las funcionalidades específicas del curso de Lógica
 */
function initLogicCourse() {
    // Evitar inicialización duplicada
    if (logicCourseInitialized) {
        console.log('🧠 Curso de Lógica ya inicializado');
        return;
    }
    logicCourseInitialized = true;

    console.log('🧠 Inicializando curso de Lógica...');

}

// ============================================================
// EXPORTAR FUNCIONES AL ÁMBITO GLOBAL
// ============================================================
window.initLogicCourse = initLogicCourse;

// Inicializar automáticamente si estamos en el curso de Lógica
document.addEventListener('DOMContentLoaded', function () {
    if (window.location.pathname.startsWith('/logica')) {
        initLogicCourse();
    }
});