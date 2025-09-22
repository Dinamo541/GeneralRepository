#include <iostream>
#include <cstdlib>
class Practica {
private:
    static const int SIZE = 10;
    int arr[SIZE] = {1, 2, 6, 4, 10, 3, 9, 2, 3, 5};
    int duplicados[SIZE / 2];

public:
    Practica();
    ~Practica();

    void buscarDuplicados() {
        for (int i = 0, k = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                if (arr[i] == arr[j] && i != j && duplicados[k] != arr[i]) {
                    duplicados[k] = arr[i];
                    k++;
                }
            }
        }
    }

};

int main() {
    std::cout << "Hello\n";
    return 0;
}