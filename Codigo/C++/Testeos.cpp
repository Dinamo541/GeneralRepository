// Testeos.cpp : This file contains the 'main' function. Program execution begins
#include <iostream>

class TicTacToe {
private:
    char board[3][3];

public:
    TicTacToe() {
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                board[i][j] = ' ';
            }
        }
    }
    ~TicTacToe() {}
    char whoWins() {
        if (ifPlayerWin('X')) {
            return 'X';
        } else if (ifPlayerWin('O')) {
            return 'O';
        }
    }
    bool ifPlayerWin(char playerChar) {
        if (ifPlayerWinByRows(playerChar)){
            return true;
        } else if (ifPlayerWinByColumns(playerChar)){
            return true;
        } else if (ifPlayerWinByDiagonals(playerChar)){
            return true;
        }
        return false;  
    }
    bool ifPlayerWinByRows(char playerChar) { 
        for (int i = 0; i < 3; i++) {
            if ((board[i][0] == playerChar) && (board[i][0] == board[i][1]) && (board[i][1] == board[i][2])) {
                return true;
            }
        } 
        return false;
    }
    bool ifPlayerWinByColumns(char playerChar) {
        for (int i = 0; i < 3; i++) {
            if ((board [0][i] == playerChar) && (board[0][i] == board[1][i]) && (board[1][i] == board[2][i])) {
                return true;
            }
        }
        return false;
    }
    bool ifPlayerWinByDiagonals(char playerChar) {
        for (int i = 0; i < 3; i + 2) {
            for (int j = 2; j >= 0; j - 2) {
                if ((board[1][1] == playerChar) && (board[i][j] == playerChar) && (board[i][j] == board[i][j])) {
                    return true;
                }
            }
        }
        return false;
    }
    void registerAMove(int row, int col, char playerChar) {
        if (board[row][col] == ' ') {
            board[row][col] = playerChar;
        }
    }
    void cleanBoard() {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; i < 3; j++) {
               board[i][j] = ' '; 
            }
        }   
    }
};


int main() {
    

    return 0;
}