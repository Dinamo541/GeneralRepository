#include <iostream>
#include <ctime>

class Board {
private:
    int board[8][8];

public:
    Board() {
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                board[i][j] = (rand() % 5) + 1;
                printf("%d ", board[i][j]);
            }
            std::cout << std::endl;
        }
    }
    ~Board();

    void printBoard() {
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++)
                printf("%d ", board[i][j]);
            std::cout << std::endl;
        }
    }
    void confirmColumsAndRows() {
        int countJ = 0, countI = 0;
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                for (int k = i; k < 8 - i && board[i][j] == board[k][j]; k++) {
                    countI++;
                }
                for (int k = j; k < 8 - j && board[i][j] == board[i][k]; k++) {
                    countJ++;
                }
            }
        }
        for (int i = 0; i < 8; i++)
            if (board[1][i] == 0) 
                board[1][i] = (rand() % 5) + 1;
    }
    void moveFromUpToDown() {
        for (int row = 8; row > 1; row--) {
            for (int colum = 0; colum < 8; colum++) {
                if (board[row][colum] == 0 ) {
                    moveAllTheColum(row, colum);
                }
            }
        }
    }
    void moveAllTheColum(int row, int colum) {
        for (int i = 0; i < row; i++) {
            if (board[0][colum] == 0)
                board[0][colum] = (rand() % 5) + 1;
            for (int j = 0; j > row - i; j--) {
                if (board[j + 1][colum] != 0) {
                    board[j][colum] = board[j + 1][colum];
                    board[j + 1][colum] = 0;
                }
            }
        }
    }

};

int main() {
    srand(time(NULL));
    int continuar = 1;
    while (continuar != 0) {
        Board boardOne;
        printf("\n----------------\n\n");
        boardOne.confirmColumsAndRows();
        boardOne.printBoard();
        boardOne.moveFromUpToDown();
        boardOne.printBoard();
        std::cin >> continuar;
    }

    return 0;
}