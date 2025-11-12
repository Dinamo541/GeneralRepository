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
    void setData(T newData) { data = newData; }
    Nodo<T>* getNext() { return next; }
    T getData() { return data; }
};

template <class T>
class List {
private:
    Nodo<T>* first;
    int count;

public:
    List() {
        first = nullptr;
        count = 0;
    }
    List(Nodo<T>* newFirst) {
        first = newFirst;
        count = 1;
    }
    ~List() {}

    void addWhitData(T data) {
        Nodo<T>* newNodo = new Nodo<T>(data);
        if (first == nullptr) {
            first = newNodo;
        } else {
            Nodo<T>* current = first;
            while (current->getNext() != nullptr) {
                current = current->getNext();
            }
            current->setNext(newNodo);
        }
    }
    void countHowMany() {
        Nodo* current = first;
        count = 0;
        while (current != nullptr) {
            current = current->getNext();
            count++;
        }
    }
    int getHowMany() {
        countHowMany();
        return count;
    }
    T getDataByIndex(int index) {
        Nodo* current = first;
        for (int i = 1; i < index; i++) {
            if (current != nullptr) {
                current = current->getNext();
            }
        }
        return current->getData();
    }
};

List<std::string> load() {
    std::fstream file("table.txt");
    std::string line;
    List<std::string> list;

    while(std::getline(file, line)) {
        list.addWhitData(line);
    }

    file.close();

    return list;
}

void countLetres(List<std::string> list) {
    std::string line;
    int lines = list.getHowMany();
    int count = 0;

    for (int i = 0; i < lines; i++) {
        line = list.getDataByIndex(i);
        count += line.length();
    }

    std::cout << "La cantidad de letras es: " << count << "\n";
}

void save(List<std::string> list) {
    std::ofstream outFile("table.txt");
    std::string line;

}

int main() { // "table.txt"

    
    return 0;
}