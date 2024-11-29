
#include <cfloat>
#include <cmath>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;

// Función para calcular la distancia euclidiana entre dos puntos (x1, y1) y (x2, y2)
/// @brief Calcula la distancia euclidiana entre dos puntos en un plano cartesiano.
/// @param a Primer punto, representado como un par de enteros (x1, y1).
/// @param b Segundo punto, representado como un par de enteros (x2, y2).
/// @return La distancia euclidiana entre los dos puntos.
double euclidean_distance(pair<int, int> a, pair<int, int> b)
{
    // Calculamos la distancia utilizando la fórmula de la distancia euclidiana
    return sqrt(pow(a.first - b.first, 2) + pow(a.second - b.second, 2));
}

/// @brief Encuentra la central más cercana a una nueva casa dada, calculando la distancia euclidiana.
/// @param coordinates Lista de pares de enteros que representan las coordenadas de las centrales.
/// @param new_house Par de enteros que representan las coordenadas de la nueva casa.
/// @return No devuelve un valor, pero imprime las coordenadas de la central más cercana.
void nearest_central(const vector<pair<int, int>> &coordinates,
                     pair<int, int> new_house)
{
    /// @brief Inicializamos la distancia mínima a un valor muy grande
    double min_distance = DBL_MAX;
    /// @brief Índice de la central más cercana
    int nearest_central_idx = -1;

    // Iteramos sobre todas las centrales para encontrar la más cercana
    for (int i = 0; i < coordinates.size(); i++)
    {
        // Calculamos la distancia de la nueva casa a la central actual
        double distance = euclidean_distance(coordinates[i], new_house);
        if (distance < min_distance)
        {
            // Actualizamos la central más cercana si encontramos una distancia menor
            min_distance = distance;
            nearest_central_idx = i;
        }
    }

    // Imprimimos el resultado: las coordenadas de la central más cercana
    cout << "4." << endl;
    cout << "(" << coordinates[nearest_central_idx].first << ", "
         << coordinates[nearest_central_idx].second << ")" << endl;
}
