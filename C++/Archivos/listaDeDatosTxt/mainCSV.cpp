#include <iostream>
#include <fstream>
#include <string>

class File {
protected:
    std::ifstream inFile;
    std::ofstream outFile;
    std::string fileName;
    std::string name;
    std::string lastName;
    std::string age;
    int id;

public:
    File() {
        fileName = "archivo.csv";
        id = 0;
        name = "";
        lastName = "";
        age = "";
    }
    File(int newId) : id(newId) {
        fileName = "archivo.csv";
        setData();
    }
    ~File() {}

    void setName(std::string newName) { name = newName; }
    void setLastName(std::string newLastName) { lastName = newLastName; }
    void setAge(std::string newAge) { age = newAge; }

    std::string getName() { return name; }
    std::string getLastName() { return lastName; }
    std::string getAge() { return age; }

    void setData() {
        std::string line;
        try {
            inFile = std::ifstream(fileName);
            if (inFile.is_open()) {
                std::string idStr = std::to_string(id);
                while (std::getline(inFile, line)) {
                    if (line.find(idStr + ".") != std::string::npos) {
                        size_t dot = line.find('.');

                        if (dot == std::string::npos) continue;

                        size_t start = dot + 1;
                        size_t comma1 = line.find(',', start);

                        if (comma1 == std::string::npos) continue;

                        name = line.substr(start, comma1 - start);

                        size_t comma2 = line.find(',', comma1 + 1);
                        
                        if (comma2 == std::string::npos) continue;
                        lastName = line.substr(comma1 + 1, comma2 - (comma1 + 1));

                        age = line.substr(comma2 + 1);
                    }
                }
                inFile.close();
            } else {
                throw(-1);
            }
        } catch (int error) {
            if (error == -1) {
                std::cerr << "No se pudo abrir el archivo para leer.\n";
            }
        }
    }
    void changeData(int objective, std::string data) {
        std::string line;
        objective = 0;
        data = "";
        try {
            outFile = std::ofstream(fileName);
            if (inFile.is_open() && objective == 0) {
                
                inFile.close();
            } else {
                throw(-1);
            }
        } catch (int error) {
            if (error == -1) {
                std::cerr << "No se pudo abrir el archivo para leer.\n";
            }
        }
    }
    void printData() {
        std::cout << "Persona numero: " << id << std::endl;
        std::cout << "Nombre: " << name << std::endl;
        std::cout << "Apellido: " << lastName<< std::endl;
        std::cout << "Edad: " << age << std::endl;
    }
};

int main() {
    File archivo(1);
    archivo.printData();
    return 0;
}