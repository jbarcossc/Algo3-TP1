#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>
#include <sstream>

using namespace std;
using namespace std::chrono;

struct Actividad
{
    int ini;
    int fin;
};

vector<Actividad> bucketSort(pair<int, vector<Actividad>> a)
{
    int n = a.first;
    vector<Actividad> actividades = a.second;
    vector<Actividad> res;

    vector<int> vacio = {};
    vector<vector<int>> vec(2 * n, vacio);

    // creo los buckets
    for (int i = 0; i < n; i++)
    { // O(n)
        vec[actividades[i].fin - 1].push_back(i);
    }
    // formo res
    for (int i = 0; i < 2 * n; i++)
    {
        for (int j = 0; j < vec[i].size(); j++)
        {
            res.push_back(actividades[vec[i][j]]);
        }
    }
    return res;
}

bool esCompatible(Actividad anterior, Actividad a)
{
    if (anterior.fin == -1)
        return true;
    return anterior.fin < a.ini;
}

vector<int> greedy(pair<int, vector<Actividad>> a)
{ // O(n)
    vector<Actividad> actividades = a.second;
    actividades = bucketSort(a); // O(n)
    vector<int> res;

    Actividad anterior;
    anterior.fin = -1;
    for (int i = 0; i < actividades.size(); i++)
    { // O(n)
        if (esCompatible(anterior, actividades[i]))
        {
            res.push_back(i);
            anterior = actividades[i];
        }
    }
    return res;
}

int main(int argc, char **argv)
{

    // leo intancia
//    std::ios::sync_with_stdio(false);
//    std::cin.tie(0);
//    string _ignore;

    int n;
    cin >> n;
    vector<Actividad> actividades;
    for (int j = 0; j < n; j++)
    {
        int s;
        int t;
        cin >> s;
        cin >> t;
        Actividad a;
        a.ini = s;
        a.fin = t;
        actividades.push_back(a);
    }
    pair<int, vector<Actividad>> instancia;
    instancia.first = n;
    instancia.second = actividades;

//    // corro el algoritmo y le tomo el tiempo
//    auto start = high_resolution_clock::now();
//    auto stop = high_resolution_clock::now();
//    float tiempo = duration_cast<milliseconds>(stop - start).count();
//    tiempo = tiempo / 1000;
//    cout << res << "\t\t\t\t" << tiempo << "\n";
    vector<int> res = greedy(instancia);
    cout << res.size() << endl;
    for (int i=0; i< res.size();i++){
        cout << res[i] << " ";
    }

    return 0;
}
