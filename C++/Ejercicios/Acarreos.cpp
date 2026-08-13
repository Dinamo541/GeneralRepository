#include <iostream>

int size(int number) {
    int size = 0;

    while (number != 0) {
        size++;

        number = number / 10;
    }

    return size;
}

int complementOne(int numberBin) {
    int complementOne = 0;

    for (int i = 0; i < size(numberBin); i++) {
        complementOne *= 10;
        if ((numberBin % 10) == 0) {
            complementOne++;
        }
        numberBin = numberBin / 10;
    }

    return complementOne;
}

int complementTwo(int numberBin) {
    int complementTwo = 0;

    complementTwo = complementOne(numberBin) + 1;

    return complementTwo;
}

int main() {

    std::cout << "Complemento a uno de 1010: " << complementOne(1010) << std::endl;
    std::cout << "Complemento a dos de 1010: " << complementTwo(1010) << std::endl;

    return 0;
}
