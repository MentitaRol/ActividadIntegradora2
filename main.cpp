#include <iostream>
#include <vector>
#include "mst.h"
#include "TSP.h"

using namespace std;

int main() {
    int n;
    cin >> n;
    
    vector<vector<int>> distGraph(n, vector<int>(n));
    vector<vector<int>> flowGraph(n, vector<int>(n));
    
    // Leer matriz de distancias
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> distGraph[i][j];
        }
    }
    
    // Leer matriz de flujo
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> flowGraph[i][j];
        }
    }
    
    // Resolver problemas
    MST::calculateMST(distGraph, n);
    TSP::calculateTSP(distGraph, n);
    
    return 0;
}