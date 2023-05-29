#include <iostream>
#include <vector>
#include <chrono>
#include <sstream>
#include <math.h>
#include <set>

using namespace std;
using namespace std::chrono;
typedef long long ll;

vector<vector<ll>> aristas, tablaPuentes;
vector<ll> low, tin;
vector<vector<bool>> puenteEnPosicion;
ll timer,n;
vector<bool> vistos, caminoVisitado, visitado;

void dfs(ll v, ll p = -1) {
    visitado[v] = true;
    tin[v] = low[v] = timer++;
    for (ll u : aristas[v]) {
        if (u == p) continue;
        if (visitado[u]) {
            low[v] = min(low[v], tin[u]);
        } else {
            dfs(u, v);
            low[v] = min(low[v], low[u]);
            if (low[u] > tin[v]) {
                puenteEnPosicion[v][u] = true;
                puenteEnPosicion[u][v] = true;
            }
        }
    }
}

void find_bridges() {
    timer = 0;
    visitado[n] = false;
    tin[n] = -1;
    low[n] = -1;
    for (ll i = 0; i < n; ++i) {
        if (!visitado[i])
            dfs(i);
    }
}

bool esPuente(ll v, ll w){
    return puenteEnPosicion[v][w];
}

bool hayCamino(ll v, ll w){
    bool res = false;
    caminoVisitado[v] = true;
    for(ll i = 0; i < aristas[v].size(); i++){
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

bool hayPuente(ll v, ll w){
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
    for(ll i = 0; i < aristas[v].size(); i++){
        if(!vistos[aristas[v][i]]) {
            if (esPuente(v, aristas[v][i])) {
                caminoVisitado.assign(n, false);
                caminoVisitado[v] = true;
                res |= hayCamino(aristas[v][i], w);
            } else {
                res |= hayPuente(aristas[v][i], w);
            }
        }
        if(res){
            tablaPuentes[v][w] = true;
            tablaPuentes[w][v] = true;
            return true;
        }
    }
    tablaPuentes[v][w] = false;
    tablaPuentes[w][v] = false;
    return res;
}


ll formasDePerder(){
    ll res = 0;
    for (ll v=0; v<n-2; ++v){
        for (ll w=v+1; w<n-1; ++w){
            vistos.assign(n, false);
            if (hayPuente(v,w)){
                res++;
            }
        }
    }
    return res;
}

double probabilidadDePerder(){
    return ((double)formasDePerder() / (double)((n-1) * (n - 2) / 2));
}

void printTabla(){
    for(ll i = 0; i < tablaPuentes.size(); i++){
        for (ll j = 0; j < tablaPuentes[i].size(); j++) {
            cout << tablaPuentes[i][j] << " ";
        }
        cout << endl;
    }
}

int main() {
    ll m,v,w;

    cin >> n; cin >> m; n++;

    aristas.assign(n+1,{});
    vector<ll> row(n,-1);
    tablaPuentes.assign(n,row);
    timer = 0;
    visitado.assign(n+1, false);
    puenteEnPosicion.assign(n+1,visitado);
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

    printf("%.5f",probabilidadDePerder());

    return 0;
}