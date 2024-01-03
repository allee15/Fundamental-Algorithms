#include <stdio.h>
#include <vector>
#include <fstream>
#include <iostream>
#include <algorithm>
#define N_MAX 1000
using namespace std;

ifstream fin("date.in");
ofstream fout("date.out");

int n, m, dfs, p[N_MAX], order[N_MAX], dfs_order[N_MAX];
bool visited[N_MAX];
vector<vector<int>> graph;

void DFS(int index) {
    dfs_order[dfs++] = index;
    visited[index] = true;
    for(int i = 0; i < graph[index].size(); ++i) {
        if(!visited[graph[index][i]]) {
            DFS(graph[index][i]);
        }
    }
}

bool cmp(int a, int b) {
    return order[a] < order[b];
}

int main() {
    int a, b;
    fin>>n>>m;
    for(int i = 0; i < n; ++i) {
        fin>>p[i];
        order[p[i]] = i;
    }
    graph.resize(n+1);
    for(int i = 0; i < m; ++i) {
        fin>>a>>b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    for(int i = 0; i < (int)graph[2].size(); ++i) {
        fout<<graph[2][i]<<endl;
    }
    // sortam fiecare lista de adiacenta in functie de ordinea pe care o au elementele in vectorul citit
    for(int i = 0; i < (int)graph.size(); ++i)
        sort(graph[i].begin(), graph[i].end(), cmp);

    // mereu vom pleca cu DFS-ul din varful 1
    DFS(1);

    // verificam daca ordinea din DFS este aceeasi cu ordinea pe care am citit-o
    bool ok = true;
    for(int i = 0; i < n; ++i) {
        if (p[i] != dfs_order[i]) {
            ok = false;
            break;
        }
    }

    fout<<(ok ? "1\n" : "0\n");
}

// Complexitate: O(n*n*logn) -> sortarea listelor de adiacenta a tuturor nodurilor