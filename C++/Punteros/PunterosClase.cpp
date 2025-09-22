#include <iostream>

void printfExamples() {
    int x = 2;
    float f= 10.1;
    double d = 15.2f;
    int* ptr = &x;
    *ptr = 256;
    char c = 'c';
    std::string s = "String";

    printf("Tipos de datos y como imprimirlos con printf:\n");
    printf("%d \n", x);     // 256  decimales
    printf("%f \n", f);     // 10.1 float
    printf("%f \n", d);     // 15.2 double
    printf("%p \n", ptr);   // Punteros
    printf("%c \n", c);     // 'c'  char
    printf("%s \n", s);     // "String"
}

void scanfExamples() {
    int x;
    float f;
    double d;
    char c = 'c';
    std::string s = "String";

    printf("Tipos de datos y como resivirlos con scanf:\n");
    scanf("%d", &x);    // Enteros
    scanf("%f", &f);    // Float
    scanf("%f", &d);    // Double
    scanf("%c", &c);    // 'Char'
    scanf("%s", &s);    // "String"
}

void pointersAndTipes() {

    int *ptr = new int;             // Puntero que apunta a un espacio vacio

    int num = 10;
    int *ptr = &num;                // Puntero a la direccion de una variable

    int **ptrTwo = &ptr;            // Puntero a un puntero 

    int *ptr = new int[5];          // Puntero de enteros o vector

    int **ptr = new int*[5];        // Puntero de punteros o vector de punteros

    int **matrix = new int*[4]; 
    for (int i = 0; i < 4; i++)
        matrix[i] = new int[4];     // Matrix de puntero (Se puede seguir tanto como quiera)

}

void workingWithParameters(int* ptr, int** matrix, int &reference) {

    *ptr = (*ptr) + 5;              // Sumar 5 a lo que apunta el puntero

    int numOne = matrix[0][0];      // Espacios dentro de un vector
    int numTwo = **(matrix + 1);    // Espacios dentro de un vector con aritmetica de punteros

    reference = 20;                 // Parametro basado en la direccion 

}

int main() {

    printfExamples();

    int numOne = 10;
    int **matrix = new int*[2]; 
    for (int i = 0; i < 2; i++)
        matrix[i] = new int[2]; 
    int numTwo;

    workingWithParameters(&numOne, matrix, numTwo);

    return 0;
}