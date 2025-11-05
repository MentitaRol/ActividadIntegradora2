/**
 * @file maxflow.h
 * @authors Mauricio Olguín Sánchez - A01711522
 * @brief Implementación del algoritmo de Ford-Fulkerson (usando DFS) 
 * para encontrar el Flujo Máximo (Max Flow) en una red y resolver el problema 3.
 * */

#ifndef MAXFLOW_H
#define MAXFLOW_H

#include <vector>
#include <iostream>
#include <climits>
#include <algorithm>

using namespace std;

/**
 * @class MaxFlow
 * @brief Clase estática que encapsula la lógica del algoritmo de Ford-Fulkerson
 * para calcular el flujo máximo de datos.
 */
class MaxFlow {
private:
    /**
     * @brief Realiza una Búsqueda en Profundidad (DFS) para encontrar un camino de aumento
     * en el grafo residual.
     * @param u Nodo actual.
     * @param t Nodo destino (sumidero).
     * @param res Grafo residual (matriz de adyacencia). Se modifica in-place.
     * @param visited Vector para marcar nodos visitados en esta iteración de DFS.
     * @param f Flujo mínimo encontrado en el camino hasta el nodo 'u'.
     * @return int La cantidad de flujo que se pudo enviar por el camino encontrado (0 si no se encontró camino).
     */
    static int dfsFind(int u, int t, vector<vector<int>>& res, vector<char>& visited, int f) {
        if (u == t) return f; // Se llegó al sumidero
        visited[u] = 1;
        int n = (int)res.size();
        for (int v = 0; v < n; ++v) {
            if (!visited[v] && res[u][v] > 0) {
                int can = min(f, res[u][v]);
                int pushed = dfsFind(v, t, res, visited, can);
                
                if (pushed > 0) {
                    res[u][v] -= pushed;
                    res[v][u] += pushed;
                    return pushed;
                }
            }
        }
        return 0;
    }

public:
    /**
     * @brief Calcula y muestra el flujo máximo desde la fuente (nodo 0) al sumidero (nodo n-1).
     * Resuelve el problema 3.
     * @param capacity Matriz de adyacencia que representa la capacidad de flujo.
     * @param n Número de nodos (colonias).
     * @return long long El valor del flujo máximo.
     * @note Complejidad: O(f * E) donde f es el flujo máximo y E el número de aristas.
     * Para matriz de adyacencia E = O(n^2), por lo que es O(f * n^2).
     */
    static long long calculateMaxFlow(const vector<vector<int>>& capacity, int n) {
        if (n == 0) return 0;
        vector<vector<int>> residual = capacity;
        int s = 0, t = n - 1;
        long long maxflow = 0;

        while (true) {
            vector<char> visited(n, 0);
            int pushed = dfsFind(s, t, residual, visited, INT_MAX);
            if (pushed == 0) break;
            maxflow += pushed;
        }

        cout << "3. Flujo máximo desde nodo inicial (A) al nodo final (" << char('A' + n - 1) << "):\n";
        cout << maxflow << "\n\n";
        return maxflow;
    }
};

#endif // MAXFLOW_H