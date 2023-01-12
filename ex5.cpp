#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

ifstream f("graf.in");
int n,m,d,e, a[201][201],  viz[201], prec[201], gata;
int cd[201];
void citire() //citim si formam matricea de adiacenta
{
    int x, y;
    f >> n >> m ;
    for(int i=1;i<=m;i++)
    {
        f>>x>>y;
        a[x][y] = 1;
    }
    f>>d>>e; //citim si cele 2 noduri catre care trebuie sa cautam drumurile
}
void parc_lat(int x,int p)//parcurgem in latime graful pt nodul x pana la nodul p
{

    int prim, ultim;
    prim = ultim = 1;
    cd[prim] = x;
    viz[x] = 1;
    prec[x] = -1;


    while (prim <= ultim && !gata)
    {
        x = cd[prim];
        for (int i = 1; i <= n && !gata; i++)
            if (viz[i] == 0 && a[x][i] == 1)
            {

                ultim++;
                cd[ultim] = i;
                viz[i] = viz[x] + 1;
                prec[i] = x;
                if (i == p)
                    gata = 1;

            }
        prim++;
    }
}
void drum(int i, int rez[201], int &l) //aici reluam traseul parcurs in subprogramul de parccurgere si il
//stocam intr-un vector, pentru a-l afisa mai tarziu
{
    if (i == -1)
        return;
    drum(prec[i], rez,l);
    rez[l++]=i;
}
void restartare()
{
    gata=0;
    for(int i=1;i<=n;i++)
    {
        cd[i]=0;
        viz[i]=0;
        prec[i]=0;
    }
}
int main()
{
    citire();//citim muchiile, formam matricea de adiacenta si parcurgem nodurile grafului
    for(int i=1;i<=n;i++)
    {//cautam drumuri de la nodul i pana la nodul d si apoi de la i pana la nkodul e
        //d si e sunt cele 2 noduri din input
        //la final afisam minimul dintre lungimile celor 2 drumul gasite
        int rez1[201], rez2[201],l1=0,l2=0;
        restartare();
        parc_lat(i,d);
        drum(d,rez1,l1);
        restartare();
        parc_lat(i,e);
        drum(e,rez2,l2);

       cout<<i<<": "<<endl;
        for(int j=0;j<l1;j++)
            cout<<rez1[j]<<" ";
        cout<<endl;
        for(int j=0;j<l2;j++)
            cout<<rez2[j]<<" ";
        cout<<endl;

        cout<<min(l1,l2)-1<<" ";
        cout<<endl<<"***********"<<endl;

    }
    return 0;
}