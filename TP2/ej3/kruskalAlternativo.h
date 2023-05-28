#ifndef TP2_KRUSKALALTERNATIVO_H
#define TP2_KRUSKALALTERNATIVO_H

#include <iostream>
#include <fstream>
#include <vector>
#include <bits/stdc++.h>
#include <algorithm>
#include <random>

using namespace std;


struct worseDisjointSet{
    worseDisjointSet(int n){
        padre = vector<int>(n);
        for(int v = 0; v < n; v++) padre[v] = v;
    }

    int find(int x){
        //NOPathCompression
        while (x != padre[x]) {
            x = padre[x];
        }
        return x;
    }

    void unite(int u,int v){
        //unionNoRank
        int rootX = find(u);
        int rootY = find(v);
        if (rootX != rootY) {
            padre[rootX] = rootY;
        }
    }

    vector<int> padre;
};

vector<double> findMinimumSpanningTree(int n, int k, vector<tuple<double,int,int>>& edges);
void generarTests(int a,int b,int c);
void crearTest();




#endif //TP2_KRUSKALALTERNATIVO_H
