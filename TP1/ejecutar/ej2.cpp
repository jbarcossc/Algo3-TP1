#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>
#include <sstream>
#include <list>
#include <cmath>

using namespace std;
using namespace std::chrono;

int64_t modulo(int64_t n, int64_t d){
    if (n >= 0){
        return n % d;
    }
    return d + (n % d);
}

int64_t mod_bin_exp(int64_t x, int64_t y, int64_t n) {
    // visto en el taller 1
    // X^y mod n
    if (y==0) return 1;

    if (y % 2 == 0) {
        return  modulo(pow( mod_bin_exp(x, y/2, n),2) , n);
    }
    else{
        return modulo(modulo(pow(mod_bin_exp(x, y/2, n),2), n) *x , n);
    }
}


class TablaDinamica {
private:
    vector<int> v;
    int m;
    int r;
    vector<vector<int>> memTable;
public:
    TablaDinamica(){
        vector<int> vector;
        this->v = vector;
        this->m = 0;
        this->r = 0;
    }
    TablaDinamica(vector<int> v, int r, int m){
        this->v = v;
        this->m = m;
        this->r = r;
        vector<int> fila(m,-1);
        vector<vector<int>> tablaValores(v.size(),fila);
        this->memTable = tablaValores;
    }
    vector<int> v_(){
        return this->v;
    }
    int divisor(){
        return this->m;
    }
    int resto(){
        return this->r;
    }
    vector<vector<int>> tablaMemoizacion(){
        return this->memTable;
    }
    bool dinamica(){
        return PD(1,modulo(v[0],m));
    }
    bool PD(int i, int64_t k){
        // i = iterador del vector
        // k = suma parcial
        if (i == v.size()) return (modulo(k,m) == r);

        if (memTable[i][k] != -1 ) return memTable[i][k];

        bool res = false;
        res = res or PD(i+1,modulo(k + v[i],m));
        res = res or PD(i+1,modulo(k * v[i],m));
        res = res or PD(i+1,modulo(k - v[i],m));
        res = res or PD(i+1, mod_bin_exp(k,v[i],m));
        //        res = res or PD(i+1,modulo(pow(k, v[i]),m));
        memTable[i][k] = res;
        return res;
    }
};


void leerInput(vector<vector<int>> &vs, vector<pair<int,int>> &rta) {
    int n,r,m,k, casos;
    cin >> casos;
    while (casos --){
        vector<int> v;
        cin >> n;
        cin >> r;
        cin >> m;
        for (int j =0; j<n;j++){
            cin >> k;
            v.push_back(k);
        }
        vs.push_back(v);
        rta.push_back(make_pair(r,m));
    }
}

int main() {
    //leer
    vector<vector<int>>vs;
    vector<pair<int,int>> rta;
    leerInput(vs,rta);
    vector<bool> res;


    //ejecutar y tomar el tiempo
//    auto start = high_resolution_clock::now();
    //llamar al algoritmo//
    for (int i=0;i<vs.size();i++){
        TablaDinamica tabla(vs[i],rta[i].first,rta[i].second);
        res.push_back(tabla.dinamica());
    }
//    auto stop = high_resolution_clock::now();
//    float tiempo = duration_cast<milliseconds>(stop - start).count();
//    tiempo = tiempo / 1000;

    //imprimir respuesta
    for(int i=0; i<res.size();i++){
        if (res[i])
            cout << "Si" << endl;
        else
            cout << "No" << endl;
    }
    //SOLO IMPRIMIR EN PANTALLA EL RESULTADO!!!
//    cout << "\n tardo: " << tiempo << " seg\n" << endl;

    return 0;
}