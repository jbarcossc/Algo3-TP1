#include <iostream>
#include <vector>
#include <tuple>

using namespace std;

struct Edge {
    int source;
    int destination;
    int peso;

    Edge(int src, int dest, int w) : source(src), destination(dest), peso(w) {}
};

vector<Edge> aristas;
vector<Edge> propuestas;
int n,m,k,s,t;

int main() {
    int casos; cin >> casos;
    int v,w,p;
    while (casos--){
        //input
        cin >> n; cin >> m; cin >> k; cin >> s; cin >> t;
        while (m--){
            cin >> v; cin >> w; cin >> p;
            aristas.push_back({v,w,p});
        }
        while (k--){
            cin >> v; cin >> w; cin >> p;
            propuestas.push_back({v,w,p});
        }
        //algoritmo


        // output
        cout << res << endl;
    }

    return 0;
}
