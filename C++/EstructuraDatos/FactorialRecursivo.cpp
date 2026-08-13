#include <iostream>
using namespace std;

int t = 0;

int recursiveFactorial(int n)
{
    if (n == 0)
        return 0;
    return n * recursiveFactorial(n - 1);
}

int cuadraticsSum(int n)
{
    if (n == 1)
        return 1;
    return n * n + cuadraticsSum(n - 1);
}

long fibonacci(long n)
{
    t++;
    if (n <= 0)
        return 0;
    t++;
    if (n == 1)
        return 1;
    t++;
    return fibonacci(n - 1) + fibonacci(n - 2);
}

unsigned long long A(int m, int n)
{
    if ((m != 0) && (n == 0))
    {
        t++;
        return A(m - 1, 1);
    }
    else if ((m != 0) && (n != 0))
    {
        t++;
        return A(m - 1, A(m, n - 1));
    }
    else if ((m == 0) && (n != 0))
    {
        t++;
        return n + 1;
    }
    t++;
    return 0ULL;
}

void moverDisco(const std::string &desde, const std::string &hacia)
{
    std::cout << "mover disco desde " << desde << " a " << hacia << '\n';
}

void moverTorre(int disco, const std::string &origen, const std::string &destino, const std::string &intermedio)
{
    if (disco == 0)
        return;
    if (disco == 1)
    {
        moverDisco(origen, destino);
        return;
    }
    moverTorre(disco - 1, origen, intermedio, destino);
    moverDisco(origen, destino);
    moverTorre(disco - 1, intermedio, destino, origen);
}

long A(long n)
{
    if (n == 0)
        return 5;
    if (n == 1)
        return 16;
    return (7 * A(n - 1)) - (10 * A(n - 2));
}

bool primoRecursivo(long long n, long long divisor = 3)
{
    if (n < 2)
        return false;
    if (n == 2)
        return true;
    if (n % 2 == 0)
        return false;
    if (divisor > n / divisor)
        return true;
    if (n % divisor == 0)
        return false;
    return primoRecursivo(n, divisor + 1);
}

long long potencia(long a, long n)
{
    if (a == 0 && n == 0)
        return -1LL;
    if (a == 0 && n != 0)
        return 0LL;
    if (a != 0 && n == 0)
        return 1LL;
    if (a != 0 && n != 0)
    {
        long m = a;
        for (int i = 1; i < n; i++)
        {
            a = a * m;
        }
        return a;
    }
    return -1LL;
}

int main(int argc, char *argv[])
{

    cout << primoRecursivo(29);

    return 0;
}
