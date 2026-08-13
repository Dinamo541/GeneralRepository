#include <iostream>
using namespace std;

int N;

int main(int argc, char *argv[])
{
    srand(time(NULL));

    N = 4;

    int *V[N];

    for (int i = 0; i < N; i++)
    {
        V[i] = new int(rand() % 100);

        cout << *V[i] << " ";
    }

    cout << endl
         << endl;

    for (int i = 0; i < 4; i++)
    {

        for (int j = 0; j < 4; j++)
        {
            cout << (*V[i]) * (j + 1) << " ";
        }

        cout << endl;
    }

    for (int i = 0; i < 4; i++)
    {
        delete V[i];
        V[i] = nullptr;
    }

    return 0;
}
