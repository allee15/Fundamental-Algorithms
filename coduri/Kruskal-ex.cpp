#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <bits/stdc++.h>

using namespace std;

ifstream fin("date.in");
ofstream fout("date.out");
int N, M;
float totalSum;

bool isEmpty(const vector<int>& nodes) {
    // verificam ca toate elementele au fost vizitate si ca s-a terminat cautarea/crearea arborelui
    for(auto el: nodes) {
        if(el) {
            // a ramas cel putin un nod nevizitat
            return false;
        }
    }
    // toti au fost vizitati
    return true;
}

float Prim(vector<vector<pair<int,float>>> graph) {
    // ne setam vectorii cu care vom lucra -> de vizitati, de tati si de distante
    vector<int> visited;
    visited.resize(N+M, 1);
    vector<float> distances;
    distances.resize(N+M, 9999);
    vector<int> fathers;
    fathers.resize(N+M, 0);
    distances[0] = 0;

    // cat timp inca exista noduri nevizitate
    while(!isEmpty(visited)) {
        // luam nodul cu distanta cea mai mica.
        int node = min_element(distances.begin(), distances.end()) - distances.begin();
        visited[node] = 0;
        // parcurgem toti vecinii
        for(auto el: graph[node]) {
            // daca vecinul lui nu si-a terminat ciclul de cautare pentru vecinii lui si daca are distanta mai mica decat distanta dintre dist dintre nodul actual si nodul vecin
            if(visited[el.first] && el.second < distances[el.first]) {
                distances[el.first] = el.second;
                fathers[el.first] = node;
                // in cazul in care nodul curent se duce catre o fabrica iar tatal acestui nod este tot o fabrica
                if(node >= N && el.first < N && fathers[node] < N && distances[node] > distances[el.first]) {
                    // cautam nodul care este conectat la cele doua fabrici si ii stergem conexiunea la fabrica cu dist mai mare
                    for(auto it: graph[fathers[node]]) {
                        if(it.first == node) {
                            totalSum -= it.second;
                        }
                    }
                }
            }
        }
        // la final adaugam distanta si ii setam la maxim pentru a nu o mai selecta vreodata
        if(node >= N) {
            totalSum += distances[node];
        }
        distances[node] = 9999;
    }
    // returnam suma totala
    return totalSum;
};

int main() {
    fin>>N>>M;
    if(N > 2000 || M > 2000)
        exit(0);

    vector<pair<int ,int>>roots;
    vector<vector<pair<int,float>>> graph;
    graph.resize(N+M);
    int x, y;
    // vectorul de centrale
    for(int i = 0; i < N; ++i) {
        fin>>x>>y;
        roots.push_back(make_pair(x, y));
    }

    // ne cream legaturile dintre fabrici si orase dar si legaturi intre orase
    for(int i = 0; i < M; ++i) {
        fin>>x>>y;
        roots.push_back(make_pair(x,y));
        for(int j = 0; j < N; ++j) {
            graph[j].push_back(make_pair(N+i,sqrt((x-roots[j].first)*(x-roots[j].first) + (y-roots[j].second)*(y-roots[j].second))));
            graph[i+N].push_back(make_pair(j,sqrt((x-roots[j].first)*(x-roots[j].first) + (y-roots[j].second)*(y-roots[j].second))));
        }
        for(int k = 0 ; k < i; ++k) {
            graph[N+k].push_back(make_pair(N+i,sqrt((x-roots[N+k].first)*(x-roots[N+k].first) + (y-roots[N+k].second)*(y-roots[N+k].second))));
            graph[N+i].push_back(make_pair(N+k,sqrt((x-roots[N+k].first)*(x-roots[N+k].first) + (y-roots[N+k].second)*(y-roots[N+k].second))));
        }
    }

    float min = Prim(graph);
    fout<<fixed<<showpoint;
    fout<<setprecision(8)<<min<<endl;
    return 0;
}

// Complexitate: O(m log n) - unde m - nr de muchii, n - numarul de noduri