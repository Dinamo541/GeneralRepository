#include <iostream>
#include <ctime>

void moveFromUpToDown(int matrix[8][8]) {
    for (int i = 8; i > 1; i--) {
        for (int j = 0; j < 8; j++) {
            if (matrix[i][j] == 0 )
                moveAllTheColum(matrix, j, i);
        }
    }
    for (int i = 0; i < 8; i++)
        if (matrix[1][i] == 0) 
            matrix[1][i] = (rand() % 5) + 1;
}

void moveAllTheColum(int matrix[8][8], int colum, int row) {
    for (int i = 0; i < row; i++) {
        if (matrix[0][colum] == 0)
            matrix[0][colum] = (rand() % 5) + 1;
        for (int j = 0; j > row - i; j--)
            if (matrix[j + 1][colum] != 0) {
                matrix[j][colum] = matrix[j + 1][colum];
                matrix[j + 1][colum] = 0;
            }
    }
}

int main() {
    int matrix[8][8];
    srand(time(NULL));
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            matrix[i][j] = (rand() % 5) + 1;
            std::cout << matrix[i][j];
        }
        std::cout << std::endl;
    }
    moveFromUpToDown(matrix);

    return 0;
}