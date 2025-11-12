#include <iostream>
#include <string>

template <class T>
class Nodo {
private:
    T* variable;
    Nodo<T>* next;

public:
    Nodo() : variable(nullptr), next(nullptr) {}
    Nodo(T* val) : variable(val), next(nullptr) {}
    ~Nodo() {
        delete variable;
        next = nullptr;
    }

    T* getVariable() {
        return variable;
    }
    Nodo<T>* getNext() {
        return next;
    }
    void setVariable(T* newVariable) {
        variable = newVariable;
    }
    void setNext(Nodo* newNext) {
        next = newNext;
    }
};

class Rooms {
private:
    int number;
    int capacity;
    bool occupied;
    std::string headline;

public:
    Rooms() {
        number = 0;
        capacity = 0;
        occupied = false;
        headline = "";
    }
    Rooms(int newNumber, int newCapacity, bool newOccupied, std::string newHeadline)
    : number(newNumber), capacity(newCapacity), occupied(newOccupied), headline(newHeadline) {
    }
    ~Rooms() {}

    void booking(std::string customerName) {
        if (!occupied) {
            occupied = true;
            headline = customerName;
            std::cout << "Habitacion numero " << number << " ha sido reservada por " << customerName << ".\n";
        } else {
            std::cout << "Habitacion numero " << number << " ya esta ocupada.\n";
        }
    }
    void vacate() {
        if (occupied) {
            occupied = false;
            headline = "";
            std::cout << "Habitacion numero " << number << " a sido desocupada.\n";
        } else {
            std::cout << "Habitacion numero " << number << " ya esta desocupada.\n";
        }
    }
    void printLine() {
        std::cout << "Habitacion numero: " << number << ", Capacidad: " << capacity 
                  << ", Ocupada: " << (occupied ? "Si" : "No") << ", Titular: " << headline << std::endl;
    }
};

class Floors {
private:
    int floorNumber;
    Nodo<Rooms>* first;
    
public:
    Floors() : floorNumber(0), first(nullptr) {}
    Floors(int newFloorNumber) : floorNumber(newFloorNumber), first(nullptr) {} 
    ~Floors() {
        Nodo<Rooms>* current = first; 
        Nodo<Rooms>* next = current->getNext();
        while(next != nullptr) {
            next = current->getNext();
            delete current;
            current = next;
        }
        first = nullptr;
    }

    void addRoomAtTheEnd(int newNumero, int newCapacity) {
        if (first == nullptr) {
            first = new Nodo<Rooms>(new Rooms(newNumero, newCapacity, false, ""));
        } else {
            Nodo<Rooms>* current = first;
    
            while (current->getNext() != nullptr) {
                current->setNext(current->getNext());
            }
            current->setNext(new Nodo<Rooms>(new Rooms(newNumero, newCapacity, false, "")));
        }
    }
};

int main() {
    int gt = 0;
    return 0;
}