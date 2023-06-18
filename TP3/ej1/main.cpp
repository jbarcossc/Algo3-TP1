#include <iostream>
#include <vector>
#include <tuple>
#include <queue>

const int INT_MAX = 10000000;

using namespace std;
using Edge = pair<int,int>;;// peso, v
vector<vector<Edge>> aristas;
vector<tuple<int,int,int>> propuestas;
pair<vector<int>, vector<int>> distancias;
int n,m,k,s,t;


void dijkstra(int source, vector<int>& dist) {
    vector<bool> visited(n, false);

    priority_queue<Edge, vector<Edge>, greater<Edge>> pq; // Min-heap
    dist[source] = 0;
    pq.push(make_pair(0, source));

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        if (visited[u])
            continue;

        visited[u] = true;

        for (const auto& arista : aristas[u]) {
            int v = arista.second;
            int weight = arista.first;

            if (!visited[v] && dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                pq.push(make_pair(dist[v], v));
            }
        }
    }
}


void calcularDistancias(){
    distancias.first.assign(n,INT_MAX);
    distancias.second.assign(n,INT_MAX);
    dijkstra(s, distancias.first);
    dijkstra(t, distancias.second);
}

int calcularResultado(){
    calcularDistancias();
    int distOriginal = distancias.first[t];
    int res = distancias.first[get<0>(propuestas[0])] + distancias.second[get<1>(propuestas[0])] + get<2>(propuestas[0]);
    for(auto arista : propuestas){
        int nuevaDistancia = distancias.first[get<0>(arista)] + distancias.second[get<1>(arista)] + get<2>(arista);
        res = min(res, nuevaDistancia);
    }
    return distOriginal == INT_MAX ? - 1 : res;
}


int main() {
    int casos; cin >> casos;
    int v,w,p;
    vector<int> res;
    while (casos--){
        //input
        cin >> n; cin >> m; cin >> k; cin >> s; cin >> t;
            n++;
        aristas.assign(n,{});
        propuestas.clear();
        distancias.first.clear();
        distancias.second.clear();

        while (m--){
            cin >> v; cin >> w; cin >> p;
            aristas[v].push_back(make_pair(p,w));
            aristas[w].push_back(make_pair(p,v));
        }
        while (k--){
            cin >> v; cin >> w; cin >> p;
            propuestas.push_back({v,w,p});
        }
        //algoritmo

        res.push_back(calcularResultado());
    }

    // output
    for (int i = 0; i < res.size(); ++i) {
        cout << res[i] << endl;
    }

    return 0;
}

/// EL CAMINO DE RESPUESTA SI O SI TIENE QUE PASAR POR UNA CALLE DE LAS PROPUESTAS