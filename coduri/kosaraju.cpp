#include <iostream>
#include <stack>
#include <vector>
#include <fstream>

using namespace std;

ifstream f("date.in");
ofstream g("date.out");

stack<int>nodes_order;
vector<bool> viz;

vector<vector<int>>graph;
vector<vector<int>>graphT;

int N, M;

void DFS(int x) {
    viz[x] = true;
    for(auto& vec: graph[x]) {
        if(!viz[vec]) {
            DFS(vec);
        }
    }
    nodes_order.push(x);
}

void DFS_write(int x) {
    viz[x] = true;
    g<<x<<" ";
    for(auto& vec: graphT[x]) {
        if(!viz[vec]) {
            DFS_write(vec);
        }
    }
}

void kosaraju() {
    // facem DFS pentru toate nodurile grafului
    for(int i = 1; i <= N; ++i) {
        if(!viz[i])
            DFS(i);
    }

    // reinitializam vectorul de vizitati
    viz.clear();
    viz.resize(N+1, false);

    while(!nodes_order.empty()) {
        int node = nodes_order.top();
        nodes_order.pop();

        if(!viz[node]) {
            // DFS pe graful transpus
            DFS_write(node);
            g<<"\n";
        }
    }
}


int main() {
    // citim numarul de noduri si numarul de muchii
    f>>N>>M;

    // initializam vectorul de vizitati si cele doua grafuri
    viz.resize(N+1, false);
    graph.resize(N+1);
    graphT.resize(N+1);

    // ne cream atat graful normal, cat si cel transpus
    for(int i = 0; i < M; ++i) {
        int x, y;
        f>>x>>y;
        graph[x].push_back(y);
        graphT[y].push_back(x);
    }

    // apelam kosaraju
    kosaraju();
}