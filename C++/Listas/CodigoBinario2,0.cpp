#include <iostream>
#include <fstream>
#include <string>

template <class T>
class Nodo {
private:
    Nodo<T>* next;
    T* data;

public:
    Nodo() : next(nullptr), data(nullptr) {}
    Nodo(Nodo<T>* newNext) : next(newNext), data(nullptr) {}
    Nodo(T* newData) : next(nullptr), data(newData) {}
    Nodo(Nodo<T>* newNext, T* newData) : next(newNext), data(newData) {}
    ~Nodo() {}

    void setNext(Nodo<T>* newNext) { next = newNext; }
    void setData(T* newData) { data = newData; }
    Nodo<T>* getNext() { return next; }
    T* getData() { return data; }
};

class Characters {
private:
    int binary[8];
    char character;
    int ASCII;

public:
    Characters() : character(0), ASCII(0) {
        for (int i = 0; i < 8; i++) {
            binary[i] = 0;
        }
    }
    Characters(char newCharacter) : character(newCharacter), ASCII(0) {
        for (int i = 0; i < 8; i++) {
            binary[i] = 0;
        }
        fromCharToBin();
    }
    Characters(std::string numBinary) : character(0), ASCII(0) {
        int size = numBinary.size();
        for (int i = 0; i < 8; i++) {
            if (i < size) {
                binary[i] = numBinary[i] - '0';
            } else {
                binary[i] = 0;
            }
        }
        fromBinToChar();
    }
    ~Characters() {}

    std::string getBinary() {
        std::string numBinary = "";
        for (int i = 0; i < 8; i++) {
            numBinary += std::to_string(binary[i]); 
        }
        return numBinary;
    }
    char getCharacter() {
        return character;
    }
    int getASCII() {
        return ASCII;
    }
    void setBinary(int numBinary) {
        std::string numS = std::to_string(numBinary);
        int size = numS.size();
        for (int i = 0; i < 8; i++) {
            if (i < size) {
                binary[i] = numS[i] - '0';
            } else {
                binary[i] = 0;
            }
        }
    }
    void setCharacter(char newCharacter) {
        character = newCharacter;
    }
    void setASCII(int newASCCI) {
        ASCII = newASCCI;
    }

    int pow(int base, int exponente) {
        int resultado = 1;
        for(int i = 0; i < exponente; i++) {
            resultado *= base;
        }
        return resultado;
    }
    void fromBinToChar() {
        ASCII = 0;
        for (int i = 0; i < 8; i++) {
            ASCII += binary[i] * pow(2, 7 - i);
        }
        character = ASCII;
    }
    void fromCharToBin() {
        ASCII = character;
        std::string bin = decimalToBinary(ASCII);
        int size = bin.length();
        for (int i = 0; i < 8; i++) {
            if (i < (8 - size)) {
                binary[i] = 0;
            } else {
                binary[i] = bin[i - (8 - size)] - '0';
            }
        }
        binary[7] = (ASCII % 2);
        ASCII /= 2;
    }
    std::string decimalToBinary(int decimal) {
        std::string binario;
        while (decimal > 0) {
            binario = std::to_string(decimal % 2) + binario;
            decimal /= 2;
        }
        return binario;
    }
    void printChar() {
        std::cout << character;
    }
    void printBin() {
        for (int i = 0; i < 8; i++) {
            std::cout << binary[i];
        }
    }
    void printASCCI() {
        std::cout << ASCII;
    }
    void printAll() {
        std::cout << "Character: " << character << std::endl;
        std::cout << "Binary: ";
        for (int i = 0; i < 8; i++) {
            std::cout << binary[i];
        }
        std::cout << "\nASCII: " << ASCII << std::endl;
    }
};

class NodoCh {
private:
    Characters* character;
    NodoCh* next;

public:
    NodoCh() {
        character = nullptr;
        next = nullptr;
    }
    NodoCh(Characters* newCharacter) : character(newCharacter) {
        next = nullptr;
    }
    ~NodoCh() {
        character = nullptr;
        next = nullptr;
        delete next;
    }

    Characters* getData() {
        return character;
    }
    NodoCh* getNext() {
        return next;
    }
    void setData(Characters *newCharacter) {
        character = newCharacter;
    }
    void setNext(NodoCh *newNext) {
        next = newNext;
    }

    void addOneChar(char newCharacter) {
        character = new Characters(newCharacter);
    }
    void addOneBin(std::string binary) {
        character = new Characters(binary);
    }
    void printChar() {
        character->printChar();
    }
    void printBin() {
        character->printBin();
        std::cout << " ";
    }
    void printASCCI() {
        character->printASCCI();
    }
    void printAll() {
        character->printAll();
    }
};

class List {
private:
    NodoCh* first;
    std::string phrase;
    std::string binary;

public:
    List() {
        phrase = "";
        binary = "";
        first = nullptr;
    }
    ~List() {
        NodoCh* current = first; 
        NodoCh* next = first->getNext();
        while(next != nullptr) {
            next = current->getNext();
            delete current;
            current = next;
        }
        first = nullptr;
    }

    void setPhrase(std::string newPhrase) {
        phrase = newPhrase;
        setWithPhrase();
    }
    void setBinary(std::string newBinary) {
        binary = newBinary;
        setWithBin();
    }
    std::string getsPhrase() {
        return phrase;
    }
    std::string getsBinary() {
        return binary;
    }

    void setWithPhrase() {
        first = new NodoCh(new Characters(phrase[0]));
        NodoCh* current = first;
        int size = phrase.size();
        for (int i = 1; i < size; i++) {
            current->setNext(new NodoCh(new Characters(phrase[i])));
            current = current->getNext();
        }
    }
    void printBin() {
        NodoCh* current = first;
        while (current != nullptr) {
            current->printBin();
            current = current->getNext();
        }
    }
    void setWithBin() {
        int size = binary.size();
        std::string numBinary = "";
        for (int i = 0; i < size; i++) {
            if (binary[i] != ' ') {
                numBinary += binary[i];
            }
            if (numBinary.size() == 8) {
                NodoCh* newNodo = new NodoCh(new Characters(numBinary));
                if (first == nullptr) {
                    first = newNodo;
                } else {
                    NodoCh* current = first;
                    while (current->getNext() != nullptr) {
                        current = current->getNext();
                    }
                    current->setNext(newNodo);
                }
                numBinary = "";
            }
        }
    }
    void printChar() {
        NodoCh* current = first;
        while (current != nullptr) {
            current->printChar();
            current = current->getNext();
        }
    }
};

class ListHisto {
private:
    Nodo<List>* first;
    std::ifstream inFile;
    std::ofstream outFile;

public:
    ListHisto() : first(nullptr) {
        load();
    }
    ListHisto(Nodo<List>* newFirst) : first(newFirst) {
        load();
    }
    ~ListHisto() {
        save();
        Nodo<List>* current = first; 
        Nodo<List>* next = first->getNext();
        while(next != nullptr) {
            next = current->getNext();
            delete current;
            current = next;
        }
        first = nullptr;
    }

    void load() {
        std::string line;
        if (first == nullptr) {
            first = new Nodo<List>();
        }
        Nodo<List>* current = first;
        try {
            inFile = std::ifstream("historial.csv");
            if (inFile.is_open()) {
                while (std::getline(inFile, line)) {
                    if (line.find('.') != std::string::npos) {
                        size_t dot = line.find('.');
                        size_t start = dot + 1;
                        size_t end = line.length();
                        std::string bin = line.substr(start, end - start);
                        
                        List* newList = new List();
                        newList->setBinary(bin);
                        current->setData(newList);
                        current = current->getNext();
                        current->setNext(new Nodo<List>());
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
    void add(List* newList) {
        if (first == nullptr) {
            first = new Nodo<List>(newList);
        } else {
            Nodo<List>* current = first;
            while (current->getNext() == nullptr) {
                current = current->getNext();
            }

            current->setNext(new Nodo<List>(newList));
        }
    }
    void print() {
        if (first == nullptr) {
            std::cout << "Todavia no hay historial";
        }
        recursivePrint(first, 1);
    }
    void recursivePrint(Nodo<List>* current, int id) {
        if (current != nullptr) {
            std::cout << "Numero " << id << std::endl << std::endl;
            std::cout << "Binario: ";
            current->getData()->printBin();
            std::cout << "\nTexto: ";
            current->getData()->printChar();
            if (current->getNext() != nullptr) {
                std::cout << "\n -----------------------------------------------\n\n";
            }
            recursivePrint(current->getNext(), id++);
        }
    }
    void save() {
        int id = 1;
        Nodo<List>* current = first;
        try {
            outFile = std::ofstream("historial.csv");
            if (inFile.is_open()) {
                while (current != nullptr) {
                    outFile << id << ".";
                    outFile << current->getData()->getsBinary();

                    current = current->getNext();
                    if (current != nullptr) {
                        outFile << std::endl;
                        id++;
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
};

int main() {
    std::string phrase = " ", options = " ";
    int size = 0;
    ListHisto record;
    while (true) {
        std::cout << "Eliga el formato: " << std::endl;
        std::cout << "0. Cerrar " << std::endl;
        std::cout << "1. Texto -> Binario " << std::endl;
        std::cout << "2. Binario -> Texto " << std::endl;
        std::cout << "3. Historial " << std::endl;
        std::getline(std::cin, options);
        system("cls");
        if (options == "1") {
            std::cout << "(Tex -> Bin) Escriba la frase que desea pasar a binario: " << std::endl;
            std::getline(std::cin, phrase);
            size = phrase.size();
            for (int i = size - 1; i >= 0 && phrase[i] == ' '; i--) {
                phrase[i] = 0;
            }
            List calculator;
            calculator.setPhrase(phrase);
            std::cout << std::endl << "Binario: ";
            calculator.printBin();
            std::cout << std::endl << std::endl;
            std::cout << "Ingrese cualquier tecla para continuar" << std::endl;
            record.add(&calculator);
            std::getline(std::cin, phrase);
            phrase = "";
        } else if (options == "2") {
            std::cout << "(Bin -> Text) Escriba el binario que desea decifrar: " << std::endl;
            std::getline(std::cin, phrase);
            size = phrase.size();
            for (int i = size - 1; i >= 0 && phrase[i] == ' '; i--) {
                phrase[i] = 0;
            }
            List calculator;
            calculator.setBinary(phrase);
            std::cout << std::endl << "Texto: ";
            calculator.printChar();
            std::cout << std::endl << std::endl;
            std::cout << "Ingrese cualquier tecla para continuar" << std::endl;
            record.add(&calculator);
            std::getline(std::cin, phrase);
            phrase = "";
        } else if (options == "3") {
            record.print();
            std::cout << std::endl << "Ingrese cualquier tecla para continuar" << std::endl;
            std::getline(std::cin, options);
            phrase = "";
        } else if (options == "0") {
            std::cout << "Gracias por usar el programa." << std::endl;
            return 0;
        } else {
            std::cout << "La opcion digitada no es correcta." << std::endl;
            std::cout << "Ingrese cualquier tecla para continuar" << std::endl;
            std::getline(std::cin, options);
            phrase = "";
        }
        system("cls");
    }
}