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
    // FIX ACELASI ALGORITM CA LA FLUX MAXIM - cu mici exceptii
    f>>N>>M;
    src = 1, dest = N;

    int node1, node2, c;

    for(int i = 1; i <= M; ++i) {
        f>>node1>>node2>>c;
        cap[node1][node2] = c;
    }

    while(construieste_s_t_lant_nesaturat_BF()) {
        revizuieste_lant();
    }

    g<<total_flux<<endl;
    return 0;
}

bool construieste_s_t_lant_nesaturat_BF() {
    queue<int> q;
    tata.clear();
    tata.resize(N+1, -1);

    cap_rez.clear();
    cap_rez.resize(N+1, MAX);

    q.push(src);
    tata[src] = -2;

    while(!q.empty()) {
        int node = q.front();
        q.pop();

        for(int j = 1; j <= N; ++j) {
            if(cap[node][j]) {
                if(tata[j] == -1 && cap[node][j] - flow[node][j] > 0) {
                    q.push(j);
                    tata[j] = node;
                    cap_rez[j] = cap[node][j] - flow[node][j];
                    if(j == dest) {
                        return true;
                    }
                }
            }
        }

        for(int j = 1; j <= N; ++j) {
            if(cap[j][node]) {
                if(tata[j] == -1 && flow[j][node] > 0) {
                    q.push(j);
                    tata[j] = -node;
                    cap_rez[j] = flow[node][j];
                    if(j == dest) {
                        return true;
                    }
                }
            }
        }
    }
    // inainte de a returna fals - faptul ca nu mai exista lanturi am putea sa:

    // 1. sa afisam cele doua multime care fac delimitarea dintre taietura-minima

    // multimea de noduri la care se poate ajunge din src (au tatal diferit de -1)
    for(int i = 1; i < N; ++i) {
        if(tata[i] != -1) {
            cout<<i<<" ";
        }
    }
    cout<<endl;

    // multimea de noduri la care nu se poate ajunge din src (au tatal egal cu -1)
    for(int i = 2; i <= N; ++i) {
        if(tata[i] == -1) {
            cout<<i<<" ";
        }
    }
    cout<<endl;

    // 2. sa afisam muchiile care delimiteaza cele doua mutimi de noduri
    for(int i = 1; i <N; ++i) {
        if(tata[i] != -1) {
            for(int j = 2; j <= N; ++j) {
                if(cap[i][j]) {
                    cout<<i<<" "<<j<<endl;
                }
            }
        }
    }
    return false;
}

void revizuieste_lant() {
    int minim_cap_rez = MAX;
    int aux = dest;

    while (aux != src) {
        if(minim_cap_rez > cap_rez[aux]) {
            minim_cap_rez = cap_rez[aux];
        }

        if(tata[aux] > 0) {
            aux = tata[aux];
        } else {
            aux = -tata[aux];
        }
    }
    aux = dest;

    while(aux != src) {
        if (tata[aux] > 0) {
            flow[tata[aux]][aux] += minim_cap_rez;
            aux = tata[aux];
        } else if (tata[aux] < 0) {
            flow[aux][-tata[aux]] -= minim_cap_rez;
            aux = -tata[aux];
        }
    }
    total_flux += minim_cap_rez;
}