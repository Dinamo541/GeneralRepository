#include <iostream>
#include <string>

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

class Nodo {
private:
    Characters* character;
    Nodo* next;

public:
    Nodo() {
        character = nullptr;
        next = nullptr;
    }
    Nodo(Characters* newCharacter) : character(newCharacter) {
        next = nullptr;
    }
    ~Nodo() {
        character = nullptr;
        next = nullptr;
        delete next;
    }

    Characters* getData() {
        return character;
    }
    Nodo* getNext() {
        return next;
    }
    void setData(Characters *newCharacter) {
        character = newCharacter;
    }
    void setNext(Nodo *newNext) {
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
    Nodo* first;
    std::string phrase;
    std::string binary;

public:
    List() {
        phrase = "";
        binary = "";
        first = nullptr;
    }
    ~List() {
        Nodo* current = first; 
        Nodo* next = first->getNext();
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
        first = new Nodo(new Characters(phrase[0]));
        Nodo* current = first;
        int size = phrase.size();
        for (int i = 1; i < size; i++) {
            current->setNext(new Nodo(new Characters(phrase[i])));
            current = current->getNext();
        }
    }
    void printBin() {
        Nodo* current = first;
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
                Nodo* newNodo = new Nodo(new Characters(numBinary));
                if (first == nullptr) {
                    first = newNodo;
                } else {
                    Nodo* current = first;
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
        Nodo* current = first;
        while (current != nullptr) {
            current->printChar();
            current = current->getNext();
        }
    }
};

int main() {
    std::string phrase = " ", options = " ";
    int size = 0;
    while (options != "0") {
        std::cout << "Eliga el formato: " << std::endl;
        std::cout << "0. Cerrar " << std::endl;
        std::cout << "1. Texto -> Binario " << std::endl;
        std::cout << "2. Binario -> Texto " << std::endl;
        std::getline(std::cin, options);
        if (options == "1") {
            system("cls");
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
            std::getline(std::cin, phrase);
        } else if (options == "2") {
            system("cls");
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
            std::getline(std::cin, phrase);
        } else if (options == "0") {
            system("cls");
            std::cout << "Gracias por usar el programa." << std::endl;
            return 0;
        } else {
            system("cls");
            std::cout << "La opcion digitada no es correcta." << std::endl;
            std::cout << "Ingrese cualquier tecla para continuar" << std::endl;
            std::getline(std::cin, options);
        }
        system("cls");
    }
    return 0;
}