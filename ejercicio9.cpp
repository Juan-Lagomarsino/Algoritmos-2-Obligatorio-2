#include <cassert>
#include <string>
#include <iostream>
#include <limits>

struct archivo
{
    int tamanio;
    int linea;
    int puntos;
};

using namespace std;

int tab(archivo *arr, int N, int S, int L)
{
    int **tab = new int *[S + 1]();

    for (int s = 0; s <= S; s++)
        tab[s] = new int[L + 1]();

    for (int i = 0; i < N; i++)
    {
        int t = arr[i].tamanio;
        int l = arr[i].linea;
        int p = arr[i].puntos;

        for (int s = S; s >= t; s--)
        {
            for (int li = L; li >= l; li--){
                int nuevo = tab[s - t][li - l] + p;
                if(nuevo > tab[s][li]){
                    tab[s][li] = nuevo;
                }
            }
        }
    }
    return tab[S][L];
}

int main()
{
    int N;
    int S;
    int L;
    cin >> N;
    cin >> S;
    cin >> L;

    archivo *a = new archivo[N];
    for (int i = 0; i < N; i++)
    {
        int t;
        int l;
        int p;
        cin >> t >> l >> p;

        a[i].tamanio = t;
        a[i].linea = l;
        a[i].puntos = p;
    }

    cout << tab(a, N, S, L) << endl;
    return 0;
}