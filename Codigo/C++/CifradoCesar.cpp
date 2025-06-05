#include <iostream>

class Vector {
private:
    static constexpr int SIZE = 26;
    std::string vector[SIZE] = {"A", "B", "C", "D", "E", "F", "G", 
        "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", 
        "T", "U", "V", "W", "X", "Y", "Z"};
    std::string  auxiliaryList[SIZE] = {"A", "B", "C", "D", "E", "F",
        "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R",
        "S", "T", "U", "V", "W", "X", "Y", "Z"};
public:
    Vector() {
        std::cout << "Default constructor called" << std::endl;
    }
    Vector(const Vector& other) {
        std::cout << "Copy constructor called" << std::endl;
        for (int i = 0; i < SIZE; ++i) {
            vector[i] = other.vector[i];
        }
    }
    ~Vector() {
        std::cout << "Destructor called" << std::endl;
    }

    const std::string* getVector() const {
        return vector;
    }
    static constexpr int getSize() {
        return SIZE;
    }

    void setVector(int index, int value) {
        if (index >= 0 && index < SIZE) {
            vector[index] = value;
        } else {
            std::cout << "Index out of bounds" << std::endl;
        }
    }

    void printVector() const {
        std::cout << "The vector is: ";
        for (int i = 0; i < SIZE; ++i) {
            std::cout << vector[i] << " ";
        }
        std::cout << std::endl;
    }
    void printAuxiliaryList() const {
        std::cout << "The vector is: ";
        for (int i = 0; i < SIZE; ++i) {
            std::cout << auxiliaryList[i] << " ";
        }
        std::cout << std::endl;
    }

    void rotateVector(int steps) {
        while (steps > SIZE) {
            steps = steps - SIZE;
        }
        for (int i = 0; i < SIZE; ++i) {
            if (i + steps < SIZE) {
                vector[i] = auxiliaryList[i + steps];
            } else {
                vector[i] = auxiliaryList[i + steps - SIZE];
            }
        }
    }
};

int main() {
    Vector vectorOne;
    int steps = 1;
    while (steps != 0) {
        std::cout << "How many steps do you want to rotate the vector?(0 to exit)" << std::endl;
        std::cin >> steps;
        if (steps == 0) {
            std::cout << "Exiting the program." << std::endl;
            break;
        }
        system("cls");
        vectorOne.rotateVector(steps);
        vectorOne.printVector();
        vectorOne.printAuxiliaryList();
    }
    return 0;
}