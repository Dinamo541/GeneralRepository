#include "Book.hpp"
#include <iostream>
#include <string>


// Implementación de los métodos

std::string Book::getTitle() {
    return title;
}

std::string Book::getAuthor() {
    return author;
}

int Book::getYearOfPublication() {
    return yearOfPublication;
}

void Book::setTitle(std::string newTitle) {
    title = newTitle;
}

void Book::setAuthor(std::string newAuthor) {
    author = newAuthor;
}

void Book::setYearOfPublication(int newYearOfPublication) {
    yearOfPublication = newYearOfPublication;
}

void Book::displayInfo() {
    std::cout << "Título: " << title << std::endl;
    std::cout << "Autor: " << author << std::endl;
    std::cout << "Año de publicación: " << yearOfPublication << std::endl;
}