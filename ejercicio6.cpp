#include <cassert>
#include <string>
#include <iostream>
#include <limits>

using namespace std;
struct nodoCalle {
    int valor;
    nodoCalle* sig;
}

class SkatePropulsado{
    private:
        int* nodoCalle;
    public: 
        SkatePropulsado(int amigo){
            calle = new nodoCalle[amigo+1]; // Segun recuerdo el () te los pone todos en 0
            for(int i = 0 ; i<=amigo ; i++){
                nodoCalle[i]=NULL;
            }
        }
        agregarPozo(int i, int d){
            // -1 Signifca pozo
            for(int ponerPozosEn = i ; ponerPozosEn< d ; ponerPozosEn++){
                nodoCalle* pozo = new nodoCalle();
                calle[ponerPozosEn]=-1;
            }
        }
        agregarPotencia(int en, int Cuanto){
            // -1 Signifca pozo
            for(int ponerPozosEn = i ; ponerPozosEn< d ; ponerPozosEn++){
                calle[ponerPozosEn]=-1;
            }
        }
}


int main()
{
    int N; // N es la cantidad de pozos
    int M; // M es la cantidad de mejoras disponibles
    int F; // F es donde vive su amigo
    cin >> N >> M >> F; // Los toma
    SkatePropulsado ejercicio6 = new SkatePropulsado(F); 
    for(int j = 0; i<N ; j++){
        int I;
        int D;
        cin >> I >> D;
        ejercicio6->agregarPozo(I,D);
    }

    for()
    return 0;
}