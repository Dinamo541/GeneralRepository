#include "Functions.cpp"
#include <iostream>
#include <string>

int main() {
    float height = 0.0f;
    float weight = 0.0f;

    std::cout << "Hola, ingrese su altura (en metros): ";
    std::cin >> height;

    std::cout << "Ahora ingrese su peso (en kilogramos): ";
    std::cin >> weight;

    BodyComposition personOne(height, weight);

    if (personOne.getHeight() == 0.0f || personOne.getWeight() == 0.0f) {
        std::cout << "Error: Altura o peso inválidos." << std::endl;
        return 1;
    }

    std::cout << "Su índice de masa corporal (BMI) es: " << personOne.getBMI() << std::endl;
    std::cout << "Usted posee: " << personOne.getObesityType() << std::endl;

    return 0;
}