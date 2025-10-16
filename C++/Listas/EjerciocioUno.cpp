#include <iostream>
#include <sstream>
using namespace std;

class Entity {
private:
    string id;
    string name;

public:
    Entity() {
        id = "";
        name = "";
    }
    Entity(string newId, string newName) : id(newId), name(newName) {}
    ~Entity() {}

    string getId() {
        return id;
    }
    string getName() {
        return name;
    }

    virtual string toString() = 0;

};

class People : public Entity {
private:
    int age;
    int dailySteps;

public:
    People() : Entity() {
        age = 0;
        dailySteps = 0;
    }
    People(int newAge, int newDailySteps, string newId, string newName) : Entity(newId, newName) {
        age = newAge;
        dailySteps = newDailySteps;
    }
    ~People() {}

    void setAge(int newAge) {
        age = newAge;
    }
    void setDailySteps(int newDailySteps) {
        dailySteps = newDailySteps;
    }

    int getAge() {
        return age;
    }
    int getDailySteps() {
        return dailySteps;
    }

    string toString() {
        std::stringstream ss;
        ss << "-------------------------------\n"
        << "Tipo: Persona\nId: " << getId() << "\nNombre: " << getName()
        << "\nEdad: " << age << "\nPasos diarios: " << dailySteps;
        return ss.str();
    }

};

class Automobile : public Entity {
private:
    int year;
    int kilometersTraveled;

public:
    Automobile() : Entity() {
        year = 0;
        kilometersTraveled = 0;
    }
    Automobile(int newYear, int newKilometersTraveled, string newId, string newName) : Entity(newId, newName) {
        year = newYear;
        kilometersTraveled = newKilometersTraveled;
    }
    ~Automobile() {}

    void setYear(int newYear) {
        year = newYear;
    }
    void setKilometersTraveled(int newKilometersTraveled) {
        kilometersTraveled = newKilometersTraveled;
    }

    int getYear() {
        return year;
    }
    int getKilometersTraveled() {
        return kilometersTraveled;
    }

    string toString() {
        std::stringstream ss;
        ss << "-------------------------------\n"
        << "Tipo: Automovil\nId: " << getId() << "\nNombre: " << getName()
        << "\nannio: " << year << "\nKilometros recorridos: " << kilometersTraveled;
        return ss.str();
    }

};

class Nodo {
private:
    Entity* entity;
    Nodo* next;

public:
    Nodo() {
        entity = nullptr;
        next = nullptr;
    }
    ~Nodo() {
        entity = nullptr;

        next = nullptr;
    }

    void setEntity(Entity *newEntity) {
        entity = newEntity;
    }
    void setNext(Nodo *newNext) {
        next = newNext;
    }

    Entity* getEntity() {
        return entity;
    }
    Nodo* getNext() {
        return next;
    }

    void print() {
        cout << entity->toString() << endl;
    }

};

class List {
private:
    Nodo* first;

public:
    List() {
        first = nullptr;
    }
    List(Entity* Entity) {
        first = new Nodo;
        first->setEntity(Entity);
        first->setNext(nullptr);
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

    void add(Entity* newEntity) {
        Nodo* current = first;

        while(current->getNext() != nullptr) {
            current = current->getNext();
        }

        current->setEntity(newEntity);
        current->setNext(new Nodo);
        
    }
    void addPersonToBeginning(Entity* newEntity) {
        Nodo* current = first;
        first = new Nodo;
        first->setEntity(newEntity);
        first->setNext(current);
    }
    void print() {
        Nodo* current = first;

        while(current->getEntity() != nullptr) {
            current->print();
            current = current->getNext();
        }
    }
    void addToLast(Entity* newEntity) {
        Nodo* current = first;

        while(current->getNext() != nullptr) {
            current = current->getNext();
        }

        first->setEntity(newEntity);
        current->setNext(new Nodo);
    }
    
};

int main() {
    List list(nullptr);
    int type;
    string id, retray = "1", name;
    int age;
    int dailySteps;
    int year;
    int kilometersTraveled;
    while (retray == "1") {
        system("cls");
        id = "";
        name = "";
        age = 0;
        dailySteps = 0;
        year = 0;
        kilometersTraveled = 0;
        printf("Elija el tipo de Entidad:\n");
        printf("1. Persona\n");
        printf("2. Automovil\n");
        cin >> type;
        if (type == 1) {
            printf("Ingrese el id: ");
            cin >> id;
            printf("\nIngrese el nombre: ");
            cin >> name;
            printf("\nIngrese la edad: ");
            cin >> age;
            printf("\nIngrese pasos diarios: ");
            cin >> dailySteps;

            list.add(new People(age, dailySteps, id, name));
            list.print();
        } else {
            printf("Ingrese el id: ");
            cin >> id;
            printf("\nIngrese el nombre: ");
            cin >> name;
            printf("\nIngrese el anio: ");
            cin >> year;
            printf("\nIngrese los kilomtros viajados: ");
            cin >> kilometersTraveled;

            list.add(new Automobile(year, kilometersTraveled, id, name));
            list.print();
        }
        retray = "";
        printf("\nIngrese 1 para continuar o otra cosa para salir: ");
        cin >> retray;
    }
    
    return 0;
}