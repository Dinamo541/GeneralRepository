/* ============================================================
   EDUcore - LABORATORIO (Simulador de Algoritmos)
   ============================================================ */

// ============================================================
// 1. CONFIGURACIÓN Y ESTADO
// ============================================================

let codigo = [];
let totalLineas = 0;

let estado = {
    pasoActual: 0,
    variables: {},
    variablesAnteriores: {},
    salida: [],
    ejecutando: false
};

// ============================================================
// 2. FUNCIÓN PARA ESCAPAR CARACTERES HTML
// ============================================================

function escapeHtml(texto) {
    return texto
        .replace(/&/g, "&amp;")
        .replace(/</g, "&lt;")
        .replace(/>/g, "&gt;");
}

// ============================================================
// 3. RESALTAR SINTAXIS
// ============================================================

function resaltar(texto) {
    const keywords = ['INICIO', 'FIN', 'SI', 'ENTONCES', 'SINO', 'FIN SI',
        'MIENTRAS', 'HACER', 'FIN MIENTRAS', 'PARA', 'DE', 'HASTA', 'CON', 'PASO', 'FIN PARA',
        'FUNCION', 'FIN FUNCION', 'RETORNAR', 'LEER', 'ESCRIBIR',
        'VERDADERO', 'FALSO', 'Y', 'O', 'NO', 'MOD', 'DIV', 'LONGITUD'];

    let html = escapeHtml(texto);

    let listaComments = [];
    let listaStrings = [];

    // Extraer y proteger COMENTARIOS
    html = html.replace(/\/\/(.*)$/gm, function (match, p1) {
        let idPlaceholder = '___COMMENT_PLACEHOLDER_' + listaComments.length + '___';
        listaComments.push('<span class="comment">//' + p1 + '</span>');
        return idPlaceholder;
    });

    // Extraer y proteger STRINGS
    html = html.replace(/&quot;([^&]*)&quot;|"([^"]*)"/g, function (match, p1, p2) {
        let contenido = p1 || p2 || '';
        let idPlaceholder = '___STRING_PLACEHOLDER_' + listaStrings.length + '___';
        listaStrings.push('<span class="string">"' + contenido + '"</span>');
        return idPlaceholder;
    });

    // Palabras clave
    for (const kw of keywords) {
        const regex = new RegExp('\\b' + kw + '\\b', 'g');
        html = html.replace(regex, '<span class="keyword">' + kw + '</span>');
    }

    // Números
    html = html.replace(/(?<!_[A-Z]+_)\b(\d+)\b/g, '<span class="number">$1</span>');

    // Variables
    html = html.replace(/(?<!<\/?[^>]*)(?<![a-zA-Z0-9_áéíóúüñÁÉÍÓÚÜÑ])[a-z_áéíóúüñ][a-zA-Z0-9_áéíóúüñ]*(?![a-zA-Z0-9_áéíóúüñ])(?!=[^<]*>)/g, function (m) {
        if (keywords.includes(m.toUpperCase())) return m;
        if (['span', 'class', 'keyword', 'string', 'number', 'variable', 'comment', 'lt', 'gt', 'amp'].includes(m)) {
            return m;
        }
        return '<span class="variable">' + m + '</span>';
    });

    // Restaurar STRINGS
    listaStrings.forEach(function (stringFormateado, index) {
        var idPlaceholder = '___STRING_PLACEHOLDER_' + index + '___';
        html = html.replace(idPlaceholder, stringFormateado);
    });

    // Restaurar COMENTARIOS
    listaComments.forEach(function (commentFormateado, index) {
        var idPlaceholder = '___COMMENT_PLACEHOLDER_' + index + '___';
        html = html.replace(idPlaceholder, commentFormateado);
    });

    return html;
}

// ============================================================
// 4. RENDERIZAR CÓDIGO
// ============================================================

function renderizarCodigo() {
    var container = document.getElementById('codigo-container');
    if (!container) return;

    var html = '';
    codigo.forEach(function (instruccion, i) {
        var num = i + 1;
        var texto = resaltar(instruccion.texto);
        html += '<div class="line" data-line="' + num + '"><span class="line-number">' + num + '</span>' + texto + '</div>';
    });
    container.innerHTML = html;
}

// ============================================================
// 5. EVALUAR EXPRESIÓN
// ============================================================

function evaluar(expr) {
    if (!expr) return null;
    var e = expr;

    // Resolver accesos a arreglos dinámicos
    e = e.replace(/([a-z_][a-zA-Z0-9_]*)\s*\[([^\]]+)\]/gi, function (match, varName, indexExpr) {
        var arreglo = estado.variables[varName];
        if (!arreglo || !Array.isArray(arreglo)) return match;

        var indiceEvaluado = evaluar(indexExpr);
        if (indiceEvaluado !== null && indiceEvaluado >= 0 && indiceEvaluado < arreglo.length) {
            return arreglo[indiceEvaluado];
        }
        return null;
    });

    // Sustituir variables simples
    for (var k in estado.variables) {
        if (estado.variables.hasOwnProperty(k)) {
            var v = estado.variables[k];
            if (Array.isArray(v)) continue;
            var regex = new RegExp('\\b' + k + '\\b', 'g');
            e = e.replace(regex, typeof v === 'string' ? '"' + v + '"' : v);
        }
    }

    // Traducir LONGITUD(variable)
    e = e.replace(/LONGITUD\(([^)]+)\)/g, function (m, p1) {
        var val = estado.variables[p1.trim()];
        return Array.isArray(val) ? val.length : 0;
    });

    // Mapeo de operadores
    e = e.replace(/\bMOD\b/g, '%');
    e = e.replace(/\bDIV\b/g, '/');
    e = e.replace(/\bY\b/g, '&&');
    e = e.replace(/\bO\b/g, '||');
    e = e.replace(/\bNO\b/g, '!');

    try {
        return Function('"use strict"; return (' + e + ')')();
    } catch (err) {
        console.error('❌ Error evaluando [' + expr + '] → [' + e + ']:', err);
        return null;
    }
}

// ============================================================
// 6. ACTUALIZAR UI
// ============================================================

function actualizarUI() {
    var lineas = document.querySelectorAll('.line');
    lineas.forEach(function (linea, i) {
        linea.classList.toggle('line-active', i === estado.pasoActual);
    });

    var lineaActual = document.getElementById('linea-actual');
    if (lineaActual) {
        lineaActual.textContent = estado.pasoActual + 1 + '/' + totalLineas;
    }

    var barra = document.getElementById('barra-progreso');
    var label = document.getElementById('progreso-label');
    if (barra) {
        var pct = totalLineas > 0 ? (estado.pasoActual / totalLineas) * 100 : 0;
        barra.style.width = Math.min(pct, 100) + '%';
        if (label) {
            label.textContent = Math.round(Math.min(pct, 100)) + '%';
        }
    }

    var tbody = document.getElementById('tabla-variables');
    var keys = Object.keys(estado.variables);

    if (keys.length === 0) {
        tbody.innerHTML = '<tr><td colspan="2" class="text-center text-white-50 py-3">Sin variables</td></tr>';
    } else {
        tbody.innerHTML = keys.map(function (k) {
            var v = estado.variables[k];
            var valorActualString = Array.isArray(v) ? '[' + v.join(', ') + ']' : String(v);
            if (typeof v === 'string') valorActualString = '"' + v + '"';

            var vAnterior = estado.variablesAnteriores[k];
            var valorAnteriorString = vAnterior !== undefined
                ? (Array.isArray(vAnterior) ? '[' + vAnterior.join(', ') + ']' : String(vAnterior))
                : null;
            if (typeof vAnterior === 'string') valorAnteriorString = '"' + vAnterior + '"';

            var debeAnimar = (valorAnteriorString !== null && valorActualString !== valorAnteriorString) ? 'true' : 'false';

            return '<tr data-animar="' + debeAnimar + '"><td><strong>' + k + '</strong></td><td class="valor">' + valorActualString + '</td></tr>';
        }).join('');

        var filasAAnimar = tbody.querySelectorAll('tr[data-animar="true"]');
        filasAAnimar.forEach(function (fila) {
            fila.classList.remove('linea-variable-cambiada');
            void fila.offsetWidth;
            fila.classList.add('linea-variable-cambiada');
        });
    }

    estado.variablesAnteriores = JSON.parse(JSON.stringify(estado.variables));

    var salida = document.getElementById('panel-salida');
    if (salida) {
        if (estado.salida.length === 0) {
            salida.innerHTML = '<span class="text-muted">La salida aparecerá aquí...</span>';
        } else {
            salida.innerHTML = estado.salida.map(function (m) { return '<div>' + m + '</div>'; }).join('');
            salida.scrollTop = salida.scrollHeight;
        }
    }
}

// ============================================================
// 7. EJECUTAR PASO
// ============================================================

function ejecutarPaso() {
    if (estado.pasoActual >= totalLineas) {
        alert('El algoritmo ha terminado. Presiona "Reiniciar".');
        return;
    }

    var inst = codigo[estado.pasoActual];
    var tipo = inst.tipo;

    switch (tipo) {
        case 'inicio': break;

        case 'asignacion':
            if (inst.expresion) {
                var r = evaluar(inst.expresion);
                if (r !== null) estado.variables[inst.var] = r;
            } else if (inst.valor !== undefined) {
                estado.variables[inst.var] = inst.valor;
            }
            break;

        case 'leer':
            var input = prompt('Ingrese valor para "' + inst.var + '":');
            if (input !== null) {
                var num = parseFloat(input);
                estado.variables[inst.var] = isNaN(num) ? input : num;
            }
            break;

        case 'escribir':
            var texto = inst.texto_salida || '';
            for (var k in estado.variables) {
                if (estado.variables.hasOwnProperty(k)) {
                    var v = estado.variables[k];
                    var sv = Array.isArray(v) ? '[' + v.join(', ') + ']' : v;
                    texto = texto.replace(new RegExp('{' + k + '}', 'g'), sv);
                }
            }
            estado.salida.push('> ' + texto);
            break;

        case 'si':
            var condSi = evaluar(inst.condicion);
            if (!condSi) {
                var nivel = 1, pos = estado.pasoActual + 1;
                while (pos < totalLineas && nivel > 0) {
                    if (codigo[pos].tipo === 'si') nivel++;
                    else if (codigo[pos].tipo === 'fin_si') {
                        nivel--;
                        if (nivel === 0) break;
                    } else if (codigo[pos].tipo === 'sino' && nivel === 1) {
                        pos++; break;
                    }
                    pos++;
                }
                estado.pasoActual = pos - 1;
            }
            break;

        case 'sino':
            var nivelS = 1, posS = estado.pasoActual + 1;
            while (posS < totalLineas && nivelS > 0) {
                if (codigo[posS].tipo === 'si') nivelS++;
                else if (codigo[posS].tipo === 'fin_si') nivelS--;
                posS++;
            }
            estado.pasoActual = posS - 1;
            break;

        case 'mientras':
            var condM = evaluar(inst.condicion);
            if (!condM) {
                var nivel = 1, pos = estado.pasoActual + 1;
                while (pos < totalLineas && nivel > 0) {
                    if (codigo[pos].tipo === 'mientras') nivel++;
                    else if (codigo[pos].tipo === 'fin_mientras') nivel--;
                    pos++;
                }
                estado.pasoActual = pos - 1;
            }
            break;

        case 'fin_mientras':
            var nivelM = 1, posM = estado.pasoActual - 1;
            while (posM >= 0 && nivelM > 0) {
                if (codigo[posM].tipo === 'fin_mientras') nivelM++;
                else if (codigo[posM].tipo === 'mientras') nivelM--;
                if (nivelM === 0) break;
                posM--;
            }
            estado.pasoActual = posM - 1;
            break;

        case 'para':
            if (estado.variables[inst.var] === undefined) {
                estado.variables[inst.var] = inst.de;
            }

            var valorActualPara = estado.variables[inst.var];
            var limitePara = inst.hasta;
            var incremento = inst.paso !== undefined ? inst.paso : 1;

            if ((incremento > 0 && valorActualPara > limitePara) ||
                (incremento < 0 && valorActualPara < limitePara)) {
                var nivel = 1, pos = estado.pasoActual + 1;
                while (pos < totalLineas && nivel > 0) {
                    if (codigo[pos].tipo === 'para') nivel++;
                    else if (codigo[pos].tipo === 'fin_para') nivel--;
                    pos++;
                }
                estado.pasoActual = pos - 1;
                delete estado.variables[inst.var];
            }
            break;

        case 'fin_para':
            var nivelFP = 1, posFP = estado.pasoActual - 1;
            while (posFP >= 0 && nivelFP > 0) {
                if (codigo[posFP].tipo === 'fin_para') nivelFP++;
                else if (codigo[posFP].tipo === 'para') nivelFP--;
                posFP--;
            }
            posFP++;

            var instCabecera = codigo[posFP];
            var inc = instCabecera.paso !== undefined ? instCabecera.paso : 1;

            estado.variables[instCabecera.var] = (estado.variables[instCabecera.var] || 0) + inc;
            estado.pasoActual = posFP - 1;
            break;

        case 'fin_si':
        case 'fin': break;
    }

    estado.pasoActual++;
    actualizarUI();
}

// ============================================================
// 8. EJECUTAR TODO
// ============================================================

function ejecutarTodo() {
    if (estado.ejecutando) return;
    if (estado.pasoActual >= totalLineas) {
        reiniciar();
        setTimeout(ejecutarTodo, 100);
        return;
    }

    estado.ejecutando = true;
    document.getElementById('btn-ejecutar').disabled = true;
    document.getElementById('btn-paso').disabled = true;

    var interval = setInterval(function () {
        if (estado.pasoActual >= totalLineas || !estado.ejecutando) {
            clearInterval(interval);
            estado.ejecutando = false;
            document.getElementById('btn-ejecutar').disabled = false;
            document.getElementById('btn-paso').disabled = false;
            return;
        }
        ejecutarPaso();
    }, 400);
}

// ============================================================
// 9. REINICIAR
// ============================================================

function reiniciar() {
    estado.pasoActual = 0;
    estado.variables = {};
    estado.salida = [];
    estado.ejecutando = false;
    estado.variablesAnteriores = {};
    document.getElementById('btn-ejecutar').disabled = false;
    document.getElementById('btn-paso').disabled = false;
    actualizarUI();
}

// ============================================================
// 10. CARGAR ALGORITMO DESDE EL BACKEND
// ============================================================

async function cargarAlgoritmo(algoritmoId) {
    try {
        var respuesta = await fetch('/lab/api/algorithm/' + algoritmoId);
        if (!respuesta.ok) throw new Error('No disponible');

        codigo = await respuesta.json();
        totalLineas = codigo.length;

        renderizarCodigo();
        actualizarUI();

        document.getElementById('btn-paso').disabled = false;
        document.getElementById('btn-ejecutar').disabled = false;
        document.getElementById('btn-reiniciar').disabled = false;
    } catch (err) {
        console.error('Error:', err);
        document.getElementById('codigo-container').innerHTML = '<div class="text-danger p-3">Error al conectar con el backend.</div>';
    }
}

// ============================================================
// 11. EXPORTAR FUNCIONES GLOBALES
// ============================================================

window.ejecutarPaso = ejecutarPaso;
window.ejecutarTodo = ejecutarTodo;
window.reiniciar = reiniciar;
window.cargarAlgoritmo = cargarAlgoritmo;

console.log('🔷 Laboratorio JS cargado correctamente');