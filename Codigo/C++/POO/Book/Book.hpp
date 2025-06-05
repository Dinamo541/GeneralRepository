#include <iostream>
#include <string>

class Book {
private:
    std::string title = "";
    std::string author = "";
    int yearOfPublication = 0;

public:
    Book();
    Book(std::string newTitle, std::string newAuthor, int newYearOfPublication) : 
        title(newTitle), author(newAuthor), yearOfPublication(newYearOfPublication) {}

    std::string getTitle(); // Declaración del método
    std::string getAuthor(); // Nuevo método para obtener el autor
    int getYearOfPublication(); // Nuevo método para obtener el año de publicación

    void setTitle(std::string newTitle); // Método para establecer el título
    void setAuthor(std::string newAuthor); // Método para establecer el autor
    void setYearOfPublication(int newYearOfPublication); // Método para establecer el año de publicación
    void displayInfo(); // Método para mostrar la información del libro
};