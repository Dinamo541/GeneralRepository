#include <iostream>
using namespace std;

template <class T>
class Fraccion {
public:
    T numerador;
    T denominador;
    Fraccion() {
        numerador = 0;
        denominador = 0;
    }
    Fraccion(T newNumerador, T newDenominador) : numerador(newNumerador), denominador(newDenominador) {}
    ~Fraccion() {}

    static Fraccion sumarValores(Fraccion<T> a, Fraccion<T> b) {
        Fraccion<T> r((a.numerador*b.denominador)+(b.numerador*a.denominador), (a.denominador*b.denominador));
        return r;
    }
    static Fraccion dividirValores(Fraccion<T> a, Fraccion<T> b) {
        try {
            if (a.denominador == 0 || b.numerador == 0)
                throw (-1);
            else {
                Fraccion<T> r(a.numerador * b.denominador, a.denominador * b.numerador);
                return r;
            }
            
        } catch (int error) {
            if (error == -1) {
                cout << "Error de division por cero";
                exit(error);
            }
        }
    }
    void printR() {
        printf("La fraccion es %f/%f", numerador, denominador);
    }
};


int main() {
    Fraccion<float> Uno(1.4, 2);
    Fraccion<float> Dos(1, 2);
    Fraccion<float> a = Fraccion<float>::dividirValores(Uno, Dos);
    Fraccion<float> b = Fraccion<float>::sumarValores(Uno, Dos);

    a.printR();
    cout << endl << endl;
    b.printR(); 
    
    return 0;
}