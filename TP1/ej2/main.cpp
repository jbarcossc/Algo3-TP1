#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>
#include <sstream>
#include "dinamica.h"

using namespace std;
using namespace std::chrono;



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
        TablaDinamica tabla(vs[i],rta[i].first,rta[i].second));
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