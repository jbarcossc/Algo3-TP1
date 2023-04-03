//
// Created by Lautaro on 2/4/2023.
//

#include "auxiliares.h"

list<numeroMagico> generarCuadrados(int n){
    numeroMagico cuadrado = numeroMagico(n);
    vector<bool> vals (n^2,true);
    return(generarCuadradosRecursivos(cuadrado, vals, 0));
}

list<numeroMagico> generarCuadradosRecursivos(numeroMagico c, vector<bool> valores, int i){
    list<numeroMagico> res;
    if(i == c.size()) {
        res.push_back(c);
        return res;
    }
    int fila = floor(i / c.size());
    int columna = i % c.size();

    // PODAS
    int valorSumaAdecuado = (c.size()^3 + c.size()) / 2; // JUSTIFICADO POR ENUNCIADO
    // CHEQUEAR FILA RECIEN COMPLETADA
    if(c.filasLlenas() >= 1 && columna == 0 && c.sumaFila(fila - 1) != valorSumaAdecuado){
        return res;
    }
    // CHEQUEAR SI LA FILA ACTUAL YA SE PASO DEL VALOR
    if(c.sumaFila(fila) > valorSumaAdecuado){
        return res;
    }
    // CHEQUEAR COLUMNA RECIEN COMPLETADA
    if(fila == c.size() - 1 && columna > 0 && c.sumaCol(columna - 1) != valorSumaAdecuado){
        return res;
    }
    // CHEQUEAR SI LA COLUMNA ACTUAL YA SE PASO DEL VALOR
    if(c.sumaCol(columna) > valorSumaAdecuado){
        return res;
    }

    for(int j = 0; j < valores.size(); j++){
        if(valores[j]){
            numeroMagico nuevoCuadrado = c;
            nuevoCuadrado.rellenarCasilla(fila, columna, j+1);
            vector<bool> nuevoVectorValores = valores;
            nuevoVectorValores[j] = false;
            res.splice(res.end(), generarCuadradosRecursivos(nuevoCuadrado, nuevoVectorValores, i+1));
        }
    }
    return res;
}

