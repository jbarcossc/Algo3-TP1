#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

vector<vector<int>> aristas;
vector<int> low, tin,camino;
vector<bool> visitado;
set<pair<int,int>> puentes;
int timer;
long long n;
vector<bool> vistos(n,false);

int numeroCombinatorio(int n, int k){
    // casos base
    if (k > n) return 0;
    if (k == 0 || k == n) return 1;

    return numeroCombinatorio(n - 1, k - 1) + numeroCombinatorio(n - 1, k);
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
            dfsParaPuentes(i);
    }
}

bool esPuente(int v, int w){
    bool res = false;
    res = res || puentes.count(make_pair(w,v)) != 0;
    res = res || puentes.count(make_pair(v,w)) != 0;
    return res;
}

bool dfsCamino(int s, int t){
    visitado[s]= true;
    camino.push_back(s);
    if (s==t) return true; // existe camino

    for (int v: aristas[s]){
        if (!visitado[v]){
            if (dfsCamino(v,t)) return true;
        }
    }
    //no encontre camino
    camino.pop_back();
    return false;
}


int formasDePerder(){
    int res = 0;
    for (int v=0; v<n-1; v++){
        for (int w=v+1; w<n; w++){
            visitado.assign(n,false);
            camino.clear();
            if (dfsCamino(v,w)){
                bool hayPuente=false;
                for (int i=0;i<camino.size()-1;i++){
                    if (esPuente(camino[i],camino[i+1])){
                        hayPuente=true;
                        break;
                    }
                }
                if (hayPuente)
                    res++;
            }
        }
    }
    return res;
}

double probabilidadDePerder(){
    return ((double)formasDePerder() / (double)numeroCombinatorio(n-1,2));
}

int main() {
    //input
    long long m;
    int v, w;
    cin >> n; cin >> m; n++;

    aristas.assign(n,{});
    timer = 0;
    visitado.assign(n, false);
    vistos.assign(n, false);
    tin.assign(n, -1);
    low.assign(n, -1);
    while (m--){
        cin >> v; cin >> w;
        aristas[v-1].push_back(w-1);
        aristas[w-1].push_back(v-1);
    }

    //algoritmo
    find_bridges();

    //printf("hayPuente 1 2: %d \n", (int) hayPuente(0,1));
    //printf("hayPuente 1 3: %d \n", (int) hayPuente(0,2));
    //printf("hayPuente 1 4: %d \n", (int) hayPuente(0,3));
//    printf("hayPuente 1 2: %d \n", (int) esPuente(1,2));
    //printf("hayPuente 2 4: %d \n", (int) hayPuente(1,3));
//    printf("hayPuente 3 4: %d \n", (int) esPuente(2,3));

    printf("%.5f\n",probabilidadDePerder());

    return 0;
}
