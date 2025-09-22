#include "FeaturesContainer.cpp"
#include <iostream>
#include <string>

int main() {
    int size = 0;
    int amount = 0;
    std::cout << "Ingrese la cantidad de espacios que utilizara en el vector (max:50): " << std::endl;
    std::cin >> size;

    Container container(amount, size);

    for (int i = 0; i < size; i++) {
        std::cout << container.getContainer(i);
    }

    return 0;
}