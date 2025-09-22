#include <iostream>
#include <cstdlib>
#include <ctime>

class colleccion {
private: 
    int farm[9][4];

public:
    colleccion() {
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 4; j++) {
                farm[i][j] = -1;
            }
        }
    }


    void printFarm() {
        std::cout << "Primera columna hortensias, segunda columna rosas, tercera columna tulipanes, cuarta columna helechos" << std::endl;
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 4; j++) {
                std::cout << farm[i][j];
                std::cout << "     ";
            }
            std::cout << std::endl;
        }
    }

    //2
    void clearFarm() {
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 4; j++) {
                farm[i][j] = -1;
            }
        }
    }

    //3
    void sow() {
        int plant = 0;
        std::cout << "Dijite 1 para plantar las hortensias, 2 para plantar las rosas, 3 para plantar los tulipanes o 4 para plantar los helechos" << std::endl;
        std::cin >> plant;
        plant--;
        for (int i = 0; i < 9; i++) {
            farm[i][plant] = 0;
        }
    }

    //4
    void sleep() {
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 4; j++) {
                if ((farm[i][j] > -1) && (farm[i][j] < 3)) {
                    if (farm[i][j] == 2) {
                        farm[i][j] = farm[i][j]++;
                    }
                    if (farm[i][j] == 0) {
                        farm[i][j] = farm[i][j]+2;
                    }
                    
                }
            }
        }
    }

    //5
    void randomPlantStages() { //Preguntar a Andersoon 
        int randomNum = 0;
        std::srand(time(0)); // Inicializa la semilla con la hora actual
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 4; j++) {
                randomNum = 1 + std::rand() % 4; // Número aleatorio entre 0 y 3
                farm[i][j] = randomNum;
            }
        }
    }

    //6
    int numberOfPlantsOfSpecificPlantReadyToHarvest(int plantOpcion) {
        int numberOfPlants = 0;
        plantOpcion--;
        for (int i = 0; i < 9; i++) {
            if (farm[i][plantOpcion] == 3) {
                numberOfPlants++;
            }
        }
        return numberOfPlants;
    }

    //7 
    int numberOfPlantsReadyToHarvest() {
        int numberOfPlants = 0;
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 4; j++) {
                if (farm[i][j] == 3) {
                    numberOfPlants++;
                }
            }
        }
        return numberOfPlants;
    }

    //8
    void valueOfPlants() {
        std::cout << "Cada hortensia vale = 2000 colones" << std::endl << "Cada rosa vale = 1000 colones" << std::endl << "Cada tulipan vale = 3000 colones" << std::endl
            << "Cada helecho vale = 500";
    }

    //9
    int valueOfSpecificPlant(int plantOpcion) {
        switch (plantOpcion)
        {
        case 1:
            return numberOfPlantsOfSpecificPlantReadyToHarvest(plantOpcion) * 2000;
            break;

        case 2:
            return numberOfPlantsOfSpecificPlantReadyToHarvest(plantOpcion) * 1000;
            break;

        case 3:
            return numberOfPlantsOfSpecificPlantReadyToHarvest(plantOpcion) * 3000;
            break;

        case 4:
            return numberOfPlantsOfSpecificPlantReadyToHarvest(plantOpcion) * 500;
            break;
        
        default:
            return 0;
        }
    }
    
    //10
    int valueOfPlantsInASpecificFurrow(int furrow) {
        int result = 0;
        furrow--;
        for (int j = 0; j < 4; j++) {
            if (farm[furrow][j] == 3) {
                switch (j)
                {
                case 0: 
                    result += 2000; 
                    break;

                case 1:
                    result += 1000;
                    break;

                case 2:
                    result += 3000;
                    break;

                case 3:
                    result += 500;
                    break;

                default:
                    break;
                }
            }
        }
        return result;
    }

    //12

    void cleanHorizontalRangeofFurrows(int firstFurrow, int endFurrow) {
        firstFurrow--;
        endFurrow--;
        
        if (firstFurrow == endFurrow) {
            for (int j = 0; j < 4; j++) {
                farm[firstFurrow][j] = -1;
            }
        }
        
        for (int i = firstFurrow; i < endFurrow; i++) {
            for (int j = 0; j < 4; j++) {
                farm[i][j] = -1;
            }
        }
    }

    //13
    
    void transplantPlantsToTheSecondPlot(colleccion& farm2, int plantOpcion) {
        plantOpcion--;
        for (int i = 0; i < 9; i++) {
            if (farm[i][plantOpcion] != -1) {
                farm2.farm[i][plantOpcion] = farm[i][plantOpcion];
                farm[i][plantOpcion] = -1;
            }
        }
    }
    
};

void printMenu() {
    std::cout << "0 = Salir del sisrema" << std::endl << "1 = Mostrar la granja" << std::endl << "2 = Eliminar el cultivo" << std::endl
        << "3 = Sembrar" << std::endl << "4 = Pasar el tiempo" << std::endl << "5 = Plantar las plantas en etapas aleatorias" << std::endl << 
        "6 = Contar cuantas plantas de una planta en especifico estan listas para cosechar" << std::endl << "7 = Contar todas las plantas listas para cosechar" << std::endl <<
        "8 = Ver precio undiviual de cada planta" << std::endl << "9 = Calcular el valor total de todas las plantas de una planta en especifica listas para cosechar" << std::endl
        << "10 = Calcular el valor de un zurco en horizonal" << std::endl << "11 = Limpiar un rango zurcos horizontales" << std::endl << "12 = Trasplantar plantas a otro terreno" 
        << std::endl;
}

//Empieza el main &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&

int main()
{
    int opcion = 1, plantOpcion = 0, furrow = 0, firsFurrow = 0, endFurrow = 0;
    colleccion farm1;
    colleccion farm2;
    std::cout << "Ingrese Enter para comenzar";
    std::cin.get();
    system("cls");

    while (opcion != 0) {
        std::cout << "Seleccione la opcion que desea realizar" << std::endl << std::endl;
        printMenu();
        std::cin >> opcion;
        system("cls");
        while ((opcion < 0) || (opcion > 12)) { // Numero de opciones
            std::cout << "Digite un valor valido" << std::endl;
            printMenu();
            std::cin >> opcion;
            system("cls");
        }
        system("cls");

        switch (opcion)
        {
        case 1:
            farm1.printFarm();
            std::cout << "Ingrese Enter para continuar";
            std::cin.get();
            std::cin.get();
            system("cls");
            break;

        case 2:
            farm1.clearFarm();
            std::cout << "El cultivo se elimino con exito";
            std::cout << std::endl << "Ingrese Enter para continuar";
            std::cin.get();
            std::cin.get();
            system("cls");
            break;

        case 3:
            farm1.sow();
            std::cout << "Se sembro correctamente";
            std::cout << std::endl << "Ingrese Enter para continuar";
            std::cin.get();
            std::cin.get();
            system("cls");
            break;

        case 4:
            farm1.sleep();
            std::cout << "Ha pasado el tiempo";
            std::cout << std::endl << "Ingrese Enter para continuar";
            std::cin.get();
            std::cin.get();
            system("cls");
            break;

        case 5:
            farm1.randomPlantStages();
            std::cout << "Se plantaron las plantas en etapas aleatorias";
            std::cout << std::endl << "Ingrese Enter para continuar";
            std::cin.get();
            std::cin.get();
            system("cls");
            break;

        case 6:
            std::cout << "Ingrese la opcion de la planta que quiere contar" << std::endl << " Dijite 1 para hortensias, 2 para rosas, 3 para tulipanes o 4 para helechos" << std::endl;
            std::cin >> plantOpcion;
            while ((plantOpcion < 1) || (plantOpcion > 4)) {
                std::cout << "Digite una opcion valida" << std::endl;
                std::cout << "Ingrese la opcion de la planta que quiere contar" << "Dijite 1 para hortensias, 2 para rosas, 3 para tulipanes o 4 para helechos" << std::endl;
                std::cin >> plantOpcion;
            }
            std::cout << "Hay " << farm1.numberOfPlantsOfSpecificPlantReadyToHarvest(plantOpcion) << " listas para cosechar";
            std::cout << std::endl << "Ingrese Enter para continuar";
            std::cin.get();
            std::cin.get();
            system("cls");
            break;

        case 7:
            std::cout << "Hay " << farm1.numberOfPlantsReadyToHarvest() << " listas para cosechar";
            std::cout << std::endl << "Ingrese Enter para continuar";
            std::cin.get();
            std::cin.get();
            system("cls");
            break;

        case 8:
            farm1.valueOfPlants();
            std::cout << std::endl << "Ingrese Enter para continuar";
            std::cin.get();
            std::cin.get();
            system("cls");
            break;

        case 9:
            std::cout << "Ingrese la opcion de la planta que quiere averiguar el monto total de las plantas listas" << std::endl
                << " Dijite 1 para hortensias, 2 para rosas, 3 para tulipanes o 4 para helechos" << std::endl;
            std::cin >> plantOpcion;
            while ((plantOpcion < 1) || (plantOpcion > 4)) {
                std::cout << "Digite una opcion valida" << std::endl;
                std::cout << "Ingrese la opcion de la planta que quiere contar" << "Dijite 1 para hortensias, 2 para rosas, 3 para tulipanes o 4 para helechos" << std::endl;
                std::cin >> plantOpcion;
            }
            std::cout << "El valor total es " << farm1.valueOfSpecificPlant(plantOpcion);
            std::cout << std::endl << "Ingrese Enter para continuar";
            std::cin.get();
            std::cin.get();
            system("cls");
            break;

        case 10:
            std::cout << "Ingrese el numero del zurco que desea averiguar el valor " << std::endl;
            std::cin >> furrow;
            while ((furrow < 1) || (furrow > 4)) {
                std::cout << "Zurco invalido, ingrese un zurco valido" << std::endl;
                std::cin >> furrow;
            }
            std::cout << "El valor total del zurco es " << farm1.valueOfPlantsInASpecificFurrow(furrow);
            std::cout << std::endl << "Ingrese Enter para continuar";
            std::cin.get();
            std::cin.get();
            system("cls");
            break;

        case 11:
            std::cout << "Dijite el surco inicial desde el cual quiere eliminar" << std::endl;
            std::cin >> firsFurrow;
            while ((firsFurrow < 1) || (firsFurrow > 9)) {
                std::cout << "Zurco invalido, ingrese un zurco valido" << std::endl;
                std::cin >> furrow;
            }
            std::cout << "Dijite el surco final el cual quiere eliminar" << std::endl;
            std::cin >> endFurrow;
            while ((endFurrow < 1) || (endFurrow > 9)) {
                std::cout << "Zurco invalido, ingrese un zurco valido" << std::endl;
                std::cin >> furrow;
            }
            farm1.cleanHorizontalRangeofFurrows(firsFurrow, endFurrow);
            std::cout << "Los surcos fueron borrados con exito";
            std::cout << std::endl << "Ingrese Enter para continuar";
            std::cin.get();
            std::cin.get();
            system("cls");
            break;
        case 12:           
            std::cout << "Seleccione el tipo de planta que desea transplantar" << " Dijite 1 para hortensias, 2 para rosas, 3 para tulipanes o 4 para helechos" << std::endl;
            std::cin >> plantOpcion;
            while ((plantOpcion < 1) || (plantOpcion > 4)) {
                std::cout << "Digite una opcion valida" << std::endl;
                std::cout << "Ingrese la opcion de la planta que quiere contar" << "Dijite 1 para hortensias, 2 para rosas, 3 para tulipanes o 4 para helechos" << std::endl;
                std::cin >> plantOpcion;
            }
            farm1.transplantPlantsToTheSecondPlot(farm2, plantOpcion);
            farm1.printFarm();
            farm2.printFarm();
            std::cout << std::endl << "Ingrese Enter para continuar";
            std::cin.get();
            std::cin.get();
            system("cls");
            break;
        default:
            break;
        }
    }
    std::cout << "gracias por usar el sistema" << std::endl;
    std::cout << "Aguante Verstappen" << std::endl;
    return 0;
}