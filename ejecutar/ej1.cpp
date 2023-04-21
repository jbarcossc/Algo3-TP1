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
    vector<bool> valores;

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
        vector<bool> valores;
        this->valores = valores;
    }

    explicit NumeroMagico(int n) {
        this->n = n;
        Cuadrado matrix;
        for (int i = 0; i < this->n; i++) {
            vector<int> row(this->n,0);
            matrix.push_back(row);
        }
        this->mat = matrix;
        this->sumaAdecuada = (pow(n, 3) + n) / 2; // JUSTIFICADO POR ENUNCIADO
        this->esMagico = true;
        vector<int> filas(n, 0);
        vector<vector<int>> sumas(2, filas);
        this->sumas = sumas;
        this->sumasDiagonales = {0,0};
        vector<bool> valores(n*n + 1, false);
        this->valores = valores;
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

    void setVal(int i, bool val){
        this->valores[i] = val;
    }

    bool esta(int a){
        return this->valores[a];
    }

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

    void rellenarCasilla(int fila, int columna, int valor) {
        bool filaEnRango = fila >= 0 && fila < this->n;
        bool colEnRango = columna >= 0 && columna < this->n;
        bool valorEnRango = valor > 0 && valor <= (pow(this->n,2));
        if (filaEnRango && colEnRango && valorEnRango) {
            // ACTUALIZAR VALORES
            int valorPrevio = this->mat[fila][columna];
            this->mat[fila][columna] = valor;
            this->sumas[0][fila] += valor - valorPrevio;
            this->sumas[1][columna] += valor - valorPrevio;
            // SUMAS DIAGONALES
            if(fila == columna) {
                this->sumasDiagonales.first += valor - valorPrevio;
            }
            if((this->n - columna - 1) == fila) {
                this->sumasDiagonales.second += valor - valorPrevio;
            }
            // ACTUALIZAR ES MAGICO
            if(columna == (this->n - 1)) {
                this->esMagico = this->esMagico && (this->sumas[0][fila] == this->sumaAdecuada);
            }
            if(fila == (this->n - 1)) {
                this->esMagico = this->esMagico && (this->sumas[1][columna] == this->sumaAdecuada);
            }
            if(fila == (this->n - 1) && columna == (this->n - 1)) {
                this->esMagico = this->esMagico && (this->sumasDiagonales.first == this->sumaAdecuada);
            }
            if(fila == (this->n - 1) && columna == 0) {
                this->esMagico = this->esMagico && (this->sumasDiagonales.second == this->sumaAdecuada);
            }
            this->esMagico = this->esMagico && (this->sumas[0][fila] + (this->n * this->n * (this->n - columna - 1)) >= this->sumaAdecuada);
            this->esMagico = this->esMagico && (this->sumas[1][columna] + (this->n * this->n * (this->n - fila - 1)) >= this->sumaAdecuada);
        }
    }

};

void generarCuadradosRecursivos(NumeroMagico &c, int i, int &k, int &s, bool &exit) {
    if (exit) return;
    if (i == c.size() * c.size() ) {
        if(c.esCuadradoMagico()){
            s++;
            if(s == k){
                exit = true;
                return;
            }
        }
    }
    int fila = floor(i / c.size());
    int columna = i % c.size();
    if (fila >= c.size() || exit){
        return;
    }
    if (c.esCuadradoMagico()) {
        for (int j = 1; j <= c.size() * c.size(); j++) {
            if (!c.esta(j)) {
                c.rellenarCasilla(fila, columna, j);
                c.setVal(j, true);
                generarCuadradosRecursivos(c, i + 1, k, s, exit);
                if(exit) return;
                c.setVal(j, false);
                c.rellenarCasilla(fila, columna, 0);
                c.setMagico();
            }
        }
    }
}

void generarCuadrados(int &n, int &k){
    NumeroMagico cuadrado = NumeroMagico(n);
    int s = 0;
    bool exit = false;
    generarCuadradosRecursivos(cuadrado, 0, k, s, exit);
    if(exit){
        cout << cuadrado << endl;
    } else {
        cout << "-1" << endl;
    }
}

int main() {
    int n,k;
    cin >> n;
    cin >> k;
    generarCuadrados(n,k);
    return 0;
}