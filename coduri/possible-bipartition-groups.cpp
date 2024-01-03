#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

ifstream fin("date.in");
ofstream fout("date.out");

bool DFS(int varf, int color, vector<int>& colors, vector <vector<int>> graph, pair<vector<int>, vector<int>> &groups) {
    colors[varf] = color;
    for (auto &vecin: graph[varf]) {
        if (colors[vecin] == color) return false;
        if (colors[vecin] == 0 && !DFS(vecin, -color, colors, graph, groups)) return false;
    }

    // in functie de culoarea pe care o are, punem varful in una din echipe/grupe
    if (color == 1 && colors[varf]) {
        groups.first.push_back(varf+1);
    } else if(color == -1 && colors[varf]) {
        groups.second.push_back(varf+1);
    }
    return true;
}

pair <vector<int>, vector<int>> possibleBipartition(int N, vector <pair<int, int>> dislikes) {
    vector <vector<int>> graph;
    pair<vector<int>, vector<int>> groups;
    graph.resize(N);
    // ne cream listele de adiacenta
    for (auto &dislike: dislikes) {
        graph[dislike.first - 1].push_back(dislike.second - 1);
        graph[dislike.second - 1].push_back(dislike.first - 1);
    }
    // ne initializam vectorul de culori prin care putem distinge culorile a doua varfuri vecine
    vector<int> colors;
    colors.resize(N, 0);
    for (int i = 0; i < N; ++i) {
        // in cazul in care varful i nu are o culoare...
        if(!colors[i]) {
            // si in cazul in care ajunge sa aiba aceeasi culoare cu un vecin de al lui
            if(!DFS(i, 1, colors, graph, groups)) {
                // returnam o lista vida/goala
                return {};
            }
        }
    }
    return make_pair(groups.first, groups.second);
}

int main() {
    int N;
    int x, y;
    vector<int> colors;
    vector <pair<int, int>> dislikes;
    fin >> N;
    colors.resize(N);
    while (fin >> x >> y) {
        dislikes.push_back(make_pair(x, y));
    }
    pair <vector<int>, vector<int>> groups;
    groups = possibleBipartition(N, dislikes);

    // Verificam lungimile celor doua grupuri formate
    if (!groups.first.size() || !groups.second.size()) {
        fout << "Nu se pot imparti in doua grupe\n";
    } else {
        fout << "Prima grupa: ";
        // iteram primul grup
        for (auto &aux: groups.first) {
            fout << aux << " ";
        }
        fout << "\nA doua grupa: ";
        // iteram al doilea grup
        for (auto &aux: groups.second) {
            fout << aux << " ";
        }
        fout << "\n";
    }
    return 0;
}