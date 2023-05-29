#include <iostream>
#include <vector>
#include <chrono>
#include <sstream>
#include <math.h>
#include <set>

using namespace std;
using namespace std::chrono;

vector<vector<int>> aristas;
vector<vector<bool>> hayPuente, tablaCaminos;
vector<int> low, tin;
int timer,n;
vector<bool> vistos, caminoVisitado, visitado;

int numeroCombinatorio(int n, int k){
    // casos base
    if (k > n) return 0;
    if (k == 0 || k == n) return 1;

    return numeroCombinatorio(n - 1, k - 1) + numeroCombinatorio(n - 1, k);}

void dfsCamino(int v) {
    visitado[v] = true;
    for (int u : aristas[v]) {
        if (!visitado[u])
            dfsCamino(u);
    }
}
void dfsParaPuentes(int v, int p = -1) {
    visitado[v] = true;
    tin[v] = low[v] = timer++;
    for (int u : aristas[v]) {
        if (u == p) continue;
        if (visitado[u]) {
            low[v] = min(low[v], tin[u]);
        } else {
            dfsParaPuentes(u, v);
            low[v] = min(low[v], low[u]);
            if (low[u] > tin[v]){
                hayPuente[v][u]= true;
                hayPuente[u][v]=true;
            }
        }
    }
}

void find_bridges() {
    timer = 0;
    visitado[n] = false;
    tin[n] = -1;
    low[n] = -1;
    for (int i = 0; i < n; ++i) {
        if (!visitado[i])
            dfsParaPuentes(i);
    }
}

bool esPuente(int v, int w){
    return hayPuente[v][w];
}

void sacarPuentes(){
    vector<vector<int>> aristasSinPuentes(n);
    for (int v=0;v<n; v++){
        for (int w : aristas[v]){
            if (!esPuente(v,w)){
                aristasSinPuentes[v].push_back(w);
                aristasSinPuentes[w].push_back(v);
            }
        }
    }
    aristas=aristasSinPuentes;
}

void calcularCaminosRecursivos(int v){
    for (int w : aristas[v]) {
        if(!tablaCaminos[v][w] && !caminoVisitado[w]){
            caminoVisitado[w] = true;
            calcularCaminosRecursivos(w);
        }
    }
}

void calcularCaminos(){
    for(int v = 0; v < n-1; v++){
        caminoVisitado.assign(n, false);
        caminoVisitado[v] = true;
        calcularCaminosRecursivos(v);
        for (int i = 0; i < caminoVisitado.size(); ++i) {
            if (caminoVisitado[i]){
                tablaCaminos[v][i] = true;
                tablaCaminos[i][v] = true;
            }
        }
    }
}

int formasDePerder(){
    int res = 0;
    for (int v=0; v<n-2; v++){
        for (int w = v+1; w < n-1; ++w) {
            res += (int) tablaCaminos[v][w];
        }
    }
    return res;
}

double probabilidadDePerder(){
    return ((double)formasDePerder() / (double)numeroCombinatorio(n-1,2));
}

int main() {
    //input

    int m,v,w;

    cin >> n; cin >> m; n++;

    aristas.assign(n,{});
    timer = 0;
    visitado.assign(n, false);
    tablaCaminos.assign(n, visitado);
    hayPuente.assign(n,visitado);
    vistos.assign(n, false);
    caminoVisitado.assign(n, false);
    tin.assign(n, -1);
    low.assign(n, -1);
    while (m--){
        cin >> v; cin >> w;
        aristas[v-1].push_back(w-1);
        aristas[w-1].push_back(v-1);
    }


    //algoritmo
    find_bridges();
    sacarPuentes();
    calcularCaminos();


    printf("%.5f\n",probabilidadDePerder());


    return 0;
}
