#include <iostream>
using namespace std;

class People {
private:
    int age;
    string name;

public:
    People() {
        age = 0;
        name = "desconocido";
    }
    People(int newId, string newName) {
        age = newId;
        name = newName;
    }
    ~People() {}

    void setId(int newId) {
        age = newId;
    }
    void setName(string newName) {
        name =newName;
    }

    int getId() {
        return age;
    }
    string getName() {
        return name;
    }

};

class Nodo {
private:
    People* person;
    Nodo* next;

public:
    Nodo() {
        person = nullptr;
        next = nullptr;
    }
    ~Nodo() {
        person = nullptr;

        delete next;
        next = nullptr;
    }

    void setData(People *newPersona) {
        person = newPersona;
    }
    void setNext(Nodo *newNext) {
        next = newNext;
    }

    People* getData() {
        return person;
    }
    Nodo* getNext() {
        return next;
    }

    void print() {
        printf("Id: %d\n", person->getId());
        cout << "Nombre: " << person->getName() << endl;
        //printf("Nombre: \n", person->getName());
    }

};

class List {
private:
    Nodo* first;

public:
    List() {
        first = nullptr;
    }
    List(People* newPerson) {
        first = new Nodo;
        first->setData(newPerson);
        first->setNext(new Nodo);
    }
    ~List() {
        delete first;
        first = nullptr;
    }

    void add(People* newPerson) {
        Nodo* current = first;

        while(current->getNext() != nullptr) {
            current = current->getNext();
        }

        current->setData(newPerson);
        current->setNext(new Nodo);
        
    }
    void print() {
        Nodo* current = first;

        while(current->getNext() != nullptr) {
            current->print();
            current = current->getNext();
        }
    }
    void deleteByName(string name) {
        Nodo* current = first;

        while(current->getNext() != nullptr) {
            if (current->getData()->getName() == name) {
                while (current->getNext() != nullptr) {
                    current->setData(current->getNext()->getData());
                    current->setNext(current->getNext()->getNext());
                    if (current->getNext()->getNext() == nullptr) {
                        current->setNext(nullptr);
                    } else {
                            current = current->getNext();
                    }
                }
            } else {
                current = current->getNext();
            }
        }
    }
    People* FindByName(string name) {
        Nodo* current = first;
        if (current->getData()->getName() == name) {
            return current->getData();
        }

        while(current->getNext() != nullptr) {
            current = current->getNext();
            if (current->getData()->getName() == name) {
                return current->getData();
            }
        }
        return nullptr;
    }

};

int main() {
    List list(new People(1, "Primero"));\
    string nombre;
    int id = 0;
    while (true) {
        printf("Agrege un nombre");
        cin >> nombre;
        printf("Agrege el id");
        cin >> id;

        list.add(new People(id, nombre));
        list.print();
    }
    
    return 0;
}