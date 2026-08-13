/* ============================================================
   EDUcore - FUNCIONES PARA PÁGINA DE INICIO
   ============================================================ */

/**
 * Inicializa la página de inicio
 */
function initHomePage() {
    console.log('🏠 Página de inicio inicializada');

    // Animación de entrada para las cards (opcional)
    const cards = document.querySelectorAll('.curso-card');
    cards.forEach((card, index) => {
        card.style.opacity = '0';
        card.style.transform = 'translateY(20px)';
        setTimeout(function () {
            card.style.transition = 'all 0.5s ease';
            card.style.opacity = '1';
            card.style.transform = 'translateY(0)';
        }, 100 * (index + 1));
    });
}

// ============================================================
// EXPORTAR FUNCIONES AL ÁMBITO GLOBAL
// ============================================================
window.initHomePage = initHomePage;