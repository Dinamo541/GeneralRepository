#include <iostream>

void printVector(int vec[10], int number) {
    for (int i = 0; i < 10; i++) {
        vec[i] = vec[i] * number;
        std::cout << vec[i] << " ";
    }
}

int main() {
    int vector[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    int number = 3;
    printVector(vector, number);
    return 0;
}