#include <iostream>
#include "nlohmann/json.hpp"
using json = nlohmann::json;

int main() {
    // Crear JSON
    json persona = {
        {"nombre", "Juan"},
        {"edad", 30},
        {"correo", "juan@example.com"}
    };

    std::cout << persona.dump(4) << std::endl;

    // Leer datos
    std::string nombre = persona["nombre"];
    int edad = persona["edad"];
    std::cout << nombre << " tiene " << edad << " años." << std::endl;
}