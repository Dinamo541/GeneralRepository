#include <iostream>

class Grades
{
private:
    int **grades = nullptr;
    int *average = nullptr;
    int majorGrade;
    int overEightyFive;
    int amountStudents;
    int amountNotes;
    std::string nombres;

public:
    Grades()
        : grades(nullptr), average(nullptr), majorGrade(0), overEightyFive(0), amountStudents(0), amountNotes(0), nombres("")
    {
    }
};

int main(int argc, char *argv[])
{
    int notas[3][5] = {
        {80, 75, 95, 85, 96},
        {85, 80, 82, 75, 93},
        {95, 90, 80, 70, 70}};
    int promedio;
    int mayor = notas[0][0];
    int contador = 0;

    for (int i = 0; i < 3; i++)
    {
        promedio = 0;

        if (i == 0)
            std::cout << "Carlos:\t";
        if (i == 1)
            std::cout << "María:\t";
        if (i == 2)
            std::cout << "Pedro:\t";

        for (int j = 0; j < 5; j++)
        {
            std::cout << notas[i][j] << "\t";

            promedio += notas[i][j];

            if (mayor < notas[i][j])
                mayor = notas[i][j];

            if (notas[i][j] < 85)
                contador++;
        }

        promedio = promedio / 5;

        std::cout << "Promedio: " << promedio << std::endl;
    }

    std::cout << "La nota mayor es: " << mayor << std::endl;

    std::cout << "La cantidad de notas mayores a 85 fueron: " << contador << std::endl;

    return 0;
}
