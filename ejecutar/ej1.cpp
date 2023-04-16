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
    int sumaAecuada;
public:
    NumeroMagico(){
        this->n = 0;
        Cuadrado matrix;
        this->mat = matrix;
        this->sumaAecuada = 0;
    }
    explicit NumeroMagico(int n) {
        this->n = n;
        Cuadrado matrix;
        for (int i = 0; i < this->n; i++) {
            vector<int> row(this->n,0);
            matrix.push_back(row);
        }
        this->mat = matrix;
        this->sumaAecuada = (pow(n, 3) + n) / 2; // JUSTIFICADO POR ENUNCIADO
    }
    int size(){
        return this->n;
    }
    int sumaAdecuada(){
        return this->sumaAecuada;
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

    bool filaLlenas(int fila){
        for (int j = 0; j < this->n; j++) {
            if(this->mat[fila][j] <= 0){
                return false;
            }
        }
        return true;
    }     // Retorna si la fila pasada por paramtro esta llena


    bool columnaLlenas(int col){
        for (int i = 0; i < this->n; i++) {
            if(this->mat[i][col] <= 0){
                return false;
            }
        }
        return false;
    } // Retorna si la columna pasada por paramtro esta llena

    bool estaLleno() {
        bool res= true;
        for (int i =0; i< this->n; i++){
            res &= this->filaLlenas(i) ;
        }
        return res;
    }
    int sumaFila(int fila){
        int suma = 0;
        for(int i = 0; i < this->n; i++){
            suma += this->mat[fila][i];
        }
        return suma;
    }
    int sumaCol(int columna){
        int suma = 0;
        for(int i = 0; i < this->n; i++){
            suma += this->mat[i][columna];
        }
        return suma;
    }
    pair<int,int> sumaDiagonal(){
        pair<int,int> res;
        // suma1 corresponde a la diagonal que surge desde la casilla (0,0) y recorre hasta la casilla (n-1,n-1)
        int suma1 = 0;
        // suma2 corresponde a la diagonal que surge desde la casilla (n-1,0) y recorre hasta la casilla (0,n-1)
        int suma2 = 0;
        for(int i = 0; i < this->n; i++){
            suma1 += this->mat[i][i];
            suma2 += this->mat[this->n - i - 1][i];
        }
        res.first = suma1;
        res.second = suma2;
        return res;
    }
    bool esMagico() {
        if(!this->estaLleno()){
            return false;
        }
        int suma = this->sumaFila(0);
        for(int i = 0; i < this->n; i++) {
            if(this->sumaFila(i) != suma || this->sumaCol(i) != suma){
                return false;
            }
        }
        pair<int,int> sumaDiag = this->sumaDiagonal();
        return(sumaDiag.first == suma && sumaDiag.second == suma);
    }

    void rellenarCasilla(int fila, int columna, int valor) {
        // Debe cumplir: fila y columna en rango y valor válido
        bool filaEnRango = fila >= 0 && fila < this->n;
        bool colEnRango = columna >= 0 && columna < this->n;
        bool valorEnRango = valor > 0 && valor <= (pow(this->n,2));
        if (filaEnRango && colEnRango && valorEnRango) {
//        cout << "[" << fila << ", " << columna << "]" << endl;
            this->mat[fila][columna] = valor;
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

//auxiliares

void generarCuadradosRecursivos(NumeroMagico &c, vector<bool> &valores, int i, vector<NumeroMagico> &res, int &filaSumParcial, int &colSumParcial) {
    if (i == (pow(c.size(), 2))) {
        if(c.esMagico()){
            res.push_back(c);
        }
    }
    int fila = floor(i / c.size());
    int columna =i % c.size();

    if (fila >= c.size() ) return;

//     PODAS
//    int valorSumaAdecuado = (pow(c.size(), 3) + c.size()) / 2; // JUSTIFICADO POR ENUNCIADO
//    // CHEQUEAR FILA RECIEN COMPLETADA
//    bool filaRecienCompletadaMal = c.filaLlenas(fila) && columna == 0 && c.sumaFila(fila) != valorSumaAdecuado;
//    // CHEQUEAR SI LA FILA ACTUAL YA SE PASO DEL VALOR
//    bool filaYaSePaso = c.sumaFila(fila) > valorSumaAdecuado;
//    // CHEQUEAR COLUMNA RECIEN COMPLETADA
//    bool columnaRecienCompletadaMal =
//            fila == c.size() - 1 && columna > 0 && c.sumaCol(columna - 1) != valorSumaAdecuado;
//    // CHEQUEAR SI LA COLUMNA ACTUAL YA SE PASO DEL VALOR
//    bool columnaYaSePaso = c.sumaCol(columna) > valorSumaAdecuado;
//    // CHEQUEAR DIAGONAL COMPLETA
//    bool diagonalMal = fila == (c.size() - 1) && columna > 0 && c.sumaDiagonal().second != valorSumaAdecuado;



    if (!(filaRecienCompletadaMal || filaYaSePaso || columnaRecienCompletadaMal || columnaYaSePaso || diagonalMal)) {
        for (int j = 0; j < valores.size(); j++) {
            if (valores[j]) {

                    //poda para ver la suma parcial
                    if (podaSumaParcial(filaSumParcial,colSumParcial, j, c.sumaAdecuada(), fila, columna, c.size())) {
                        NumeroMagico nuevoCuadrado = c;
                        nuevoCuadrado.rellenarCasilla(fila, columna, j + 1);
                        vector<bool> nuevoVectorValores = valores;
                        nuevoVectorValores[j] = false;
                        generarCuadradosRecursivos(nuevoCuadrado, nuevoVectorValores, i + 1, res);
                    }
                }

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

    auto start = high_resolution_clock::now();


    generarCuadradosRecursivos(cuadrado, vals, 0, res);

    auto stop2 = high_resolution_clock::now();
    float tiempo2 = duration_cast<milliseconds>(stop2 - start).count(); //milisegundos
    tiempo2 = tiempo2 / 1000; // pasar a segundos
    cout << "generarCuadrado Recursivoo: " << tiempo2 << " seg\n";

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