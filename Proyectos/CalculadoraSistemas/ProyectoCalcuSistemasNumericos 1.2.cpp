#include <iostream>
#include <string>
#include <cmath>
using namespace std;

bool ifCharactersAreAllowed(const string& characterString, const string& allowedCharacters) {
    return characterString.find_first_not_of(allowedCharacters) == string::npos;
} 

string getOptionCorrect(string allowedCharacters) {
    string option = "None";
    while (!ifCharactersAreAllowed(option, allowedCharacters)) {
        cout << "Ingrese la opcion: ";
        cin >> option;
        if (!ifCharactersAreAllowed(option, allowedCharacters)) {
            cout << "El caracter digitado no es una opcion, Seleccione una opcion correcta o 0 para salir" << endl;
        }
    }
    return option;
}

string confirmationNumberWhitSistem(string allowedCharacters, string sistemFromNumber) {
    string number = "None", negativeCharacter = "-", positiveCharacter = "0123456789ABCDEFabcdef";
    while (!ifCharactersAreAllowed(number, allowedCharacters)) {
        cout << "(Sis. " << sistemFromNumber << ")Ingrese el numero que desea convertir o 0 para devolverse: ";
        cin >> number;
        if (!ifCharactersAreAllowed(number, allowedCharacters)) {
            cout << "El numero no concuerda con el sistema numerico\n";
        } else {
           for (size_t i = 1; i < number.length(); ++i) {
                if ((negativeCharacter[0] == number[i]) == true) {
                    cout << "El numero contiene un o varios caracteres en una ubicacion erronea!\n";
                    number = "None";
                }
            }
        }
    }
    return number;
}

int binaryToDecimal(const string& binario) {
    int decimal = 0, length = binario.length();
    for (int i = 0; i < length; ++i) {
        if (binario[length - i - 1] == '1') {
            decimal += pow(2, i);
        }
    }
    return decimal;
}

int octalToDecimal(const string& octal) {
    int decimal = 0;
    int length = octal.length();
    for (int i = 0; i < length; ++i) {
        decimal += (octal[length - i - 1] - '0') * pow(8, i);
    }
    return decimal;
}

int hexadecimalToDecimal(const string& number) {
    int decimal = 0, size = number.size(), power = 0;
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

string decimalToBinary(int decimal) {
    string binario;
    while (decimal > 0) {
        binario = to_string(decimal % 2) + binario;
        decimal /= 2;
    }
    return binario;
}

string decimalToHexadecimal(int decimal) {
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

string decimalToOctal(int decimal) {
    string octal;
    while (decimal > 0) {
        octal = to_string(decimal % 8) + octal;
        decimal /= 8;
    }
    return octal;
}

string everythingToDecimal(string number, string numberSistem) {
    string result = "None";
    if (numberSistem == "Bin.") {
        result = to_string(binaryToDecimal(number));
    } else if (numberSistem == "Oct.") {
        result = to_string(octalToDecimal(number));
    } else if (numberSistem == "Hex.") {
        result = to_string(hexadecimalToDecimal(number));
    } else {
        result = to_string(stoi(number));
    }
    return result;
}

void usingLastResult(string result, string sistemFromResult) {
    if (result == "None") {
        cout << "Todavia no as echo ninguna conversion, por favor eliga otra opción\n";
        return;
    }
    string option = "6", decimalCharacters = "-0123456789", positiveCharacter = "0123456789ABCDEFabcdef", decimalCharactersPositive = "0123456789";
    cout << "(Sis. " << sistemFromResult << ")Su numero es: " << result << endl;
    while (stoi(option) != 0) {
        string newResult, resultGoningToUse = "";
        cout << "(Sis. " << sistemFromResult << ")Eliga el sistema numerico al que desea convertir el numero anterior o eliga 0 para devolverse:\n";
        cout << "Eliga el mismo sistema numerico del numero si desea verlo\n";
        cout << "1. Binario\n""2. Octal\n""3. Decimal\n""4. Hexadecimal\n""0. Salir\n";
        option = getOptionCorrect(decimalCharactersPositive);
        if (stoi(option) == 0) {
            return;
        } else if ((result.find_first_not_of(positiveCharacter) == string::npos) == true) {
            newResult = "", resultGoningToUse = result;
        } else if ((result.find_first_not_of(positiveCharacter) == string::npos) == false) {
            newResult = "-";
            for (size_t i = 1; i < result.length(); ++i) {
                resultGoningToUse += result[i];
            }
        }
        switch (stoi(option)) {
            case 1: {
                if (sistemFromResult == "Bin.") {
                    cout << "(Sis. Bin.)Su numero es: " << result << endl;
                    break;
                }
                string decimal = everythingToDecimal(resultGoningToUse, sistemFromResult);
                newResult += decimalToBinary(stoi(decimal));
                cout << "(Sis. " << sistemFromResult << ")El número "<< result <<" en Binario es: " << newResult << endl;
                break;
            } case 2: {
                if (sistemFromResult == "Oct.") {
                    cout << "(Sis. Oct.)Su numero es: " << result << endl;
                    break;
                }
                string decimal = everythingToDecimal(resultGoningToUse, sistemFromResult);
                newResult += decimalToOctal(stoi(decimal));
                cout << "(Sis. " << sistemFromResult << ")El número "<< result <<" en Octal es: " << newResult << endl;
                break;
            } case 3: {
                if (sistemFromResult == "Dec.") {
                    cout << "(Sis. Dec.)Su numero es: " << result << endl;
                    break;
                }
                newResult += everythingToDecimal(resultGoningToUse, sistemFromResult);
                cout << "(Sis. " << sistemFromResult << ")El número "<< result <<" en Decimal es: " << newResult << endl;
                break;
            } case 4: {
                if (sistemFromResult == "Hex.") {
                    cout << "(Sis. Hex.)Su numero es: " << result << endl;
                    break;
                }   
                string decimal = everythingToDecimal(resultGoningToUse, sistemFromResult);
                newResult += decimalToHexadecimal(stoi(decimal));
                cout << "(Sis. " << sistemFromResult << ")El número "<< result <<" en Hexadecimal es: " << newResult << endl;
                break;
            } default: {
                cout << "El sistema elegido no existe\n";
                break;
            }
        }
    }
}

int main() {
    cout << "Bienvenido, presione ENTER para empezar.\n";
    cin.get();
    cout << "Empezemos!\n""Este programa le ayudara a convertir numeros entre los sistemas numericos Binario, Octal, Decimal y Hexadecimal\n";
    string number = "", numberGoingToUse = "", result = "None", sistemFromResult = "None", sistemFromNumber = "None";
    string optionMain, optionOne, optionTwo;
    const string binaryCharacters = "-01", octalCharacters = "-01234567", decimalCharacters = "-0123456789", decimalCharactersPositive = "0123456789";
    const string hexadecimalCharacters = "-0123456789ABCDEFabcdef", positiveCharacter = "0123456789ABCDEFabcdef", negativeCharacter = "-";
    while (optionMain != "0") {
        optionOne = "6", optionTwo = "6", optionMain = "6", number = "None";
        cout << "Eliga el sistema numerico del numero:\n""1. Binario\n""2. Octal\n""3. Decimal\n""4. Hexadecimal\n";
        if (sistemFromResult != "None") {
            cout << "5. Convertir numero anterior a otro sistema numerico (Disponible)\n";
        } else {
            cout << "5. Convertir numero anterior a otro sistema numerico (No hay resultado anterior)\n";
        }
        cout << "0. Salir\n";
        optionMain = getOptionCorrect(decimalCharactersPositive);
        if (stoi(optionMain) == 0) {
            break;
        }
        switch (stoi(optionMain)) {
            case 1: {
                sistemFromNumber = "Bin.";
                number = confirmationNumberWhitSistem(binaryCharacters, sistemFromNumber);
                break;
            } case 2: {
                sistemFromNumber = "Oct.";
                number = confirmationNumberWhitSistem(octalCharacters, sistemFromNumber);
                break;
            } case 3: {
                sistemFromNumber = "Dec.";
                number = confirmationNumberWhitSistem(decimalCharacters, sistemFromNumber);
                break;
            } case 4: {
                sistemFromNumber = "Hex.";
                number = confirmationNumberWhitSistem(hexadecimalCharacters, sistemFromNumber);
                break;
            } case 5:{
                usingLastResult(result, sistemFromResult);
                continue;
            } default: {
                cout << "El sistema elegido no existe\n";
                continue;
            }
        }
        if ((number == "0") || (number == "None")) {
            continue;
        }
        cout << "(Sis. " << sistemFromNumber << ")Su numero es: " << number << endl;
        while (stoi(optionOne) != 0) {
            numberGoingToUse = "";
            cout << "(Sis. " << sistemFromNumber << ")Eliga el sistema numerico al que desea convertir el numero o eliga 0 para devolverse:\n";
            cout << "Eliga el mismo sistema numerico del numero si desea verlo\n";
            cout << "1. Binario\n""2. Octal\n""3. Decimal\n""4. Hexadecimal\n""0. Salir\n";
            optionOne = getOptionCorrect(decimalCharactersPositive);
            if (stoi(optionOne) == 0) {
                break;
            } else if ((number.find_first_not_of(positiveCharacter) == string::npos) == true) {
                result = "", numberGoingToUse = number;
            } else if ((number.find_first_not_of(positiveCharacter) == string::npos) == false) {
                result = "-";
                for (size_t i = 1; i < number.length(); ++i) {
                    numberGoingToUse += number[i];
                }
            }
            switch (stoi(optionOne)) {
                case 1: {
                    if (sistemFromNumber == "Bin.") {
                        cout << "(Sis. Bin.)Su numero es: " << number << endl;
                        break;
                    }
                    string decimal = everythingToDecimal(numberGoingToUse, sistemFromNumber);
                    result += decimalToBinary(stoi(decimal));
                    cout << "(Sis. " << sistemFromNumber << ")El número "<< number <<" en Binario es: " << result << endl;
                    sistemFromResult = "Bin.";
                    break;
                } case 2: {
                    if (sistemFromNumber == "Oct.") {
                        cout << "(Sis. Oct.)Su numero es: " << number << endl;
                        break;
                    }
                    string decimal = everythingToDecimal(numberGoingToUse, sistemFromNumber);
                    result += decimalToOctal(stoi(decimal));
                    cout << "(Sis. " << sistemFromNumber << ")El número "<< number <<" en Octal es: " << result << endl;
                    sistemFromResult = "Oct.";
                    break;
                } case 3: {
                    if (sistemFromNumber == "Dec.") {
                        cout << "(Sis. Dec.)Su numero es: " << number << endl;
                        break;
                    }
                    result += everythingToDecimal(numberGoingToUse, sistemFromNumber);
                    cout << "(Sis. " << sistemFromNumber << ")El número "<< number <<" en Decimal es: " << result << endl;
                    sistemFromResult = "Dec.";
                    break;
                } case 4: {
                    if (sistemFromNumber == "Hex.") {
                    cout << "(Sis. Hex.)Su numero es: " << number << endl;
                    break;
                    }
                    string decimal = everythingToDecimal(numberGoingToUse, sistemFromNumber);
                    result += decimalToHexadecimal(stoi(decimal));
                    cout << "(Sis. " << sistemFromNumber << ")El número "<< number <<" en Hexadecimal es: " << result << endl;
                    sistemFromResult = "Hex.";
                    break;
                } default: {
                    cout << "El sistema elegido no existe\n";
                    break;
                }
            }
        }
    }
    cout << "El programa ha terminado, gracias por usar el programa\n";
    return 0;
8;}