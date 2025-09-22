#include <iostream>
#include <string>

class Container {
private:

    int container[50];
    int size;
    int amount;

public:

    Container();
    Container(int newAmount, int newSize);

    int getSize();
    int getAmount();
    int getContainer(int index);

    void setSize(int newSize);
    void setAmount(int newAmount);

    void showContainer(); // Eliminado el parámetro innecesario

};