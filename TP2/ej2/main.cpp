#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>
#include <sstream>
#include <algorithm>


using namespace std;
using namespace std::chrono;

int n;
vector<vector<int>> aristas;
vector<bool> fichas; // las fichas "paradas"
vector<bool> tiradas; // cuales son las que "hay que tirar a mono"

void tirar(int f, int i){
    // tirar ficha f cuyo padre es i
    if (fichas[f-1]) {
        if (f == i) { tiradas[f-1] = true;}
        fichas[f-1] = false;

        for (int j = 0; j < aristas[f-1].size(); j++) {
            int fichaATirar = aristas[f-1][j];
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
    aristas.assign(n,{});
    while (m--){
        cin >> v; cin >> w;
        aristas[v-1].push_back(w);
    }

    //llamar al algoritmo//
    fichas.assign(n, true);
    tiradas.assign(n, false);
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
    return 0;
}