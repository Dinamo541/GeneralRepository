// Testeos.cpp : This file contains the 'main' function. Program execution begins
#include <iostream>
#include <cmath>
#include <ctime>

class Practica {
private:
    float a;
    float b;
    float c;

public:
    Practica(float newA, float newB, float newC) {
        a = newA;
        b = newB;
        c = newC;
    }
    ~Practica() {}

    int ifFunctionTouchX() {
        if (((b * b) - (4 * a * c)) < 0) {
            return 0;
        } else if (((b * b) - (4 * a * c)) == 0) {
            return 1;
        }
        return 2;
    }
    float getUniqueX() {
        return (-b) / 2 * a;
    }
    float getX1() {
        int square = std::sqrtl(((b * b) - (4 * a * c)));
        return (-b + square) / (2 * a);
    }
    float getX2() {
        int square = std::sqrtl(((b * b) - (4 * a * c)));
        return (-b - square) / (2 * a);
    }

};

int main () {
    char option = 'Y';
    while (option == 'Y' || option == 'y') {
        float a = 0, b = 0, c = 0;
        printf("Ingrese la a: \n");
        scanf("%f", &a);
        printf("Ingrese la b: \n");
        scanf("%f", &b);
        printf("Ingrese la c: \n");
        scanf("%f", &c);
        Practica practica(a, b, c);
        if (practica.ifFunctionTouchX() == 0) {
            printf("La funcion no toca el eje de las x.\n");
        } else if (practica.ifFunctionTouchX() == 1) {
            printf("La funcion toca el eje de las x una unica vez en (%f,0).\n", practica.getUniqueX());
        } else {
            printf("La funcion toca el eje de las x en (%f,0) y en (%f,0).\n", practica.getX1(), practica.getX2());
        }
        printf("Desea repetir ('Y' para reintentar o cualquier cosas para cerrar): \n");
        scanf("%c", &option);
        system("cls");
    }
    return 0;
}