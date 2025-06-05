#include <iostream>
#include <string>
#include <cmath>
using namespace std;

bool confirmationCharacters(const string& cadena, const string& caracteresPermitidos) {
    return cadena.find_first_not_of(caracteresPermitidos) == string::npos;
}

int binarioADecimal(const string& binario) {
    int decimal = 0;
    int longitud = binario.length();
    for (int i = 0; i < longitud; ++i) {
        if (binario[longitud - i - 1] == '1') {
            decimal += pow(2, i);
        }
    }
    return decimal;
}

int octalADecimal(const string& octal) {
    int decimal = 0;
    int length = octal.length();
    for (int i = 0; i < length; ++i) {
        decimal += (octal[length - i - 1] - '0') * pow(8, i);
    }
    return decimal;
}

string decimalABinario(int decimal) {
    string binario;
    while (decimal > 0) {
        binario = to_string(decimal % 2) + binario;
        decimal /= 2;
    }
    return binario;
}

string decimalAHexadecimal(int decimal) {
    string hexadecimal = "";
    while (decimal > 0) {
        int residuo = decimal % 16;
        if (residuo < 10) {
            hexadecimal = to_string(residuo) + hexadecimal;
        } else {
            hexadecimal = (char)(residuo + 55) + hexadecimal;
        }
        decimal /= 16;
    }
    return hexadecimal;
}

string decimalAOctal(int decimal) {
    string octal;
    while (decimal > 0) {
        octal = to_string(decimal % 8) + octal;
        decimal /= 8;
    }
    return octal;
}

int hexadecimalADecimal(const string& number) {
    int decimal = 0;
    int size = number.size();
    int power = 0;

    for (int i = size - 1; i >= 0; i--) {
        if (number[i] >= '0' && number[i] <= '9') {
            decimal += (number[i] - '0') * pow(16, power);
        } else if (number[i] >= 'A' && number[i] <= 'F') {
            decimal += (number[i] - 'A' + 10) * pow(16, power);
        } else if (number[i] >= 'a' && number[i] <= 'f') {
            decimal += (number[i] - 'a' + 10) * pow(16, power);
        }
        power++;
    }
    return decimal;
}

int main() {
    string result = "None";
    string sistemFromResult;
    int optionMain = -1;
    int optionOne = -1;
    int optionTwo = -1;
    int optionThree = -1;
    int optionFour = -1;
    int optionFive = -1;
    string number = "1";
    string caracteresBinarios = "01";
    string caracteresOctales = "01234567";
    string caracteresDecimales = "0123456789";
    string caracteresHexadecimales = "0123456789ABCDEFabcdef";

    while (optionMain != 0) {
        cout << "Eliga el sistema numerico del numero:\n";
        cout << "1. Binario\n";
        cout << "2. Octal\n";
        cout << "3. Decimal\n";
        cout << "4. Hexadecimal\n";
        cout << "5. Convertir a otro sistema numerico(Solo con conversión previa)\n";
        cout << "0. Salir\n";
        do {
            cout << "Ingrese la opcion: ";
            cin >> optionMain;
            if (!confirmationCharacters(to_string(optionMain), caracteresDecimales)) {
                cout << "El caracter digitado no es una opcion, Seleccione una opcion correcta o 0 para salir" << endl;
            }
        } while (!confirmationCharacters(to_string(optionMain), caracteresDecimales) || optionMain == 0);
        
        if (optionMain == 0) {
            break;
        }
        switch (optionMain) {
            case 1:
                cout << "(Sis. Bin.)Escriba el numero que deseas convertir o 0 para salir: ";
                cin >> number;
                if (confirmationCharacters(number, caracteresBinarios)) {
                    cout << "(Sis. Bin.)La cadena contiene caracteres permitidos.\n";
                } else {
                    cout << "Hubo un error, empieze otra vez y eliga el sistema numerico correcto o corriga el numero.\n";
                    continue;
                }
                while (optionOne != 0) {
                    cout << "(Sis. Bin.)Eliga el sistema numerico al que desea convertir el numero o eliga 0 para devolverse:\n";
                    cout << "1. Octal\n";
                    cout << "2. Decimal\n";
                    cout << "3. Hexadecimal\n";
                    cout << "0. Salir\n";
                    do {
                        cout << "Ingrese el numero del sistema: ";
                        cin >> optionOne;
                        if (!confirmationCharacters(to_string(optionOne), caracteresDecimales)) {
                            cout << "El caracter digitado no es una opcion, Seleccione una opcion correcta o 0 para salir" << endl;
                        }
                    } while (!confirmationCharacters(to_string(optionOne), caracteresDecimales) || optionOne == 0);

                    if (optionOne == 0) {
                        break;
                    }
                    switch (optionOne) {
                        case 1: {
                                int decimal = binarioADecimal(number);
                                result = decimalAOctal(decimal);
                                cout << "(Sis. Bin.)El número en Octal es: " << result << endl;
                                sistemFromResult = "Octal";
                            }
                            break;
                        case 2: {
                                result = to_string(binarioADecimal(number));
                                cout << "(Sis. Bin.)El número en Decimal es: " << result << endl;
                                sistemFromResult = "Decimal";
                            }
                            break;
                        case 3: {
                                int decimal = binarioADecimal(number);
                                result = decimalAHexadecimal(decimal);
                                cout << "(Sis. Bin.)El número en Hexadecimal es: " << result << endl;
                                sistemFromResult = "Hexadecimal";
                            }
                            break;
                        default:{
                            cout << "El sistema elegido no existe\n";
                            break;
                        }
                    }
                }
                break;
            case 2:
                cout << "(Sis. Oct.)Escriba el numero que deseas convertir o 0 para salir: ";
                cin >> number;
                if (confirmationCharacters(number, caracteresOctales)) {
                    cout << "(Sis. Oct.)La cadena contiene caracteres permitidos.\n";
                } else {
                    cout << "Hubo un error, empieze otra vez y eliga el sistema numerico correcto o corriga el numero.\n";
                    continue;
                }
                while (optionTwo != 0) {
                    cout << "(Sis. Oct.)Eliga el sistema numerico al que desea convertir el numero o eliga 0 para devolverse:\n";
                    cout << "1. Binario\n";
                    cout << "2. Decimal\n";
                    cout << "3. Hexadecimal\n";
                    cout << "0. Salir\n";
                    do {
                        cout << "Ingrese el numero del sistema: ";
                        cin >> optionTwo;
                        if (!confirmationCharacters(to_string(optionTwo), caracteresDecimales)) {
                            cout << "El caracter digitado no es una opcion, Seleccione una opcion correcta o 0 para salir" << endl;
                        }
                    } while (!confirmationCharacters(to_string(optionTwo), caracteresDecimales) || optionTwo == 0);

                    if (optionTwo == 0) {
                        break;
                    }
                    switch (optionTwo) {
                        case 1: {
                                int decimal = octalADecimal(number);
                                result = decimalABinario(decimal);
                                cout << "(Sis. Oct.)El número en Binario es: " << result << endl;
                                sistemFromResult = "Binario";
                            }
                            break;
                        case 2: {
                                result = to_string(octalADecimal(number));
                                cout << "(Sis. Oct.)El número en Decimal es: " << result << endl;
                                sistemFromResult = "Decimal";
                            }
                            break;
                        case 3: {
                                int decimal = octalADecimal(number);
                                result = decimalAHexadecimal(decimal);
                                cout << "(Sis. Oct.)El número en Hexadecimal es: " << result << endl;
                                sistemFromResult = "Hexadecimal";
                            }
                            break;
                        default:{
                            cout << "El sistema elegido no existe\n";
                            break;
                        }
                    }
                }
                break;
            case 3:
                cout << "(Sis. Dec.)Escriba el numero que deseas convertir o 0 para salir: ";
                cin >> number;
                if (confirmationCharacters(number, caracteresDecimales)) {
                    cout << "(Sis. Dec.)La cadena contiene caracteres permitidos.\n";
                } else {
                    cout << "Hubo un error, empieze otra vez y eliga el sistema numerico correcto o corriga el numero.\n";
                    continue;
                }
                while (optionThree != 0) {
                    cout << "(Sis. Dec.)Eliga el sistema numerico al que desea convertir el numero o eliga 0 para devolverse:\n";
                    cout << "1. Binario\n";
                    cout << "2. Octal\n";
                    cout << "3. Hexadecimal\n";
                    cout << "0. Salir\n";
                    do {
                        cout << "Ingrese el numero del sistema: ";
                        cin >> optionThree;
                        if (!confirmationCharacters(to_string(optionThree), caracteresDecimales)) {
                            cout << "El caracter digitado no es una opcion, Seleccione una opcion correcta o 0 para salir" << endl;
                        }
                    } while (!confirmationCharacters(to_string(optionThree), caracteresDecimales) || optionThree == 0);

                    if (optionThree == 0) {
                        break;
                    }
                    switch (optionThree) {
                        case 1: {
                                int decimal = stoi(number);
                                result = decimalABinario(decimal);
                                cout << "(Sis. Dec.)El número en Binario es: " << result << endl;
                                sistemFromResult = "Binario";
                            }
                            break;
                        case 2: {
                                int decimal = stoi(number);
                                result = decimalAOctal(decimal);
                                cout << "(Sis. Dec.)El número en Octal es: " << result << endl;
                                sistemFromResult = "Octal";
                            }
                            break;
                        case 3: {
                                int decimal = stoi(number);
                                result = decimalAHexadecimal(decimal);
                                cout << "(Sis. Dec.)El número en Hexadecimal es: " << result << endl;
                                sistemFromResult = "Hexadecimal";
                            }
                            break;
                        default:{
                            cout << "El sistema elegido no existe\n";
                            break;
                        }
                    }
                }
                break; 
            case 4:
                cout << "(Sis. Hex.)Escriba el numero que deseas convertir o 0 para salir: ";
                cin >> number;
                if (confirmationCharacters(number, caracteresHexadecimales)) {
                    cout << "La cadena contiene caracteres permitidos.\n";
                } else {
                    cout << "Hubo un error, empieze otra vez y eliga el sistema numerico correcto o corriga el numero.\n";
                    continue;
                }
                while (optionFour != 0) {
                    cout << "(Sis. Hex.)Eliga el sistema numerico al que desea convertir el numero o eliga 0 para devolverse:\n";
                    cout << "1. Binario\n";
                    cout << "2. Octal\n";
                    cout << "3. Decimal\n";
                    cout << "0. Salir\n";
                    do {
                        cout << "Ingrese el numero del sistema: ";
                        cin >> optionFour;
                        if (!confirmationCharacters(to_string(optionFour), caracteresDecimales)) {
                            cout << "El caracter digitado no es una opcion, Seleccione una opcion correcta o 0 para salir" << endl;
                        }
                    } while (!confirmationCharacters(to_string(optionFour), caracteresDecimales) || optionFour == 0);

                    if (optionFour == 0) {
                        break;
                    }
                    switch (optionFour) {
                        case 1: {
                                int decimal = hexadecimalADecimal(number);
                                result = decimalABinario(decimal);
                                cout << "(Sis. Hex.)El número en Binario es: " << result << endl;
                                sistemFromResult = "Binario";
                            }
                            break;
                        case 2: {
                                int decimal = hexadecimalADecimal(number);
                                result = decimalAOctal(decimal);
                                cout << "(Sis. Hex.)El número en Octal es: " << result << endl;
                                sistemFromResult = "Octal";
                            }
                            break;
                        case 3: {
                                result = to_string(hexadecimalADecimal(number));
                                cout << "(Sis. Hex.)El número en Decimal es: " << result << endl;
                                sistemFromResult = "Decimal";
                            }
                            break;
                        default:{
                            cout << "El sistema elegido no existe\n";
                            break;
                        }
                    }
                }
                break;
            case 5:
                if (result == "None") {  
                    cout << "Todavia no as echo ninguna conversion, por favor eliga otra opción\n";
                    break;
                }
                cout << "(Sis. " << sistemFromResult << ")Su numero es: " << result << endl;

                while (optionFive != 0) {
                    cout << "(Sis. " << sistemFromResult << ")Eliga el sistema numerico al que desea convertir el numero anterior o eliga 0 para devolverse:\n";
                    cout << "Eliga el mismo sistema numerico del numero si desea verlo\n";
                    cout << "1. Binario\n";
                    cout << "2. Octal\n";
                    cout << "3. Decimal\n";
                    cout << "4. Hexadecimal\n";
                    cout << "0. Salir\n";
                    do {
                        cout << "Ingrese el numero del sistema: ";
                        cin >> optionFive;
                        if (!confirmationCharacters(to_string(optionFive), caracteresDecimales)) {
                            cout << "El caracter digitado no es una opcion, Seleccione una opcion correcta o 0 para salir" << endl;
                        }
                    } while (!confirmationCharacters(to_string(optionFive), caracteresDecimales) || optionFive == 0);

                    if (optionFive == 0) {
                        break;
                    }
                    if (sistemFromResult == "Binario") {
                        result = to_string(binarioADecimal(result));
                        continue;
                    } else if (sistemFromResult == "Octal") {
                        result = to_string(octalADecimal(result));
                        continue;
                    } else if (sistemFromResult == "Decimal") {
                        continue;
                    } else if (sistemFromResult == "Hexadecimal") {
                        result = to_string(hexadecimalADecimal(result));
                        continue;
                    }

                    switch (optionFive) {
                        case 1: {
                                if (sistemFromResult == "Binario") {
                                    cout << "Su numero es: " << result << " \n";
                                    break;
                                }
                                result = decimalABinario(stoi(result));
                                cout << "(Sis. " << sistemFromResult << ")El número en Binario es: " << result << endl;
                                sistemFromResult = "Binario";
                            }
                            break;
                        case 2: {
                                if (sistemFromResult == "Octal") {
                                    cout << "Su numero es: " << result << " \n";
                                    break;
                                }
                                result = decimalAOctal(stoi(result));
                                cout << "(Sis. " << sistemFromResult << ")El número en Octal es: " << result << endl;
                                sistemFromResult = "Octal";
                            }
                            break;
                        case 3: {
                                if (sistemFromResult == "Decimal") {
                                    cout << "Su numero es: " << result << " \n";
                                    break;
                                }
                                cout << "(Sis. " << sistemFromResult << ")El número en Decimal es: " << result << endl;
                                sistemFromResult = "Decimal";
                            }
                            break;
                        case 4: {
                                if (sistemFromResult == "Hexadecimal") {
                                    cout << "Su numero es: " << result << " \n";
                                    break;
                                }
                                result = decimalAHexadecimal(stoi(result));
                                cout << "(Sis. " << sistemFromResult << ")El número en Hexadecimal es: " << result << endl;
                                sistemFromResult = "Hexadecimal";
                            }
                            break;
                        default:{
                            cout << "El sistema elegido no existe\n";
                            break;
                        }
                    }
                }
                break;
            default:{
                cout << "El sistema elegido no existe\n";
                break;
            }
        }
    }
    return 0;
8;} 