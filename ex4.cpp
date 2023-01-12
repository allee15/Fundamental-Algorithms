#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int n,m,nrtc;
ifstream f("graf.in");

void citire(vector< vector<int> >& a) //citim si formam matricea de adiacenta
{
    int x, y;

    for (int i = 1; i <= m; i++)
    {
        f >> x >> y;
        a[x][y] = 1;
    }

}
void parc_l(int x, int c, vector< vector<int> > a, vector<int>& viz1) //parcurgem in latime graful BFS
{
    viz1[x] = c; //marcam nodul curent ca l-am vizitat
    for (int i = 1; i <= n; i++) //parcurgem nodurile
        if (a[x][i] == 1 && viz1[i] == 0)  //daca avem muchie intre nodul x si nodul i, iar nodul i este nevizitat
            parc_l(i, c,a,viz1); //atunci realizam o parcurgere BFS si pt nodul i
}
void parc_c(int x, int c, vector< vector<int> >a, vector<int> &viz2)
{ //realizam de asemenea si o parcurgere in adancime DFS
    viz2[x] = c; //marcam ca am vizitat nodul curent x
    for (int i = 1; i <= n; i++) //analog ca la subprogramul pt BFS
        if (a[i][x] == 1 && viz2[i] == 0)
            parc_c(i, c,a,viz2);
}
int main()
{
    f >> n >> m;
    vector< vector<int> >a(n+1, vector<int>(n+1,0));
    vector<int> viz1(n+1,0);
    vector<int>viz2(n+1,0);
    citire(a);
    for (int i = 1; i <= n; i++) //parcurgem nodurile grafului
        if (viz1[i] == 0) //daca nodul curent nu a fost vizitat
        { //realizam intai parcurgerea sa in adancime si apoi in latime
            nrtc++; //inseamna ca am gasit o noua componenta tare conexa
            parc_c(i, nrtc,a,viz2);
            parc_l(i, nrtc,a,viz1);
            for (int j = 1; j <= n; j++)//la finalizarea parcurgerilor, daca nodul j nu are acelasi tata in
                //cei 2 de vizite corespunzatori fiecarei parcurgeri, atunci marcam nodul cu 0 in ambii vectori de
                //vizite, pentru a-l prelucra mai tarziu
                if (viz1[j] != viz2[j])
                    viz1[j] = viz2[j] = 0;
        }
    cout << nrtc<<endl; //afisam nr de componente conexe
    int contor = 1; //apoi cu un while vrem sa afisam pe rand , fiecare componenta conexa cu nodurile ei
    while(contor<=nrtc)
    {
        for (int j = 1; j <= n; j++)
            if (viz1[j] == contor)
                cout << j << " ";
        contor++;
        cout << endl;
    }
    return 0;
}
//preprocesare: O(m)
//procesare: O(n+m)