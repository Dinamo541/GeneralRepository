#include <iostream>
#include <vector>
using namespace std;

class NQueens {
private:
    int n;
    vector<vector<string>> soluciones;

    bool esSeguro(vector<string>& tablero, int fila, int col) {
        // Verificar columna
        for (int i = 0; i < fila; i++) {
            if (tablero[i][col] == 'Q')
                return false;
        }

        // Diagonal izquierda superior
        for (int i = fila - 1, j = col - 1; i >= 0 && j >= 0; i--, j--) {
            if (tablero[i][j] == 'Q')
                return false;
        }

        // Diagonal derecha superior
        for (int i = fila - 1, j = col + 1; i >= 0 && j < n; i--, j++) {
            if (tablero[i][j] == 'Q')
                return false;
        }

        return true;
    }

    void resolver(vector<string>& tablero, int fila) {
        if (fila == n) {
            soluciones.push_back(tablero);
            return;
        }

        for (int col = 0; col < n; col++) {
            if (esSeguro(tablero, fila, col)) {
                tablero[fila][col] = 'Q';
                resolver(tablero, fila + 1);
                tablero[fila][col] = '.'; // backtracking
            }
        }
    }

public:
    NQueens(int n) : n(n) {}

    void solve() {
        vector<string> tablero(n, string(n, '.'));
        resolver(tablero, 0);

        // Mostrar soluciones
        cout << "Total soluciones: " << soluciones.size() << "\n\n";
        for (const auto& sol : soluciones) {
            for (const auto& fila : sol) {
                cout << fila << endl;
            }
            cout << "-----------------\n";
        }
    }
};

int main() {
    int n;
    cout << "Ingrese N: ";
    cin >> n;

    NQueens problema(n);
    problema.solve();

    return 0;
}