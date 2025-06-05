#include <iostream>
#include <string>
#include <cmath>
using namespace std;

bool confirmationCharacters(const string& characterString, const string& allowedCharacters) {
    return characterString.find_first_not_of(allowedCharacters) == string::npos;
}

string confirmationOption(string allowedCharacters) {
    string option = "None";
    while (!confirmationCharacters(option, allowedCharacters)) {
        cout << "Ingrese la opcion: ";
        cin >> option;
        if (!confirmationCharacters(option, allowedCharacters)) {
            cout << "El caracter digitado no es una opcion, Seleccione una opcion correcta o 0 para salir" << endl;
        }
    }
    return option;
}

int binarioADecimal(const string& binario) {
    int decimal = 0;
    int length = binario.length();
    for (int i = 0; i < length; ++i) {
        if (binario[length - i - 1] == '1') {
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

string everythingToDecimal (string number,string numberSistem){
    string result = "None";
    if (numberSistem == "Bin.") {
        result = to_string(binarioADecimal(number));
    } else if (numberSistem == "Oct.") {
        result = to_string(octalADecimal(number));
    } else if (numberSistem == "Hex.") {
        result = to_string(hexadecimalADecimal(number));
    } else {
        result = number;
    }
    return result;
}

int main() {
    cout << "Bienvenido, presione ENTER para empezar.\n";
    cin.get();
    cout << "Empezemos!\n";
    string number = "1", result = "None", sistemFromResult = "None";
    string optionMain, optionOne, optionTwo, optionThree, optionFour, optionFive;
    const string caracteresBinarios = "01";
    const string caracteresOctales = "01234567";
    const string caracteresDecimales = "0123456789";
    const string caracteresHexadecimales = "0123456789ABCDEFabcdef";

    while (optionMain != "0") {
        optionOne = "6", optionTwo = "6", optionThree = "6", optionFour = "6", optionFive = "6";
        cout << "Eliga el sistema numerico del numero:\n";
        cout << "1. Binario\n""2. Octal\n""3. Decimal\n""4. Hexadecimal\n";
        if (sistemFromResult != "None") {
            cout << "5. Convertir numero anterior a otro sistema numerico (Disponible)\n";
        } else {
            cout << "5. Convertir numero anterior a otro sistema numerico (No disponible todavia)\n";
        }
        cout << "0. Salir\n";

        optionMain = confirmationOption(caracteresDecimales);
        if (stoi(optionMain) == 0) {
            break;
        }
        switch (stoi(optionMain)) {
            case 1:
                cout << "(Sis. Bin.)Escriba el numero que deseas convertir o 0 para salir: ";
                cin >> number;
                if (number == "0") {
                    break;
                } else if (confirmationCharacters(number, caracteresBinarios)) {
                    cout << "(Sis. Bin.)La cadena contiene caracteres permitidos.\n";
                } else {
                    cout << "Hubo un error, empieze otra vez y eliga el sistema numerico correcto o corriga el numero.\n";
                    continue;
                }
                while (stoi(optionOne) != 0) {
                    cout << "(Sis. Bin.)Eliga el sistema numerico al que desea convertir el numero o eliga 0 para devolverse:\n";
                    cout << "1. Octal\n""2. Decimal\n""3. Hexadecimal\n""0. Salir\n";

                    optionOne = confirmationOption(caracteresDecimales);
                    if (stoi(optionOne) == 0) {
                        break;
                    }
                    switch (stoi(optionOne)) {
                        case 1: {
                                int decimal = binarioADecimal(number);
                                result = decimalAOctal(decimal);
                                cout << "(Sis. Bin.)El número en Octal es: " << result << endl;
                                sistemFromResult = "Oct.";
                            }
                            break;
                        case 2: {
                                int decimal = binarioADecimal(number);
                                result = to_string(decimal); 
                                cout << "(Sis. Bin.)El número en Decimal es: " << result << endl;
                                sistemFromResult = "Dec.";
                            }
                            break;
                        case 3: {
                                int decimal = binarioADecimal(number);
                                result = decimalAHexadecimal(decimal);
                                cout << "(Sis. Bin.)El número en Hexadecimal es: " << result << endl;
                                sistemFromResult = "Hex.";
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
                if (number == "0") {
                    break;
                } else if (confirmationCharacters(number, caracteresOctales)) {
                    cout << "(Sis. Oct.)La cadena contiene caracteres permitidos.\n";
                } else {
                    cout << "Hubo un error, empieze otra vez y eliga el sistema numerico correcto o corriga el numero.\n";
                    continue;
                }
                while (stoi(optionTwo) != 0) {
                    cout << "(Sis. Oct.)Eliga el sistema numerico al que desea convertir el numero o eliga 0 para devolverse:\n";
                    cout << "1. Binario\n""2. Decimal\n""3. Hexadecimal\n""0. Salir\n";

                    optionTwo = confirmationOption(caracteresDecimales);
                    if (stoi(optionTwo) == 0) {
                        break;
                    }
                    switch (stoi(optionTwo)) {
                        case 1: {
                                int decimal = octalADecimal(number);
                                result = decimalABinario(decimal);
                                cout << "(Sis. Oct.)El número en Binario es: " << result << endl;
                                sistemFromResult = "Bin.";
                            }
                            break;
                        case 2: {
                                int decimal = octalADecimal(number);
                                result = to_string(decimal);
                                cout << "(Sis. Oct.)El número en Decimal es: " << result << endl;
                                sistemFromResult = "Dec.";
                            }
                            break;
                        case 3: {
                                int decimal = octalADecimal(number);
                                result = decimalAHexadecimal(decimal);
                                cout << "(Sis. Oct.)El número en Hexadecimal es: " << result << endl;
                                sistemFromResult = "Hex.";
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
                if (number == "0") {
                    break;
                } else if (confirmationCharacters(number, caracteresDecimales)) {
                    cout << "(Sis. Dec.)La cadena contiene caracteres permitidos.\n";
                } else {
                    cout << "Hubo un error, empieze otra vez y eliga el sistema numerico correcto o corriga el numero.\n";
                    continue;
                }
                while (stoi(optionThree) != 0) {
                    cout << "(Sis. Dec.)Eliga el sistema numerico al que desea convertir el numero o eliga 0 para devolverse:\n";
                    cout << "1. Binario\n""2. Octal\n""3. Hexadecimal\n""0. Salir\n";

                    optionThree = confirmationOption(caracteresDecimales);
                    if (stoi(optionThree) == 0) {
                        break;
                    }
                    switch (stoi(optionThree)) {
                        case 1: {
                                int decimal = stoi(number);
                                result = decimalABinario(decimal);
                                cout << "(Sis. Dec.)El número en Binario es: " << result << endl;
                                sistemFromResult = "Bin.";
                            }
                            break;
                        case 2: {
                                int decimal = stoi(number);
                                result = decimalAOctal(decimal);
                                cout << "(Sis. Dec.)El número en Octal es: " << result << endl;
                                sistemFromResult = "Oct.";
                            }
                            break;
                        case 3: {
                                int decimal = stoi(number);
                                result = decimalAHexadecimal(decimal);
                                cout << "(Sis. Dec.)El número en Hexadecimal es: " << result << endl;
                                sistemFromResult = "Hex.";
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
                if (number == "0") {
                    break;
                } else if (confirmationCharacters(number, caracteresHexadecimales)) {
                    cout << "(Sis. Hex.)La cadena contiene caracteres permitidos.\n";
                } else {
                    cout << "Hubo un error, empieze otra vez y eliga el sistema numerico correcto o corriga el numero.\n";
                    continue;
                }
                
                while (stoi(optionFour) != 0) {
                    cout << "(Sis. Hex.)Eliga el sistema numerico al que desea convertir el numero o eliga 0 para devolverse:\n";
                    cout << "1. Binario\n""2. Octal\n""3. Decimal\n""0. Salir\n";

                    optionFour = confirmationOption(caracteresDecimales);
                    if (stoi(optionFour) == 0) {
                        break;
                    }
                    switch (stoi(optionFour)) {
                        case 1: {
                                int decimal = hexadecimalADecimal(number);
                                result = decimalABinario(decimal);
                                cout << "(Sis. Hex.)El número en Binario es: " << result << endl;
                                sistemFromResult = "Bin.";
                            }
                            break;
                        case 2: {
                                int decimal = hexadecimalADecimal(number);
                                result = decimalAOctal(decimal);
                                cout << "(Sis. Hex.)El número en Octal es: " << result << endl;
                                sistemFromResult = "Oct.";
                            }
                            break;
                        case 3: {
                                int decimal = hexadecimalADecimal(number);
                                result = to_string(decimal);
                                cout << "(Sis. Hex.)El número en Decimal es: " << result << endl;
                                sistemFromResult = "Dec.";
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

                while (stoi(optionFive) != 0) {
                    cout << "(Sis. " << sistemFromResult << ")Eliga el sistema numerico al que desea convertir el numero anterior o eliga 0 para devolverse:\n";
                    cout << "Eliga el mismo sistema numerico del numero si desea verlo\n";
                    cout << "1. Binario\n""2. Octal\n""3. Decimal\n""4. Hexadecimal\n""0. Salir\n";

                    optionFive = confirmationOption(caracteresDecimales);
                    if (stoi(optionFive) == 0) {
                        break;
                    }
                    switch (stoi(optionFive)) {
                        case 1: {
                                if (sistemFromResult == "Bin.") {
                                    cout << "(Sis. Bin.)Su numero es: " << result << endl;
                                    break;
                                }
                                string decimal = everythingToDecimal(result, sistemFromResult);
                                string newResult = decimalABinario(stoi(decimal));
                                cout << "(Sis. " << sistemFromResult << ")El número en Binario es: " << newResult << endl;
                                string sistemFromResult = "Bin.";
                            }
                            break;
                        case 2: {
                                if (sistemFromResult == "Oct.") {
                                    cout << "(Sis. Oct.)Su numero es: " << result << endl;
                                    break;
                                }
                                string decimal = everythingToDecimal(result, sistemFromResult);
                                string newResult = decimalAOctal(stoi(decimal));
                                cout << "(Sis. " << sistemFromResult << ")El número en Octal es: " << newResult << endl;
                                string sistemFromResult = "Oct.";
                            }
                            break;
                        case 3: {
                                if (sistemFromResult == "Dec.") {
                                    cout << "(Sis. Dec.)Su numero es: " << result << endl;
                                    break;
                                }
                                string newResult = everythingToDecimal(result, sistemFromResult);
                                cout << "(Sis. " << sistemFromResult << ")El número en Decimal es: " << newResult << endl;
                                string sistemFromResult = "Dec.";
                            }
                            break;
                        case 4: {
                                if (sistemFromResult == "Hex.") {
                                    cout << "(Sis. Hex.)Su numero es: " << result << endl;
                                    break;
                                }
                                string decimal = everythingToDecimal(result, sistemFromResult);
                                string newResult = decimalAHexadecimal(stoi(decimal));
                                cout << "(Sis. " << sistemFromResult << ")El número en Hexadecimal es: " << newResult << endl;
                                string sistemFromResult = "Hex.";
                            }
                            break;
                        default: {
                                cout << "El sistema elegido no existe\n";
                            break;
                        }
                    }
                }
                break;
            default:{
                cout << "El sistema elegido no existe\n";
            }
            break;
        }
    }
    system("cls");
    cout << "Gracias por usar el programa\n";
return 0;
8;}