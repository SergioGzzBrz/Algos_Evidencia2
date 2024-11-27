/*
 * ----------------------------------------------------------------------------
 * File: main.cpp
 * Description: Main entry point for the Evidencia 2 - Algoritmos Avanzados
 *              project. Integrates and runs parts 1 through 4 of the project.
 *
 * Repository: https://github.com/SergioGzzBrz/Algos_Evidencia2
 *
 * Copyright (c) 2024 Sergio Eduardo Gonzalez Barraza
 * License: MIT License (see LICENSE file for details)
 *
 * This file is subject to the terms and conditions defined in the LICENSE file
 * located in the root directory of this project.
 * ----------------------------------------------------------------------------
 */

#include <fstream>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;

#include "parte_1.h"
#include "parte_2.h"
#include "parte_3.h"
#include "parte_4.h"

void get_input_matrix(vector<vector<int>> &matrix, int n, ifstream &input)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            input >> matrix[i][j];
        }
    }
}

int main()
{
    ifstream input("input.txt");
    int n;
    input >> n;
    vector<vector<int>> adjacency_matrix(n, vector<int>(n));
    vector<vector<int>> flow_capacity_matrix(n, vector<int>(n));
    vector<pair<int, int>> coordinates(n);

    get_input_matrix(adjacency_matrix, n, input);

    // Leyendo la matriz de capacidad de flujo
    get_input_matrix(flow_capacity_matrix, n, input);

    string line;
    for (int i = 0; i < n; i++)
    {
        // skip empty lines
        getline(input, line);
        if (line == "")
        {
            i--;
            continue;
        }
        line = line.substr(1, line.size() - 2);
        string x = "", y = "";
        char num;

        int index = 0;
        while (index < line.size() && line[index] != ',')
        {
            index++;
        }
        x = line.substr(0, index + 1);
        y = line.substr(index + 1);
        coordinates[i].first = stoi(x);
        coordinates[i].second = stoi(y);
    }

    // Leyendo las coordenadas de cada colonia
    pair<int, int> new_house;
    getline(input, line);
    line = line.substr(1, line.size() - 2);
    string x = "", y = "";
    char num;

    int index = 0;
    while (index < line.size() && line[index] != ',')
    {
        index++;
    }
    x = line.substr(0, index + 1);
    y = line.substr(index + 1);
    new_house.first = stoi(x);
    new_house.second = stoi(y);

    kruskal_algorithm(adjacency_matrix, n);
    traveling_salesman(adjacency_matrix, n);
    maximum_flow(flow_capacity_matrix, n);
    nearest_central(coordinates, new_house);
}
