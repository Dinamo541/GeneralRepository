// Testeos.cpp : This file contains the 'main' function. Program execution begins
#include<iostream>
#include <string>
using namespace std;

void elevarPotencia(int myArray[], int expo, int tam){
    int resultado;
    for (int i = 0; i < tam; i++) {
        resultado = 1;
        for (int j = 0; j < expo; j++) {
            resultado *= myArray[i];
        }
        myArray[i] = resultado;
    }
}


int main () {

    const int tam = 10;

    int myArreglo[tam];

    //llenado del arreglo
    for ( int i = 0; i < tam ; i++){
        cout << "Ingrese el valor" << i <<  " del arreglo " << endl;
        cout << "Ingrese el valor" << i+1 <<  " del arreglo " << endl;
        cin  >> myArreglo[i];
    }

    // imprimir los valores del arreglo 
    cout << "\n"<< "\n"<< "Los valores del arreglos son:";
    for ( int i =0; i< tam; i++){
        cout << myArreglo[i] << " ";

    }

    // calcular la suma de los valores de un vector 

    int suma = 0;
    for ( int i =0; i< tam; i++){
        suma += myArreglo[i];
    }
    cout << "\n"<< "\n"<< "La suma de los valores del arreglos da: " << suma;



    return 0;
}