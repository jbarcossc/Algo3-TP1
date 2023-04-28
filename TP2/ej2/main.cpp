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
    int n,m;
    Nodo v, w;
    cin >> n; cin >> m;
    vector<Arista> aristas;
    while (m--){
        cin >> v; cin >> w;
        aristas.push_back(make_pair(v,w));
    }


    //ejecutar y tomar el tiempo
    auto start = high_resolution_clock::now();

    //llamar al algoritmo//

    // salida
    auto stop = high_resolution_clock::now();
    float tiempo = duration_cast<milliseconds>(stop - start).count(); //milisegundos
    tiempo = tiempo / 1000; // pasar a segundos
    cout << "tardo: " << tiempo << " seg\n";

    return 0;
}
