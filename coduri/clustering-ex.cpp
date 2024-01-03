#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

using namespace std;

ifstream fin("date.in");
ofstream fout("date.out");

void editDistance(vector<pair<int, pair<int, int>>>&graph, pair<int, string> w1, pair<int, string> w2) {
    vector<vector<int>> matrix;
    matrix.resize(w1.second.length()+1);
    for(int i = 0; i <= w1.second.length(); ++i) {
        matrix[i].resize(w2.second.length()+1);
    }
    for(int i = 0; i <= w1.second.length(); ++i) {
        matrix[i][0] = i;
    }
    for(int j = 0; j <= w2.second.length(); ++j) {
        matrix[0][j] = j;
    }

    for(int i = 1; i <= w1.second.length(); ++i) {
        for(int j = 1; j <= w2.second.length(); ++j) {
            if(w1.second[i-1] == w2.second[j-1]) {
                matrix[i][j] = matrix[i-1][j-1];
            } else {
                matrix[i][j] = min(min(matrix[i - 1][j], matrix[i][j - 1]), matrix[i-1][j-1]) + 1;
            }
        }
    }

    // adaugam in graful nostru tuplul: (distanta de editare, (primul cuvant, al doilea cuvant))
    graph.push_back(make_pair(matrix[w1.second.length()][w2.second.length()], make_pair(w1.first, w2.first)));
}

void afisare(int nr, vector<int>classes, vector<pair<int, string>> words) {
    // cream vectorul responsabil pentru retinerea diferitelor clase pe care le au cuvintele
    vector<int>clusters;
    for(int i = 0; i < nr; ++i) {
        bool ok = true;
        for(auto cluster: clusters) {
            if(classes[i] == cluster) {
                ok = false;
            }
        }
        if(ok) {
            clusters.push_back(classes[i]);
        }
    }

    // parcurgem toate clasele existente si afisam cuvintele in functie de clasa respectiva -> pt organizare
    for(auto cluster: clusters) {
        for(int i = 0; i < nr; ++i) {
            if(cluster == classes[i]) {
                fout<<words[i].second<<" ";
            }
        }
        fout<<endl;
    }
}

void Kruskal(int k, int nr, vector<pair<int ,pair<int, int>>>graph, vector<pair<int, string>>words) {
    // cream vectorul responsabil pentru retinerea claselor cuvintelor -> initial fiecare cuvant are propria clasa
    vector<int> cls;
    cls.resize(nr+1);
    for(int i = 0; i < nr; ++i) {
        cls[i] = i;
    }

    // pentru a ajunge la fix k clase, trebuie sa facem length - k pasi de legare a cuvintelor/grupurilor de cuvinte(unde nr este numarul de cuvinte, iar k este numarul de clase disponibile pt organizarea cuvintelor)
    int length = nr - k;
    for(int i = 0; i <= length; ++i) {
        // din moment ce graph este un vector ordonat crescator dupa distanta de editare dintre cuvinte, mereu vom lua cuvintele cu distanta de editare minima
        auto edge = graph[i];

        // verificam ca cele doua cuvinte sa fie din clase diferite
        if(cls[edge.second.second] != cls[edge.second.first]) {
            // daca da, alipim toate cuvintele din a doua clasa in prima clasa
            for(int j = 0; j < nr; ++j) {
                if(cls[j] == cls[edge.second.second]) {
                    cls[j] = cls[edge.second.first];
                }
            }
        } else {
            // crestem length-ul doar daca muchia pe care am luat-o apartine leaga doua noduri din aceeasi clasa ---> trebuie neaparat sa facem nr - k pasi(daca nu cresteam length, am fi putut face nr-k-1 pasi si nu e corect)
            ++length;
        }
    }

    // ca sa afisam distanta minima dintre clasele create, trebuie sa afisam urmatoarea muchie care vine la rand in graph-ul nostru dupa ce am creat clasele respective
    fout<<graph[length].first<<endl;
    // afisam cuvintele dupa clasele create
    afisare(nr, cls, words);
}

int main() {
    string word;
    int k;
    vector<pair<int, pair<int, int>>> graph;
    vector<pair<int, string>> words;
    int nr = 0;

    // citim toate cuvintele care ne vin din fisier si le punem intr-un vector, retinem numarul de cuvinte citite in nr
    while(fin>>word) {
        words.push_back(make_pair(nr, word));
        ++nr;
    }

    // parcurgem vectorul de cuvinte si pt fiecare pereche de doua cuvinte cream muchia cu ponderea egala cu distanta de editare
    for(int i = 0; i < nr-1; ++i) {
        for(int j = i+1; j < nr; ++j) {
            // alg care creaza muchia in graful nostru(in listele de adiacenta)
            editDistance(graph, words[i], words[j]);
        }
    }

    // sortam vectorul crescator dupa distanta de editare ---> functioneaza deoarece sort-ul o sa mearga in primul pair din vector si o sa verifice first mai intai care e distanta de editare
    sort(graph.begin(), graph.end());


    cin>>k;
    cout<<endl;

    Kruskal(k, nr, graph, words);

    return 0;
}

// Complexitate: O(n*n) --> constructia listelor de adiacenta cu distanta de editare intre oricare 2 noduri