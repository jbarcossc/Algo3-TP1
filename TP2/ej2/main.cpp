#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>
#include <sstream>
#include <algorithm>


using namespace std;
using namespace std::chrono;

int n;
vector<vector<int>> listaAdyacencia;
vector<bool> fichas;
vector<bool> tiradas;

void tirar(int f, int i){
    if (fichas[f-1]) {
        if (f == i) { tiradas[f-1] = true;}
        fichas[f-1] = false;

        for (int j = 0; j < listaAdyacencia[f-1].size(); j++) {
            int fichaATirar = listaAdyacencia[f-1][j];
            if (fichaATirar != i) {
                tiradas[fichaATirar-1] = false;
                if (fichas[fichaATirar - 1]) {
                    tirar(fichaATirar, i);
                }
            }
        }
    }
}

vector<int> result(){
    vector<int> res;
    for(int i = 0; i < tiradas.size();i++){
        if(tiradas[i]){
            res.push_back(i+1);
        }
    }
    return res;
}

int main() {
    //leer
    int m, v, w;
    cin >> n; cin >> m;
    vector<vector<int>> mat(n);
    listaAdyacencia = mat;
    while (m--){
        cin >> v; cin >> w;
        listaAdyacencia[v-1].push_back(w);
    }

    //ejecutar y tomar el tiempo
    //auto start = high_resolution_clock::now();

    //llamar al algoritmo//

    vector<bool> f(n,true);
    fichas = f;
    vector<bool> t(n,false);
    tiradas = t;
    for(int i = 1; i <= n; i++){
        tirar(i,i);
    }

    vector<int> res = result();
    cout << res.size() << endl;
    for(int i = 0; i < res.size();i++){
        if(i != 0) {cout << " ";}
        cout << res[i];
    }
    cout << endl;
    // salida
//    auto stop = high_resolution_clock::now();
//    float tiempo = duration_cast<milliseconds>(stop - start).count(); //milisegundos
//    tiempo = tiempo / 1000; // pasar a segundos
//    cout << "tardo: " << tiempo << " seg\n";

    return 0;
}