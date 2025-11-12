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
    Nodo<T>* first;

public:
    List() {}
    List(Nodo<T>* newFirst) {
        first = newFirst;
    }

};

int main() {
    return 0;
}