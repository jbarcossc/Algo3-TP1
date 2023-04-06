#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>
#include <sstream>
using namespace std;

#ifndef ALGO3_TP1_NUMEROMAGICO_H
#define ALGO3_TP1_NUMEROMAGICO_H


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
    void rellenarCasilla(int fila, int columna, int valor);
    bool operator< ( numeroMagico &b);
    void operator= (numeroMagico &b);

    friend ostream &operator<< (ostream &out, const numeroMagico& b){
        for (int i=0;i<b.n;i++){
            for (int j=0; j<b.n; j++){
                out<< b.mat[i][j] << "\t";
            }
            out << "\n";
        }
        return out;
    }
};


#endif //ALGO3_TP1_NUMEROMAGICO_H
