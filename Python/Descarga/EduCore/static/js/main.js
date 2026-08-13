/* ============================================================
   EDUcore - FUNCIONES GLOBALES
   ============================================================ */

/**
 * Genera una tabla de contenidos (TOC) a partir de los encabezados
 */
function generarTOC(containerSelector, tocSelector) {
    var container = document.querySelector(containerSelector);
    var toc = document.querySelector(tocSelector);

    if (!container || !toc) return;

    var headers = container.querySelectorAll('h2, h3');
    if (headers.length === 0) {
        toc.innerHTML = '<li class="text-muted small">Sin secciones</li>';
        return;
    }

    headers.forEach(function (header, index) {
        var id = 'section-' + index;
        header.id = id;
        var li = document.createElement('li');
        var a = document.createElement('a');
        a.href = '#' + id;
        a.textContent = header.textContent;
        if (header.tagName === 'H3') {
            a.style.paddingLeft = '20px';
            a.style.fontSize = '0.85rem';
            a.style.opacity = '0.8';
        }
        li.appendChild(a);
        toc.appendChild(li);
    });
}

// ============================================================
// INICIALIZACIÓN AUTOMÁTICA
// ============================================================

document.addEventListener('DOMContentLoaded', function () {
    console.log('🔷 EduCore inicializado');

    // Generar TOC en páginas de lecciones
    var content = document.querySelector('.lesson-content');
    var toc = document.getElementById('toc');
    if (content && toc) {
        generarTOC('.lesson-content', '#toc');
    }

    // Actualizar progreso (si estamos en una página con barras)
    if (document.querySelector('.topic-item') || document.querySelector('.topic-progress-bar')) {
        if (typeof window.actualizarTodasLasBarras === 'function') {
            window.actualizarTodasLasBarras();
        }
    }

    // Marcar enlaces activos en la navegación
    var currentPath = window.location.pathname;
    document.querySelectorAll('.navbar-nav .nav-link').forEach(function (link) {
        if (link.getAttribute('href') === currentPath) {
            link.classList.add('active');
        }
    });
});

// ============================================================
// EXPORTAR FUNCIONES AL ÁMBITO GLOBAL
// ============================================================
window.generarTOC = generarTOC;