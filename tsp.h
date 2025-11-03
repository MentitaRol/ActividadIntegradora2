#ifndef TSP_H
#define TSP_H

#include <vector>
#include <algorithm>
#include <climits>
#include <iostream>
using namespace std;

class TSP {
public:
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
        cout << " -> A\n";
    }
};

#endif // TSP_H