#include <iostream>
using namespace std;

// Ejercicio 9: Escribir un programa que lea un número entero y determine si es un número capicúa o no.

bool isNumberCapicúa(int number) { 
    int reverseNumber = 0;
    int originalNumber = number;
    while (number != 0) {
        reverseNumber = reverseNumber * 10 + number % 10;
        number /= 10; 
    }
    return (reverseNumber == originalNumber);
}

int main () {
    int number = 0;
    cout << "Escriba un numero entero\n";
    cin >> number;

    if (isNumberCapicúa(number)) {
        cout << "El numero " << number << " es capicúa";
    } else {
        cout << "El numero " << number << " no es capicúa";
    }

    return 0;
}