#include <iostream>

template <class T>
class Nodo {
private:
    Nodo<T>* next;
    Nodo<T>* previous;
    T* data;

public:

    Nodo() : next(nullptr), data(nullptr), previous(nullptr) {}
    Nodo(Nodo<T>* newNext) : next(newNext), data(nullptr), previous(nullptr) {}
    Nodo(Nodo<T>* newPrevious) : next(nullptr), data(nullptr), previous(newPrevious) {}
    Nodo(T* newData) : next(nullptr), data(newData), previous(nullptr) {}
    Nodo(Nodo<T>* newNext, Nodo<T>* newPrevious) : next(newNext), data(nullptr), previous(newPrevious) {}
    Nodo(Nodo<T>* newNext, T* newData) : next(newNext), data(newData), previous(nullptr) {}
    Nodo(Nodo<T>* newPrevious, T* newData) : next(nullptr), data(newData), previous(newPrevious) {}
    Nodo(Nodo<T>* newNext, T* newData) : next(newNext), data(newData), previous(nullptr) {}

    ~Nodo() {
        delete next;
        delete previous;
        delete data;
    }

    void setNext(Nodo<T>* newNext) { next = newNext; }
    void setPrevious(Nodo<T>* newPrevious) { previous = newPrevious; }
    void setData(T* newData) { data = newData; }

    Nodo<T>* getNext() { return next; }
    Nodo<T>* getPrevious() { return previous; }
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
            delete current;
        }
    }

    void add(int newData) {
        Nodo<int>* newNodo = new Nodo<int>();
        newNodo->setData(&newData);

        if (first == nullptr) {
            first = newNodo;
        } else {
            Nodo<int>* current = first;
            while (current->getNext() != nullptr) {
                current = current->getNext();
            }

            newNodo->setPrevious(current);
            current->setNext(newNodo);
        }
    }
    void addInOrder(int* data) {
        Nodo<int>* newNodo = new Nodo<int>();
        newNodo->setData(data);

        if (first->getData() == data) {
            newNodo->setPrevious(first);
            first->setNext(newNodo);
        } else {
            Nodo<int>* current = first;
            while (current->getNext()->getData() != data && current->getNext() == nullptr) {
                current = current->getNext();
            }

            newNodo->setPrevious(current);
            current->setNext(newNodo);
        }
    }
    void deleteLast() {
        if (first == nullptr) {
            return;
        } else if (first->getNext() == nullptr) {
            first = nullptr;
        } else {
            Nodo<int>* current = first;
            while (current->getNext()->getNext() != nullptr) {
                current = current->getNext();
            }
            current->getNext()->setPrevious(nullptr);
            current->setNext(nullptr);
        }
    }
    void deletePenultimate() {
        if (first == nullptr) {
            return;
        } else if (first->getNext() == nullptr) {
            first = nullptr;
        } else {
            Nodo<int>* current = first;
            while (current->getNext()->getNext() != nullptr) {
                current = current->getNext();
            }

            current->getNext()->setPrevious(current->getPrevious());
            current->getPrevious()->setNext(current->getNext());
            current->setPrevious(nullptr);
            current->setNext(nullptr);
        }
    }
    void deleteByData(int* index) {
        if (first->getData() == index) {
            return;
        } else if (first->getNext()->getData() == index) {
            first = nullptr;
        } else {
            Nodo<int>* current = first;
            while (current->getNext()->getNext()->getData() != index && current->getNext()->getNext() != nullptr) {
                current = current->getNext();
            }
            if (current->getNext()->getNext() != nullptr) {
                return;
            }

            current->getNext()->setPrevious(current->getPrevious());
            current->getPrevious()->setNext(current->getNext());
            current->setPrevious(nullptr);
            current->setNext(nullptr);
        }
    }
};

int main() {
    
    return 0;
}