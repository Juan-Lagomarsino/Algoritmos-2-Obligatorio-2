#include <cassert>
#include <string>
#include <iostream>
#include <limits>

struct nodoAyuda
{
    int donde;
    int potencia;
};

struct nodoPozo
{
    int empieza;
    int termina;
};

// maxHeap
using namespace std;
class maxHeap
{ // Copio y pego del anterior obli
private:
    nodoAyuda **array;
    int proxLibre;
    int capacidad;
    bool (*esMenor)(nodoAyuda, nodoAyuda);

    // https://heap.uruguayan.ninja/15
    int hijoIzq(int i)
    {
        return 2 * i;
    }
    int hijoDer(int i)
    {
        return 2 * i + 1;
    }
    int padre(int i)
    {
        return i / 2;
    }

    void cambiarLugares(int pos1, int pos2)
    {
        nodoAyuda *aux = array[pos1];
        array[pos1] = array[pos2];
        array[pos2] = aux;
    }

    void flotar(int pos)
    {
        if (pos > 1)
        { // si no llegamos a la raiz
            int posPadre = padre(pos);
            if (array[pos]->potencia > array[posPadre]->potencia)
            {
                cambiarLugares(pos, posPadre);
                flotar(posPadre);
            }
        }
    }

    void hundir(int pos)
    {
        int posIzq = hijoIzq(pos);
        int posDer = hijoDer(pos);
        if (posIzq < proxLibre)
        { // tiene al menos un hijo (no es una hoja)
            int posHMenor = posIzq;
            if (posDer < proxLibre && array[posDer]->potencia > array[posIzq]->potencia)
            {                       // si tengo hijo derecho y es menor que el izquierdo
                posHMenor = posDer; // cambio el menor hijo
            }
            if (array[posHMenor]->potencia > array[pos]->potencia)
            { // si el menor de mis hijos es menor que yo, intercambio
                cambiarLugares(pos, posHMenor);
                hundir(posHMenor); // llamo de forma recursiva
            }
        }
    }

public:
    maxHeap(int capacidadConstructora)
    {
        array = new nodoAyuda *[capacidadConstructora + 1];
        proxLibre = 1;
        capacidad = capacidadConstructora;
    }

    void agregar(nodoAyuda *nuevo)
    {
        assert(!estaLleno()); // No se deberia llamar si esta lleno, pero entiendo que la letra no lo hace, porque no hace trampa
        if (nuevo == NULL)
        {
            return;
        }
        array[proxLibre] = nuevo;
        proxLibre++;
        flotar(proxLibre - 1);
    }

    nodoAyuda *sacarElDeArriba()
    { // Capas que hay que sacarla, no se seguto si se usa todavia
        assert(!estaVacio());
        nodoAyuda *ret = array[1];
        array[1] = array[--proxLibre];
        hundir(1);
        return ret;
    }

    bool estaLleno()
    {
        return proxLibre > capacidad;
    }

    bool estaVacio()
    {
        return proxLibre == 1;
    }
};

using namespace std;
class SkatePropulsado
{
private:
    nodoAyuda **ayudas;
    nodoPozo **pozos;
    int posPozo;
    maxHeap *comparoPozos;
    int pideA;
    bool sePuede;

    int llegaPidiendo()
    {
        int salto = pozos[posPozo]->termina - pozos[posPozo]->empieza + 1; // Discreta core
        for (int i = posPozo; i < pozos[posPozo]->empieza; i++)
        {
            if (ayudas[i] != NULL)
            {
                comparoPozos->agregar(ayudas[i]);
            }
        }
        posPozo = pozos[posPozo]->termina;
        int necesita = 0;
        int lePideA = 0;
        while (necesita < salto)
        {
            nodoAyuda *aux = comparoPozos->sacarElDeArriba();
            if (aux == NULL && necesita < salto)
            {
                sePuede = false;
                return; // Si llega a no ser es un break
            }
            necesita += aux->potencia;
            lePideA++;
        }
    }

public:
    SkatePropulsado(int cantAyudas, int cantPozos, int amigo)
    {
        ayudas = new nodoAyuda *[cantAyudas];
        pozos = new nodoPozo *[cantPozos];
        for (int x = 0; x < cantAyudas; x++)
        {
            ayudas[x] = NULL;
        }
        for (int x = 0; x < cantPozos; x++)
        {
            pozos[x] = NULL;
        }
        posPozo = 0;
        comparoPozos = new maxHeap(cantAyudas);
        sePuede = true;
    }
    void agregarPozo(int i, int d, int j)
    {
        nodoPozo *pozo = new nodoPozo();
        pozo->empieza = i;
        pozo->termina = d;
        pozos[j] = pozo;
    }
    void agregarPotencia(int en, int cuanto, int k)
    {
        nodoAyuda *ayuda = new nodoAyuda();
        ayuda->donde = en;
        ayuda->potencia = cuanto;
        ayudas[k] = ayuda;
    }
    int minimasAyudas()
    {
    }
};

int main()
{
    int N;              // N es la cantidad de pozos
    int M;              // M es la cantidad de mejoras disponibles
    int F;              // F es donde vive su amigo
    cin >> N >> M >> F; // Los toma
    SkatePropulsado *ejercicio6 = new SkatePropulsado(N, M, F);
    for (int j = 0; j < N; j++)
    {
        int I;
        int D;
        cin >> I >> D;
        ejercicio6->agregarPozo(I, D, j);
    }
    for (int k = 0; k < M; k++)
    {
        int X;
        int P;
        cin >> X >> P;
        ejercicio6->agregarPotencia(X, P, k);
    }

    cout << ejercicio6->minimasAyudas() << endl;
    return 0;
}