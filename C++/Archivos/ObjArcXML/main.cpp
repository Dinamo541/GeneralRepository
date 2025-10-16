#include <iostream>
#include <fstream>
#include <string>

class File {
protected:
    std::ifstream inFile;
    std::ofstream outFile;
    std::string fileName;

public:
    File() {
        fileName = "archivo.xml";
    }
    ~File() {}

    void openOut() {
        try {
            outFile = std::ofstream(fileName);
            if (outFile.is_open()) {
                outFile << "Hola, mundo!\n";
                outFile << "Este es un archivo de texto\n";
                outFile.close();
            } else {
                throw(-1);
            }
        } catch (int error) {
            if (error == -1) {
                std::cerr << "No se pudo abrir el arcivho para leer.\n";
            }
        }
    }
    void openIn() {
        std::string line, name, age, email;
        try {
            inFile = std::ifstream(fileName);
            if (inFile.is_open()) {
                while (getline(inFile, line)) {
                    if (line.find("<nombre>") != std::string::npos) {
                        size_t start = line.find("<nombre>") + 8;
                        size_t end = line.find("</nombre>");
                        name = line.substr(start, end - start);
                    } else if (line.find("<edad>") != std::string::npos) {
                        size_t start = line.find("<edad>") + 6;
                        size_t end = line.find("</edad>");
                        age = line.substr(start, end - start);
                    } else if (line.find("<correo>") != std::string::npos) {
                        size_t start = line.find("<correo>") + 8;
                        size_t end = line.find("</correo>");
                        email = line.substr(start, end - start);
                    }
                    if (!name.empty() && !age.empty() && !email.empty()) {
                        std::cout << "Nombre: " << name << std::endl;
                        std::cout << "Edad: " << age << std::endl;
                        std::cout << "Correo: " << email << std::endl;
                        std::cout << "-------------------------" << std::endl;
                        name.clear();
                        age.clear();
                        email.clear();
                    }
                }
                inFile.close();
            } else {
                throw(-1);
            }
        } catch (int error) {
            if (error == -1) {
                std::cerr << "No se pudo abrir el arcivho para leer.\n";
            }
        }
    }
};

int main() {
    File archivo;
    archivo.openIn();
    return 0;
}