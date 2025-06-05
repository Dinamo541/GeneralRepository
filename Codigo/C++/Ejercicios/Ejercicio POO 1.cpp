#include <iostream>
#include <string>
using namespace std;

class Student {
private:
    string name = "Sin nombre";
    int id = 0;
    float grade = 0.0f;
public:
    Student() : name("Sin nombre"), id(0), grade(0.0f) {}
    Student(string name, int id, float grade) : name(name), id(id), grade(grade) {}
    
    void setName(string n) {name = n;}
    void setId(int i) {id = i;}
    void setGrade(float g) {grade = g;}

    string getName() {return name;}
    int getId() {return id;}
    float getGrade() {return grade;}
    
    void display() {
        cout << "Nombre: " << name << endl;
        cout << "ID: " << id << endl;
        cout << "Nota: " << grade << endl;
    }
};

int main (int argc, char *argv[]) {
    Student studentOne("Juan", 123, 8.5f);
    Student studentTwo("Maria", 456, 9.0f);

    cout << "Datos del estudiante 1:" << endl;
    studentOne.display();
    cout << endl;

    cout << "Datos del estudiante 2:" << endl;
    studentTwo.display();

    return 0;
}