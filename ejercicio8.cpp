#include <cassert>
#include <string>
#include <iostream>
#include <limits>

using namespace std;
class crystalCascade
{
private:
    int largoA;
    int *arr;
    int ***memo;

    int funcionMemo(int i, int f, int k, int ***memo)
    {
        // Caso base
        if (i > f)
        {
            return 0;
        }
        if (i == f)
        {
            return (k + 1) * (k + 1);
        }
        if (memo[i][f][k] != -1)
        {
            return memo[i][f][k];
        }

        // Lo uso   {1,2,3,4,5}
        int val = (k + 1) * (k + 1) + funcionMemo(i + 1, f, 0, memo);

        // No lo uso
        int iterM = i + 1;
        while (iterM <= f)
        {
            if (arr[iterM] == arr[i])
            {
                val = max(val, funcionMemo(i + 1, iterM - 1, 0, memo) + funcionMemo(iterM, f, k + 1, memo));
            }
            iterM++;
        }

        memo[i][f][k] = val;
        return val;
    }

public:
    crystalCascade(int *f, int n)
    {
        largoA = n;
        arr = f;
        memo = new int **[n];
        for (int i = 0; i < n; i++)
        {
            memo[i] = new int *[n];
            for (int j = 0; j < n; j++)
            {
                memo[i][j] = new int[n];
                for (int k = 0; k < n; k++)
                {
                    memo[i][j][k] = -1;
                }
            }
        }
    }

    int resultado()
    {
        return funcionMemo(0, largoA - 1, 0, memo);
    }
};

int main()
{
    int N;    // N es la cantidad total de fragmentos
    cin >> N; // Los toma
    int *fragmentos = new int[N];

    for (int j = 0; j < N; j++)
    {
        int frag;
        cin >> frag;
        fragmentos[j] = frag;
    }
    crystalCascade *ejercicio8 = new crystalCascade(fragmentos, N);

    cout << ejercicio8->resultado() << endl;

    return 0;
}