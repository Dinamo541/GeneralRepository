#include <iostream>
#include <string>

int main() {
    int num = 0;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            std::cout << num << std::endl;
            num++;
        }
    }
    return 0;
}