#include <iostream>
#include <string>

class Vehicles {
protected:
    std::string brand;
    std::string model;
    int year;

public:
    Vehicles(std::string newBrand, std::string newModel, int newYear)
    : brand(newBrand), model(newModel), year(newYear) {}
    Vehicles() : brand(" "), model(" "), year(0) {}

    virtual ~Vehicles() {}

    virtual void showInfo() {
        printf("| Marca: %s\n", brand.c_str());
        printf("| Modelo: %s\n", model.c_str());
        printf("| Anio: %d\n", year);
    }

    virtual void fillGas() {
        printf("%s %s esta llenando con gasolina\n", model.c_str(), brand.c_str());
    }
};

class Cars : public Vehicles {
private:
    int doorsNumber;
    std::string gasType;

public:
    Cars(std::string newBrand, std::string newModel, int newYear, int newDoorsNumber, std::string newGasType)
    : Vehicles(newBrand, newModel, newYear), doorsNumber(newDoorsNumber), gasType(newGasType) {}

    ~Cars() {}

    void showInfo() override {
        Vehicles::showInfo();
        printf("| Puertas: %d\n", doorsNumber);
        printf("| Gasolina: %s\n", gasType.c_str());
    }
};

class Motos : public Vehicles {
private:
    int cylinderCapacity;
    std::string motoType;

public:
    Motos(std::string newBrand, std::string newModel, int newYear, int newCylinderCapacity, std::string newMotoType)
    : Vehicles(newBrand, newModel, newYear), cylinderCapacity(newCylinderCapacity), motoType(newMotoType) {}

    ~Motos() {}

    void showInfo() override {
        Vehicles::showInfo();
        printf("| Cilindraje: %d\n", cylinderCapacity);
        printf("| Typo de moto: %s\n", motoType.c_str());
    }
};

class Trucks : public Vehicles {
private:
    int tonCapacity;
    int axleNumbers;

public:
    Trucks(std::string newBrand, std::string newModel, int newYear, int newTonCapacity, int newAxleNumbers)
    : Vehicles(newBrand, newModel, newYear), tonCapacity(newTonCapacity), axleNumbers(newAxleNumbers) {}

    ~Trucks() {}

    void showInfo() override {
        Vehicles::showInfo();
        printf("| Toneladas: %d\n", tonCapacity);
        printf("| Ejes: %d\n", axleNumbers);
    }
};

int main() {
    int size = 0, option = 0;

    printf("Cuantos vehiculos desea registrar: ");
    scanf("%d", &size);

    Vehicles** vehicles = new Vehicles*[size];
    for (int i = 0; i < size; i++) {
        printf("Cual va a ser el vehiculo de la posicion %d\n", i + 1);
        printf("1. Carro\n");
        printf("2. Moto\n");
        printf("3. Camion\n");
        scanf("%d", &option);
        if (option == 1) {
            vehicles[i] = new Cars("GT3", "RedBull", 2017, 2, "Especial");
        } else if (option == 2) {
            vehicles[i] = new Motos("GT3", "RedBull", 2017, 4, "Meado");
        } else {
            vehicles[i] = new Trucks("GT3", "RedBull", 2017, 2, 6);
        }
    }
    for (int i = 0; i < size; i++) {
        vehicles[i]->showInfo();
        printf("\n");
        delete vehicles[i];
    }
    delete[] vehicles;
    return 0;
}