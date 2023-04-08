#include <iostream>
#include <vector>
#include "numeroMagico.h"
#include <list>
#include <cmath>

#ifndef ALGO3_TP1_AUXILIARES_H
#define ALGO3_TP1_AUXILIARES_H
bool comparador( numeroMagico &a,  numeroMagico &b);


vector<numeroMagico> generarCuadrados(int n); // FUNCION PRINCIPAL
void generarCuadradosRecursivos(numeroMagico c, vector<bool> valores, int i, vector<numeroMagico> *resPointer);
#endif //ALGO3_TP1_AUXILIARES_H
