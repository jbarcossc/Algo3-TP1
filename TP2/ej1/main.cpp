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

vector<vector<int>> aristas;
vector<int> low, tin;
set<pair<int,int>> puentes;
int timer;
int n;
vector<bool> vistos, caminoVisitado, visitado;

int numeroCombinatorio(int n, int k){
    // casos base
    if (k > n) return 0;
    if (k == 0 || k == n) return 1;

    return numeroCombinatorio(n - 1, k - 1) + numeroCombinatorio(n - 1, k);
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

vector<int> conexiones(int v){
    vector<int> res;
    for(int i = 0; i < aristas[v].size(); i++){
        if(!vistos[aristas[v][i]]){
            res.push_back(aristas[v][i]);
        }
    }
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
    if (esPuente(v, w)) return true;
    bool res = false;
    vistos[v] = true;
    vector<int> conex = conexiones(v);
    for(int i = 0; i < conex.size(); i++){
        if (esPuente(v,conex[i])){
            caminoVisitado.assign(n, false);
            caminoVisitado[v] = true;
            res |= hayCamino(conex[i],w);
        } else {
            res |= hayPuente(conex[i], w);
        }
    }
    return res;
}


int formasDePerder(){
    int res = 0;
    for (int v=0; v<n-1; v++){
        for (int w=v+1; w<n; w++){
            vistos.assign(n, false);
            caminoVisitado.assign(n, false);
            if (hayPuente(v,w)){
                res++;
            }
        }
    }
    return res;
}

double probabilidadDePerder(){
    return ((double)formasDePerder() / (double)numeroCombinatorio(n,2));
}

int main() {
    //input
    int m,v, w;
    cin >> n; cin >> m;

    aristas.assign(n,{});
    timer = 0;
    visitado.assign(n, false);
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

/*
    caminoVisitado.assign(n, false);
    vistos.assign(n, false);
    printf("hayPuente 1 2: %d \n", (int) hayPuente(0,1));
    caminoVisitado.assign(n, false);
    vistos.assign(n, false);
    printf("hayPuente 1 3: %d \n", (int) hayPuente(0,2));
    caminoVisitado.assign(n, false);
    vistos.assign(n, false);
    printf("hayPuente 1 4: %d \n", (int) hayPuente(0,3));
    caminoVisitado.assign(n, false);
    vistos.assign(n, false);
    printf("hayPuente 2 3: %d \n", (int) hayPuente(1,2));
    caminoVisitado.assign(n, false);
    vistos.assign(n, false);
    printf("hayPuente 2 4: %d \n", (int) hayPuente(1,3));
    caminoVisitado.assign(n, false);
    vistos.assign(n, false);
    printf("hayPuente 3 4: %d \n", (int) hayPuente(2,3));
*/
/*
    printf("hayCamino 1 2: %d \n", (int) hayCamino(0,1));
    caminoVisitado.assign(n, false);
    printf("hayCamino 1 3: %d \n", (int) hayCamino(0,2));
    caminoVisitado.assign(n, false);
    printf("hayCamino 1 4: %d \n", (int) hayCamino(0,3));
    caminoVisitado.assign(n, false);
    printf("hayCamino 2 3: %d \n", (int) hayCamino(1,2));
    caminoVisitado.assign(n, false);
    printf("hayCamino 2 4: %d \n", (int) hayCamino(1,3));
    caminoVisitado.assign(n, false);
    printf("hayCamino 3 4: %d \n", (int) hayCamino(2,3));
    */
    //printf("formasDePerder %d \n",formasDePerder());

    printf("%.6f\n",probabilidadDePerder());


    return 0;
}
