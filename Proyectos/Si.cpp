#include <iostream>

class Materiales {
protected:
    std::string titulo;
    int annioDePublicacion;

public:
    Materiales() {
        titulo = "Desconocido";
        annioDePublicacion = 1000;
    }
    Materiales(std::string newTitulo, int newAnnioDePublicacion) {
        titulo = newTitulo;
        annioDePublicacion = newAnnioDePublicacion;
    }
    ~Materiales() {}
    virtual void mostrarInfo() = 0;
};

class Libros : public Materiales {
private:
    std::string nombreAutor;
    int numeroDePaginas;

public:
    Libros()
        : Materiales() {
        numeroDePaginas = 0;
        nombreAutor = "Desconocido";
    }
    Libros(std::string newTitulo, int newAnnioDePublicacion, int newNumeroDePaginas, std::string newNombreAutor)
        : Materiales(newTitulo, newAnnioDePublicacion) {
        numeroDePaginas = newNumeroDePaginas;
        nombreAutor = newNombreAutor;
    }
    ~Libros() {}

    void mostrarInfo() {
        std::cout << "Tipo: Libro" << std::endl
            << "Titulo: " << titulo << std::endl
            << "Annio de Publicacion: " << annioDePublicacion << std::endl
            << "Numero de Paginas: " << numeroDePaginas << std::endl
            << "Nombre del Autor: " << nombreAutor << std::endl;
    }
};

class Revistas : public Materiales {
private:
    std::string editorial;
    int numeroDeEdicion;

public:
    Revistas()
        : Materiales() {
        numeroDeEdicion = 0;
        editorial = "Desconocido";
    }
    Revistas(std::string newTitulo, int newAnnioDePublicacion, int newNumeroDeEdicion, std::string newEditorial)
        : Materiales(newTitulo, newAnnioDePublicacion) {
        numeroDeEdicion = newNumeroDeEdicion;
        editorial = newEditorial;
    }
    ~Revistas() {}

    void mostrarInfo() {
        std::cout << "Tipo: Revista" << std::endl
            << "Titulo: " << titulo << std::endl
            << "Annio de Publicacion: " << annioDePublicacion << std::endl
            << "Numero de Edicion: " << numeroDeEdicion << std::endl
            << "Nombre del Editorial: " << editorial << std::endl;
    }
};

class Peliculas : public Materiales {
private:
    std::string nombreDirector;
    int duracionEnMinutos;

public:
    Peliculas()
        : Materiales() {
        duracionEnMinutos = 0;
        nombreDirector = "Desconocido";
    }
    Peliculas(std::string newTitulo, int newAnnioDePublicacion, int newDuracionEnMinutos, std::string newDirector)
        : Materiales(newTitulo, newAnnioDePublicacion) {
        duracionEnMinutos = newDuracionEnMinutos;
        nombreDirector = newDirector;
    }
    ~Peliculas() {}

    void mostrarInfo() {
        std::cout << "Tipo: Pelicula" << std::endl
            << "Titulo: " << titulo << std::endl
            << "Annio de Publicacion: " << annioDePublicacion << std::endl
            << "Duracion en Minutos: " << duracionEnMinutos << std::endl
            << "Nombre del Director: " << nombreDirector << std::endl;
    }
};

class Biblioteca {
private:
    int tamannio;
    Materiales** materiales;

public:
    Biblioteca() {
        tamannio = 1;
        materiales = new Materiales * [tamannio];
    }
    Biblioteca(int newTamannio) {
        tamannio = newTamannio;
        materiales = new Materiales * [tamannio];
        for (int i = 0; i < tamannio; i++) {
            int tipo;
            printf("Elija el tipo de Matrial en la posicion %d\n", i + 1);
            printf("1. Libro\n");
            printf("2. Revistas\n");
            printf("3. Peliculas\n");
            std::cin >> tipo;
            if (tipo == 1) {
                materiales[i] = new Libros();
            } else if (tipo == 2) {
                materiales[i] = new Revistas();
            } else {
                materiales[i] = new Peliculas();
            }
        }
    }
    ~Biblioteca() {}

    void mostrarTodos() {
        for (int i = 0; i < tamannio; i++) {
            materiales[i]->mostrarInfo();
            std::cout << "------------------------" << std::endl;
        }
    }

};

int main() {
    Biblioteca biblioteca(3);
    biblioteca.mostrarTodos();
    return 0;
}