#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>
#include <sstream>
#include <algorithm>


using namespace std;
using namespace std::chrono;

using Nodo = int;
using Arista = pair<Nodo, Nodo>;


int main() {
    //leer
    int c, oficina, distanciaMax, modems, precioUTP, precioFibra, x, y;
    vector<pair<int,int>> posiciones;
    vector<pair<double,double>> res;
    while (c--){
        cin >> oficina;
        cin >> distanciaMax;
        cin >> modems;
        cin >> precioUTP;
        cin >> precioFibra;
        for (int i =0; i<n; i++){
            cin >> x; cin >> y;
            posiciones.push_back(make_pair(x,y));
        }
        auto start = high_resolution_clock::now();

        res.push_back(algoritmo());

        // salida
        auto stop = high_resolution_clock::now();
        float tiempo = duration_cast<milliseconds>(stop - start).count(); //milisegundos
        tiempo = tiempo / 1000; // pasar a segundos
        cout << "tardo: " << tiempo << " seg\n";
    }

    for (int i=0; i<res.size();i++){
        cout << "Caso #" << i << ": " << setprecision(4) << res[i].first << " "  << setprecision(4) << res[i].second << endl;
    }

    return 0;
}
