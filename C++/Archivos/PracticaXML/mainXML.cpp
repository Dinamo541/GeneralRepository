#include <iostream>
#include <fstream>
#include <string>

int main() {
    std::ifstream inFile("archivo.xml", std::ios::app);
    if (!inFile.is_open()) {
        std::cout << "No se pudo abrir el archivo." << std::endl;
        return 1;
    }

    std::string line, nombre, edad, correo;
    while (getline(inFile, line)) {
        // Buscar etiquetas de apertura y cierre manualmente
        if (line.find("<nombre>") != std::string::npos) {
            size_t start = line.find("<nombre>") + 8;
            size_t end = line.find("</nombre>");
            nombre = line.substr(start, end - start);
        } else if (line.find("<edad>") != std::string::npos) {
            size_t start = line.find("<edad>") + 6;
            size_t end = line.find("</edad>");
            edad = line.substr(start, end - start);
        } else if (line.find("<correo>") != std::string::npos) {
            size_t start = line.find("<correo>") + 8;
            size_t end = line.find("</correo>");
            correo = line.substr(start, end - start);
        }
        if (!nombre.empty() && !edad.empty() && !correo.empty()) {
            std::cout << "Nombre: " << nombre << std::endl;
            std::cout << "Edad: " << edad << std::endl;
            std::cout << "Correo: " << correo << std::endl;
            std::cout << "-------------------------" << std::endl;
            nombre.clear();
            edad.clear();
            correo.clear();
        }
    }

    inFile.close();
    return 0;
}
