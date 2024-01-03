#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;

const int INF = 110001
ifstream f("date.in");
ofstream g("date.out");

int n, m;
int capacitate[1001][1001];
vector<int>tata, viz;
vector<int>graf[1001];
queue<int>q;

int BF()
{
    viz.assign(n+1, 0);
    tata.assign(n+1, 0);
    while(!q.empty())
        q.pop();

    q.push(1);
    viz[1]=1;
    tata[1]=1;

    while(!q.empty())
    {
        int nod=q.front();
        q.pop();

        if(nod==n) continue;

        for(auto j:graf[nod])
        {
            if(viz[j]==0 && capacitate[nod][j]>0)
            {
                q.push(j);
                tata[j]=nod;
                viz[j]=1;
            }
        }
    }
    return viz[n];
}

int main()
{
    f>>n>>m;
    int x,y,c,flowmaxim;
    for(int i=1; i<=m; i++)
    {
        // muchie de la x la y cu capacitatea c
        f>>x>>y>>c;
        capacitate[x][y] = c;
        graf[x].push_back(y);
        graf[y].push_back(x);
    }
    while(BF()) // cat timp exista un lant nevizitat de la sursa la destinatie
    {
        for(auto nod: graf[n])
        {
            if(!viz[nod]) continue;

            tata[n]=nod;
            int flow=INF;

            // cautam valoarea minima cu care putem creste fluxul de pe drumul de la sursa la destinatie
            for(nod=n; nod!=1; nod=tata[nod])
                flow=min(flow, capacitate[tata[nod]][nod]);

            if(flow==0) continue;

            for(nod=n; nod!=1; nod=tata[nod])
            {
                capacitate[tata[nod]][nod]-=flow; // capacitatea muchiei din graful initial scade
                capacitate[nod][tata[nod]]+=flow; // capacitatea muchiei inverse creste
            }
            flowmaxim+=flow;
        }

    }
    g<<flowmaxim;
    return 0;
}

// Complexitate: O(n*3) unde n este numarul de noduri