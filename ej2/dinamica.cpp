#include "dinamica.h"

bool TablaDinamica::dinamica(){
    return PD(0,0);
}

bool TablaDinamica::PD(int i, int k){
    if (i==0) return PD(i+1,this->v[i] % this->m,);
    if (i==v.size()) return (k % this->m == this->r);

    bool res = false;

    if (this->tabla[i][modulo(k + this->v[i],this->m)]) {
        res = res or this->tabla[i][modulo(k + this->v[i],this->m)];
    } else {
        res = res or PD(i+1,modulo(k + this->v[i],this->m));
        this->tabla[i][modulo(k + this->v[i],this->m)] = res;
    }
    if (this->tabla[i][modulo(k - this->v[i],this->m)]) {
        res = res or this->tabla[i][modulo(k + this->v[i],this->m)];
    } else {
        res = res or PD(i+1,modulo(k - this->v[i],this->m));
        this->tabla[i][modulo(k - this->v[i],this->m)] = res;
    }
    if (this->tabla[i][modulo(k * this->v[i],this->m)]) {
        res = res or this->tabla[i][modulo(k * this->v[i],this->m)];
    } else {
        res = res or PD(i+1,modulo(k * this->v[i],this->m));
        this->tabla[i][modulo(k * this->v[i],this->m)] = res;
    }
    if (this->tabla[i][modulo(pow(k, this->v[i]),this->m)]) {
        res = res or this->tabla[i][modulo(pow(k, this->v[i]),this->m)];
    } else {
        res = res or PD(i+1,modulo(pow(k, this->v[i]),this->m));
        this->tabla[i][modulo(pow(k, this->v[i]),this->m)] = res;
    }
    return res;
}



TablaDinamica::TablaDinamica() {
    vector<int> vector;
    this->v = vector;
    this->m = 0;
    this->r = 0;
    vector<vector<int>> tablaValores;
    this->tabla = tablaValores;
}

TablaDinamica::TablaDinamica(vector<int> v, int m, int r) {
    this->v = v;
    this->m = m;
    this->r = r;
    vector<int> fila(m,false);
    vector<vector<int>> tablaValores(v.size(),fila);
    this->tabla = tablaValores;
}

vector<int> TablaDinamica::vector() {
    return this->v;
}

int TablaDinamica::divisor() {
    return this->m;
}

int TablaDinamica::resto() {
    return this->r;
}

vector<vector<bool>> TablaDinamica::tablaValores(){
    return this->tabla;
}