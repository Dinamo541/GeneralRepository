#include <iostream>
using namespace std;

void pruebaPunteros() {
    int* ptr = new int;  // Reserva memoria dinámica para un entero
    *ptr = 42;           // Guarda el valor 42 en esa memoria

    cout << "Valor dinamico: " << *ptr << endl;

    delete ptr;          // Libera la memoria
    ptr = nullptr;       // Buena práctica: evitar puntero colgante
}

void punterosDos() {
    int number = 10;

    int* ptr = &number;

    cout << ptr << endl;
    cout << *ptr << endl;
}

// Función que recibe un puntero y la cantidad de elementos
void imprimirArreglo(int* arreglo, int tamannio) {
    for (int i = 0; i < tamannio; i++) {
        cout << "Elemento " << i << ": " << arreglo[i] << endl;
        // También podrías usar: arreglo[i]
    }
}

void numero(int* numero) {
    *numero = (*numero) * 2;
}

void fromVarToPtr(int &numOne, int* ptr) {
    *ptr = numOne;
}

void createMatrix() {
    int rows = 0, colums = 0;
    printf("Agregue la cantidad de fila\n");
    scanf("%d", &rows);
    printf("Agregue la cantidad de columnas\n");
    scanf("%d", &colums);
    int **matrix = new int* [rows];
    for (int i = 0; i < rows; i++)
        matrix[i] = new int[colums];
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < colums; j++)
            matrix[i][j] = i * 10;
    for (int i = 0; i < rows; i++) {
        printf("\n");
        for (int j = 0; j < colums; j++)
            printf("%d \n", matrix[i][j]);
    }
    delete[] matrix;
    matrix = nullptr;
}


float* getCharPositionsInMatrix(char** matrix, int rows, int colums, char value) {
    int **positions = new int*[rows];
}


int main() {

    int numOne = 10, *ptr = new int;

    fromVarToPtr(numOne, ptr);

    for (int i = 0; i < (*ptr); i++) {
        printf("%d \n", (i+1));
    }
    cout << endl;

    int arreglo[] = {10, 20, 30, 40, 50};
    int cantidad = sizeof(arreglo) / sizeof(arreglo[0]);  // Calcula cuántos elementos tiene

    imprimirArreglo(arreglo, cantidad);  // Paso el arreglo como puntero y su tamaño

    int x = 10;
    numero(&x);

    return 0;
}