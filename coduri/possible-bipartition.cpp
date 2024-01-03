#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

ifstream fin("date.in");
ofstream fout("date.out");

bool DFS(int varf, int color, vector<int> colors, vector<vector<int>> graph) {
    colors[varf] = color;
    for(auto& vecin: graph[varf]) {
        // daca vecinul are aceeasi culoare cu a noastra, nu e bipartit
        if(colors[vecin] == color) return false;
        // daca vecinul nu are nicio culoare, dar vecinii vecinului nu au culori bune, nu e bipartit
        if(colors[vecin] == 0 && !DFS(vecin, -color, colors, graph)) return false;
    }
    // toti au culorile potrivite, e bipartit
    return true;
}

bool possibleBipartition(int N, vector<pair<int, int>> dislikes) {
    vector<vector<int>> graph;
    graph.resize(N);
    for(auto& dislike: dislikes) {
        graph[dislike.first - 1].push_back(dislike.second-1);
        graph[dislike.second - 1].push_back(dislike.first-1);
    }
    vector<int> colors;
    colors.resize(N, 0);
    for(int i = 0; i < N; ++i) {
        if(!colors[i] && !DFS(i, 1, colors, graph)) return false;
    }
    return true;
}

int main() {
    int N;
    int x, y;
    vector<int> colors;
    vector<pair<int, int>> dislikes;

    fin>>N;
    colors.resize(N);
    while(fin>>x>>y) {
        dislikes.push_back(make_pair(x, y));
    }
    if(possibleBipartition(N, dislikes)) {
        fout<<"Este bipartit!"<<endl;
    } else {
        fout<<"Nu este bipartit!"<<endl;
    }
    return 0;
}

// Ne cream vectorul de dislikes cu ajutorul caruia vom putea verifica daca graful este bipartit si vom crea in acelasi timp si listele de adiacenta. Vom face DFS pentru fiecare nod care nu are atribuit o culoare
// precum la vectorul de vizitati. Conditia este ca oricare doua noduri adiacente sa nu aiba aceeasi culoare. Astfel, putem spune ca graful este bipartit. Altfel, graful nu este bipartit.
// Pentru a verifica ne folosim de acel vector de culori si fiind vorba de doar doua grupuri, vom colora cu culoarea i si -i (1 si -1 in cazul nostru)
// Complexitate: O(E+n), unde E este timpul alocat crearii listei de adiacenta