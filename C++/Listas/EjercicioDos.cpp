#include <iostream>

class Nodo {
private:
    int dato;
    Nodo* next;

public:
    Nodo() {
        dato = 0;
        next = nullptr;
    }
    Nodo(int newDato) : dato(newDato) {
        next = nullptr;
    }
    ~Nodo() {
        delete next;
        next = nullptr;
    }

    void setData(int newDato) {
        dato = newDato;
    }
    void setNext(Nodo *newNext) {
        next = newNext;
    }

    int getData() {
        return dato;
    }
    Nodo* getNext() {
        return next;
    }

    void print() {
        printf("Id: %d\n", dato);
    }

};

class List {
private:
    Nodo* first;
    
public:
    List() {
        first = nullptr;
    }
    List(int newDato) {
        first = new Nodo(newDato);
    }
    ~List() {
        delete first;
        first = nullptr;
    }

    void insertAtTheBeginning(int newDato) {
        Nodo* newFirst = new Nodo(newDato);
        newFirst->setNext(first);
        first = newFirst;
    }
    void showList() {
        showListRecursive(first);
    }
    void showListRecursive(Nodo* current) {
        if (current != nullptr) {
            std::cout << current->getData() << std::endl;
        } else {
            return;
        }
        showListRecursive(current->getNext());
    }
    void deleteLast() {
        if (first->getNext() == nullptr) {
            first = nullptr;
        } else {
            deleteLastRecursive(first);
        }
    }
    void deleteLastRecursive(Nodo* current) {
        if (current->getNext()->getNext() == nullptr) {
            current->setNext(nullptr);
        } else {
            deleteLastRecursive(current->getNext());
        }
    }
    void insertIntoPosition(Nodo* newNodo, int index) {
        if (index == 1) {
            newNodo->setNext(first);
            first = newNodo;
        } else {
            Nodo* current = first;
            for (int i = 0; i < index - 1; i++) {
                if (current->getNext() == nullptr) {
                    current->setNext(newNodo);
                } else {
                    current = current->getNext();
                }
            }
            newNodo->setNext(current->getNext());
            current->setNext(newNodo);
        }
    }
    void add(int newDato) {
        Nodo* current = first;
        while(current != nullptr) {
            current = current->getNext();
        }
        current->setNext(new Nodo(newDato));
    }
};

int main() {
    
    return 0;
}