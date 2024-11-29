
#include <climits>
#include <iostream>
#include <vector>

using namespace std;

/// @brief Valor largo para costo inicial de los caminos.
const int INF = (1 << 30);

/// @brief Resuelve el problema del Viajante de Comercio usando programación dinámica
///        con una máscara de bits para representar las ciudades visitadas.
/// @param current Ciudad actual en la que nos encontramos.
/// @param bitmask Máscara de bits que representa el conjunto de ciudades visitadas.
/// @param dp Arreglo de programación dinámica que almacena el costo mínimo de recorrer las ciudades.
/// @param n Número total de ciudades.
/// @param compatible Matriz de adyacencia que representa la distancia entre ciudades.
/// @param child Arreglo que almacena el siguiente nodo en el camino más corto.
/// @return El costo mínimo para visitar todas las ciudades restantes.
/// @note Complejidad de O(N * N * 2^N), donde N es el número de ciudades
int solve(int current,
          int bitmask,
          vector<int> &dp,
          int n,
          vector<vector<int>> &compatible,
          vector<int> &child)
{
    // Caso base: si hemos visitado todas las ciudades
    if (bitmask == 0)
    {
        if (compatible[current][0] > 0)
        {
            return compatible[current][0]; // Volver a la ciudad inicial
        }
        return INF; // No hay solución válida
    }

    // Si ya se ha calculado el costo para este estado, devolver el valor almacenado
    if (dp[bitmask] != INF)
    {
        return dp[bitmask];
    }

    // Explorar todas las ciudades posibles a las que tengamos un camino
    for (int next = 0; next < n; next++)
    {
        // Si la ciudad 'next' está en la máscara de bits y hay un camino entre 'current' y 'next'
        if (bitmask & (1 << next) && compatible[current][next] > 0)
        {
            // Recursivamente resolver el problema para la ciudad 'next' y actualizar el costo
            int possibleSolution =
                solve(next, bitmask ^ (1 << next), dp, n, compatible, child) +
                compatible[current][next];
            if (possibleSolution < dp[bitmask])
            {
                dp[bitmask] = possibleSolution; // Actualizar el costo mínimo
                child[bitmask] =
                    next; // Guardar el siguiente nodo en el camino más corto
            }
        }
    }

    return dp[bitmask];
}

/// @brief Algoritmo principal para resolver el problema del Viajante de Comercio utilizando DP con bitmasking.
/// @param adjacency_matrix Matriz de adyacencia que representa las distancias entre las ciudades.
/// @param n Número total de ciudades.
void traveling_salesman(vector<vector<int>> &adjacency_matrix, int n)
{
    /// @brief Arreglo de DP con todas las posibles máscaras de bits, inicializado a infinito
    vector<int> dp(1 << n, INF);
    /// @brief Arreglo que guarda el siguiente nodo a visitar en cada estado
    vector<int> child(1 << n, -1);

    /// @brief Encontrar el mejor camino comenzando en la ciudad 0
    int minimumPath =
        solve(0, ((1 << n) - 1) ^ (1 << 0), dp, n, adjacency_matrix, child);

    // Comprobar si no existe un camino válido
    if (minimumPath >= INF)
    {
        cout << "No existe un camino válido" << endl;
        return;
    }

    /// @brief Vector para almacenar el camino recorrido
    vector<int> path;
    /// @brief Máscara que representa todas las ciudades visitadas
    int currentBitmask = ((1 << n) - 1);
    /// @brief Empezamos en la ciudad 0
    int currentCity = 0;
    /// @brief Ciudad siguiente a visitar
    int nextCity = -1;

    // Reconstruir el camino recorrido
    while (currentBitmask != 0)
    {
        currentBitmask ^=
            (1
             << currentCity); // Eliminar la ciudad actual de la máscara de bits
        path.push_back(currentCity); // Agregar la ciudad al camino
        nextCity =
            child[currentBitmask]; // Obtener la siguiente ciudad a visitar
        currentCity = nextCity;    // Actualizar la ciudad actual
    }

    path.push_back(0); // Agregar la última ciudad (la ciudad de inicio)

    // Imprimir el camino encontrado
    cout << "2. " << endl;
    for (int i = 0; i < path.size(); i++)
    {
        cout << (char)(path[i] + 'A') << " "; // Imprimir la ciudad como letra
    }
    cout << endl;
}
