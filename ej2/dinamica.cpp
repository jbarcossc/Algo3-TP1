#include "dinamica.h"

bool dinamica(vector<int> &v, int &m, int &r){
    return PD(v,0,0,&m,&r);
}

bool PD(vector<int> &v, int i, int k, int &m, int &r){
    if (i==0) return PD(v,i+1,v[i],m,r);
    if (i==v.size()) return (k % m == r);

    bool res = false;
    res = res or PD(v,i+1,k + v[i],m,r);
    res = res or PD(v,i+1,k - v[i],m,r);
    res = res or PD(v,i+1,k * v[i],m,r);
    res = res or PD(v,i+1,k^(v[i]),m,r);
    return res;
}