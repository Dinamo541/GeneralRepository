#include <iostream>

int main() {
    int Grado1;
    int Grado2;
    int Grado3;
    int Promedio;
    std::cout << "Enter your grade 1: ";
    std::cin >> Grado1;
    std::cout << "Enter your grade 2: ";
    std::cin >> Grado2;
    std::cout << "Enter your grade 3: ";
    std::cin >> Grado3;
    Promedio = (Grado1 + Grado2 + Grado3) / 3;
    if (Promedio >= 7) {
        std::cout << "You passed the subject with a grade of: " << Promedio << std::endl;
    } else if (Promedio >= 6) {
        std::cout << "You have to go to the reposicion with a grade of: " << Promedio << std::endl;
    } else {
        std::cout << "You didn't pass the subject with a grade of: " << Promedio << std::endl;
    }
    return 0;
}