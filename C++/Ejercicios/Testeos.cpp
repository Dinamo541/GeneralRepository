#include <iostream>
#include <string>

int main() {
    std::string oracion;
    std::cout << "Escriba una oracion: ";
    std::getline(std::cin, oracion);
    int size = oracion.size();
    for (int i = size - 1; i >= 0; i--) {
        if (oracion[i] == ' ') {
            oracion[i] = 0;
        }
    }
    std::cout << oracion;
    return 0;
}