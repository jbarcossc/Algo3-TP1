#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>
#include <sstream>
#include <algorithm>
#include <iomanip>
#include <set>

using namespace std;
using namespace std::chrono;

vector<vector<int>> listaAdyacencia;
vector<int> low, tin;
vector<bool> visitado, vistos;
set<pair<int,int>> puentes;
int timer;
int n;


int numeroCombinatorio(int n, int k){
    // coasos base
    if (k > n) return 0;
    if (k == 0 || k == n) return 1;

    return numeroCombinatorio(n - 1, k - 1) + numeroCombinatorio(n - 1, k);
}

void dfs(int v, int p = -1) {
    visitado[v] = true;
    tin[v] = low[v] = timer++;
    for (int u : listaAdyacencia[v]) {
        if (u == p) continue;
        if (visitado[u]) {
            low[v] = min(low[v], tin[u]);
        } else {
            dfs(u, v);
            low[v] = min(low[v], low[u]);
            if (low[u] > tin[v])
                puentes.insert(make_pair(v,u));
        }
    }
}

void find_bridges() {
    for (int i = 0; i < n; ++i) {
        if (!visitado[i])
            dfs(i);
    }
}

bool esPuente(int v, int w){
    bool res= false;
    res = res || puentes.count(make_pair(w,v)) != 0;
    res = res || puentes.count(make_pair(v,w)) != 0;
    return res;
}

vector<int> conexiones(int v){
    vector<int> res;
    for(int i = 0; i < n; i++){
        int a = listaAdyacencia[i][0];
        int b = listaAdyacencia[i][1];
        if (a == v && !visitado[b]){
            res.push_back(b);
        }
        if (b == v && !vistos[a]){
            res.push_back(a);
        }
    }
    return res;
}

bool hayPuente(int v, int w){
    if (esPuente(v, w)) return true;
    bool res=false;
    vistos[v] = true;
    for(int i=0; i<  listaAdyacencia[w].size(); i++){
        if ( listaAdyacencia[w][i] != v)
            res = res || hayPuente(w,listaAdyacencia[w][i]);
    }
    return res;
}


int formasDePerder(){
    int res=0;
    for (int v=0; v<n; v++){
        for (int w=v+1; w<n; w++){
            if (v!=w && hayPuente(v,w)){
                res++;
            }
        }
    }
    return res;
}

double probabilidadDePerder(){
//    return formasDePerder() / numeroCombinatorio(2,n);
    return formasDePerder();
}

int main() {
    //leer
    int m,v, w;
    cin >> n; cin >> m;

    listaAdyacencia.assign(n,{});
    timer = 0;
    visitado.assign(n, false);
    vistos.assign(n, false);
    tin.assign(n, -1);
    low.assign(n, -1);
    while (m--){
        cin >> v; cin >> w;
        listaAdyacencia[v-1].push_back(w-1);
        listaAdyacencia[w-1].push_back(v-1);
//        aristas.push_back(make_pair(v,w));
    }

    //ejecutar y tomar el tiempo
    auto start = high_resolution_clock::now();
    find_bridges();
//    cout << esPuente(0,2) << endl;
    cout << hayPuente(1,2) << endl;
    cout << setprecision(6) << probabilidadDePerder() << endl;

    // salida
//    auto stop = high_resolution_clock::now();
//    float tiempo = duration_cast<milliseconds>(stop - start).count(); //milisegundos
//    tiempo = tiempo / 1000; // pasar a segundos
//    cout << "tardo: " << tiempo << " seg\n";

    return 0;
}
