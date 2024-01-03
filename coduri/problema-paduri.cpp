#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

ifstream fin("date.in");
ofstream fout("disjoint.out");

int find(int x, vector<int>& tati) {
    int root = x, aux;
    // cautam un nod care pointeaza catre sine insusi cu alte cuvinte cautam radacina arborelui
    while(tati[root] != root) {
        root = tati[root];
    }

    // compresia drumurilor --> facem ca fiecare nod de la x la radacina sa pointeze catre radacina
    while(tati[x] != x) {
        // retinem tatal lui x
        aux = tati[x];
        // facem ca tatal lui x sa fie radacina
        tati[x] = root;
        // mergem la vechiul tata al nodului curent
        x = aux;
    }
    return root;
}

void unite(int node1, int node2, vector<int>& tati, vector<int>& rang) {
    if(rang[node1] > rang[node2]) {
        tati[node2] = node1;
    } else {
        tati[node1] = node2;
    }
    if(rang[node1] == rang[node2]) {
        rang[node2]++;
    }
}
int main() {
    int N, M;
    // pentru poz 1 punem un -1
    vector<int> tati;
    tati.push_back(-1);
    vector<int> rang;
    rang.push_back(-1);

    fin>>N>>M;
    for(int i = 1; i <= N; ++i) {
        tati.push_back(i);
        rang.push_back(1);
    }

    for(int i = 0 ; i < M; ++i) {
        int code, x, y;
        fin>>code>>x>>y;

        if(code == 1) {
            // in cazul in care cele doua noduri de afla in acelasi arbore, nu trebuie sa mai facem nimic si mergem mai departe
            if(find(x, tati) == find(y, tati)) {
                continue;
            }
            // altfel unim cei doi arbori
            unite(find(x, tati), find(y, tati), tati, rang);

            vector<int> aux;
            aux.push_back(rang[1]);
            for(auto it: rang) {
                bool found = false;
                for(auto el: aux) {
                    if(it == el){
                        found = true;
                    }
                }
                if(!found) {
                    aux.push_back(it);
                }
            }
            fout<<aux.size()-1<<endl;
        } else if(code == 2) {
            // verificam daca cele doua noduri se afla in arbore sau nu
            if(find(x, tati) == find(y, tati)) {
                fout<<"DA\n";
            } else {
                fout<<"NU\n";
            }
        }
    }


    return 0;
}

// Complexitate: O(log N) - unde N este numarul de noduri