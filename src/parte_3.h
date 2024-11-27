/*
 * Evidencia 2 - Algoritmos Avanzados
 * https://github.com/SergioGzzBrz/Algos_Evidencia2
 *
 * MIT License
 * Copyright (c) 2024 Sergio Eduardo Gonzalez Barraza
 */

#include <iostream>
#include <limits>
#include <queue>
#include <vector>

using namespace std;

/// @brief Realiza una búsqueda en amplitud (BFS) para encontrar un camino desde el nodo fuente 's' hasta el nodo destino 'd'.
///        Si encuentra un camino, actualiza el arreglo 'parent' para almacenar el nodo anterior de cada nodo en el camino.
/// @param adjacency_matrix Matriz de adyacencia que representa las capacidades de las aristas entre nodos.
/// @param parent Arreglo que almacena el nodo anterior de cada nodo en el camino encontrado.
/// @param n Número de nodos en el grafo.
/// @param s Nodo fuente de la búsqueda.
/// @param d Nodo destino de la búsqueda.
/// @return `true` si se encontró un camino desde 's' a 'd', de lo contrario `false`.
/// @note Complejidad: O(n + e), donde 'n' es el número de nodos y 'e' son las aristas
bool bfs_find_path(const vector<vector<int>> &adjacency_matrix,
                   vector<int> &parent,
                   int n,
                   int s,
                   int d)
{
    vector<bool> visited(n - 1,
                         false); // Arreglo para marcar los nodos visitados

    queue<int> q;      // Cola para la BFS
    q.push(s);         // Empezamos desde el nodo fuente
    visited[s] = true; // Marcamos el nodo fuente como visitado
    parent[s] = -1;    // El nodo fuente no tiene padre

    while (!q.empty())
    {
        int u = q.front();
        q.pop();

        for (int i = 0; i < n; i++)
        {
            // Si no hemos visitado el nodo 'i' y hay una capacidad positiva en la arista
            if (visited[i] == false && adjacency_matrix[u][i] > 0)
            {
                if (i == d) // Si encontramos el nodo destino
                {
                    parent[i] = u; // Guardamos el nodo anterior
                    return true;   // Camino encontrado
                }

                q.push(i);         // Agregamos el nodo 'i' a la cola
                parent[i] = u;     // Actualizamos el padre de 'i'
                visited[i] = true; // Marcamos 'i' como visitado
            }
        }
    }

    return false; // No se encontró un camino
}

/// @brief Algoritmo de Ford-Fulkerson para calcular el flujo máximo en una red de flujo.
///        Usa BFS para encontrar caminos aumentantes y actualiza las capacidades residuales.
/// @param flow_adjacency_matrix Matriz de adyacencia que representa las capacidades de las aristas.
/// @param n Número de nodos en el grafo.
/// @param s Nodo fuente.
/// @param t Nodo sumidero.
/// @return El flujo máximo de la red.
/// @note Complejidad: O(max_flow * e), donde 'max_flow' es el flujo máximo y 'e' es el número de aristas
int ford_fulkerson(const vector<vector<int>> &flow_adjacency_matrix,
                   int n,
                   int s,
                   int t)
{
    /// @brief Grafo residual, inicializado con las capacidades originales de las aristas
    vector<vector<int>> residual_graph = flow_adjacency_matrix;

    /// @brief Arreglo para almacenar los padres de los nodos
    vector<int> parent(n - 1);

    /// @brief Inicializamos el flujo máximo a 0
    int max_flow = 0;

    // Mientras exista un camino aumentante
    while (bfs_find_path(residual_graph, parent, n, s, t))
    {
        /// @brief Inicializamos el flujo de la ruta como el valor máximo
        int path_flow = numeric_limits<int>::max();

        // Encontramos el flujo máximo en el camino aumentante
        for (int i = t; i != s; i = parent[i])
        {
            path_flow =
                min(path_flow,
                    residual_graph[parent[i]]
                                  [i]); // Actualizamos el flujo del camino
        }

        // Actualizamos las capacidades residuales de las aristas
        for (int i = t; i != s; i = parent[i])
        {
            int j = parent[i];
            residual_graph[j][i] -= path_flow; // Restamos el flujo del camino
            residual_graph[i][j] +=
                path_flow; // Agregamos el flujo al camino inverso
        }

        max_flow += path_flow; // Incrementamos el flujo máximo
    }

    return max_flow; // Devolvemos el flujo máximo encontrado
}

/// @brief Calcula e imprime el flujo máximo en una red de flujo.
/// @param flow_adjacency_matrix Matriz de adyacencia que representa las capacidades de las aristas.
/// @param n Número de nodos en el grafo.
void maximum_flow(const vector<vector<int>> &flow_adjacency_matrix, int n)
{
    /// @brief Llamamos al algoritmo de Ford-Fulkerson para calcular el flujo máximo
    int max_flow = ford_fulkerson(flow_adjacency_matrix, n, 0, n - 1);

    // Imprimimos el resultado del flujo máximo
    cout << "\n3.\n" << max_flow << "\n\n";
}
