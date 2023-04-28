#include <iostream>
#include <vector>
#include <stdlib.h>
#include <chrono>
#include <sstream>
#include <cmath>
#include <list>

using namespace std;
using namespace std::chrono;

using Cuadrado = vector<vector<int>>;

class NumeroMagico {
private:
    int n;
    Cuadrado mat;
    int sumaAdecuada;
    bool esMagico;
    vector<vector<int>> sumas;
    pair<int, int> sumasDiagonales;
    list<bool> valores;
    bool exit;


public:
    NumeroMagico(){
        this->n = 0;
        Cuadrado matrix;
        this->mat = matrix;
        this->sumaAdecuada = 0;
        this->esMagico = true;
        vector<vector<int>> sumas;
        this->sumas = sumas;
        pair<int, int> diags;
        this->sumasDiagonales = diags;
        list<bool> valores;
        this->valores = valores;
        this->exit= false;
    }

    explicit NumeroMagico(int n) {
        this->n = n;
        Cuadrado matrix;
        for (int i = 0; i < this->n; i++) {
            vector<int> row(this->n,0);
            matrix.push_back(row);
        }
        this->mat = matrix;
        this->sumaAdecuada = (n*n*n + n) / 2; // JUSTIFICADO POR ENUNCIADO
        this->esMagico = true;
        vector<int> filas(n, 0);
        vector<vector<int>> sumas(2, filas);
        this->sumas = sumas;
        this->sumasDiagonales = {0,0};
        list<bool> valores(n*n + 1, false);
        this->valores = valores;
        this->exit = false;
    }

    int size(){
        return this->n;
    }

    Cuadrado cuadrado(){
        return this->mat;
    }

    int size() const{
        return this->n;
    }

    Cuadrado cuadrado() const{
        return this->mat;
    }

    int at(int fila, int columna){
        return this->mat[fila][columna];
    }

    bool esCuadradoMagico() {
        return this->esMagico;
    }

    void setMagico(){
        this->esMagico = true;
    }
/*
    void setVal(int i, bool val){
        this->valores[i] = val;
    }

    bool esta(int a){
        return this->valores[a];
    }
*/
    bool operator< ( NumeroMagico &b){
        //asumo que son del mismo size
        for (int i = 0; i < mat.size() ; ++i) {
            for (int j = 0; j < mat[0].size(); ++j) {
                if (mat[i][j] < b.at(i,j)) return true;
                if (mat[i][j] > b.at(i,j)) return false;
            }
        }
        return false;
    }

    NumeroMagico& operator = (const NumeroMagico& b){
        this->n = b.size();
        this->mat = b.cuadrado();
        this->esMagico = b.esMagico;
        this->sumas = b.sumas;
        this->sumasDiagonales = b.sumasDiagonales;
        this->sumaAdecuada = b.sumaAdecuada;
        return *this;
    }

    friend ostream &operator<<(ostream &out, const NumeroMagico& b){
        for (int i=0;i<b.n;i++){
            for (int j=0; j<b.n; j++){
                out << to_string(b.mat[i][j]) << "\t";
            }
            out << "\n";
        }
        return out;
    }

    bool exit_(){
        return this->exit;
    }

    list<bool>::iterator it(){
        auto it = this->valores.begin();
        return it;
    }

    void vaciarCasilla(int fila,int columna){
            int valorPrevio = this->mat[fila][columna];
            this->mat[fila][columna] = 0;
            // SUMAS
            this->sumas[0][fila] -= valorPrevio;
            this->sumas[1][columna] -=  valorPrevio;
            // SUMAS DIAGONALES
            if(fila == columna) {
                this->sumasDiagonales.first -= valorPrevio;
            }
            if((this->n - columna - 1) == fila) {
                this->sumasDiagonales.second -= valorPrevio;
            }
    }

    bool hayQuePodar(int fila, int columna, int valor){
        // true si  poda
        bool res = true;
        // columna
        if(columna == n - 1) {
           res &= sumas[0][fila] + valor == sumaAdecuada;
        }
        else if(columna < n - 1) {
            res &= sumas[0][fila] + valor < sumaAdecuada;
        }
        // fila
        if(fila == n - 1) {
            res &= sumas[1][columna] + valor == sumaAdecuada;
        }
        else if(fila < n - 1) {
            res &= sumas[1][columna] + valor < sumaAdecuada;
        }
        //diagonales
        if (fila == columna) {
            res &=  this->sumasDiagonales.first + valor <= sumaAdecuada;
        }
        if (fila + columna == n - 1){
            res &=  this->sumasDiagonales.second + valor <= sumaAdecuada;
        }

        return !res;
    }

    bool rellenarCasilla(int fila, int columna, int valor) {
        // devulve true si se pudo rellenar
        bool filaEnRango = fila >= 0 && fila < this->n;
        bool colEnRango = columna >= 0 && columna < this->n;
        bool valorEnRango = valor > 0 && valor <= n*n;
        bool res = filaEnRango && colEnRango && valorEnRango;
        res &= !hayQuePodar(fila,columna,valor);
        if (res) {
            this->mat[fila][columna] = valor;
            // SUMAS
            this->sumas[0][fila] += valor;
            this->sumas[1][columna] += valor;
            // SUMAS DIAGONALES
            if(fila == columna) {
                this->sumasDiagonales.first += valor;
            }
            if((this->n - columna - 1) == fila) {
                this->sumasDiagonales.second += valor;
            }
            res =  true;
            }
        return res;
}


    bool generarCuadradosRecursivos( int fila, int columna, int &k) {
        if (k == 0 ) {
            return true ;
        }

        // checkear si lleagmos al final
        if (fila == n) {
            if (sumasDiagonales.first == sumaAdecuada && sumasDiagonales.second == sumaAdecuada){
                k--;
                return k==0;
            }
           return false;
        }

        // moverse a la sig fila
        int next_fila = fila;
        int next_col = columna + 1;
        if (next_col == n) {
            next_fila++;
            next_col = 0;
        }

//        int fila = floor(i / n);
//        int columna = i % n;

        list<bool>::iterator it = this->valores.begin();
        for (int j = 1; j <= n*n; j++) {
            if (!(*it)) {
                if(rellenarCasilla(fila, columna, j)) {
                    *it = true;
                    if (generarCuadradosRecursivos( next_fila,next_col , k)){
                        return true;
                    }
                }
                vaciarCasilla(fila,columna);
                *it = false;
            }
            advance(it,1);
        }
        return  false;
    }

};


void generarCuadrados(int n, int k){
    NumeroMagico cuadrado = NumeroMagico(n);

    if(cuadrado.generarCuadradosRecursivos( 0,0, k)){
        cout << cuadrado << endl;
    } else {
//        cout << cuadrado << endl;
        cout << "-1" << endl;
    }
}

int main() {
    int n,k;
    cin >> n;
    cin >> k;
//    auto start = high_resolution_clock::now();
    generarCuadrados(n,k);
//    auto stop = high_resolution_clock::now();
//    float duration = duration_cast<milliseconds>(stop - start).count();
//    duration = duration / 1000;
//    cout << "tiempo: "<<duration << endl;
    return 0;
}