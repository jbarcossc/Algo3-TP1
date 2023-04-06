#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>
#include <sstream>
#include "numeroMagico.h"
#include "auxiliares.h"

using namespace std;
using namespace std::chrono;




void leerInstancia(string &file, int &n, int &k){
    fstream instancia;
    instancia.open(file, ios::in);
    if (instancia.is_open()){
        instancia >> n;
        instancia >> k;
    }
    instancia.close();
}


int main() {
    //leer
    string file;
    int n,k;
    leerInstancia(file,n,k);

    //ejecutar y tomar el tiempo
    auto start = high_resolution_clock::now();
    numeroMagico res(n);
    //llamar al algoritmo//

    auto stop = high_resolution_clock::now();
    float tiempo = duration_cast<milliseconds>(stop - start).count();
    tiempo = tiempo / 1000;
    //SOLO IMPRIMIR EN PANTALLA EL RESULTADO!!!
    cout << res << "\n tardo: " << tiempo << " seg\n";

    return 0;
}
