#include <iostream>

int main() {
    int *arr[3];
    int one = 5, two = 10, three = 15;

    arr[0] = &one;
    arr[1] = &two;
    arr[2] = &three;

    for (int i = 0; i < 3; i++) {
        printf("%p \n", arr[i]);
        printf("%d \n", *arr[i]);
        std::cout << std::endl;
        arr[i] = nullptr;
        delete arr[i];
    }
    
    return 0;
}