// Construirea unui graf orientat, avand numarul de grade de intrare si grade de iesire date
// Afisarea numarului de drumuri construite, si a drumurilor posibile
#include <iostream>
#include <fstream>
#include <queue>
#define INF 9999999

using namespace std;
ifstream f("harta.in");
ofstream g("harta.out");

//  O(N*M),N-nr varfuri, M-nr muchii
vector<vector<int>>la;
int capacitate[202][202];
int tata[202];
int n;
int BFS()
{
    queue<pair<int,int>> q;
    // initializam vectorul de tati
    for(int i=0; i<=2*n+1; i++)
    {
        tata[i]=-1;
    }
    q.push({0,INF});
    tata[0]=-2;

    // cat timp inca avem noduri in queue
    while(!q.empty())
    {
        int u=q.front().first;
        int flow=q.front().second;
        q.pop();
        // parcurgem vecinii nodului curent
        for(auto v:la[u])
        {
            // daca nu a fost vizitat si capacitatea reziduala este pozitiva
            if(tata[v]==-1 && capacitate[u][v]>0)
            {
                // actualizam tatal pentru vecin
                tata[v]=u;
                // actualizam capacitatea reziduala minima
                int new_flow=min(flow,capacitate[u][v]);
                // daca am ajuns la final, returnam capacitatea reziduala minima
                if(v==2*n+1)
                    return new_flow;
                // introducem vecinul in queue
                q.push({v,new_flow});
            }
        }
    }
    return 0;
}
int calc()
{
    // initializam flowul maxim si flowul
    int flow,maxflow=0;
    // cat timp exista lant de la s la t - salvam in flow valoarea returnata de BFS
    while((flow=BFS()))
    {
        // adaugam la flowul maxim
        maxflow+=flow;
        int cur=2*n+1;
        //revizuim flux lant
        while(cur!=0)
        {
            // parcurgem vectorul de tati
            int prev=tata[cur];
            capacitate[cur][prev]+=flow;
            capacitate[prev][cur]-=flow;
            cur=prev;
        }
    }
    // returnam flowul maxim
    return maxflow;

}
int main()
{
    // citim numarul de orase/noduri
    f>>n;

    // ne cream lista de adiacenta, matricea de capacitate  -> ca urmare reteaua
    la.resize(2*n+2);
    for(int i=1; i<=n; i++)
    {
        // citim gradele de intrare si iesire pentru un nod si cream muchie de la s la acesta cu prima valoare
        int x,y;
        f>>x>>y;
        la[0].push_back(i);// ad muchii cu cap x
        la[i].push_back(0);
        capacitate[0][i]=x;

        // cream muchie de la nod la t cu a doua valoare
        capacitate[n+i][2*n+1]=y;//ad muchii cu cap y
        la[n+i].push_back(2*n+1);
        la[2*n+1].push_back(n+i);
        for(int j=n+1; j<=2*n; j++)
        {

            if(j-i==n)// ad muc cu cap 1 si i!=j
                continue;

            // cream muchii de la nod din prima partitie la celelalte noduri din a doua partitie
            capacitate[i][j]=1;
            la[i].push_back(j);
            la[j].push_back(i);
        }
    }

    // afisam numarul de drumuri posibile -> fluxul maxim
    g<<calc()<<'\n';


    for(int i=1; i<=n; i++)
        for(int j=n+1; j<=2*n; j++)
            //
            if(capacitate[j][i]==1)
            {
                g<<i<<" "<<j-n<<'\n';
            }


}