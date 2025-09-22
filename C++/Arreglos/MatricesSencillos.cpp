#include <iostream>
#include <string>

class Practice {
private:
    static const int ROWS = 2; // Número de filas de la matriz
    static const int COLS = 10; // Número de columnas de la matriz
    int arr[ROWS][COLS] = {
        {1, 2, 6, 4, 10, 3, 9, 8, 7, 5},
        {5, 7, 8, 9, 10, 11, 12, 13, 14, 15}
    }; // Matriz a tratar

public:
    Practice() {
        std::cout << "Constructor called" << std::endl;
    }
    // Ejercicio 1: Suma de elementos de una matriz
    int sumOfMatrix() {
        int sum = 0;
        for (int i = 0; i < ROWS; i++) {
            for (int j = 0; j < COLS; j++) {
                sum += arr[i][j];
            }  
        }
        return sum;
    }
    // Ejercicio 2: Encontrar el mayor elemento en una matriz
    int maxElement() {
        int max = arr[0][0];
        for (int i = 0; i < ROWS; i++) {
            for (int j = 0; j < COLS; j++) {
                max = std::max(max, arr[i][j]);
            }
        }
        return max;
    }
    // Ejercicio 3: Transposición de una matriz
    void transposeMatrix() {
        int auxArr[ROWS][COLS];
        for (int i = 0; i < ROWS; i++) {
            for (int j = 0; j < COLS; j++) {
                /* code */
            }
            
        }
        
    }
    
};