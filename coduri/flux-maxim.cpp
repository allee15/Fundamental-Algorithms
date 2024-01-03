#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#define MAX 1000
#include <queue>

using namespace std;

ifstream f("date.in");
ofstream g("date.out");

int N, M;
int total_flux;
int src, dest;
vector<int> tata;
int cap[MAX][MAX];
int flow[MAX][MAX];
vector<int>cap_rez;

bool construieste_s_t_lant_nesaturat_BF();

void revizuieste_lant();

int main() {

    // nodul 1 - start, N - destinatie
    f>>N>>M;
    src = 1, dest = N;

    int node1, node2, c;

    for(int i = 1; i <= M; ++i) {
        // ne citim muchiile
        f>>node1>>node2>>c;
        // ne folosim doar de matricea pentru capacitati pentru a vedea si muchiile din graful nostru orientat - adaugam cantitatea pe muchia pe care am citit-0
        cap[node1][node2] = c;
    }

    // cat timp exista un lant f-nesaturat in reteaua noastra
    while(construieste_s_t_lant_nesaturat_BF()) {
        // revizuim lantul gasit
        revizuieste_lant();
    }

    // afisam fluxul maxim dupa ce nu mai exista lanturi nesaturate
    g<<total_flux<<endl;
    return 0;
}

bool construieste_s_t_lant_nesaturat_BF() {
    // initializarile noastre - folosim clear pentru a fi siguri ca nu ramanem cu acelasi date ca inainte
    queue<int> q;
    tata.clear();
    tata.resize(N+1, -1);

    // capacitatea reziduala a lantului nostru -> o sa ne folosim de ea pentru a calcula minimul de capacitate pe lantul gasit
    cap_rez.clear();
    cap_rez.resize(N+1, MAX);

    q.push(src);
    tata[src] = -2;

    // parcurgere BFS
    while(!q.empty()) {
        int node = q.front();
        q.pop();

        // parcurgem muchiile directe folosindu-ne de matricea lui cap - pentru asta parcugem linia lui node
        for(int j = 1; j <= N; ++j) {
            // verificam daca exista muchia - adica daca se afla capacitate pe muchia dintre cele doua noduri
            if(cap[node][j]) {
                // conditia pentru care putem inainta cu BFS-ul
                if(tata[j] == -1 && cap[node][j] - flow[node][j] > 0) {
                    q.push(j);
                    tata[j] = node;
                    // calculul pentru muchie directa
                    cap_rez[j] = cap[node][j] - flow[node][j];
                    if(j == dest) {
                        return true;
                    }
                }
            }
        }

        // parcurgem muchiile inverse folosindu-ne de matricea lui cap - pentru asta parcugem coloane lui node
        for(int j = 1; j <= N; ++j) {
            // verificam daca exista muchia - adica daca exista valoare pentru capacitate
            if(cap[j][node]) {
                // conditia pentru a avansa cu BFS-ul
                if(tata[j] == -1 && flow[j][node] > 0) {
                    q.push(j);
                    // facem tatal negativ pentru a sti ca este muchie de intoarcere
                    tata[j] = -node;
                    cap_rez[j] = flow[node][j];
                    if(j == dest) {
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

void revizuieste_lant() {
    int minim_cap_rez = MAX;
    int aux = dest;

    // parcurgem tot langul nostru folosindu-ne de vectorul de tati si retinem mininul
    while (aux != src) {
        if(minim_cap_rez > cap_rez[aux]) {
            minim_cap_rez = cap_rez[aux];
        }

        // daca tatal este pozitiv atunci luam valoarea asta cum este
        if(tata[aux] > 0) {
            aux = tata[aux];
        } else { // daca tatal este negativ, luam opusul valorii
            aux = -tata[aux];
        }
    }
    aux = dest;

    // parcurgem din nou lantul si actualizam flow-ul pentru fiecare muchie
    while(aux != src) {
        // pentru muchie directa
        if (tata[aux] > 0) {
            flow[tata[aux]][aux] += minim_cap_rez;
            aux = tata[aux];
        } else if (tata[aux] < 0) { // pentru muchie inversa
            flow[aux][-tata[aux]] -= minim_cap_rez;
            aux = -tata[aux];
        }
    }

    // adunam la total minimul pe care l-am gasit - reprezinta fluxul maxim din final
    total_flux += minim_cap_rez;
}