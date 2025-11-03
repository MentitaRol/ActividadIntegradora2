#ifndef MST_H
#define MST_H

#include <vector>
#include <climits>
#include <iostream>
using namespace std;

class MST {
public:
    static void calculateMST(vector<vector<int>>& graph, int n) {
        vector<bool> inMST(n, false);
        vector<int> key(n, INT_MAX);
        vector<int> parent(n, -1);
        
        key[0] = 0;
        
        for (int count = 0; count < n - 1; count++) {
            int minKey = INT_MAX, minIndex = -1;
            
            for (int v = 0; v < n; v++) {
                if (!inMST[v] && key[v] < minKey) {
                    minKey = key[v];
                    minIndex = v;
                }
            }
            
            int u = minIndex;
            inMST[u] = true;
            
            for (int v = 0; v < n; v++) {
                if (graph[u][v] && !inMST[v] && graph[u][v] < key[v]) {
                    parent[v] = u;
                    key[v] = graph[u][v];
                }
            }
        }
        
        cout << "1. Forma de cablear las colonias con fibra:\n";
        for (int i = 1; i < n; i++) {
            char from = 'A' + parent[i];
            char to = 'A' + i;
            cout << "(" << from << "," << to << ")\n";
        }
        cout << endl;
    }
};

#endif // MST_H