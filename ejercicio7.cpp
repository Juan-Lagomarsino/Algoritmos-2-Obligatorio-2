#include <cassert>
#include <string>
#include <iostream>
#include <limits>

using namespace std;
struct nodoRankingOficial
{
    int pos;
    string nombre;
    nodoRankingOficial *sig;
    nodoRankingOficial(string _clave, int _valor) : nombre(_clave), pos(_valor), sig(NULL) {};
};

// SOn lo mismo, la verdad podrian ser la misma struct hago dos para claridad de codigo
// class tablaHashOficial
// Copiada y pegada
class tablaHashOfical // abierta
{
private:
    // atributos
    nodoRankingOficial **arr;
    int B;
    int N;
    // metodos privados
    int normalizar(int a)
    {
        return abs(a) % B;
    }
    int hash(string key)
    {
        int h = 0;
        for (int i = 0; i < key.length(); i++)
            h = 31 * h + int(key[i]);
        return h;
    }
    void insertarRec(nodoRankingOficial *&nodo, string _clave, int _valor)
    {
        if (nodo == NULL)
        {
            nodo = new nodoRankingOficial(_clave, _valor);
            N++;
        }
        else
        {
            if (nodo->nombre == _clave)
            {
                nodo->pos = _valor;
            }
            else
            {
                insertarRec(nodo->sig, _clave, _valor);
            }
        }
    }

    bool existeRec(nodoRankingOficial *nodo, string _clave)
    {
        if (nodo == NULL)
        {
            return false;
        }
        else
        {
            if (nodo->nombre == _clave)
            {
                return true;
            }
            else
            {
                return existeRec(nodo->sig, _clave);
            }
        }
    }

    int consultarRec(nodoRankingOficial *nodo, string _clave)
    {
        if (nodo->nombre == _clave)
        {
            return nodo->pos;
        }
        else
        {
            return consultarRec(nodo->sig, _clave);
        }
    }

public:
    // constructor
    tablaHashOfical(int _capacidad)
    {
        B = _capacidad;
        arr = new nodoRankingOficial *[B]();
        N = 0;
        for (int i = 0; i < B; i++)
        {
            arr[i] = NULL;
        }
    }

    void insertar(string clave, int valor)
    {
        assert(!estaLlena());
        int hash = this->hash(clave);
        int pos = normalizar(hash);          // ahora aseguramos que pos esta entre 0 y B-1
        insertarRec(arr[pos], clave, valor); // operar sobre la lista
    }

    bool existe(string clave)
    {
        int hash = this->hash(clave);
        int pos = normalizar(hash);        // ahora aseguramos que pos esta entre 0 y B-1
        return existeRec(arr[pos], clave); // operar sobre la lista
    }

    int consultar(string clave)
    {
        assert(existe(clave));
        int hash = this->hash(clave);
        int pos = normalizar(hash);           // ahora aseguramos que pos esta entre 0 y B-1
        return consultarRec(arr[pos], clave); // operar sobre la lista
    }

    bool estaLlena()
    {
        return false;
    }

    float factorDeCarga()
    {
        return (float)this->N / this->B;
    }
};

class rankingDAC
{
private:
    int N; // cantidad de estudiantes
    tablaHashOfical *rankingOficial;
    int *rankingAyudante;
    int iterRankings;
    long long cantidadCambios;

public:
    rankingDAC(int n)
    {
        N = n;
        rankingAyudante = new int[n];
        rankingOficial = new tablaHashOfical(n);
        cantidadCambios = 0;
    };
    void agregarARankingOficial(string nombre, int lugar)
    {
        rankingOficial->insertar(nombre, lugar);
    };
    void agregarARankingAyudante(string nombre, int lugar)
    {
        rankingAyudante[lugar] = rankingOficial->consultar(nombre);
    };

    int *intercalar(int arr1[], int n1, int arr2[], int n2)
    {
        int *ret = new int[n1 + n2];

        int i = 0, j = 0, k = 0;
        while (i < n1 && j < n2)
        {
            if (arr1[i] < arr2[j]) // Si es iuual o menor igual los dos corren las pruebas. asi que no tengo ni idea
            {
                ret[k++] = arr1[i++];
            }
            else
            {
                ret[k++] = arr2[j++];
                cantidadCambios += (n1 - i);
            }
        }

        while (i < n1)
        {
            ret[k++] = arr1[i++];
        }

        while (j < n2)
        {
            ret[k++] = arr2[j++];
        }

        return ret;
    }

    int *mergeSort(int *valores, int inicio, int fin)
    {
        if (inicio == fin)
        {

            int *ret = new int[1];
            ret[0] = valores[inicio];
            return ret;
        }
        int mitad = (inicio + fin) / 2;

        int *ord1 = mergeSort(valores, inicio, mitad);
        int *ord2 = mergeSort(valores, mitad + 1, fin);

        int n1 = mitad - inicio + 1;
        int n2 = fin - mitad;

        return intercalar(ord1, n1, ord2, n2);
    }

    void cantidadCambiosFin()
    {
        mergeSort(rankingAyudante, 0, N - 1);
        cout << cantidadCambios << endl;
    }
};

int main()
{
    int N;    // N es la cantidad de estudidantes
    cin >> N; // Los toma
    rankingDAC *ejercicio7 = new rankingDAC(N);
    for (int j = 0; j < N; j++)
    {
        string rankingOficial;
        cin >> rankingOficial;
        ejercicio7->agregarARankingOficial(rankingOficial, j);
    }
    for (int j = 0; j < N; j++)
    {
        string rankingAyudante;
        cin >> rankingAyudante;
        ejercicio7->agregarARankingAyudante(rankingAyudante, j);
    }
    ejercicio7->cantidadCambiosFin();
    return 0;
}