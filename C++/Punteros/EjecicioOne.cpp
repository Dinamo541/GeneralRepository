#include <iostream>

void registerSales(int **dailySales) {
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 5; j++) {
            printf("Ingrese las ventas del dia %d del producto %d:\n", i+1, j+1);
            scanf("%d", &dailySales[i][j]);
        }
    }
}

void calculateTotalSales(int **dailySales) {
    int totalSales[7] = {0};
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 5; j++) {
            totalSales[i] += dailySales[i][j]; 
        }
        printf("El total de ventas del dia %d es %d.\n", i+1, totalSales[i]);
    }
}

void printEveriting(int **dailySales) {
    int totalSales[7] = {0};
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 5; j++) {
            printf("%d\t", totalSales[i]);
            totalSales[i] += dailySales[i][j]; 
        }
        printf("%d \n", totalSales[i]);
    }
}

int main() {
    int **dailySales = new int*[7];
    for (int i = 0; i < 7; i++) 
        dailySales[i] = new int[5];
    
    registerSales(dailySales);

    calculateTotalSales(dailySales);

    printEveriting(dailySales);

    delete[] dailySales;
    dailySales = nullptr;

    return 0;
}
