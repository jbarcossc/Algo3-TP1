#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>
#include <sstream>
#include "dinamica.cpp"

using namespace std;
using namespace std::chrono;



void leerInstancia(string &file, vector<vector<int>> &vs, vector<pair<int,int>> &rta){
    fstream instancia;
    int casos;
    instancia.open(file, ios::in);
    int n,r,w;
    int k;
    if (instancia.is_open()){
        instancia >> casos;
        for (int i=0 ; i<casos ; i++){
            vector<int> v;
            instancia >> n;
            instancia >> r;
            instancia >> w;
            for (int j =0; j<n;j++){
                instancia >> k;
                v.push_back(k);
            }
            vs.push_back(v);
            rta.push_back(make_pair(r,w));
        }

    }
    instancia.close();
}


int main() {
    //leer
    string file;
    vector<vector<int>>vs;
    vector<pair<int,int>> rta;
    leerInstancia(file,vs,rta);
    vector<bool> res;

    //ejecutar y tomar el tiempo
    auto start = high_resolution_clock::now();
    //llamar al algoritmo//

    auto stop = high_resolution_clock::now();
    float tiempo = duration_cast<milliseconds>(stop - start).count();
    tiempo = tiempo / 1000;
    for(int i=0; i<res.size();i++){
        if (res[i])
            cout << "Si" << endl;
        else
            cout << "No" << endl;
    }
    //SOLO IMPRIMIR EN PANTALLA EL RESULTADO!!!
    cout << "\n tardo: " << tiempo << " seg\n";

    return 0;
}