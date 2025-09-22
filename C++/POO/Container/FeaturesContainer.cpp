#include "Container.hpp"
#include <iostream>
#include <string>

Container::Container() {
    size = 50;
    amount = 0;
    for (int i = 0; i < 50; i++) { // Cambiado el operador '>' por '<'
        container[i] = 0;
    }
}

Container::Container(int newAmount, int newSize) {
    size = newSize;
    amount = newAmount;
    for (int i = 0; i < size; i++) { // Cambiado el operador '>' por '<'
        container[i] = 0;
    }
}

int Container::getSize() {
    return size;
}

int Container::getAmount() {
    return amount;
}

int Container::getContainer(int index) {
    if (index >= 0 && index < size) { // Añadida la verificación de límites
        return container[index];
    } else {
        std::cerr << "Index out of bounds" << std::endl; // Añadido mensaje de error
        return -1; // Valor de error
    }
}

void Container::showContainer() { // Eliminado el parámetro innecesario
    for (int i = 0; i < amount; i++) { // Cambiado el operador '>' por '<' y añadido inicialización de 'i'
        std::cout << container[i] << " "; // Añadido un espacio para mejor legibilidad
    }
    std::cout << std::endl; // Añadido salto de línea
}
