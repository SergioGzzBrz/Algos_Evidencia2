#include <cfloat>
#include <cmath>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;

// Función para calcular la distancia euclidiana entre dos puntos (x1, y1) y (x2, y2)
double euclidean_distance(pair<int, int> a, pair<int, int> b)
{
    return sqrt(pow(a.first - b.first, 2) + pow(a.second - b.second, 2));
}

// Función principal para encontrar la central más cercana
void nearest_central(const vector<pair<int, int>> &coordinates,
                     pair<int, int> new_house)
{
    double min_distance = DBL_MAX;
    int nearest_central_idx = -1;

    // Iterar sobre todas las centrales para encontrar la más cercana
    for (int i = 0; i < coordinates.size(); i++)
    {
        double distance = euclidean_distance(coordinates[i], new_house);
        if (distance < min_distance)
        {
            min_distance = distance;
            nearest_central_idx = i;
        }
    }

    // Imprimir el resultado
    cout << "4." << endl;
    cout << "(" << coordinates[nearest_central_idx].first << ", "
         << coordinates[nearest_central_idx].second << ")" << endl;
}
