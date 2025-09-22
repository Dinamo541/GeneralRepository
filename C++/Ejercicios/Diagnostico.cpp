#include <iostream>

class Practicas {
private:
    int** matrix;
    int** auxMatrix;
    int* arr;
    int* newArr;
    int cords[2] = {0, 0};
    int num;
    int rows;
    int colums;
    int size;
    int oldSize;
    int sum;
    int numMayor;
    int index;

public:
    Practicas() {
        size = 0;
        sum = 0;
        numMayor = -33;
        oldSize = 0;
        index = 0;
        num = 0;
    }
    ~Practicas() {}

    void sumArr() {
        printf("Ingrese el tamanio del arreglo: \n");
        scanf("%d", &size);
        arr = new int[size];
        for (int i = 0; i < size; i++) {
            printf("Ingrese el numero en la posicion %d: \n", i + 1);
            scanf("%d", &arr[i]); 
            sum += arr[i];
        }
        for (int i = 0; i < size; i++) {
            printf("%d ", arr[i]);
        }
        printf("\nLa suma del arreglo es: %d \n", sum);
    }
    void findMayor() {
        printf("Ingrese el tamanio del arreglo: \n");
        scanf("%d", &size);
        arr = new int[size];
        for (int i = 0; i < size; i++) {
            arr[i] = (rand() % 100) + 1;
            if (numMayor < arr[i]) {
                numMayor = arr[i];
            }
        }
        printf("El numero mas alto es: %d\n", numMayor);
    }
    void reSizeArr() {
        printf("Ingrese el tamanio del arreglo: \n");
        scanf("%d", &size);
        arr = new int[size];
        for (int i = 0; i < size; i++) {
            printf("Ingrese el numero en la posicion %d: \n", i + 1);
            scanf("%d", &arr[i]); 
        }
        oldSize = size;
        printf("Ingrese el nuevo tamanio del arreglo: \n");
        scanf("%d", &size);
        newArr = new int[size];
        for (int i = 0; i < size; i++) {
            if (oldSize > i) {
                newArr[i] = arr[i];
            } else {
                newArr[i] = 0;
            }
            printf("%d ", newArr[i]);
        }
    }
    void deleteNomber() {
        printf("\nIngrese el tamanio del arreglo: \n");
        scanf("%d", &size);
        arr = new int[size];
        for (int i = 0; i < size; i++) {
            printf("Ingrese el numero en la posicion %d: \n", i + 1);
            scanf("%d", &arr[i]); 
        }
        printf("Ingrese el indice del numero que quiere omitir: \n");
        scanf("%d", &index);
        index--;
        newArr = new int[size - 1];
        for (int i = 0; i < size - 1; i++) {
            if (i < index) {
                newArr[i] = arr[i];
            } else {
                newArr[i] = arr[i + 1];
            }
        }
        for (int i = 0; i < size - 1; i++) {
            printf("%d ", newArr[i]);
        }
    }
    void matrixEje() {
        printf("\nIngrese las filas de la matris: \n");
        scanf("%d", &rows);
        printf("\nIngrese las filas de la matris: \n");
        scanf("%d", &colums);
        *matrix = new int[rows];
        *auxMatrix = new int[rows];
        for (int i = 0; i < rows; i++) {
            matrix[i] = new int[colums];
            auxMatrix[i] = new int[colums];
        }
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < colums; j++) {
                printf("\nIngrese el numero de la fila %d, colunma %d: \n", i, j);
                scanf("%d", &matrix[i][j]);
                auxMatrix[i][j] = matrix[i][j];
            }
        }
        printf("\nIngrese el numero que desea agregar: \n");
        scanf("%d", &num);
        printf("\nIngrese la filas donde desea agregar el elemento: \n");
        scanf("%d", &cords[0]);
        cords[0]--;
        printf("\nIngrese la colunma donde desea agregar el elemento: \n");
        scanf("%d", &cords[1]);
        cords[1]--;
        for (int i = 0; i < rows; i++) {
            if (cords[0] == i) {
                matrix[i] = new int[colums + 1];
            } else {
                matrix[i] = new int[colums];
            }
            for (int j = 0; j < colums; j++) {
                if (cords[1] > j) {
                    matrix[i][j] = auxMatrix[i][j];
                } else if (cords[1] == j)  {
                    matrix[i][j] = num;
                } else {
                    matrix[i][j + 1] = auxMatrix[i][j];
                }
                printf("%d ", matrix[i][j]);
            }
            printf("\n");
        }
    }
};

int main() {
    srand(time(NULL));
    Practicas practicaOne;
    practicaOne.matrixEje();
    return 0;
}