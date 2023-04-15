#include "numeroMagico.h"

NumeroMagico::NumeroMagico() {
    this->n = 0;
    Cuadrado matrix;
    this->mat = matrix;
}

NumeroMagico::NumeroMagico(const int n) {
    this->n = n;
    Cuadrado matrix;
    for (int i = 0; i < this->n; i++) {
        vector<int> row(this->n,0);
        matrix.push_back(row);
    }
    this->mat = matrix;
}

int NumeroMagico::size() {
    return this->n;
}

Cuadrado NumeroMagico::cuadrado() {
    return this->mat;
}

int NumeroMagico::size() const {
    return this->n;
}

Cuadrado NumeroMagico::cuadrado() const {
    return this->mat;
}

int NumeroMagico::filasLlenas(){
    int res = 0;
    for (int i = 0; i < this->n; i++) {
        for (int j = 0; j < this->n; j++) {
            if(this->mat[i][j] <= 0){
                return res;
            }
        }
        res++;
    }
    return res;
}

int NumeroMagico::columnasLlenas() {
    int res = 0;
    for (int j = 0; j < this->n; j++) {
        for (int i = 0; i < this->n; i++) {
            if(this->mat[i][j] <= 0){
                return res;
            }
        }
        res++;
    }
    return res;
}

bool NumeroMagico::estaLleno() {
    return(this->filasLlenas() == this->n);
}

void NumeroMagico::rellenarCasilla(int fila, int columna, int valor) {
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

int NumeroMagico::sumaFila(int fila) {
    int suma = 0;
    for(int i = 0; i < this->n; i++){
        suma += this->mat[fila][i];
    }
    return suma;
}

int NumeroMagico::sumaCol(int columna) {
    int suma = 0;
    for(int i = 0; i < this->n; i++){
        suma += this->mat[i][columna];
    }
    return suma;
}

pair<int, int> NumeroMagico::sumaDiagonal() {
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

bool NumeroMagico::esMagico() {
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

//ostream& NumeroMagico::operator<< (ostream &out, const NumeroMagico& b){
//    for (int i=0;i<b.n;i++){
//        for (int j=0; j<b.n; j++){
//            out<< this->b.mat[i][j] << "\t";
//        }
//        out << "\n";
//    }
//    return out;
//}

bool NumeroMagico::operator< (NumeroMagico &b){
    //asumo que son del mismo size
    for (int i = 0; i < mat.size() ; ++i) {
        for (int j = 0; j < mat[0].size(); ++j) {
            if (mat[i][j] < b.cuadrado()[i][j]) return true;
            if (mat[i][j] > b.cuadrado()[i][j]) return false;
        }
    }
    return false;
}

NumeroMagico& NumeroMagico::operator =(const NumeroMagico& b) {
    this->n = b.size();
    this->mat = b.cuadrado();
    return *this;
}
