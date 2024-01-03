#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

ifstream fin("date.in");
ofstream fout("date.out");

void DFS(int node, int depth, vector<int> &distances, vector<vector<int>> graph, vector<bool>& visited) {
    // Setam in vectorul de distante, distanta de la nod la unul din nodurile de inceput, din care se face DFS-ul
    if(depth < distances[node] || !distances[node]) {
        distances[node] = depth;
    }
    visited[node] = true;

    for(auto vecin: graph[node]) {
        if(!visited[vecin]) {
            DFS(vecin, depth+1, distances, graph, visited);
        }
    }
    visited[node] = false;
}

int main() {
    int x, y, n, m;
    vector <vector<int>> graph;
    vector<int> distances;
    vector<bool> visited;
    vector<int> retea;

    fin >> n >> m;
    graph.resize(n+1);
    distances.resize(n+1, 0);
    visited.resize(n+1, false);
    for (int i = 0; i < m; ++i) {
        fin >> x >> y;
        graph[x].push_back(y);
        graph[y].push_back(x);
    }

    while(fin>>x) {
        retea.push_back(x);
    }
    for(auto node: retea) {
        DFS(node, 0, distances, graph, visited);
    }

    // Setez la 0 distantele nodurilor de inceput
    for(auto node: retea) {
        distances[node] = 0;
    }
    for (int i = 1; i < distances.size(); ++i) {
        fout << distances[i] << " ";
    }
    fout << endl;
    return 0;
}
// Complexitatea: O((n+m)*n) --> numarul de noduri din care se pleaca (<=n) * parcurgerea tuturor nodurilor ramase (<n)