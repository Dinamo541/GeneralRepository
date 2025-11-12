#include<iostream>
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

    ~Nodo() {
        delete next;
        delete data;
    }

    void setNext(Nodo<T>* newNext) { next = newNext; }
    void setData(T* newData) { data = newData; }

    Nodo<T>* getNext() { return next; }
    T* getData() { return data; }
};

class File {
private:
    std::string id;
    std::string name;
    std::string score;

    File(const File&) = delete;
    File& operator=(const File&) = delete;
public:
    File() : id(0), name(""), score("") {}
    File(std::string newId, std::string newName, std::string newScore)
        : id(newId), name(newName), score(newScore) {
    }
    ~File() {}

    void setId(std::string newId) { id = newId; }
    void setName(std::string newName) { name = newName; }
    void setScore(std::string newScore) { score = newScore; }

    std::string getId() { return id; }
    std::string getName() { return name; }
    std::string getScore() { return score; }
    int getScoreToCompare() { return std::stoi(score); }

    void print() {
        std::cout << "Id: " <<  id << std::endl;
        std::cout << "name: " <<  name << std::endl;
        std::cout << "score: " <<  score << std::endl;
        std::cout << "----------------------" << std::endl;
    }
};

class Table {
private:
    Nodo<File>* first = nullptr;
    Nodo<File>* second = nullptr;
    Nodo<File>* third = nullptr;
    std::ifstream inFile;
    std::ofstream outFile;
    std::string FNFirst;
    std::string FNSecond;
    std::string FNThird;

public:
    Table() : FNFirst(""), FNSecond(""), FNThird("") {}
    Table(std::string newFNfirst, std::string newFNSecond, std::string newFNThird)
    : FNFirst(newFNfirst), FNSecond(newFNSecond), FNThird(newFNThird) {
        inFileFirst();
        inFileSecond();
        inFileThird();
    }
    ~Table() {
        saveFirst();
        saveSecond();
        saveThird();
        deleteListRecursive(first);
        deleteListRecursive(second);
        deleteListRecursive(third);
    }

    void set() {}

    void inFileFirst() {
        std::string line;
        try {
            inFile = std::ifstream(FNFirst);
            if (inFile.is_open()) {
                size_t id = 1;
                while (std::getline(inFile, line)) {
                    if (line.empty()) { ++id; continue; }

                    size_t dot = line.find('.');
                    if (dot == std::string::npos) { ++id; continue; }

                    std::string idStr = line.substr(0, dot);

                    size_t start = dot + 1;
                    size_t comma1 = line.find(',', start);
                    if (comma1 == std::string::npos) { ++id; continue; }
                    std::string name = line.substr(start, comma1 - start);

                    size_t comma2 = line.find(',', comma1 + 1);
                    std::string score;
                    if (comma2 == std::string::npos) score = line.substr(comma1 + 1);
                    else score = line.substr(comma1 + 1, comma2 - (comma1 + 1));

                    addFirstN(new Nodo<File>(new File(idStr, name, score)));
                    ++id;
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
    void addFirstN(Nodo<File>* newNodo) {
        if (first == nullptr) {
            first = newNodo;
        } else {
            Nodo<File>* current = first;
            while (current->getNext() != nullptr) current = current->getNext();
            
            current->setNext(newNodo);
        } 
    }
    void inFileSecond() {
        std::string line;
        try {
            inFile = std::ifstream(FNSecond);
            if (inFile.is_open()) {
                size_t id = 1;
                while (std::getline(inFile, line)) {
                    if (line.empty()) { ++id; continue; }

                    size_t dot = line.find('.');
                    if (dot == std::string::npos) { ++id; continue; }

                    std::string idStr = line.substr(0, dot);

                    size_t start = dot + 1;
                    size_t comma1 = line.find(',', start);
                    if (comma1 == std::string::npos) { ++id; continue; }
                    std::string name = line.substr(start, comma1 - start);

                    size_t comma2 = line.find(',', comma1 + 1);
                    std::string score;
                    if (comma2 == std::string::npos) score = line.substr(comma1 + 1);
                    else score = line.substr(comma1 + 1, comma2 - (comma1 + 1));

                    addSecondN(new Nodo<File>(new File(idStr, name, score)));
                    ++id;
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
    void addSecondN(Nodo<File>* newNodo) {
        if (second == nullptr) {
            second = newNodo;
        } else {
            Nodo<File>* current = second;
            while (current->getNext() != nullptr) current = current->getNext();
            current->setNext(newNodo);
        } 
    }
    void inFileThird() {
        std::string line;
        try {
            inFile = std::ifstream(FNThird);
            if (inFile.is_open()) {
                size_t id = 1;
                while (std::getline(inFile, line)) {
                    if (line.empty()) { ++id; continue; }

                    size_t dot = line.find('.');
                    if (dot == std::string::npos) { ++id; continue; }

                    std::string idStr = line.substr(0, dot);

                    size_t start = dot + 1;
                    size_t comma1 = line.find(',', start);
                    if (comma1 == std::string::npos) { ++id; continue; }
                    std::string name = line.substr(start, comma1 - start);

                    size_t comma2 = line.find(',', comma1 + 1);
                    std::string score;
                    if (comma2 == std::string::npos) score = line.substr(comma1 + 1);
                    else score = line.substr(comma1 + 1, comma2 - (comma1 + 1));

                    addThirdN(new Nodo<File>(new File(idStr, name, score)));
                    ++id;
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
    void addThirdN(Nodo<File>* newNodo) {
        if (third == nullptr) {
            third = newNodo;
        } else {
            Nodo<File>* current = third;
            while (current->getNext() != nullptr) current = current->getNext();
            current->setNext(newNodo);
        } 
    }

    void printFirst() {
        std::cout << "\tLista 1" << std::endl;
        std::cout << "----------------------" << std::endl;
        printRecursive(first);
    }
    void printSecond() {
        std::cout << "\tLista 2" << std::endl;
        std::cout << "----------------------" << std::endl;
        printRecursive(second);
    }
    void printThird() {
        std::cout << "\tLista 3" << std::endl;
        std::cout << "----------------------" << std::endl;
        printRecursive(third);
    }
    void printRecursive(Nodo<File>* current) {
        if (current != nullptr) {
            current->getData()->print();
            printRecursive(current->getNext());
        }
    }

    void addToFirstOrdererByScore(File* newFile) {
        if (first->getData()->getScoreToCompare() < newFile->getScoreToCompare()) {
            Nodo<File>* newNodo = new Nodo<File>(first, newFile);
            first = newNodo;
        } else {
            Nodo<File>* current = first;
            while (current->getNext() != nullptr) {
                if (current->getNext()->getData()->getScoreToCompare() < newFile->getScoreToCompare()) {
                    Nodo<File>* newNodo = new Nodo<File>(current->getNext(), newFile);
                    current->setNext(newNodo);
                    renumber(first);
                    return;
                }
                current = current->getNext();
            }
            Nodo<File>* newNodo = new Nodo<File>(newFile);
            current->setNext(newNodo);
        }
        renumber(first);
    }
    void addToSecondOrdererByScore(File* newFile) {
        if (second->getData()->getScoreToCompare() < newFile->getScoreToCompare()) {
            Nodo<File>* newNodo = new Nodo<File>(second, newFile);
            second = newNodo;
        } else {
            Nodo<File>* current = second;
            while (current->getNext() != nullptr) {
                if (current->getNext()->getData()->getScoreToCompare() < newFile->getScoreToCompare()) {
                    Nodo<File>* newNodo = new Nodo<File>(current->getNext(), newFile);
                    current->setNext(newNodo);
                    renumber(second);
                    return;
                }
                current = current->getNext();
            }
            Nodo<File>* newNodo = new Nodo<File>(newFile);
            current->setNext(newNodo);
        }
        renumber(second);
    }
    void addToThirdOrdererByScore(File* newFile) {
        if (third->getData()->getScoreToCompare() < newFile->getScoreToCompare()) {
            Nodo<File>* newNodo = new Nodo<File>(third, newFile);
            third = newNodo;
        } else {
            Nodo<File>* current = third;
            while (current->getNext() != nullptr) {
                if (current->getNext()->getData()->getScoreToCompare() < newFile->getScoreToCompare()) {
                    Nodo<File>* newNodo = new Nodo<File>(current->getNext(), newFile);
                    current->setNext(newNodo);
                    renumber(third);
                    return;
                }
                current = current->getNext();
            }
            Nodo<File>* newNodo = new Nodo<File>(newFile);
            current->setNext(newNodo);
        }
        renumber(third);
    }
    void renumber(Nodo<File>* current) {
        for (int i = 1; i < 11 && current != nullptr; i++) {
            current->getData()->setId(std::to_string(i));
            current = current->getNext();
        }
    }

    void saveFirst() {
        std::string line;
        try {
            outFile = std::ofstream(FNFirst);
            if (outFile.is_open()) {
                Nodo<File>* current = first;
                for (int i = 0 ; i < 10 && current != nullptr; i++) {
                    File* file = current->getData();
                    outFile << file->getId() << "." << file->getName() << "," << file->getScore();
                    if (i != 9 && current->getNext() != nullptr) {
                        outFile << std::endl;
                    }
                    current = current->getNext();
                }
                outFile.close();
            } else {
                throw(-1);
            }
        } catch (int error) {
            if (error == -1) {
                std::cerr << "No se pudo abrir el archivo para leer.\n";
            }
        }
    }
    void saveSecond() {
        std::string line;
        try {
            outFile = std::ofstream(FNSecond);
            if (outFile.is_open()) {
                Nodo<File>* current = second;
                for (int i = 0 ; i < 10 && current != nullptr; i++) {
                    File* file = current->getData();
                    outFile << file->getId() << "." << file->getName() << "," << file->getScore();
                    if (i != 9 && current->getNext() != nullptr) {
                        outFile << std::endl;
                    }
                    current = current->getNext();
                }
                outFile.close();
            } else {
                throw(-1);
            }
        } catch (int error) {
            if (error == -1) {
                std::cerr << "No se pudo abrir el archivo para leer.\n";
            }
        }
    }
    void saveThird() {
        std::string line;
        try {
            outFile = std::ofstream(FNThird);
            if (outFile.is_open()) {
                Nodo<File>* current = third;
                for (int i = 0 ; i < 10 && current != nullptr; i++) {
                    File* file = current->getData();
                    outFile << file->getId() << "." << file->getName() << "," << file->getScore();
                    if (i != 9 && current->getNext() != nullptr) {
                        outFile << std::endl;
                    }
                    current = current->getNext();
                }
                outFile.close();
            } else {
                throw(-1);
            }
        } catch (int error) {
            if (error == -1) {
                std::cerr << "No se pudo abrir el archivo para leer.\n";
            }
        }
    }
    File* getFileByIndexFi(std::string id) {
        Nodo<File>* current = first;
        while (current != nullptr && current->getData()->getId() != id) {
            current = current->getNext();
        }
        if (current == nullptr) {
            return nullptr;
        }
        return current->getData();
    }

    void deleteListRecursive(Nodo<File>* current) {
        if (current != nullptr) {
            deleteListRecursive(current->getNext());
            delete current;
        }
    }
};

int main() {
    Table tablaTest("first.csv", "second.csv", "third.csv");
    tablaTest.printFirst();

    // tablaTest.addToFirstOrdererByScore(new File("0", "Dominique", "1950"));
    return 0;
}