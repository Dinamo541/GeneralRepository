#include <iostream>
#include <string>

class Practice {
private:
    static const int SIZE = 10; // Tamañon del arreglo
    int arr[SIZE] = {1, 2, 6, 4, 10, 3, 9, 8, 7, 5}; // Arreglo a tratar

public:
    // Constructor
    Practice() {
        std::cout << "Constructor called" << std::endl;
    }

    // Ejercicio 1: Muestra los elementos duplicados en el arreglo
    void showDuplicate() {
        for (int i = 0; i < SIZE; i++) {
            for (int j = i + 1; j < SIZE; j++) {
                if (arr[i] == arr[j]) {
                    std::cout << "Duplicated: " << arr[i] << std::endl;
                }
            }
        }
    }

    // Ejercicio 2: Ordena el arreglo de mayor a menor
    void orderArr() {
        int auxiliary;
        for (int i = 0; i < SIZE; i++) {
            for (int j = i; j < SIZE; j++) {
                if (arr[i] < arr[j]) {
                    auxiliary = arr[i];
                    arr[i] = arr[j];
                    arr[j] = auxiliary;
                }
            }
        }
    }

    // Ejercicio 3: Suma todos los subarreglos posibles del arreglo
    int sumOfSubArr() {
        int sum = 0;
        for (int size = 1; size <= SIZE; size++) { // define el tamaño del subarreglo
            for (int start = 0; start <= SIZE - size; start++) { // define el inicio
                sum += sumSubArr(start, size);
            }
        }
        return sum;
    }

    // Funcion del Eje.3: Suma los elementos de un subarreglo dado el inicio y el tamaño
    int sumSubArr(int start, int size) {
        int sum = 0;
        for (int i = start; i < start + size; i++) {
            sum += arr[i];
        }
        return sum;
    }

    // Ejercicio 4: Encuentra la secuencia más larga de números consecutivos en el arreglo
    std::string findLongestConsecutives() {
        std::string currentString;
        std::string longestString;

        for (int i = 0; i < SIZE; i++) {
            currentString = std::to_string(arr[i]);
            int j = i;
            while (j < SIZE - 1 && arr[j] + 1 == arr[j + 1]) {
                currentString += "," + std::to_string(arr[j + 1]);
                j++;
            }
            longestString = std::max(longestString, currentString); // Compara y guarda la cadena más larga
        }
        return longestString;
    }

    // Ejercicio 5: Mueve todos los ceros al final del arreglo
    void moveAllZeroEnd() {
        for (int i = 0; i < SIZE - 1; i++) {
            if (arr[i] == 0) {
                moveZeros(i);
            }
        }
    }

    // Funcion del Eje.5: Mueve un cero encontrado a la última posición
    void moveZeros(int index) {
        for (int i = index; i < SIZE - 1; i++) {
            arr[i] = arr[i + 1];
        }
        arr[SIZE - 1] = 0;
    }

    // Ejercicio 6: Mueve los elementos del arreglo 'steps' posiciones a la izquierda
    void moveStepsToLeft(int steps) {
        while (steps > SIZE) {
            steps = steps - SIZE;
        }
        int arrAux[SIZE];
        for (int i = 0; i < SIZE; i++) {
            arrAux[i] = arr[i];
        }
        for (int i = SIZE; i >= 0; i--) {
            if (i - steps >= 0) {
                arr[i] = arrAux[i - steps];
            } else {
                arr[i] = arrAux[i - steps + SIZE];
            }
        }
    }

    // Ejercicio 7: Devuelve la suma más alta de dos elementos consecutivos
    int highestSum() {
        int highestSum = arr[0] + arr[1];
        for (int i = 1; i < SIZE - 1; i++) {
            if (arr[i] + arr[i + 1] > highestSum) {
                highestSum = arr[i] + arr[i + 1];
            }
        }
        return highestSum;
    }

    // Ejercicio 8: Intercambia el primer y el último elemento del arreglo
    void swapFirstAndLast() {
        int first = arr[0];
        arr[0] = arr[SIZE - 1];
        arr[SIZE - 1] = first;
    }

    // Ejercicio 9: Verifica si el arreglo es un palíndromo
    bool checkPalindrome() {
        for (int i = 0; i < SIZE / 2; i++) {
            if (arr[i] != arr[SIZE - 1 - i]) {
                return false;
            }
        }
        return true;
    }
};

int main(int argc, char const *argv[]) {
    Practice practice;
    // Prueba el metodo que quieras

    return 0;
}
