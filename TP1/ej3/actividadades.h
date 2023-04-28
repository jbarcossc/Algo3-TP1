#include "vector"

using namespace std;

#ifndef ALGO3_TP1_ACTIVIDADADES_H
#define ALGO3_TP1_ACTIVIDADADES_H

struct Actividad
{
    int ini;
    int fin;
};



vector<int> greedy(vector<pair<int,int>> &s);

#endif //ALGO3_TP1_ACTIVIDADADES_H
