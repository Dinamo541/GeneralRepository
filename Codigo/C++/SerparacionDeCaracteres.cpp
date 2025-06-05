#include <iostream>
#include <string>
#include <cmath>
using namespace std;

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

string decimalAOctal(int decimal) {
    string octal;
    while (decimal > 0) {
        octal = to_string(decimal % 8) + octal;
        decimal /= 8;
    }
    return octal;
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

int main() {
    string Binario = "10101010101010101010101010101";
    int decimal = binarioADecimal(Binario);

    string octal = decimalAOctal(decimal);

    string hexadecimal = decimalAHexadecimal(decimal);

    cout << "El número en binario es: " << Binario << endl;
    cout << "El número en octal es: " << octal << endl;
    cout << "El número en decimal es: " << decimal << endl;
    cout << "El número en hexadecimal es: " << hexadecimal << endl;

    return 0;
}