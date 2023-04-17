#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>
#include <sstream>
#include <algorithm>
#include <cmath>

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

    int sumaFila(int fila){
        return this->sumas[0][fila];
    }

    int sumaCol(int columna){
        return this->sumas[1][columna];
    }

    pair<int,int> sumaDiagonal(){
        return this->sumasDiagonales;
    }

    bool esCuadradoMagico() {
        return this->esMagico;
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
        } else {
            // PRINT ERROR: INVALID ARGUMENTS
            if (!filaEnRango) cout<< "filaEnRango" << endl;
            if (!colEnRango) cout<< "colEnRango" << endl;
            if (!valorEnRango) cout<< "valorEnRango" << endl;
            cout << "Error al rellenar casilla [" << to_string(fila) << ", " << to_string(columna) << "] con el valor " << to_string(valor) << endl;
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

void generarCuadradosRecursivos(NumeroMagico &c, vector<bool> &valores, int i, vector<NumeroMagico> &res) {
    if (i == (pow(c.size(), 2))) {
        if(c.esCuadradoMagico()){
            res.push_back(c);
        }
    }
    int fila = floor(i / c.size());
    int columna = i % c.size();
    if (fila >= c.size()) return;

    if (c.esCuadradoMagico()) {
        for (int j = 0; j < valores.size(); j++) {
            if (valores[j]) {
                    NumeroMagico nuevoCuadrado = c;
                    nuevoCuadrado.rellenarCasilla(fila, columna, j + 1);
                    vector<bool> nuevoVectorValores = valores;
                    nuevoVectorValores[j] = false;
                    generarCuadradosRecursivos(nuevoCuadrado, nuevoVectorValores, i + 1, res);
                }
            }
        }
    }

bool podaSumaParcial(int &filaSum, int &colSum,  int j, int &sumaAdecuada, int &fila, int &col, int &n) {
    if (fila == 0) colSum =0;
    if (col == 0) filaSum =0;

    bool res = true;
    res &= filaSum + j <= sumaAdecuada;
    res &= colSum + j <= sumaAdecuada;

}

vector<NumeroMagico> generarCuadrados(int n){
    NumeroMagico cuadrado = NumeroMagico(n);
    vector<bool> vals (pow(n,2), true);
    vector<NumeroMagico> res;

    //auto start = high_resolution_clock::now();


    generarCuadradosRecursivos(cuadrado, vals, 0, res);

    //auto stop2 = high_resolution_clock::now();
    //float tiempo2 = duration_cast<milliseconds>(stop2 - start).count(); //milisegundos
    //tiempo2 = tiempo2 / 1000; // pasar a segundos
    //cout << "generarCuadrado Recursivoo: " << tiempo2 << " seg\n";

    return res;
}

bool comparador( NumeroMagico &a, NumeroMagico &b){
    return a<b;
}

int main() {
    //leer
    int n,k;
    cin >> n;
    cin >> k;
    //llamar al algoritmo//
    auto start = high_resolution_clock::now();

    vector<NumeroMagico> cuadradosMagicos = generarCuadrados(n);

    auto stop = high_resolution_clock::now();
    float tiempo = duration_cast<milliseconds>(stop - start).count(); //milisegundos
    tiempo = tiempo / 1000; // pasar a segundos
    cout << "tardo: " << tiempo << " seg\n";

    sort(cuadradosMagicos.begin(), cuadradosMagicos.end(), comparador);

    if (k-1>=cuadradosMagicos.size()){
        cout << "-1" << endl;
    } else {
        NumeroMagico kEsimo = cuadradosMagicos[k-1];
        cout << kEsimo << endl;
    }
    return 0;
}