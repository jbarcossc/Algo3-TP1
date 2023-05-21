#include <bits/stdc++.h>
#include<stdio.h>
#include<vector>
#include<iostream>
using namespace std;
#define M 1000005
vector<int> par(M);
vector<int> rnk(M);

void make_set(int x) {
    par[x] = x;
    rnk[x] = 0;
}

int find_set(int x)
{
    if(x!=par[x]) par[x]=find_set(par[x]);
    return par[x];
}

void merge(int x,int y)
{
    int px,py;
    px=find_set(x);py=find_set(y);
    if(rnk[px]>rnk[py]) par[py]=px;
    else par[px]=py;
    if(rnk[px]==rnk[py]) rnk[py]+=1;
}

bool funcOrd(tuple<int,int,double> a, tuple<int,int,double> b)
{
    return(get<2>(a) < get<2>(b));
}

double dist(int x1,int y1,int x2,int y2) {
    return ((double) sqrt(pow((x1-x2), 2) + pow((y1-y2), 2)));
}

int main() {
    int casos,n,r,w,u,v;
    cin >> casos;
    for(int nCaso = 0; nCaso < casos; nCaso++){
        cin >> n; cin >> r; cin >> w; cin >> u; cin >> v;
        vector<pair<int,int>> coordenadas(n);
        for(int i = 0; i < n; i++) {
            int x,y;
            cin >> x; cin >> y;
            coordenadas[i].first = x;
            coordenadas[i].second = y;
        }
        vector<tuple<int,int,double>> aristas;
        vector<tuple<int,int,double>> res(n);
        for(int i = 0; i < n; i++){
            for(int j = i + 1; j < n; j++)
            {
                double distancia = dist(coordenadas[i].first, coordenadas[i].second, coordenadas[j].first, coordenadas[j].second);
                aristas.push_back({i,j,distancia});
            }
        }
        sort(aristas.begin(), aristas.end(), funcOrd);
        for(int i = 0; i < n; i++) {
            make_set(i);
        }
        int nodosDesconectados = n;
        int k = 0;
        for(int i = 0; i < aristas.size(); i++) {
            int x = find_set(get<0>(aristas[i]));
            int y = find_set(get<1>(aristas[i]));
            if(x != y) {
                merge(x,y);
                nodosDesconectados--;
                res[k++] = aristas[i];
                if(nodosDesconectados == w) break;
            }
        }
        double costeUTP = 0;
        double costeFibra = 0;
        for(int i = 0; i < k; i++){
            double ans = get<2>(res[i]);
            if(ans > r){
                costeFibra += (double) ans*v;
            } else {
                costeUTP += (double) ans*u;
            }
        }
        printf("Caso #%d: %.3f %.3f\n",nCaso+1,costeUTP,costeFibra);
    }
}