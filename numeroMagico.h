#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>
#include <sstream>

#ifndef ALGO3_TP1_NUMEROMAGICO_H
#define ALGO3_TP1_NUMEROMAGICO_H

using namespace std;

using Cuadrado = vector<vector<int>>;

class numeroMagico {
private:
    int n;
    Cuadrado mat;
public:
    numeroMagico();
    explicit numeroMagico(int n);
    int size();
    Cuadrado cuadrado();
    int filasLlenas(); // Retorna la cantidad de filas consecutivas llenas desde la fila 0
    int columnasLlenas(); // Retorna la cantidad de columnas consecutivas llenas desde la columna 0
    bool estaLleno();
    int sumaFila(int fila);
    int sumaCol(int columna);
    pair<int,int> sumaDiagonal();
    bool esMagico();
    Cuadrado rellenarCasilla(int fila, int columna, int valor);
    ostream& operator<< (std::ostream &out);
    bool operator< ( numeroMagico& b);
    ostream& operator= (numeroMagico& b);

};


#endif //ALGO3_TP1_NUMEROMAGICO_H
