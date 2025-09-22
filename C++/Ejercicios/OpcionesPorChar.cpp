#include <iostream>
#include <string>
#include <cmath>
#include <cstdlib> // Para system("cls") en Windows
#include <limits> // Para std::numeric_limits
using namespace std;

bool confirmationCharacters(const string& cadena, const string& caracteresPermitidos) {
    return cadena.find_first_not_of(caracteresPermitidos) == string::npos;
}

string confirmationOption(const string& allowedCharacters) {
    string option;
    while (!confirmationCharacters(option, allowedCharacters)) {
        cout << "Ingrese la opcion: ";
        cin >> option;
        if (!confirmationCharacters(option, allowedCharacters)) {
            cout << "El caracter digitado no es una opcion, Seleccione una opcion correcta o 0 para salir" << endl;
        }
    }
    system("cls");
    return option;
}

int main() {
    string option;
    string caracteresDecimales = "0123456789";
    cout << "Eliga una opcion: " << endl;
    cout << "1. Opcion 1" << endl;
    cout << "2. Opcion 2" << endl;
    cout << "3. Opcion 3" << endl;
    cout << "0. Opcion Salir" << endl;

    confirmationOption(caracteresDecimales);

    switch (stoi(option)) {
        case 1:
            cout << "Opcion 1" << endl;
            break;
        case 2:
            cout << "Opcion 2" << endl;
            break;
        case 3:
            cout << "Opcion 3" << endl;
            break;
        case 0:
            cout << "Opcion Salir" << endl;
            break;
        default:
            cout << "Opcion no valida" << endl;
            break;
    }

    return 0;
}