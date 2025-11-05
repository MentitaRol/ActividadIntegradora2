/**
 * @file tsp.h
 * @authors Luisa Fernanda Valdez Guillén - A01711870
 * @brief Implementación de una solución de fuerza bruta para el 
 * Problema del Agente Viajero (Traveling Salesperson Problem - TSP) y resolver el problema 2 (ruta de personal).
 * */

#ifndef TSP_H
#define TSP_H

#include <vector>
#include <algorithm>
#include <climits>
#include <iostream>
using namespace std;

/**
 * @class TSP
 * @brief Clase estática que encapsula la lógica de fuerza bruta para el TSP.
 */
class TSP {
public:
    /**
     * @brief Calcula e imprime la ruta más corta que visita cada colonia exactamente una vez
     * y regresa al origen (Colonia 'A'). Resuelve el problema 2.
     * @param graph Matriz de adyacencia (grafo ponderado) que representa las distancias en km.
     * @param n Número de nodos (colonias).
     * @return void (Imprime directamente la ruta óptima).
     * * @note Complejidad: O(n! * n), ya que prueba todas las permutaciones (n-1)! y calcula el costo O(n).
     * Esto es viable solo para N muy pequeño.
     */
    static void calculateTSP(vector<vector<int>>& graph, int n) {
        vector<int> cities;
        for (int i = 1; i < n; i++) {
            cities.push_back(i);
        }
        
        int minCost = INT_MAX;
        vector<int> bestRoute;
        
        do {
            int currentCost = 0;
            int current = 0;
            bool validRoute = true;
            
            // Calcular costo desde ciudad inicial a primera ciudad
            if (graph[current][cities[0]] == 0) {
                validRoute = false;
            } else {
                currentCost += graph[current][cities[0]];
            }
            
            // Calcular costo entre ciudades intermedias
            for (int i = 0; i < cities.size() - 1 && validRoute; i++) {
                if (graph[cities[i]][cities[i + 1]] == 0) {
                    validRoute = false;
                } else {
                    currentCost += graph[cities[i]][cities[i + 1]];
                }
            }
            
            // Calcular costo de regreso
            if (validRoute && graph[cities[cities.size() - 1]][0] != 0) {
                currentCost += graph[cities[cities.size() - 1]][0];
                
                if (currentCost < minCost) {
                    minCost = currentCost;
                    bestRoute = cities;
                }
            }
            
        } while (next_permutation(cities.begin(), cities.end()));
        
        cout << "2. Ruta a seguir por el personal:\n";
        cout << "A";
        for (int city : bestRoute) {
            cout << " -> " << (char)('A' + city);
        }
        cout << " -> A\n\n";
    }
};

#endif // TSP_H