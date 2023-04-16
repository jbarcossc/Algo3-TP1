#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>
#include <sstream>
#include <list>
#include <cmath>

using namespace std;
using namespace std::chrono;

int modulo(int n, int d){
    if (n % d >= 0){
        return n % d;
    }
    return d - (n % d);
}

class TablaDinamica {
private:
    vector<int> v;
    int m;
    int r;
    vector<vector<bool>> memTable;
public:
    TablaDinamica(){
        vector<int> vector;
        this->v = vector;
        this->m = 0;
        this->r = 0;
        vector<vector<bool>> tablaValores;
        this->memTable = tablaValores;
    }
    TablaDinamica(vector<int> v, int m, int r){
        this->v = v;
        this->m = m;
        this->r = r;
        vector<int> fila(m,false);
        vector<vector<bool>> tablaValores(v.size(),fila);
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
    vector<vector<bool>> tablaMemoizacion(){
        return this->memTable;
    }
    bool dinamica(){
        return PD(0,0);
    }
    bool PD(int i, int k){
        if (i==0) return PD(i+1,this->v[i] % this->m);
        if (i==v.size()) return (k % this->m == this->r);

        bool res = false;

        if (this->memTable[i][modulo(k + this->v[i],this->m)]) {
            res = res or this->memTable[i][modulo(k + this->v[i],this->m)];
        } else {
            res = res or PD(i+1,modulo(k + this->v[i],this->m));
            this->memTable[i][modulo(k + this->v[i],this->m)] = res;
        }
        if (this->memTable[i][modulo(k - this->v[i],this->m)]) {
            res = res or this->memTable[i][modulo(k + this->v[i],this->m)];
        } else {
            res = res or PD(i+1,modulo(k - this->v[i],this->m));
            this->memTable[i][modulo(k - this->v[i],this->m)] = res;
        }
        if (this->memTable[i][modulo(k * this->v[i],this->m)]) {
            res = res or this->memTable[i][modulo(k * this->v[i],this->m)];
        } else {
            res = res or PD(i+1,modulo(k * this->v[i],this->m));
            this->memTable[i][modulo(k * this->v[i],this->m)] = res;
        }
        if (this->memTable[i][modulo(pow(k, this->v[i]),this->m)]) {
            res = res or this->memTable[i][modulo(pow(k, this->v[i]),this->m)];
        } else {
            res = res or PD(i+1,modulo(pow(k, this->v[i]),this->m));
            this->memTable[i][modulo(pow(k, this->v[i]),this->m)] = res;
        }
        return res;
    }
};


void leerInstancia(string &file, vector<vector<int>> &vs, vector<pair<int,int>> &rta){
    fstream instancia;
    int casos;
    instancia.open(file, ios::in);
    int n,r,m;
    int k;
    if (instancia.is_open()){
        instancia >> casos;
        for (int i=0 ; i<casos ; i++){
            vector<int> v;
            instancia >> n;
            instancia >> r;
            instancia >> m;
            for (int j =0; j<n;j++){
                instancia >> k;
                v.push_back(k);
            }
            vs.push_back(v);
            rta.push_back(make_pair(r,m));
        }
    }
    instancia.close();
}


int main() {
    //leer
    string file = "../instancias/ej1.in";
    vector<vector<int>>vs;
    vector<pair<int,int>> rta;
    leerInstancia(file,vs,rta);
    vector<bool> res;

    //ejecutar y tomar el tiempo
    auto start = high_resolution_clock::now();
    //llamar al algoritmo//
    for (int i=0;i<vs.size();i++){
        TablaDinamica tabla(vs[i],rta[i].first,rta[i].second);
        res.push_back(tabla.dinamica());
    }
    auto stop = high_resolution_clock::now();
    float tiempo = duration_cast<milliseconds>(stop - start).count();
    tiempo = tiempo / 1000;

    //imprimir respuesta
    for(int i=0; i<res.size();i++){
        if (res[i])
            cout << "Si" << endl;
        else
            cout << "No" << endl;
    }
    //SOLO IMPRIMIR EN PANTALLA EL RESULTADO!!!
    cout << "\n tardo: " << tiempo << " seg\n" << endl;

    return 0;
}