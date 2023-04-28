#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>
#include <sstream>
#include <algorithm>
#include "numeroMagico.h"
#include "auxiliares.h"

using namespace std;
using namespace std::chrono;


int main() {
    //leer
//    string file;
    int n,k;
    cin >> n;
    cin >> k;
//    leerInstancia(file,n,k);

    //ejecutar y tomar el tiempo
    auto start = high_resolution_clock::now();

    //llamar al algoritmo//
    vector<NumeroMagico> cuadradosMagicos = generarCuadrados(n);
    sort(cuadradosMagicos.begin(), cuadradosMagicos.end(), comparador);

//    generar todas los cuadrados magicos posibles
//    for(int i = 0; i < cuadradosMagicos.size();i++){
//        NumeroMagico iEsimo = cuadradosMagicos[i];
//        cout << iEsimo << endl;
//    }
//    cout << "RESPUESTA!!!!!!!!" <<endl;

    if (k-1>=cuadradosMagicos.size()){
        cout << "-1" << endl;
    } else {
        NumeroMagico kEsimo = cuadradosMagicos[k-1];
        cout << kEsimo << endl;
    }
    auto stop = high_resolution_clock::now();
    float tiempo = duration_cast<milliseconds>(stop - start).count(); //milisegundos
    tiempo = tiempo / 1000; // pasar a segundos
    cout << "tardo: " << tiempo << " seg\n";

    return 0;
}
