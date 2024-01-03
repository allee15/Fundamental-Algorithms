#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#define MAX 1000

using namespace std;

ifstream f("date.in");
ofstream g("date.out");

int N, M, src, dest;
int graph[MAX][MAX]; // exact ca la matricea pt capacitate
int rezGraph[MAX][MAX]; // graful rezidual pe care il cream din graful initial
vector<int>tata;
vector<bool>viz;

bool BFS() {
    viz.clear();
    viz.resize(N+1, false);

    tata.clear();
    tata.resize(N+1, 0);
    // facem BFS incepand din nodul src
    queue<int> q;
    q.push(src);
    viz[src] = true;
    tata[src] = -1;

    // parcurgem vecinii cu BFS pana nu mai putem
    while(!q.empty()) {
        int node = q.front();
        q.pop();

        for(int i = 1; i <= N; ++i) {
            // cautam doar muchiile directe cu ponderea pozitiva
            if(!viz[i] && rezGraph[node][i] > 0) {
                // daca am ajuns la destinatie
                if(i == dest) {
                    tata[i] = node;
                    return true;
                }
                q.push(i);
                tata[i] = node;
                viz[i] = true;
            }
        }
    }
    // nu am gasit niciun drum de la src la dest
    return false;
}

int EdmondsKarp() {
    // initial facem o copie a grafului nostru in cel rezidual
    for(int i = 1; i <= N; ++i) {
        for(int j = 1; j <= N; ++j) {
            rezGraph[i][j] = graph[i][j];
        }
    }

    int max_flow = 0; // fluxul maxim pe care il vom afisa la final

    // cautam DRUM-ul de la src la dest in graful rezidual
    while(BFS()) {
        // vom retine minimul rezidual din drumul pe care l-am gasit - initial ii vom atribui o valoare ff mare
        int path_flow = MAX;

        // parcurgem drumul prin vectorul de tati si cautam minimul
        for(int node = dest; node != src; node = tata[node]) {
            int aux = tata[node];
            path_flow = min(path_flow, rezGraph[aux][node]);
        }

        // parcurgem din nou drumul prin vectorul de tati si actualizam graful rezidual
        for(int node = dest; node != src; node = tata[node]) {
            int aux = tata[node];

            // pentru arcele inverse adunam
            rezGraph[node][aux] += path_flow;

            // pentru arcele directe scadem
            rezGraph[aux][node] -= path_flow;
        }

        // actualizam flowul
        max_flow += path_flow;
    }
    return max_flow;
}

int main() {
    // ne cream graful
    f>>N>>M;
    src = 1, dest = N;
    int node1, node2, c;
    for(int i = 1; i <= M; ++i) {
        f>>node1>>node2>>c;
        graph[node1][node2] = c;
    }
    // algoritmul care va intoarce fluxul maxim folosind graf rezidual
    int rez = EdmondsKarp();
    g<<rez<<endl;

    return 0;
}