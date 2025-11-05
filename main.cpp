/**
 * @file main.cpp
 * @authors Luisa Fernanda Valdez Guillén - A01711870
 *          Mauricio Olguín Sánchez - A01711522
 * @brief Programa principal que lee la entrada y ejecuta los algoritmos
 * para resolver los 4 problemas de la Situación Problema.
 * */

#include <iostream>
#include <vector>
#include "mst.h"
#include "tsp.h"
#include "maxflow.h"
#include "nearest.h"

using namespace std;

int main() {
    int n;
    cin >> n; // Leer N (número de colonias)
    
    vector<vector<int>> distGraph(n, vector<int>(n));
    vector<vector<int>> flowGraph(n, vector<int>(n));
    
    // Leer matriz de distancias (para MST y TSP)
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> distGraph[i][j];
        }
    }
    
    // Leer matriz de flujo (para MaxFlow)
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> flowGraph[i][j];
        }
    }

    vector<vector<double>> centrales;
    centrales.reserve(n);
    char delim; // Para leer '(', ',' y ')'
    
    // Leer N líneas con coordenadas de centrales (para Nearest)
    for (int i = 0; i < n; ++i) {
        double x, y;
        // Leemos con formato: (x,y)
        cin >> delim >> x >> delim >> y >> delim;
        centrales.push_back({x, y});
    }

    vector<double> nueva;
    double x_new, y_new;
    // Leer coordenada de la nueva central (para Nearest)
    cin >> delim >> x_new >> delim >> y_new >> delim;
    nueva = {x_new, y_new};

    // --- Resolver problemas ---
    // 1. Cableado de fibra
    MST::calculateMST(distGraph, n);
    // 2. Ruta del personal
    TSP::calculateTSP(distGraph, n);
    // 3. Flujo máximo
    MaxFlow::calculateMaxFlow(flowGraph, n);
    // 4. Central más cercana
    Nearest::calculateNearestAndPrint(centrales, nueva);
    
    return 0;
}