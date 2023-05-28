#include <iostream>
#include <vector>
#include <chrono>
#include <sstream>
#include <math.h>
#include <set>

using namespace std;
using namespace std::chrono;

vector<vector<int>> aristas, tablaPuentes;
vector<int> low, tin;
set<pair<int,int>> puentes;
int timer,n;
vector<bool> vistos, caminoVisitado, visitado;

int numeroCombinatorio(int n, int k){
    return (tgamma(n+1) / (tgamma(n - k + 1)* tgamma(k+1)));
}

void dfs(int v, int p = -1) {
    visitado[v] = true;
    tin[v] = low[v] = timer++;
    for (int u : aristas[v]) {
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
    timer = 0;
    visitado[n] = false;
    tin[n] = -1;
    low[n] = -1;
    for (int i = 0; i < n; ++i) {
        if (!visitado[i])
            dfs(i);
    }
}

bool esPuente(int v, int w){
    bool res = false;
    res |= puentes.find(make_pair(w,v)) != puentes.end();
    res |= puentes.find(make_pair(v,w)) != puentes.end();
    return res;
}

bool hayCamino(int v, int w){
    bool res = false;
    caminoVisitado[v] = true;
    for(int i = 0; i < aristas[v].size(); i++){
        if(!caminoVisitado[aristas[v][i]]){
            if(aristas[v][i] == w){
                return true;
            } else {
                res |= hayCamino(aristas[v][i],w);
            }
        }
    }
    return res;
}

bool hayPuente(int v, int w){
    if(tablaPuentes[v][w] != -1){
        return (bool) tablaPuentes[v][w];
    }
    if (esPuente(v, w)){
        tablaPuentes[v][w] = true;
        tablaPuentes[w][v] = true;
        return true;
    }
    bool res = false;
    vistos[v] = true;
    for(int i = 0; i < aristas[v].size(); i++){
        if(!vistos[aristas[v][i]]) {
            if (esPuente(v, aristas[v][i])) {
                caminoVisitado.assign(n, false);
                caminoVisitado[v] = true;
                res |= hayCamino(aristas[v][i], w);
            } else {
                res |= hayPuente(aristas[v][i], w);
            }
        }
    }
    tablaPuentes[v][w] = (int) res;
    tablaPuentes[w][v] = (int) res;
    return res;
}


int formasDePerder(){
    int res = 0;
    for (int v=0; v<n-2; ++v){
        for (int w=v+1; w<n-1; ++w){
            vistos.assign(n, false);
            caminoVisitado.assign(n, false);
            if (hayPuente(v,w) || !hayCamino(v,w)){
                res++;
            } else {
            }
        }
    }
    return res;
}

double probabilidadDePerder(){
    return ((double)formasDePerder() / (double)numeroCombinatorio(n-1,2));
}

void printTabla(){
    for(int i = 0; i < tablaPuentes.size(); i++){
        for (int j = 0; j < tablaPuentes[i].size(); j++) {
            cout << tablaPuentes[i][j] << " ";
        }
        cout << endl;
    }
}

int main() {
    //input

    int m,v,w;

    cin >> n; cin >> m; n++;

    aristas.assign(n+1,{});
    vector<int> row(n,-1);
    tablaPuentes.assign(n,row);


    timer = 0;
    visitado.assign(n+1, false);
    vistos.assign(n+1, false);
    caminoVisitado.assign(n+1, false);
    tin.assign(n+1, -1);
    low.assign(n+1, -1);
    while (m--){
        cin >> v; cin >> w;
        aristas[v-1].push_back(w-1);
        aristas[w-1].push_back(v-1);
    }

    //algoritmo
    find_bridges();

    printf("%.5f\n",probabilidadDePerder());

    return 0;
}
