#include "Functions.cpp"
#include <iostream>
#include <string>

int main() {
    // Crear un objeto de la clase Book
    Book bookOne("1984", "George Orwell", 1949);
    Book bookTwo("El Principito", "Antoine de Saint-Exupéry", 1943);

    std::cout << std::endl << "Título: " << bookOne.getTitle() << std::endl;
    std::cout << "Autor: " << bookOne.getAuthor() << std::endl;
    std::cout << "Año de publicación: " << bookOne.getYearOfPublication() << std::endl << std::endl;

    bookTwo.displayInfo();
    std::cout << std::endl;

    return 0;
}