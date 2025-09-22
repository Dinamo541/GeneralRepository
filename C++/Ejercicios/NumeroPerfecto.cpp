#include <iostream>

bool isPerfectNumber(int number) {
    int divisors = 0;
    for (int i = 1; i < number; i++) {
        if (number % i == 0) {
            divisors += i;
        }
    }
    return (number == divisors);
}

int main() {
    int x = 21;
    if (isPerfectNumber(x)) {
        std::cout << x << " is a perfect number" << std::endl;
    } else {
        std::cout << x << " is not a perfect number" << std::endl;
    }

    return 0;
}