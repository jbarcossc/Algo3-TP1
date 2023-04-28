#include "auxiliares.h"

vector<numeroMagico> generarCuadrados(int n){
    numeroMagico cuadrado = numeroMagico(n);
    vector<bool> vals (pow(n,2), true);
    vector<numeroMagico> *resPointer = new vector<numeroMagico>;
    generarCuadradosRecursivos(cuadrado, vals, 0, resPointer);
    return *resPointer;
}

void generarCuadradosRecursivos(numeroMagico c, vector<bool> valores, int i, vector<numeroMagico> *resPointer) {
    if (i == (pow(c.size(), 2))) {
        if(c.esMagico()){
            (*resPointer).push_back(c);
        }
    }
    int fila = floor(i / c.size());
    int columna =i % c.size();

    if (fila >= c.size() ) return; //////////////


    // PODAS
    int valorSumaAdecuado = (pow(c.size(), 3) + c.size()) / 2; // JUSTIFICADO POR ENUNCIADO
    // CHEQUEAR FILA RECIEN COMPLETADA
    bool filaRecienCompletadaMal = c.filasLlenas() >= 1 && columna == 0 && c.sumaFila(fila - 1) != valorSumaAdecuado;
    // CHEQUEAR SI LA FILA ACTUAL YA SE PASO DEL VALOR
    bool filaYaSePaso = c.sumaFila(fila) > valorSumaAdecuado;
    // CHEQUEAR COLUMNA RECIEN COMPLETADA
    bool columnaRecienCompletadaMal =
            fila == c.size() - 1 && columna > 0 && c.sumaCol(columna - 1) != valorSumaAdecuado;
    // CHEQUEAR SI LA COLUMNA ACTUAL YA SE PASO DEL VALOR
    bool columnaYaSePaso = c.sumaCol(columna) > valorSumaAdecuado;
    // CHEQUEAR DIAGONAL COMPLETA
    bool diagonalMal = fila == (c.size() - 1) && columna > 0 && c.sumaDiagonal().second != valorSumaAdecuado;

    if (!(filaRecienCompletadaMal || filaYaSePaso || columnaRecienCompletadaMal || columnaYaSePaso || diagonalMal)) {
        for (int j = 0; j < valores.size(); j++) {
            if (valores[j]) {
                numeroMagico nuevoCuadrado = c;
                nuevoCuadrado.rellenarCasilla(fila, columna, j + 1);
                vector<bool> nuevoVectorValores = valores;
                nuevoVectorValores[j] = false;
                generarCuadradosRecursivos(nuevoCuadrado, nuevoVectorValores, i + 1, resPointer);
            }
        }
    }
}


bool comparador( numeroMagico &a, numeroMagico &b){
    return a<b;
}
