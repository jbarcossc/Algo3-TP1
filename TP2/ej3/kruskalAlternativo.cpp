#include "kruskalAlternativo.h"


vector<double> findMinimumSpanningTree(int n, int k, vector<tuple<double,int,int>>& edges) {
    sort(edges.begin(), edges.end());

    vector<double> minimumSpanningTree;
    vector<int> components(n);

    // Initialize each office as a separate component
    for (int i = 0; i < n; i++) {
        components[i] = i;
    }

    int modemCount = 0;
    int edgeCount = 0;

    for (auto edge : edges) {
        int source = get<1>(edge), destination=  get<2>(edge);
        double weight = get<0>(edge);
        int sourceComponent = components[source];
        int destComponent = components[destination];

        if (sourceComponent != destComponent && modemCount < k) {
            minimumSpanningTree.push_back((double)weight);
            modemCount++;
            edgeCount++;

            // Merge the connected components
            for (int i = 0; i < n; i++) {
                if (components[i] == destComponent) {
                    components[i] = sourceComponent;
                }
            }
        }

        if (edgeCount == n - 1 || modemCount == k) {
            break;
        }
    }

    if (edgeCount < n - 1) {
        minimumSpanningTree.clear(); // Not possible to connect all offices
    }

    return minimumSpanningTree;
}


void generarTests(int testNum, int n, int w){
    ofstream file("ej" + to_string(testNum));

    if (!file) {
        std::cout << "Failed to create file." << endl;
        return;
    }

    file << 1 << endl;
    file << n << " " << 5 << " " << w << " " << 1 << " " << 2 << endl;

    for (int i = 0; i < n; i++) {
        int x = rand() % 1000;
        int y = rand() % 1000;
        file << x << " " << y << std::endl;
    }

    file.close();
}

void crearTest(){
    int count=0;
    for (int i=100; i<=100000; i*=10){
        generarTests(count,i,10);
        count++;
    }
}