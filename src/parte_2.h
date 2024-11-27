/*
 * Evidencia 2 - Algoritmos Avanzados
 * https://github.com/SergioGzzBrz/Algos_Evidencia2
 *
 * MIT License
 * Copyright (c) 2024 Sergio Eduardo Gonzalez Barraza
 */

#include <climits>
#include <iostream>
#include <vector>

using namespace std;

const int INF = (1 << 30); // Valor largo para costo inicial

// complejidad de (N*2^N)
int solve(int current,
          int bitmask,
          vector<int> &dp,
          int n,
          vector<vector<int>> &compatible,
          vector<int> &child)
{
    if (bitmask == 0)
    { // Caso base si ya visitamos todas las ciudades
        if (compatible[current][0] > 0)
        {
            return compatible[current][0]; // Volver a la ciudad inicial
        }
        return INF;
    }

    if (dp[bitmask] != INF)
    {
        return dp[bitmask];
    }

    // Explorar todas las ciudades posibles a las que tengamos un camino
    for (int next = 0; next < n; next++)
    {
        if (bitmask & (1 << next) && compatible[current][next] > 0)
        {
            int possibleSolution =
                solve(next, bitmask ^ (1 << next), dp, n, compatible, child) +
                compatible[current][next];
            if (possibleSolution < dp[bitmask])
            {
                dp[bitmask] = possibleSolution;
                child[bitmask] =
                    next; // Guardar el nodo siguiente para el camino mas corto
            }
        }
    }

    return dp[bitmask];
}

void traveling_salesman(vector<vector<int>> &adjacency_matrix, int n)
{
    vector<int> dp(1 << n,
                   INF); // Arreglo de DP con todas las bitmasks posibles
    vector<int> child(
        1 << n,
        -1); // Guarda la siguiente ciudad a visitar en cada estado

    // Encontramos el mejor camino empezando en la ciudad 0
    int minimumPath =
        solve(0, ((1 << n) - 1) ^ (1 << 0), dp, n, adjacency_matrix, child);

    // Checamos si no existe el camino
    if (minimumPath >= INF)
    {
        cout << "No existe un camino valido" << endl;
        return;
    }
    vector<int> path;
    int currentBitmask = ((1 << n) - 1);
    int currentCity = 0;
    int nextCity = -1;
    // Reconstruimos el camino
    while (currentBitmask != 0)
    { // Paramos cuando ya visitamos todas las ciudades
        currentBitmask ^= (1 << currentCity); // Quitamos la ciudad del bitmask
        path.push_back(currentCity);
        nextCity = child[currentBitmask];
        currentCity = nextCity;
    }

    path.push_back(0); // Agregamos la ultima ciudad a visitar

    // Imprimir camino
    cout << "2. " << endl;
    for (int i = 0; i < path.size(); i++)
    {
        cout << (char)(path[i] + 'A') << " ";
    }
    cout << endl;
}
