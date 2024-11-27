/*
 * Evidencia 2 - Algoritmos Avanzados
 * https://github.com/SergioGzzBrz/Algos_Evidencia2
 *
 * MIT License
 * Copyright (c) 2024 Sergio Eduardo Gonzalez Barraza
 */

#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;

/// @brief Representa un borde (arista) en un grafo ponderado.
struct Edge
{
    /// @brief Nodo de inicio del borde.
    int u;

    /// @brief Nodo de fin del borde.
    int v;

    /// @brief Peso o costo asociado al borde.
    int weight;

    /// @brief Sobrecarga del operador < para permitir la comparación de bordes
    ///        según su peso. Útil para algoritmos que requieren ordenar bordes.
    /// @param other Otro objeto Edge con el cual se compara.
    /// @return `true` si el peso del borde actual es menor que el peso del borde proporcionado.
    bool operator<(Edge const &other) const
    {
        return weight < other.weight;
    }

    /// @brief Constructor de la estructura Edge.
    /// @param u Nodo de inicio del borde.
    /// @param v Nodo de fin del borde.
    /// @param weight Peso o costo asociado al borde.
    Edge(int u, int v, int weight)
    {
        this->u = u;
        this->v = v;
        this->weight = weight;
    }
};
/// @brief Constante que define el número máximo de nodos permitido.
const int MAXN = 1e5;

/// @brief Vector que implementa el conjunto disjunto (DSU), donde cada nodo
///        almacena el representante de su componente.
vector<int> dsu(MAXN + 1);

/// @brief Vector que almacena el rango de cada componente en el DSU,
///        utilizado para optimizar la unión de conjuntos.
vector<int> rankk(MAXN + 1, 0);

/// @brief Encuentra el representante del conjunto al que pertenece un nodo,
///        utilizando compresión de caminos para optimizar futuras consultas.
/// @param node Nodo del cual se quiere encontrar el representante.
/// @return Representante del conjunto al que pertenece el nodo.
int get(int node)
{
    return dsu[node] = (dsu[node] != node) ? get(dsu[node]) : node;
}

/// @brief Une dos conjuntos utilizando la técnica de Union por Rango
///        para mantener un árbol equilibrado.
/// @param a Nodo representativo del primer conjunto.
/// @param b Nodo representativo del segundo conjunto.
void dsu_union(int a, int b)
{
    a = get(a);
    b = get(b);
    if (a == b)
        return;

    // Incrementar el rango si ambos conjuntos tienen el mismo rango
    if (rankk[a] == rankk[b])
    {
        rankk[a]++;
    }

    // Hacer que el árbol con menor rango apunte al de mayor rango
    if (rankk[a] > rankk[b])
    {
        dsu[b] = a;
    }
    else
    {
        dsu[a] = b;
    }
}

/// @brief Algoritmo de Kruskal para encontrar el Árbol de Expansión Mínima
///        en un grafo ponderado representado por una matriz de adyacencia.
/// @param adjacency_matrix Matriz de adyacencia que representa el grafo.
/// @param n Número de nodos en el grafo.
/// @note La complejidad del algoritmo es O(M log N), donde M es el número de bordes
///       y N el número de nodos.
void kruskal_algorithm(vector<vector<int>> &adjacency_matrix, int n)
{
    /// @brief Vector para almacenar todas las aristas del grafo.
    vector<Edge> edges;

    /// @brief Vector para almacenar las aristas del Árbol de Expansión Mínima.
    vector<Edge> minimum_spanning_tree;

    // Crear las aristas a partir de la matriz de adyacencia
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (adjacency_matrix[i][j] > 0)
            {
                edges.emplace_back(i + 1, j + 1, adjacency_matrix[i][j]);
            }
        }
    }

    // Inicializar DSU: cada nodo es su propio representante al inicio
    for (int i = 1; i <= n; i++)
    {
        dsu[i] = i;
    }

    // Ordenar las aristas por peso en orden ascendente
    sort(edges.begin(), edges.end());

    // Procesar las aristas
    for (Edge edge : edges)
    {
        // Verificar si los nodos de la arista están en diferentes componentes
        if (get(edge.u) != get(edge.v))
        {
            // Agregar la arista al Árbol de Expansión Mínima
            minimum_spanning_tree.push_back(edge);
            // Unir los conjuntos de los nodos
            dsu_union(edge.u, edge.v);
        }
    }

    // Imprimir las aristas del Árbol de Expansión Mínima
    cout << "1." << endl;
    for (Edge edge : minimum_spanning_tree)
    {
        cout << '(' << (char)(edge.u + 'A' - 1) << ','
             << (char)(edge.v + 'A' - 1) << ')' << endl;
    }
    cout << endl;
}
