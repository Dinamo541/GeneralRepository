#include <iostream>
using namespace std;

struct Node
{
    Node *next;
    int data;
};

struct Stack
{
    Node *top;
};

Stack createStack(int newData)
{
    Stack stack = Stack();

    stack.top = new Node();

    stack.top->data = newData;

    return stack;
}

void insert(Stack &stack, Node *newNode)
{
    newNode->next = stack.top;

    stack.top = newNode;
}

Node *pop(Stack &stack)
{
    Node *node = stack.top;

    stack.top = stack.top->next;

    node->next = NULL;

    return node;
}

bool emptyStack(Stack &stack)
{
    return stack.top == NULL;
}

void cleanStack(Stack &stack)
{
    while (stack.top != NULL)
    {
        Node *node = pop(stack);
        delete node;
        node = nullptr;
    }
}

Node *topStack(Stack &stack)
{
    return stack.top;
}

int stackSize(Stack stack)
{
    int size = 0;
    while (stack.top != NULL)
    {
        pop(stack);
        size++;
    }
    return size;
}

int main(int argc, char *argv[])
{

    return 0;
}
