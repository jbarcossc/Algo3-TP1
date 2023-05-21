#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int n;
vector<vector<int>> aristas;
vector<bool> visitado;
vector<int> tiradas; // cuales son las que "hay que tirar a mono"

void bfs(int s) {
    visitado[s] = true;
    queue<int> q;
    q.push(s);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (auto v : aristas[u]) {
            if (visitado[v]) continue;
            visitado[v] = true;
            q.push(v);
        }
    }
}


int main() {
    //intput
    int m, v, w;
    cin >> n; cin >> m;
    aristas.assign(n,{});
    visitado.assign(n, false);
    tiradas.assign(0,0);
    while (m--){
        cin >> v; cin >> w;
        aristas[v-1].push_back(w-1);
    }

    //llamar al algoritmo//
    for(int i = 0; i < n; i++){
        if (!visitado[i]){
            tiradas.push_back(i);
            bfs(i);
        }
    }

    // output
    cout << tiradas.size() << endl;
    for(int i = 0; i <tiradas.size()-1;i++){
           cout << tiradas[i]+1 << " ";
    }
    cout << tiradas[tiradas.size()-1]+1 << endl;
    return 0;
}