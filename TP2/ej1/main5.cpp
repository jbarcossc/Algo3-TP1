#include <iostream>
#include <vector>
#include <chrono>
#include <iomanip>


using namespace std;
typedef long long ll;


vector<vector<int>> aristas;
vector<vector<bool>> hayPuente;
vector<int> low, tin;
int timer, n;
ll id=0;
vector<bool> visitado;
vector<int> count;

void dfsCamino(int v) {
    visitado[v] = true;
    count[id]++;
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
                //puentes en u - v
                hayPuente[v][u]= true;
                hayPuente[u][v]=true;
            }
        }
    }
}

void encontrarPuentes() {
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


void formasDePerder(){
    visitado.assign(n, false);
    for (int v=0; v<n-1; v++){
        if (!visitado[v]){
            dfsCamino(v);
            id++;
        }
    }
}

ll probabilidadDePerder(){
    formasDePerder();
    ll fail = 0;
    for(int i = 0; i <= id; i++){
        if(count[i]){
            fail += ll(count[i]*(count[i]-1))/2;
        }
    }
    return fail;
}

int main() {
    //input

    int m,v,w;

    cin >> n; cin >> m; n++;n++;

    aristas.assign(n,{});
    timer = 0;
    visitado.assign(n, false);
    hayPuente.assign(n,visitado);
    count.assign(n,0);
    tin.assign(n, -1);
    low.assign(n, -1);
    while (m--){
        cin >> v; cin >> w;
        aristas[v-1].push_back(w-1);
        aristas[w-1].push_back(v-1);
    }


    //algoritmo
    encontrarPuentes();
    sacarPuentes();


//    printf("%.5f",(double)1-1.0*probabilidadDePerder()/((n-1) * ((n-1) - 1) / 2));
    cout << setprecision(5) << 1- 1.0 * probabilidadDePerder() / ((n-1) * ((n-1) - 1) / 2);


    return 0;
}
