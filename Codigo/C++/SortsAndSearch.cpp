#include <iostream>

class Sorts {
public:
    static const int SIZE = 5;
    int arr[SIZE] = {64, 34, 25, 12, 22}; 
    
    void burbelSorter() {
        for (int i = 0; i < SIZE - 1; i++) {
            for (int j = 0; j < SIZE - i - 1; j++) {
                swapArray(j);
            }
        }
    }
    void swapArray(int index) {
        if (arr[index] > arr[index + 1]) {
            int swap = arr[index];
            arr[index] = arr[index + 1];
            arr[index + 1] = index;
        }
    }

    void selectionSort() {
        for (int i = 0; i < SIZE - 1; i++) {
            int minIndex = findMin(i);
            if (minIndex != i) { // Si el actual no es el menor intercambiamos
                int swap = arr[i];
                arr[i] = arr[minIndex];
                arr[minIndex] = swap;
            }
        }
    }
    int findMin(int start) {
        int index = start;
        for (int i = index + 1; i < SIZE; i++) { // recorre bucando el menor
            if (arr[i] < arr[index]) {
                index = i;
            }
        }
        return index;
    }

};

class BinarySearch {
public:
    static const int SIZE = 5;
    int arr[SIZE] = {1, 2, 3, 4, 5}; // Debe estar ordenado para la busqueda binaria

    int binarySearch(int target) { // Busca un elemento en el arreglo ordenado
        int left = 0, right = SIZE - 1;
        while (left <= right) {
            int mid = (left + right) / 2; // Evita overflow
            if (arr[mid] == target) {
                return mid; // Elemento encontrado
            } else if (arr[mid] < target) {
                left = mid + 1; // Buscar en la mitad derecha
            } else {
                right = mid - 1; // Buscar en la mitad izquierda
            }
        }
        return -1; // Elemento no encontrado
    }
};
int main() {
    Sorts sorter;
    sorter.burbelSorter();
    std::cout << "Array after Bubble Sort: ";
    for (int i = 0; i < Sorts::SIZE; i++) {
        std::cout << sorter.arr[i] << " ";
    }
    std::cout << std::endl;

    sorter.selectionSort();
    std::cout << "Array after Selection Sort: ";
    for (int i = 0; i < Sorts::SIZE; i++) {
        std::cout << sorter.arr[i] << " ";
    }
    std::cout << std::endl;

    BinarySearch searcher;
    int target = 3;
    int result = searcher.binarySearch(target);
    if (result != -1) {
        std::cout << "Element " << target << " found at index: " << result << std::endl;
    } else {
        std::cout << "Element " << target << " not found." << std::endl;
    }

    return 0;
}