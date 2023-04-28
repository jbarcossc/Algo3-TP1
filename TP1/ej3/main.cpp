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

vector<int> bucketSort(vector<Actividad> &actividades)
{
    int n = actividades.size();
    vector<Actividad> ordenado;
    vector<int> res;

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
            ordenado.push_back(actividades[vec[i][j]]);
            res.push_back(vec[i][j]);
        }
    }
    actividades=ordenado;
    return res;
}

bool esCompatible(Actividad anterior, Actividad a)
{
    if (anterior.fin == -1)
        return true;
    return anterior.fin <= a.ini;
}



vector<int> greedy(vector<Actividad> actividades)
{ // O(n)
    vector<int> posiciones = bucketSort(actividades); // O(n)
    vector<int> res;

    Actividad anterior;
    anterior.fin = -1;
    for (int i = 0; i < actividades.size(); i++)
    { // O(n)
        if (esCompatible(anterior, actividades[i]))
        {
            res.push_back(posiciones[i]+1);
            anterior = actividades[i];
        }
    }
    return res;
}

int main(int argc, char **argv)
{

    // leo intancia
    int n;
    cin >> n;
    vector<Actividad> actividades;
    while(n--){
        int s;
        int t;
        cin >> s;
        cin >> t;
        Actividad a;
        a.ini = s;
        a.fin = t;
        actividades.push_back(a);
    }

    vector<int> res = greedy(actividades);
    cout << res.size() << endl;
    for (int i=0; i< res.size();i++){
        cout << res[i] << " ";
    }
    cout << endl;
    return 0;
}
