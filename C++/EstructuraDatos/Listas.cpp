#include <iostream>

struct Node
{

    Node *next;
    int data;
};

void printList(Node &list)
{
    Node *current = list.next;
    while (current != NULL)
    {
        std::cout << current->data << "\n";
        current = current->next;
    }
}

void insert(Node &list, int newData)
{
    Node *newNode = new Node();

    newNode->data = newData;

    newNode->next = list.next;

    list.next = newNode;
}

void insertAtTheEnd(Node &list, int newData)
{
    Node *newNode = new Node();
    newNode->data = newData;

    if (list.next != NULL)
    {
        newNode->next = list.next;
        list.next = newNode;
    }
    else
    {
        Node *current = list.next;
        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = newNode;
    }
}

bool isSort(Node &list)
{
    Node *current = list.next;

    while (current->next != NULL)
    {
        if (current->data > current->next->data)
            return false;

        current = current->next;
    }
    return true;
}

void changeNodes(Node* current) {

}

void sort(Node &list)
{
    Node *current = list.next;

    if (current == NULL || current->next == NULL)
    {
        return;
    }
    else if (current->data > current->next->data)
    {
        list.next = current->next;

        current->next = list.next->next;

        list.next->next = current;
    }

    while (!isSort(list))
    {
        current = list.next;
        while (current->next->next != NULL)
        {
            if (current->next->data > current->next->next->data)
            {

            }
            current = current->next;
        }
    }
}

/*Node *aux = current->next;

                current->next = current->next->next;

                aux->next = aux->next->next;

                current->next->next = aux;*/

int main(int argc, char *argv[])
{
    Node list;

    insert(list, 3);
    insert(list, 2);
    insert(list, 1);
    insert(list, 4);
    insert(list, 4);

    sort(list);

    printList(list);

    return 0;
}
