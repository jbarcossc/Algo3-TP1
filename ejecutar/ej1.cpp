#include <iostream>
#include <vector>
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

    bool esCuadradoMagico() {
        return this->esMagico;
    }

    bool probar(int &fila, int &columna, int valor){
        bool prevEsMagico = this->esMagico;
        this->rellenarCasilla(fila, columna, valor);
        bool res = this->esMagico;
        this->rellenarCasilla(fila, columna, 0);
        this->sumas[0][fila] -= valor;
        this->sumas[1][columna] -= valor;
        if(fila == columna) {
            this->sumasDiagonales.first -= valor;
        }
        if((this->n - columna - 1) == fila) {
            this->sumasDiagonales.second -= valor;
        }
        this->esMagico = prevEsMagico;
        return res;
    }

    void rellenarCasilla(int fila, int columna, int valor) {
        bool filaEnRango = fila >= 0 && fila < this->n;
        bool colEnRango = columna >= 0 && columna < this->n;
        bool valorEnRango = valor > 0 && valor <= (pow(this->n,2));
        if (filaEnRango && colEnRango && valorEnRango) {
            // ACTUALIZAR VALORES
            this->mat[fila][columna] = valor;
            this->sumas[0][fila] += valor;
            this->sumas[1][columna] += valor;
            // SUMAS DIAGONALES
            if(fila == columna) {
                this->sumasDiagonales.first += valor;
            }
            if((this->n - columna - 1) == fila) {
                this->sumasDiagonales.second += valor;
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

    bool operator< ( NumeroMagico &b){
        //asumo que son del mismo size
        for (int i = 0; i < mat.size() ; ++i) {
            for (int j = 0; j < mat[0].size(); ++j) {
                if (mat[i][j] < b.cuadrado()[i][j]) return true;
                if (mat[i][j] > b.cuadrado()[i][j]) return false;
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

};

void generarCuadradosRecursivos(NumeroMagico &c, vector<bool> &valores, int i, list<NumeroMagico> &res, int k) {
    if (i == (pow(c.size(), 2))) {
        if(c.esCuadradoMagico()){
            res.push_back(c);
        }
    }
    int fila = floor(i / c.size());
    int columna = i % c.size();
    if (fila >= c.size() || res.size() >= k) return;

    if (c.esCuadradoMagico()) {
        for (int j = 0; j < valores.size(); j++) {
            if (valores[j]) {
                if(c.probar(fila, columna, j+1)){
                    NumeroMagico nuevoCuadrado = c;
                    nuevoCuadrado.rellenarCasilla(fila, columna, j + 1);
                    vector<bool> nuevoVectorValores = valores;
                    nuevoVectorValores[j] = false;
                    generarCuadradosRecursivos(nuevoCuadrado, nuevoVectorValores, i + 1, res, k);
                }
            }
        }
    }
}

list<NumeroMagico> generarCuadrados(int n, int k){
    NumeroMagico cuadrado = NumeroMagico(n);
    vector<bool> vals (pow(n,2), true);
    list<NumeroMagico> res;
    generarCuadradosRecursivos(cuadrado, vals, 0, res, k);
    return res;
}

int main() {
    int n,k;
    cin >> n;
    cin >> k;
    list<NumeroMagico> cuadradosMagicos = generarCuadrados(n,k);
    auto it = cuadradosMagicos.begin();
    if (k-1>=cuadradosMagicos.size()){
        cout << "-1" << endl;
    } else {
        advance(it, k-1);
        NumeroMagico kEsimo = *it;
        cout << kEsimo << endl;
    }
    return 0;
}