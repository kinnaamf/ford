#include <iostream>
#include <vector>
#include <climits>

using namespace std;

int INF = INT_MAX;

struct Edge {
    int from, to, capacity;
};

void findAllPaths(int current, int finish, const vector<int>& dist,
                  const vector<Edge>& edges, vector<int>& path,
                  vector<vector<int>>& allPaths) {

    path.push_back(current);

    if (current == finish) {
        allPaths.push_back(path);
        path.pop_back();
        return;
    }

    for (int i = 0; i < edges.size(); i++) {
        if (edges[i].from == current) {
            int next = edges[i].to;
            int weight = edges[i].capacity;

            if (dist[current] != INF && dist[next] == dist[current] + weight) {
                findAllPaths(next, finish, dist, edges, path, allPaths);
            }
        }
    }

    path.pop_back();
}

void displayMatrix(int n, vector<vector<int>> &iterations) {
    cout << "\n\nIteration matrix:\n\t";
    for (int i = 0; i < n; i++) {
        cout << 'x' << i << '\t';
    }

    cout << "\n";

    for (int i = 0; i < iterations.size(); i++) {
        cout << 'I' << i;

        for (int j = 0; j < n; j++) {
            if (i == 0 || i == iterations.size() - 1) {
                if (iterations[i][j] == INF)
                    cout << "\tINF";
                else
                    cout << '\t' << iterations[i][j];
            }
            else {
                if (iterations[i][j] != iterations[i - 1][j])
                    cout << '\t' << iterations[i][j];
                else cout << '\t';
            }
        }

        cout << '\n';
    }
}

void relaxEdges(int n, int m, vector<Edge> &edges, vector<int> &dist, vector<vector<int>> &iterations) {
    for (int vertex = 0; vertex < n; vertex++) {
        bool changed = false;
        vector<int> prevDist = dist;

        for (int i = 0; i < m; i++) {
            if (edges[i].from == vertex) {
                int u = edges[i].from;
                int v = edges[i].to;
                int w = edges[i].capacity;

                if (prevDist[u] != INF && dist[v] > prevDist[u] + w) {
                    dist[v] = prevDist[u] + w;
                    changed = true;
                }
            }
        }

        if (changed) {
            iterations.push_back(dist);
        }
    }
}

int main() {
    int n, m;

    cout << "Numarul varfurilor: "; cin >> n;
    cout << "Numarul arcelor: "; cin >> m;

    cout << "\nInsert edges (from to capacity):\n ";

    vector<Edge> edges(m);

    for (int i = 0; i < m; i++) {
        cin >> edges[i].from >> edges[i].to >> edges[i].capacity;
    }

    int start, finish;

    vector<int> dist(n, INF);

    cout << "Varful start: "; cin >> start;
    cout << "\nVarful destinatie: " ; cin >> finish;

    dist[start] = 0;

    vector<vector<int>> iterations;
    iterations.push_back(dist);

    relaxEdges(n, m, edges, dist, iterations);

    displayMatrix(n, iterations);

    if (dist[finish] == INF) {
        cout << "\nDrumul nu exista";
        return 0;
    }

    cout << "\nLmin(x" << start << " -> x" << finish << ") = " << dist[finish];

    vector<vector<int>> allPaths;
    vector<int> currentPath;
    findAllPaths(start, finish, dist, edges, currentPath, allPaths);

    cout << "\n\nToate drumurile minime gasite:\n";
    for (const auto& path : allPaths) {
        for (int i = 0; i < path.size(); i++) {
            cout << "x" << path[i];
            if (i < path.size() - 1) cout << " -> ";
        }
        cout << "\n";
    }

    return 0;
}