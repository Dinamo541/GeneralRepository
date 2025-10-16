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
        fileName = "archivo.txt";
    }
    ~File() {}

    void openOut() {
        try {
            outFile = std::ofstream(fileName);
            if (outFile.is_open()) {
                outFile << "Hola, mundo!\n";
                outFile << "Este es un archivo de texto\n";
                outFile.close();
            }
            else {
                throw(-1);
            }
        }
        catch (int error) {
            if (error == -1) {
                std::cerr << "No se pudo abrir el arcivho para leer.\n";
            }
        }
    }
    void openIn() {
        std::string line = "Hola";
        try {
            inFile = std::ifstream(fileName);
            if (inFile.is_open()) {
                while (std::getline(inFile, line)) {
                    std::cout << line << std::endl; // Imprimir la linea
                }
                inFile.close(); // Cerrar el archivo
            }
            else {
                throw(-1);
            }
        }
        catch (int error) {
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