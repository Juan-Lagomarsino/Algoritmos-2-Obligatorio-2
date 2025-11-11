#include <cassert>
#include <string>
#include <iostream>
#include <limits>

#ifndef minHeapImp
#define minHeapImp

#include "minHeap.h"
#include <cassert>

using namespace std;
template <class T>
    : public List<T> class minHeapImp
{ // Copio y pego del anterior obli
private:
    T **array;
    int proxLibre;
    int capacidad;
    bool (*esMenor)(T, T);

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
        T *aux = array[pos1];
        array[pos1] = array[pos2];
        array[pos2] = aux;
    }

    void flotar(int pos)
    {
        if (pos > 1)
        { // si no llegamos a la raiz
            int posPadre = padre(pos);
            if (esMenor(arr[pos], arr[posPadre]))
            {
                cambiarLugares(pos, posPadre);
                flotar(posPadre);
            }
        }
    }

    void hundir(int pos)
    {
        int posIzq = hIzq(pos);
        int posDer = hDer(pos);
        if (posIzq < proxLibre)
        { // tiene al menos un hijo (no es una hoja)
            int posHMenor = posIzq;
            if (posDer < proxLibre && esMenor(arr[posDer], arr[posIzq]))
            {                       // si tengo hijo derecho y es menor que el izquierdo
                posHMenor = posDer; // cambio el menor hijo
            }
            if (esMenor(arr[posHMenor], arr[pos]))
            { // si el menor de mis hijos es menor que yo, intercambio
                cambiarLugares(pos, posHMenor);
                hundir(posHMenor); // llamo de forma recursiva
            }
        }
    }

public:
    minHeap(int capacidadConstructora, bool (*_esMenor)(T, T))
    {
        array = new T *[capacidadConstructora + 1];
        proxLibre = 1;
        capacidad = capacidadConstructora;
        esMenor = _esMenor;
    }

    void agregar(T *nuevo)
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

    T *sacarElDeArriba()
    { // Capas que hay que sacarla, no se seguto si se usa todavia
        assert(!estaVacio());
        T *ret = array[1];
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

#endif