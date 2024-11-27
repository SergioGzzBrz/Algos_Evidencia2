/*
 * SonarQube, open source software quality management tool.
 * Copyright (C) 2008-2013 SonarSource
 * http://github.com/SonarOpenCommunity/sonar-cxx
 *
 * SonarQube is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 3 of the License, or (at your option) any later version.
 *
 * SonarQube is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
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
