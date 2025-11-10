#include <cassert>
#include <string>
#include <iostream>
#include <limits>
// #include "tads/minHeap.h"

using namespace std;
struct nodoCalle
{
    int valor;
    nodoCalle *sig;
};

class SkatePropulsado
{
private:
    nodoCalle **calle;

public:
    SkatePropulsado(int amigo)
    {
        calle = new nodoCalle *[amigo + 1]; // Segun recuerdo el () te los pone todos en 0
        for (int i = 0; i <= amigo; i++)
        {
            nodoCalle *posicion = new nodoCalle();
            posicion->sig = NULL;
            posicion->valor = 0;
            calle[i] = posicion;
        }
    }
    void agregarPozo(int i, int d)
    {
        // -1 Signifca pozo
        for (int ponerPozosEn = i; ponerPozosEn < d; ponerPozosEn++)
        {
            calle[ponerPozosEn]->valor = -1;
        }
    }
    void agregarPotencia(int en, int cuanto)
    {
        // -1 Signifca pozo
        if (calle[en]->valor = !0)
        { // No checkeo que sea distinto a -1 porque no tendria sentido
            nodoCalle *concateno = new nodoCalle();
            concateno->sig = NULL;
            concateno->valor = cuanto;
            calle[en]->sig = concateno;
        }
        else
        { // Significa que si es 0
            calle[en]->valor = cuanto;
        }
    }
}

int
main()
{
    int N;              // N es la cantidad de pozos
    int M;              // M es la cantidad de mejoras disponibles
    int F;              // F es donde vive su amigo
    cin >> N >> M >> F; // Los toma
    SkatePropulsado ejercicio6 = new SkatePropulsado(F);
    for (int j = 0; i < N; j++)
    {
        int I;
        int D;
        cin >> I >> D;
        ejercicio6->agregarPozo(I, D);
    }

    for ()
        return 0;
}