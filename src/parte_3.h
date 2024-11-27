#include <iostream>
#include <limits>
#include <queue>
#include <vector>

using namespace std;

// complejidad: O(n + e): donde e son las edges
bool bfsFindPath(const vector<vector<int> > &adjacency_matrix,
                 vector<int> &parent, int n, int s, int d) {
  vector<bool> visited(n - 1, false);

  queue<int> q;
  q.push(s);
  visited[s] = true;
  parent[s] = -1;

  while (!q.empty()) {
    int u = q.front();
    q.pop();

    for (int i = 0; i < n; i++) {
      if (visited[i] == false && adjacency_matrix[u][i] > 0) {
        if (i == d) {
          parent[i] = u;
          return true;
        }

        q.push(i);
        parent[i] = u;
        visited[i] = true;
      }
    }
  }

  return false;
}

// complejidad: O(max_flow * e)xs
int fordFulkerson(const vector<vector<int> > &flow_adjacency_matrix, int n,
                  int s, int t) {
  // Residual graph
  vector<vector<int> > residual_graph = flow_adjacency_matrix;

  vector<int> parent(n - 1);

  int max_flow = 0;

  while (bfsFindPath(residual_graph, parent, n, s, t)) {
    int path_flow = numeric_limits<int>::max();
    for (int i = t; i != s; i = parent[i]) {
      path_flow = min(path_flow, residual_graph[parent[i]][i]);
    }

    // update residual capacities
    for (int i = t; i != s; i = parent[i]) {
      int j = parent[i];
      residual_graph[j][i] -= path_flow;
      residual_graph[i][j] += path_flow;
    }

    max_flow += path_flow;
  }

  return max_flow;
}

// Imprime el resultado de la parte 3
void maximum_flow(const vector<vector<int> > &flow_adjacency_matrix, int n) {

  int max_flow = fordFulkerson(flow_adjacency_matrix, n, 0, n - 1);

  cout << "\n3.\n" << max_flow << "\n\n";
}