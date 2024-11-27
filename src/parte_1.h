#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;

struct Edge
{
    int u, v, weight;
    bool operator<(Edge const &other) const
    {
        return weight < other.weight;
    }

    Edge(int u, int v, int weight)
    {
        this->u = u;
        this->v = v;
        this->weight = weight;
    }
};

const int MAXN = 1e5;
vector<int> dsu(MAXN + 1), rankk(MAXN + 1, 0);

// Encontrar el representante de cada componente
int get(int node)
{
    return dsu[node] = (dsu[node] != node) ? get(dsu[node]) : node;
}

// Union por Rank
void dsu_union(int a, int b)
{
    a = get(a);
    b = get(b);
    if (a == b)
        return;

    if (rankk[a] == rankk[b])
    {
        rankk[a]++;
    }
    if (rankk[a] > rankk[b])
    {
        dsu[b] = a;
    }
    else
    {
        dsu[a] = b;
    }
}

// Complejidad: O(M LOG N) donde M son los edges y N son las conexiones
void kruskal_algorithm(vector<vector<int>> &adjacency_matrix, int n)
{
    vector<Edge> edges;
    vector<Edge> minimum_spanning_tree;

    // Agregar conexiones como edges
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

    // Inicialmente, cada nodo del componente se representa a si mismo
    for (int i = 1; i <= n; i++)
    {
        dsu[i] = i;
    }

    // Ordenar los edges por peso en orden ascendente
    sort(edges.begin(), edges.end());
    for (Edge edge : edges)
    {
        if (get(edge.u) != get(edge.v))
        {
            minimum_spanning_tree.push_back(edge);
            dsu_union(edge.u, edge.v);
        }
    }

    // Imprimir los edges del Minimum Spanning Tree
    cout << "1." << endl;

    for (Edge edge : minimum_spanning_tree)
    {
        cout << '(' << (char)(edge.u + 'A' - 1) << ','
             << (char)(edge.v + 'A' - 1) << ')' << endl;
    }
    cout << endl;
}
