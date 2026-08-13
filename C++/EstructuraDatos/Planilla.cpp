#include <iostream>
#include <string>
using namespace std;

struct Employee
{
    int id;
    string name;
    string surname;
    int salary;
    int vacations;
    char workShift;
};

struct Node
{
    Node *next = nullptr;
    Node *previous = nullptr;
    Employee data;
};

struct List
{
    Node *first = nullptr;
};

bool isEmpty(List &list)
{
    return list.first == NULL;
}

void insert(List &list, Employee newData)
{
    if (list.first == NULL)
    {
        list.first == new Node();
        list.first->data = newData;
    }
    Node *newNode = new Node();

    newNode->data = newData;
    newNode->previous = nullptr;

    newNode->next = list.first;

    list.first->previous = newNode;

    if (list.first->next == NULL) {
        newNode->previous = list.first;
        newNode->next = list.first;
        list.first = newNode;
        return;
    }

    Node *current = list.first;
    while (current->next != list.first)
    {
        current = current->next;
    }

    newNode->previous = current;
    newNode->next = list.first;

    list.first = newNode;
}

Employee getFirst(List &list)
{
    return list.first->data;
}

Employee getLast(List &list)
{
    Node *current = list.first;

    while (current->next == list.first)
    {
        current = current->next;
    }

    return current->data;
}

void printEmployee(Employee employee)
{
    cout << "--- Empleado ---" << endl;
    cout << "Identificacion: " << employee.id << endl;
    cout << "Nombre: " << employee.name << endl;
    cout << "Apellidos: " << employee.surname << endl;
    cout << "Salario: " << employee.salary << endl;
    cout << "Vacaciones: " << employee.vacations << endl;
    cout << "Jornada: " << employee.workShift << endl;
    cout << "---------------" << endl;
}

void printList(List list)
{
    Node *current = list.first;

    while (current != NULL)
    {
        printEmployee(current->data);
        current = current->next;
    }
}

int locate(List &list, Employee employee)
{
    Node *current = list.first;
    if (current == NULL)
    {
        cout << "La lsta esta vacia." << endl;
    }
    for (int i = 1; current != NULL; i++)
    {
        if (current->data.id == employee.id)
        {
            return i + 1;
        }
        current = current->next;
    }
    return 0;
}

void insertInOrder(List &list, Employee employee)
{
    Node *newNode = new Node();
    newNode->data = employee;

    if (list.first == nullptr || employee.id < list.first->data.id)
    {
        newNode->next = list.first;
        if (list.first != nullptr)
        {
            list.first->previous = newNode;
        }
        list.first = newNode;
        return;
    }

    Node *current = list.first;
    while (current->next != nullptr && current->next->data.id < employee.id)
    {
        current = current->next;
    }

    newNode->next = current->next;
    newNode->previous = current;
    if (current->next != nullptr)
    {
        current->next->previous = newNode;
    }
    current->next = newNode;
}

void deleteEmployee(List &list, Employee employee)
{
    if (isEmpty(list))
    {
        cout << "The list is empty" << endl;
        return;
    }
    Node *current = list.first; // Head
    if (current->data.id == employee.id)
    {
        list.first = current->next;
        delete current;
        current = nullptr;
        return;
    }

    while (current->next != NULL)
    {
        if (current->next->data.id == employee.id)
        {
            Node *aux = current->next;
            current->next = aux->next;

            delete aux;
            aux = nullptr;
            return;
        }
    }
    cout << "El usuario a borrar no se encontro" << endl;
}

/*
Integrantes:

Yuliana Mora Cedeño :D
Dominique Mariano Quiros Castro :D

*/

int main(int argc, char *argv[])
{
    List list;
    List sortList;
    Employee employeeOne = Employee{100019999, "Maria", "Solis Blanco", 125350, 3, 'D'};
    Employee employeeTwo = Employee{700019999, "Felipe", "Bonilla Ruiz", 250370, 5, 'D'};
    Employee employeeThree = Employee{300019999, "Juan", "Mora Mora", 525470, 6, 'M'};
    Employee employeeFour = Employee{200019999, "Margarita", "Sanchez", 650000, 12, 'N'};
    Employee employeeFive = Employee{400019999, "Andres", "Vargas ", 425000, 20, 'M'};

    // Us :D
    Employee employeeY = Employee{119640147, "Yuliana", "Mora Cedeno", 10000000, 4, 'D'};
    Employee employeeD = Employee{120020283, "Dominique", "Quiros Castro", 33, 12, 'N'};

    insert(list, employeeOne);
    insert(list, employeeTwo);
    insert(list, employeeThree);
    insert(list, employeeFour);
    insert(list, employeeFive);
    insert(list, employeeY);
    insert(list, employeeD);

    insertInOrder(sortList, employeeOne);
    insertInOrder(sortList, employeeTwo);
    insertInOrder(sortList, employeeThree);
    insertInOrder(sortList, employeeFour);
    insertInOrder(sortList, employeeFive);

    printList(list);
    cout << "______________________" << endl;
    printList(sortList);

    int i = locate(list, employeeFour);
    if (i == 0)
    {
        cout << "The employee " << employeeFour.name << " was not found on the list.\n";
    }
    else
    {
        cout << "The employee " << employeeFour.name << " was found at index: " << i << endl;
    }

    return 0;
}
