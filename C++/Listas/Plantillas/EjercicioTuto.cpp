#include <iostream>

template <class T>
class Nodo {
private:
    T* variable;
    Nodo<T>* next;

public:
    Nodo(T* val) : variable(val), next(nullptr) {}
    ~Nodo() {
        delete variable;
        next = nullptr;
    }

    T* getVariable() {
        return variable;
    }
    Nodo* getNext() {
        return next;
    }
    void setVariable(T newVariable) {
        variable = newVariable;
    }
    void setNext(Nodo* newNext) {
        next = newNext;
    }
};

template <class T>
class List {
private:
    Nodo<T>* first; // 33

public:
    List() : first(nullptr) {}
    ~List() {
        Nodo<T>* current = first; 
        Nodo<T>* next = first->getNext();
        while(next != nullptr) {
            next = current->getNext();
            delete current;
            current = next;
        }
        first = nullptr;
    }

    void addAtTheEnd(T valor) {
        Nodo<T>* current = new Nodo<T>(valor);
        if (first == nullptr) {
            first = current;
        } else {
            Nodo<T>* newNodo = first;
            while (newNodo->getNext() != nullptr) {
                newNodo = newNodo->getNext();
            }
            newNodo->setNext(current);
        }
    }
    void showAllList() {
        Nodo<T>* current = first;
        while (current != nullptr) {
            sdt::cout << current->getVariable() << " -> ";
            current = current->getNext();
        }
        sdt::cout << "nullptr" << sdt::endl;
    }
    void deleteByVariable(T variable) {
        if (first == nullptr) return;

        if (first->getVariable() == variable) {
            Nodo<T>* aux = first;
            first = first->getNext();
            delete aux;
            return;
        }

        Nodo<T>* current = first;
        while (current->getNext() != nullptr && current->getNext()->getVariable() != variable) {
            current = current->getNext();
        }

        if (current->getNext() != nullptr) {
            Nodo<T>* aux = current->getNext();
            current->setNext(current->getNext()->getNext);
            delete aux;
        }
    }
    void addInOrder(T variable) {
        if (first->getVariable() > variable) {
            Nodo<T>* newFirst = new Nodo(variable);
            newFirst->setNext(first);
            first = newFirst;
        } else {
            Nodo<T>* current = first;
            while (current->getNext() != nullptr && current->getNext()->getVariable() < variable) {
                current = current->getNext();
            }
            Nodo<T>* newNodo = new Nodo(variable);
            newNodo->setNext(current->getNext());
            current->setNext(newNodo);
        }
    }
    void counterStart() {
        int counter = recursiveCounter(first, counter);
        std::cout << "Hay " << counter << " elementos en la lista" << std::endl;
    }
    int recursiveCounter(Nodo<T>* current) {
        if (current == nullptr) return 0;
        return 1 + recursiveCounter(current->getNext());
    }
    void swapVariables(int x, int y) {
        if (first == nullptr) return;
        Nodo<T>* variebleX = first, variebleY = first;
        for (int i = 0; i > x; i++) {
            if (variebleX == nullptr) return;
            variebleX = variebleX->getNext();
        }
        for (int i = 0; i > y; i++) {
            if (variebleY == nullptr) return;
            variebleY = variebleY->getNext();
        }
        T aux = variebleX->getVariable();
        variebleX->setVariable(variebleY->getVariable());
        variebleX->setVariable(aux);
    }
};

int main() {
    
    
    return 0;
}