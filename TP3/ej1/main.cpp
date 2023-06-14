#include <iostream>
#include <vector>
#include <tuple>
#include <queue>
#include <limits>

using namespace std;
using Edge = tuple<int,int,int>;// v, w , peso

vector<Edge> aristas;
vector<Edge> propuestas;
pair<vector<int>, vector<int>> distancias;
vector<bool> visitado;
vector<int> distancia;
priority_queue<Edge, vector<Edge>, greater<Edge>> pq; // Min-heap
int n,m,k,s,t;

vector<int> dijkstra(int source) {

    distancia[source] = 0;
    pq.push(make_pair(0, source));

    while (!pq.empty()) {
        int u =  get<0>(pq.top());
        pq.pop();

        if (visitado[u]) continue;

        visitado[u] = true;

        for (auto vecino : aristas[u]) {
            int v = get<1>(vecino);
            int weight =get<2>(vecino);

            if (!visitado[v] && distancia[u] + weight < distancia[v]) {
                distancia[v] = distancia[u] + weight;
                pq.push(make_pair(distancia[v], v));
            }
        }
    }
    return dist;
}

void calcularDistancias(){
    distancias.first = dijkstra(s);
    distancias.second = dijkstra(t);
}

int calcularResultado(){
    calcularDistancias();
    int distOriginal = distancias.first[t-1];
    int res = distOriginal;
    for(Edge arista : propuestas){
        int nuevaDistancia = distancias.first[get<0>(arista) - 1] + get<2>(arista) + distancias.second[get(<1>(arista)) - 1];
        res = min(res, nuevaDistancia);
    }
    return res == distOriginal ? - 1 : res;
}


int main() {
    int casos; cin >> casos;
    int v,w,p;

    while (casos--){
        //input
        cin >> n; cin >> m; cin >> k; cin >> s; cin >> t;
        n++;
        visitado.assign(n,false);
        aristas.assign(n,{});
        distancia.assign(n,INT_MAX-1);
        while (m--){
            cin >> v; cin >> w; cin >> p;
            aristas.push_back({v,w,p});
        }
        while (k--){
            cin >> v; cin >> w; cin >> p;
            propuestas.push_back({v,w,p});
        }
        //algoritmo

        int res = calcularResultado();
        // output
        cout << res << endl;
    }

    return 0;
}
