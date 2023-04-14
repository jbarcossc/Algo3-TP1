#include <iostream>
#include <vector>
#include <chrono>
#include <algorithm>
#include "actividadades.h"

using namespace std;
using namespace std::chrono;


int main() {
    //leer
    int n; cin >> n;
    int s,t;
    vector<pair<int,int>> tasks;
    while (n--){
        cin >> s;
        cin >> t;
        tasks.push_back(make_pair(s,t));
    }

    //ejecutar y tomar el tiempo
    auto start = high_resolution_clock::now();

    //llamar al algoritmo//
    vector<int> res = greedy(tasks);

    auto stop = high_resolution_clock::now();
    float tiempo = duration_cast<milliseconds>(stop - start).count(); //milisegundos
    tiempo = tiempo / 1000; // pasar a segundos

    //imprimir el resultado
    cout << res.size() << endl;
    for (int i=0;i<res.size();i++){
        cout << res[i] << "\t";
    }
    //SOLO IMPRIMIR EL RESULTADO!!
    cout << "\n" << "tardo: " << tiempo << " seg\n";

    return 0;
}
