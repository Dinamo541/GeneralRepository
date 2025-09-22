#include <iostream>
#include <string>

struct People {
    std::string name = "";
    int age = 0;
    int weight = 0;
};

void fillData(People* list, int quantity) {
    for (int i = 0; i < quantity; i++) {
        std::cout << "\nPersona " << i + 1 << ": \n";
        std::cout << "Nombre: ";
        std::cin >> list[i].name;
        std::cout << "Edad: ";
        std::cin >> list[i].age;
        std::cout << "Peso (Kg): ";
        std::cin >> list[i].weight;
    }
}

void printData(People* list, int quantity) {
    std::cout << "Lista de personas\n\n";
    for (int i = 0; i < quantity; i++) {
        std::cout << "\nPersona " << i + 1 << ": \n";
        std::cout << "Nombre: " << list[i].name;
        std::cout << "\nEdad: " << list[i].age;
        std::cout << "\nPeso (Kg): "<< list[i].weight;
    }
}


int main() {
    int quantity = 0;

    std::cout << "Cuantas personas quieres registrar: " << std::endl;
    std::cin >> quantity;

    People* list = new People[quantity];

    fillData(list, quantity);

    printData(list, quantity);

    delete[] list;
    list = nullptr;

    return 0;
}
