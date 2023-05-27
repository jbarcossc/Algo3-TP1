#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>
#include <sstream>
#include <algorithm>
#include <bits/stdc++.h>

using namespace std;

int n, m, distanciaMax, modems, precioUTP, precioFibra;
vector<tuple<double,int,int>> E;
vector<pair<int,int>> posiciones;


struct DSU{
    DSU(int n){
        padre = rank = vector<int>(n);
        for(int v = 0; v < n; v++) padre[v] = v;
    }

    int find(int v){
        if(v == padre[v]) return v;
        return padre[v] = find(padre[v]);
    }

    int findNOPathCompression(int v){
        if(v == padre[v]) return v;
        return find(padre[v]);
    }

    void unite(int u, int v){
        u = find(u), v = find(v);
        if(u == v) return;
        if(rank[u] < rank[v]) swap(u,v);
        padre[v] = padre[u];
        rank[u] = max(rank[u],rank[v]+1);
    }

    void unionNoRank(int u,int v){
//        u = findNOPathCompression(u), v = findNOPathCompression(v);
//        if(u == v) return;
        padre[u]= findNOPathCompression(v);
    }

    vector<int> padre;
    vector<int> rank;
};

vector<double> kruskal(){
    vector<double> res;
    sort(E.begin(),E.end());
    int componentesConexos = n;
    DSU dsu(n);
    for(auto i : E){
        int u = get<1>(i), v = get<2>(i);
        double c= get<0>(i);
        //si (u,v) es arista segura
        if(dsu.find(u) != dsu.find(v)){
            // agregar
            dsu.unite(u,v);
            res.push_back(c);
            componentesConexos--;
            if (componentesConexos == modems ) break;
        }
    }
    return res;
}

double distancia(pair<int,int> a, pair<int,int> b){
    return ((double)sqrt((a.first-b.first)*(a.first-b.first) + (a.second-b.second)*(a.second-b.second)));
}

pair<double,double> precios(vector<double> dist){
    double utp=0, fibra=0;
    for (int i=0; i< dist.size(); i++){
        if (dist[i] <= distanciaMax){
            utp += dist[i] * precioUTP;
        }else{
            fibra += dist[i] * precioFibra;
        }
    }
    return make_pair(utp,fibra);
}

void crearAristas(){
    for (int i =0; i<n; i++){
        for(int j=i+1; j<n; j++){
            double dist = distancia(posiciones[i],posiciones[j]);
            E.push_back({dist,i,j});
            E.push_back({dist,j,i});
        }
    }
}

int main() {
    int c, x, y,j=1;
    cin >> c;
    while (c--){
        //input
        cin >> n;
        cin >> distanciaMax;
        cin >> modems;
        cin >> precioUTP;
        cin >> precioFibra;
        posiciones.assign(0,{});
        E.assign(0,{});
        for (int i =0; i<n; i++){
            cin >> x; cin >> y;
            posiciones.push_back(make_pair(x,y));
        }

        //algoritmo
        crearAristas();
        pair<double,double> res = precios(kruskal());

        // output
        printf("Caso #%d: %.3f %.3f\n",j,res.first,res.second);
        j++;
    }

    return 0;
}