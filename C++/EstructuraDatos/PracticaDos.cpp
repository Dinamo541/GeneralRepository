#include <iostream>
using namespace std;

const int N = 5;

int main(int argc, char *argv[])
{

    int t = 0;

    int *V[N];
    t++;

    int **M[N];
    t++;

    t += 2 * N + 2;
    for (int i = 0; i < N; i++)
    {
        V[i] = new int(rand() % 100);
        t++;

        cout << *V[i] << " ";

        M[i] = new int *[N];
        for (int j = 0; j < N; j++) {
            M[i][j] = new int;
        }

        t++;
    }

    t += 2 * N + 2;
    for (int i = 0; i < N; i++)
    {

        M[i][i] = V[i];

        t += 2 * N + 2;
        for (int j = 0; j < N; j++)
        {

            if (i < j)
            {
                t++;

                *M[i][j] = *M[i][j - 1] * 2;
                t++;
            }
            else if (j < i)
            {
                t++;

                *M[i][j] = *M[i][i] - (i - j);
                t++;
            }

            cout << *M[i][j] << " ";
            t++;
        }
        cout << endl;
        t++;
    }

    cout << endl
         << t;

    return 0;
}
