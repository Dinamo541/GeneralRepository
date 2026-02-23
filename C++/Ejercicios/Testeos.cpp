#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

class Book {
private:
    std::string ISBN;
    std::string title;
    std::string author;
    int year;
    bool available;

public:
    Book() : ISBN(""), title(""), author(""), year(-1), available(false) {}
    Book(std::string newISBN, std::string newTitle, std::string newAuthor, int newYear, bool newAvailable) 
    : ISBN(newISBN), title(newTitle), author(newAuthor), year(newYear), available(newAvailable) {}

    std::string getISBN() { return ISBN; }
    std::string getTitle() { return title; }
    std::string getAuthor() { return author; }
    int getYear() { return year; }
    bool getAvailable() { return available; }

    void setISBN(std::string newISBN) { ISBN = newISBN; }
    void setTitle(std::string newTitle) { title = newTitle; }
    void setTitle(std::string newAuthor) { author = newAuthor; }
    void setYear(int newYear) { year = newYear; }
    void setAvailable(bool newAvailable) { available = newAvailable; }
};

class Librery {
private:
    int shelves;
    int sections;
    Book** books;

public:
    Librery() : shelves(2), sections(2) {
        setBooks();
    }
    Librery(int newShelves, int newSections) : shelves(newShelves), sections(newSections) {
        setBooks();
    }
    void setBooks() {
        books = new Book*[shelves];
        for (int i = 0; i < shelves; i++) {
            books[i] = new Book[sections];
        }
    }

    void agregarLibro(int newShelves, int newSections, std::string ISBN, std::string titulo, std::string autor, int año, bool disponible) {
        if ((newShelves >= 0 && newShelves < shelves) && (newSections >= 0 && newSections < sections)) {
            books[newShelves][newSections] = Book(ISBN, titulo, autor, año, disponible);
        }
    }
};


int main() {
    
    return 0;
}