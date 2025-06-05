#include <iostream>
#include <cmath>
using namespace std;
void mostrarMenu() {
    cout << "2 = Binario" << endl;
    cout << "8 = Octal" << endl;
    cout << "10 = Decimal" << endl;
    cout << "16 = Hexadecimal" << endl << endl;
}
bool esNegativo(string numeroConvertir) {
	if (numeroConvertir[0] == '-') {
		return true;
	}
	return false;
}
bool esBinario(string numeroConvertir) {
    for (int i = 0; i < numeroConvertir.length(); i++) {
        if (numeroConvertir[i] != '0' && numeroConvertir[i] != '1') {
            return false;
        }
    }
    return true;
}
bool esOctal(string numeroConvertir) {
    for (int i = 0; i < numeroConvertir.length(); i++) {
        if (numeroConvertir[i] < '0' || numeroConvertir[i] > '7') {
            return false;
        }
    }
    return true;
}
bool esDecimal(string numeroConvertir) {
    for (int i = 0; i < numeroConvertir.length(); i++) {
        if (numeroConvertir[i] < '0' || numeroConvertir[i] > '9') {
            return false;
        }
    }
    return true;
}
bool esHexadecimal(string numeroConvertir) {
    for (int i = 0; i < numeroConvertir.length(); i++) {
        if (!((numeroConvertir[i] >= '0' && numeroConvertir[i] <= '9') ||
            (numeroConvertir[i] >= 'A' && numeroConvertir[i] <= 'F') ||
            (numeroConvertir[i] >= 'a' && numeroConvertir[i] <= 'f'))) {
            return false;
        }
    }
    return true;
}
bool validarNumero(string numeroConvertir, int base) {
    if (base == 2) return esBinario(numeroConvertir);
    if (base == 8) return esOctal(numeroConvertir);
    if (base == 10) return esDecimal(numeroConvertir);
    if (base == 16) return esHexadecimal(numeroConvertir);
    return false;
}
int convertirABaseDecimal(string numero, int baseOrigen) {
    int decimal = 0, potencia = 0;
    for (int i = numero.length() - 1; i >= 0; i--) {
        char c = numero[i];
        int valor = (c >= '0' && c <= '9') ? (c - '0') : (toupper(c) - 'A' + 10);
        decimal += valor * pow(baseOrigen, potencia);
        potencia++;
    }
    return decimal;
}
string convertirDesdeDecimal(int numero, int base) {
    if (numero == 0) return "0";
    string resultado = "";
    while (numero > 0) {
        int residuo = numero % base;
        char digito = (residuo < 10) ? (residuo + '0') : (residuo - 10 + 'A');
        resultado = digito + resultado;
        numero /= base;
    }
    return resultado;
}
string convertirDesdeDecimalHex(int numero) {
    if (numero == 0) return "0";
    string resultado = "";
    while (numero > 0) {
        int residuo = numero % 16;
        char digito;
        if (residuo < 10) {
            digito = residuo + '0';
        }
        else {
            digito = residuo - 10 + 'A';
        }
        resultado = digito + resultado;
        numero /= 16;
    }
    return resultado;
}
int main() {
    int baseOrigen = 0, baseDestino = 0, numero = 0, continuarPrograma = 1, usarResultadoAnterior = 0;
    string numeroConvertir, resultado;
	bool esNumeroNegativo = false;
    cout << "Bienvenido a la calculadora de conversion de bases presione ENTER para comenzar" << endl << endl;
	cin.get();
    while (continuarPrograma == 1) {
		// Reutilizacion del resultado anterior
        if (usarResultadoAnterior == 1) {
			cout << "Usando el resultado anterior: " << resultado << " en base " << baseOrigen << endl << endl;
            numeroConvertir = resultado;
        } else {
			// Selección y validación de la base de origen           
            cout << "Seleccione la base del numero que va a convertir: " << endl << endl;
            mostrarMenu();
            cin >> baseOrigen;
            while ((baseOrigen != 2) && (baseOrigen != 8) && (baseOrigen != 10) && (baseOrigen != 16) || cin.fail()) {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << endl << "Base no disponible" << endl << endl;
                cout << "Digite una base valida" << endl << endl;
                mostrarMenu();
                cin >> baseOrigen;
            }
            cout << endl << "Base " << baseOrigen << " seleccionada" << endl << endl;
        }
		// Ingreso del número a convertir, validación respecto a la base ingresa y determinar si es negativo
        if (usarResultadoAnterior == 0) {
            cout << "Digite el numero a convertir" << endl << endl;
            cin >> numeroConvertir;
        }
		// Validación de si el número es negativo
        esNumeroNegativo = esNegativo(numeroConvertir); 
        if (esNumeroNegativo) {
			numeroConvertir = numeroConvertir.substr(1); 
        }
		// Validación del número respecto a la base ingresada
        if (usarResultadoAnterior == 0) {
            while (!validarNumero(numeroConvertir, baseOrigen)) {
                cout << endl << "El numero no es valido en la base " << baseOrigen << endl << endl;
                cout << "Digite un numero valido en la base " << baseOrigen << endl << endl;
                cin >> numeroConvertir;
            }
            cout << endl << "El numero es valido en la base " << baseOrigen << endl << endl;
        }
        // Selección y validación de la base de destino
        cout << "Seleccione la base a la que desea convertir el numero, no seleccione la misma base anterior " << endl << endl;
        mostrarMenu();
        cin >> baseDestino;
        while (((baseDestino != 2) && (baseDestino != 8) && (baseDestino != 10) && (baseDestino != 16)) ||
            (baseDestino == baseOrigen) || (cin.fail())) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << endl << "Base no disponible" << endl << endl;
            cout << "Digite una base valida y diferente a la primera base seleccionada" << endl << endl;
            mostrarMenu();
            cin >> baseDestino;
        }
        cout << endl << "Base " << baseDestino << " seleccionada" << endl << endl;
        // Conversiones entre bases
        if (baseOrigen == 2) {
            if ((baseDestino == 10) || (baseDestino == 8)) {
                numero = convertirABaseDecimal(numeroConvertir, baseOrigen);
                resultado = convertirDesdeDecimal(numero, baseDestino);
            } else {
                numero = convertirABaseDecimal(numeroConvertir, baseOrigen);
                resultado = convertirDesdeDecimalHex(numero);
            }
        }
        if (baseOrigen == 8) {
            if ((baseDestino == 10) || (baseDestino == 2)) {
                numero = convertirABaseDecimal(numeroConvertir, baseOrigen);
                resultado = convertirDesdeDecimal(numero, baseDestino);
            }
            else {
                numero = convertirABaseDecimal(numeroConvertir, baseOrigen);
                resultado = convertirDesdeDecimalHex(numero);
            }
        }
        if (baseOrigen == 10) {
            if ((baseDestino == 2) || (baseDestino == 8)) {
                numero = convertirABaseDecimal(numeroConvertir, baseOrigen);
                resultado = convertirDesdeDecimal(numero, baseDestino);
            } else {
                numero = convertirABaseDecimal(numeroConvertir, baseOrigen);
                resultado = convertirDesdeDecimalHex(numero);
            }
        }
        if (baseOrigen == 16) {
            numero = convertirABaseDecimal(numeroConvertir, baseOrigen);
            resultado = convertirDesdeDecimal(numero, baseDestino);
        }
        if (esNumeroNegativo) {
			resultado = "-" + resultado; 
        }
        cout << "El resultado es: " << resultado << endl << endl;
		// Preguntar si se desea continuar o no y utilizar el resultado anterior
        cout << "Desea continuar? 1 = Si, 0 = No" << endl << endl;
        cin >> continuarPrograma;
        cout << endl;
        if (continuarPrograma == 1) {
            cout << "Desea utilizar el resultado anterior en la siguiente operacion? 1 = Si, 0 = No" << endl << endl;
            cin >> usarResultadoAnterior;
            cout << endl;
            if (usarResultadoAnterior == 1) {
                baseOrigen = baseDestino;
            }
        }
    }
    cout << "Gracias por usar la calculadora de conversion de bases" << endl << endl;
    return 0;
}