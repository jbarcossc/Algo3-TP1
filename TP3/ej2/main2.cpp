#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const int INF = 10000000;

int n,m, numVertices;
vector<vector<int>> capacidad;
vector<vector<int>> amistades;
vector<int> votos;

vector<vector<int>> adjacencyMatrix;
vector<int> parent;


bool bfs(int source, int sink) {
    parent.assign(numVertices, -1);
    vector<bool> visited(numVertices, false);
    queue<int> q;

    q.push(source);
    visited[source] = true;

    while (!q.empty()) {
        int current = q.front();
        q.pop();

        for (int next = 0; next < numVertices; next++) {
            int residualCapacity = adjacencyMatrix[current][next] - adjacencyMatrix[next][current];
            if (!visited[next] && residualCapacity > 0) {
                q.push(next);
                parent[next] = current;
                visited[next] = true;
            }
        }
    }

    // Return true if we reached the sink
    return visited[sink];
}

int getMaxFlow(int source, int sink) {
    int maxFlow = 0;
    while (bfs(source, sink)) {
        int pathFlow = INF;

        // Find the bottleneck capacity (minimum residual capacity) along the augmenting path
        for (int v = sink; v != source; v = parent[v]) {
            int u = parent[v];
            pathFlow = min(pathFlow, adjacencyMatrix[u][v] - adjacencyMatrix[v][u]);
        }

        // Update the residual capacities and reverse edges along the augmenting path
        for (int v = sink; v != source; v = parent[v]) {
            int u = parent[v];
            adjacencyMatrix[u][v] -= pathFlow;
            adjacencyMatrix[v][u] += pathFlow;
        }

        // Add the path flow to the overall maximum flow
        maxFlow += pathFlow;
    }

    return maxFlow;
}

void crearGrafo(){
    //crear s y t donde s=0 y t=n+1
    int t = n+1;
    int s =0;
    numVertices=n+2;
    for (int i = 1; i <= n; ++i) {
        if(votos[i] == 1){ //source
            adjacencyMatrix[s][i]=1;
        } else { //sink
            adjacencyMatrix[i][t]=1;
        }
    }
}

int main() {
    //intput
    vector<int> res;
    while (true){
        cin >> n; cin >> m;
        if (n==0 && m==0) break;
        votos.assign(n+2,0);
        adjacencyMatrix.assign(n+2,votos);
        for (int i = 1; i <= n; ++i) {
            bool v; cin >> v;
            votos[i]=v;
        }

        while (m--){
            int v,w;
            cin >> v; cin >> w;
            adjacencyMatrix[v][w]=INF;
        }

        //llamar al algoritmo//
        crearGrafo();

        res.push_back(getMaxFlow(0,n+1));

    }

    // output
    for (int i = 0; i < res.size(); ++i) {
        cout << res[i] << endl;
    }

    return 0;
}