/**
 * @file nearest.h
 * @authors Mauricio Olguín Sánchez - A01711522
 * @brief Implementación de Búsqueda de Vecino más Cercano (Nearest Neighbor)
 * utilizando una estructura de datos KD-Tree para resolver el problema 4.
 * */

#ifndef NEAREST_H
#define NEAREST_H

#include <vector>
#include <cmath>
#include <iostream>

using namespace std;

/**
 * @class Nearest
 * @brief Clase estática que encapsula la lógica para encontrar la central más cercana
 * a una nueva contratación usando un KD-Tree.
 */
class Nearest {
public:
    /**
     * @brief Calcula y muestra la central (punto) más cercana a una consulta (nueva central) usando un KD-Tree.
     * @param centers Vector de vectores (coordenadas {x, y}) de las centrales existentes.
     * @param query Vector (coordenadas {x, y}) de la nueva central (punto de consulta).
     * @return vector<double> Vector de dos elementos {índice_del_más_cercano, distancia_mínima}.
     * @note Complejidad de construcción del KD-Tree: O(n log n)
     * @note Complejidad promedio de búsqueda: O(log n).
     */
    static vector<double> calculateNearestAndPrint(const vector<vector<double>>& centers, const vector<double>& query) {
        vector<double> res = { -1.0, 0.0 };
        int m = (int)centers.size();
        if (m == 0) {
            cout << "4. No hay centrales registradas.\n";
            return res;
        }

        vector<Point> pts;
        pts.reserve(m);
        for (int i = 0; i < m; ++i) {
            pts.push_back({centers[i][0], centers[i][1], i});
        }

        KDNode* root = buildKD(pts, 0, m, 0);
        double bestDist2 = INFINITY;
        int bestIdx = -1;
        Point q{query[0], query[1], -1};
        
        nearestRec(root, q, bestDist2, bestIdx);
        double bestDist = (bestIdx == -1) ? 0.0 : sqrt(bestDist2);
        freeTree(root);

        cout << "4. Distancia entre la nueva central y la central existente mas cercana (km):\n";
        cout.setf(std::ios::fixed); cout.precision(6);
        cout << bestDist << "\n";
        
        return {(double)bestIdx, bestDist};
    }

private:
    /**
     * @struct Point
     * @brief Estructura para representar un punto en 2D (central), guardando su índice original.
     */
    struct Point {
        double x, y;
        int idx;
    };

    /**
     * @struct KDNode
     * @brief Estructura para un nodo del KD-Tree.
     */
    struct KDNode {
        Point p;
        KDNode* left;
        KDNode* right;
        int axis; // Eje de división (0 para x, 1 para y)
        KDNode(const Point& pt): p(pt), left(nullptr), right(nullptr), axis(0) {}
    };

    // --- Implementación de Merge Sort ---
    /**
     * @brief Compara dos puntos basado en el eje (x o y).
     * @param a Primer punto.
     * @param b Segundo punto.
     * @param axis Eje de comparación (0 para x, 1 para y).
     * @return true si a < b en ese eje, false en caso contrario.
     */
    static bool comparePoints(const Point& a, const Point& b, int axis) {
        return (axis == 0) ? (a.x < b.x) : (a.y < b.y);
    }
    
    /**
     * @brief Función de merge para Merge Sort.
     */
    static void merge(vector<Point>& pts, int l, int m, int r, int axis) {
        int n1 = m - l + 1;
        int n2 = r - m;
        vector<Point> L(n1), R(n2);
        for (int i = 0; i < n1; i++)
            L[i] = pts[l + i];
        for (int j = 0; j < n2; j++)
            R[j] = pts[m + 1 + j];
        int i = 0, j = 0, k = l;
        while (i < n1 && j < n2) {
            if (comparePoints(L[i], R[j], axis)) {
                pts[k] = L[i];
                i++;
            } else {
                pts[k] = R[j];
                j++;
            }
            k++;
        }

        while (i < n1) {
            pts[k] = L[i];
            i++;
            k++;
        }
        while (j < n2) {
            pts[k] = R[j];
            j++;
            k++;
        }
    }

    /**
     * @brief Algoritmo Merge Sort para ordenar puntos según un eje.
     */
    static void mergeSort(vector<Point>& pts, int l, int r, int axis) {
        if (l >= r) return;
        int m = l + (r - l) / 2;
        mergeSort(pts, l, m, axis);
        mergeSort(pts, m + 1, r, axis);
        merge(pts, l, m, r, axis);
    }

    /**
     * @brief Construye recursivamente el KD-Tree.
     * @param pts Vector de Puntos (se modifica in-place).
     * @param l Índice izquierdo (inclusivo).
     * @param r Índice derecho (exclusivo).
     * @param depth Profundidad actual (para determinar el eje).
     * @return Puntero al nodo raíz del subárbol construido.
     */
    static KDNode* buildKD(vector<Point>& pts, int l, int r, int depth) {
        if (l >= r) return nullptr;
        
        int axis = depth % 2;
        int m = (l + r) / 2;

        mergeSort(pts, l, r - 1, axis);
        KDNode* node = new KDNode(pts[m]);

        node->axis = axis;
        node->left  = buildKD(pts, l, m, depth + 1);
        node->right = buildKD(pts, m + 1, r, depth + 1);
        return node;
    }

    /**
     * @brief Búsqueda recursiva del vecino más cercano en el KD-Tree.
     * @param node Nodo actual en la recursión.
     * @param q Punto de consulta.
     * @param bestDist2 Mejor distancia cuadrada encontrada hasta ahora.
     * @param bestIdx Índice del mejor punto (vecino más cercano) encontrado.
     */
    static void nearestRec(KDNode* node, const Point& q, double &bestDist2, int &bestIdx) {
        if (!node) return;
        
        double dx = node->p.x - q.x;
        double dy = node->p.y - q.y;
        double d2 = dx*dx + dy*dy;
        if (d2 < bestDist2) {
            bestDist2 = d2;
            bestIdx = node->p.idx;
        }

        int axis = node->axis;
        double diff = (axis == 0) ? (q.x - node->p.x) : (q.y - node->p.y);

        KDNode* first = diff < 0 ? node->left : node->right;
        KDNode* second = diff < 0 ? node->right : node->left;

        if (first) nearestRec(first, q, bestDist2, bestIdx);

        if (second) {
            double diff2 = diff * diff;
            if (diff2 < bestDist2) {
                nearestRec(second, q, bestDist2, bestIdx);
            }
        }
    }

    /**
     * @brief Libera la memoria (post-orden) de todos los nodos del KD-Tree.
     * @param node Nodo raíz del árbol/subárbol a liberar.
     */
    static void freeTree(KDNode* node) {
        if (!node) return;
        if (node->left) freeTree(node->left);
        if (node->right) freeTree(node->right);
        delete node;
    }
};

#endif // NEAREST_H