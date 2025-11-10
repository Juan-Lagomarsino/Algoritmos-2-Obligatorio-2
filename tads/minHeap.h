#ifndef minHeap
#define minHeap

template <class T>
class Heap
{
public:
    virtual minHeap(int capacidadConstructora, bool (*_esMenor)(T, T)) = 0;

    virtual void agregar(T *nuevo) = 0;

    virtual T *sacarElDeArriba() = 0;

    virtual bool estaLleno() = 0;

    virtual bool estaVacio() = 0;
};

#endif