#include <cassert>
#include <string>
#include <iostream>
#include <limits>
#include <climits>

using namespace std;
class busqueda
{
private:
    string **mat;
    int **sandbox;
    string busco;
    int filas;     // M filas
    int columnas;  // N columnas
    int mejorPaso; // Arranca en 0

public:
    busqueda(string **m, int **s, string b, int f, int c)
    {
        mat = m;
        sandbox = s;
        busco = b;
        filas = f;
        columnas = c;
        mejorPaso = 0;
    }
    bool esSolucion(int filaAc, int colAc)
    {
        return mat[filaAc][colAc] == busco;
    }

    bool coordenadaValida(int f, int c)
    {
        return f >= 0 && c >= 0 && f < filas && c < columnas && (mat[f][c] == "C" || mat[f][c] == busco);
    }

    bool puedoAplicarMovimiento(int fila, int col, int **sandbox)
    {
        return coordenadaValida(fila, col) && sandbox[fila][col] == 0;
    }

    void aplicarMovimiento(int fila, int col, int **sandbox, int paso)
    {
        sandbox[fila][col] = paso;
    }

    void deshacerMovimiento(int fila, int col, int **sandbox, int paso)
    {
        sandbox[fila][col] = 0;
    }

    bool mejorSolucion(int paso, int mejorPaso)
    {
        return paso < mejorPaso;
    }

    bool podemosPodar(int paso, int mejorPaso)
    {
        return paso > mejorPaso;
    }

    int buscoEnPasos(int **sandbox, int filaAc, int colAc, int paso, int &mejorPaso)
    {
        if (!podemosPodar(paso, mejorPaso))
        {
            if (esSolucion(filaAc, colAc) && mejorSolucion(paso, mejorPaso))
            {
                mejorPaso = paso;
            }
            else
            {
                int df[4] = {-1, 0, 1, 0};
                int dc[4] = {0, 1, 0, -1};
                for (int mov = 0; mov < 4; mov++)
                {
                    int nuevaFila = filaAc + df[mov];
                    int nuevaCol = colAc + dc[mov];
                    if (puedoAplicarMovimiento(nuevaFila, nuevaCol, sandbox))
                    {
                        aplicarMovimiento(nuevaFila, nuevaCol, sandbox, paso);
                        buscoEnPasos(sandbox, nuevaFila, nuevaCol, paso + 1, mejorPaso);
                        deshacerMovimiento(nuevaFila, nuevaCol, sandbox, paso);
                    }
                }
            }
        }
        return mejorPaso;
    }
};

int main()
{
    string S;
    int cantFC;
    cin >> S;
    cin >> cantFC;
    int FC = 0;
    int min = INT_MAX;

    for (int i = 0; i < cantFC; i++)
    {
        int f;
        int c;
        cin >> f >> c;

        string **mat = new string *[f]();
        for (int j = 0; j < f; j++)
        {
            mat[j] = new string[c]();
        }
        for (int j = 0; j < f; j++)
        {
            for (int n = 0; n < c; n++)
            {
                cin >> mat[j][n];
            }
        }

        int **sandbox = new int *[f]();
        for (int j = 0; j < f; j++)
        {
            sandbox[j] = new int[c]();
        }

        sandbox[0][0] = 1;

        busqueda *ejercicio10 = new busqueda(mat, sandbox, S, f, c);
        int mejorPaso = INT_MAX;

        int res = ejercicio10->buscoEnPasos(sandbox, 0, 0, 2, mejorPaso);

        if (res < min)
        {
            min = res;
            FC = i + 1;
        }
    }

    cout << FC << " " << min << endl;

    return 0;
}