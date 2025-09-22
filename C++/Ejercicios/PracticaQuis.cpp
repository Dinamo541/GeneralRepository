#include <iostream>
#include <cstdlib>
#include <ctime>

void ejerciceOne() {
    int matrix[6][6], sum;
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            matrix[i][j] = (rand() % 50) + 1;
            std::cout << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
    for (int i = 1; i < 6; i++) {
        for (int j = 0; j < i; j++) {
            sum += matrix[i][j];
        }
    }
    std::cout << sum;
}

void ejerciceTwo() {
    int matrixOne[3][3], matrixTwo[3][3], matrix[3][3] = {0};
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            matrixOne[i][j] = (rand() % 10) + 1;
            matrixTwo[i][j] = (rand() % 10) + 1;
        }
    }
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            for (int k = 0; k < 3; k++) {
                matrix[i][j] += matrixOne[i][k] * matrixTwo[k][j];
            }
        }
    }
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            for (int k = 0; k < 3; k++) {
                if (i == 0) {
                    std::cout << matrixOne[j][k] << " ";
                } else if (i == 1) {
                    std::cout << matrixTwo[j][k] << " ";
                } else {
                    std::cout << matrix[j][k] << " ";
                }
            }
            std::cout << std::endl;
        }
        std::cout << std::endl << std::endl;
    }
}


void ejerciceThree() {
    int matrix[5][5], rows[5], colums[5], number, many = 0;
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            matrix[i][j] = (rand() % 20) + 1;
        }
    }
    std::cout << " Introdusca un numero a buscar: ";
    std::cin >> number;
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (number == matrix[i][j]) {
                rows[many] = i;
                colums[many] = j;
                many++;
            }
        }
    }
    std::cout << "Se encontraron " << many << " '" << number << "' en las posiciones:\n";
    for (int i = 0; i < many; i++) {
        std::cout << "El numero " << i << " en la posicion: ";
        std::cout << rows[i] << " " << colums[i] <<std::endl;
    }
    std::cout << std::endl << std::endl;
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

void ejerciceFour() {
    int matrix[7][7], sum;
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 7; j++) {
            matrix[i][j] = (rand() % 90) + 10;
            std::cout << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
    for (int i = 7; i < 0; i--) {
        for (int j = 0; j < 7; j++) {
            if (i - 1 != -1) {
                sum += matrix[i - 1][j];
                sum += matrix[i][j + 1];
            }
            sum += matrix[i][j];
        }
    }
    std::cout << sum;
}

void ejerciceFive() {
    int matrix[4][4], sum;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            matrix[i][j] = (rand() % 50) + 1;
            std::cout << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }

}

int main() {
    srand(time(NULL));
    ejerciceTwo();
    
    return 0;
}