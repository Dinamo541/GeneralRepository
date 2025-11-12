#include <iostream>

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

class List {
private:
    Nodo<int>* first;

public:
    List() {}
    ~List() {
        deleteList(first);
    }
    void deleteList(Nodo<int>* current) {
        if (current != nullptr) {
            deleteList(current->getNext());
        }
        delete current;
    }


};

int main() {
    
    return 0;
}