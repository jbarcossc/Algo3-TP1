#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const int INF = 10000000;

int n,m;
vector<vector<int>> capacidad;
vector<vector<int>> amistades;
vector<int> votos;

int bfs(int s, int t, vector<int>& parent) {
    fill(parent.begin(), parent.end(), -1);
    parent[s] = -2;
    queue<pair<int, int>> q;
    q.push({s, INF});

    while (!q.empty()) {
        int cur = q.front().first;
        int flow = q.front().second;
        q.pop();
        for (int next : amistades[cur]) {
            if (parent[next] == -1 && capacidad[cur][next]) {
                parent[next] = cur;
                int new_flow = min(flow, capacidad[cur][next]);
                if (next == t)
                    return new_flow;
                q.push({next, new_flow});
            }
        }
    }

    return 0;
}

int maxflow(int s, int t) {
    int flow = 0;
    vector<int> parent(n+3);
    int new_flow;
    while (new_flow = bfs(s, t, parent)) {
        flow += new_flow;
        int cur = t;

        while (cur != s) {
            int prev = parent[cur];
            capacidad[prev][cur] -= new_flow;
            capacidad[cur][prev] += new_flow;
            cur = prev;
        }
    }

    return flow;
}

void crearGrafo(){
    //crear s y t donde s=0 y t=1
    for (int i = 0; i < n; ++i) {
        if(votos[i] == 1){
            amistades[0].push_back(i+2);
            capacidad[0].push_back(1);
        } else {
            amistades[i+2].push_back(1);
            capacidad[i+2].push_back(1);
        }
    }
}

int main() {
    //intput
    vector<int> res;
    while (true){
        cin >> n; cin >> m;
        if (n==0 && m==0) break;
        votos.assign(n+3,0);
        amistades.assign(n+3,{});
        capacidad.assign(n+3,{});
        for (int i = 0; i < n; ++i) {
            bool v; cin >> v;
            votos[i]=v;
        }

        while (m--){
            int v,w;
            cin >> v; cin >> w;
            amistades[v+2].push_back(w+2);
            capacidad[v+2].push_back(1);
            amistades[w+2].push_back(v+2);
            capacidad[w+2].push_back(1);

        }

        //llamar al algoritmo//
        crearGrafo();

        res.push_back(maxflow(0,1));

    }

    // output
    for (int i = 0; i < res.size(); ++i) {
        cout << res[i] << endl;
    }

    return 0;
}