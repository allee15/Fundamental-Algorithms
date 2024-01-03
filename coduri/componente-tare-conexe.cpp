#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

ifstream fin("date.in");
ofstream fout("date.out");

vector <vector<int>> graph, graphT;
int n, m;

vector<bool> visited;
vector<int> S;

void DFS(int i) {
    visited[i] = true;
    for (int j = 0; j < graph[i].size(); ++j)
        if (!visited[graph[i][j]])
            DFS(graph[i][j]);
    S.push_back(i);
}

void DFST(int i) {
    visited[i] = true;
    for (int j = 0; j < graphT[i].size(); ++j)
        if (!visited[graphT[i][j]]) {
            fout << graphT[i][j] << " ";
            DFST(graphT[i][j]);
        }
}

int main() {
    int a, b, numberComp = 0;
    fin >> n >> m;
    graph = graphT = vector < vector < int >> (n + 1);
    for (int i = 1; i <= m; i++) {
        fin >> a >> b;
        graph[a].push_back(b);
        graphT[b].push_back(a);
    }

    visited = vector<bool>(n + 1, false);
    for (int i = 1; i <= n; i++)
        if (!visited[i])
            DFS(i);

    visited = vector<bool>(n + 1, false);
    for (vector<int>::reverse_iterator it = S.rbegin(); it != S.rend(); it++) {
        if (!visited[*it]) {
            numberComp++;
            fout << *it << " ";
            DFST(*it);
            fout << endl;
        }
    }
    fout << "Numarul de componente tare conexe: " << numberComp << endl;
    return 0;

}

// Algoritmul se bazeaza pe cel numit Plus-Minus in care fac doua tipuri de parcurgere, intr-un sens si apoi in celalt pentru a nota nodurile cu + (in primul sens) si cu - (in al doilea)
// Odata cu parcurgerea verific nodurile care nu au fost vizitate si le marchez prin parcurgere, incrementand numarul de componente tare conexe.
// Complexitate: O(n+m) datorita listelor de adiacenta