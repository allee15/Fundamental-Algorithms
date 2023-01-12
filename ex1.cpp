#include <iostream>
#include <fstream>

using namespace std;

int n,gata=1;
ifstream f("graf.in");
void citire(int a[101][101]) //citim muchiile si formam matricea de adiacenta
{
    f>>n;
    int x,y;
    while(f>>x>>y)
        a[x][y]=a[y][x]=1;
}

void parc_ad(int x, int c,int a[101][101], int culoare[101])
{
    culoare[x]= c;
    for(int i=1;i<=n;i++) //parcurgem in adancime matricea (DFS) si practic vrem sa coloram matricea in 2 culori
        //daca acest lucru este posibil => graful este bipartit
        //pentru culori vom folosi 1 si -1
        //culoarea fiecarui nod va fi retinuta intr-un vector de culori
        if(a[x][i]==1) //daca exista muchia
        {
            if(culoare[i]==0) //daca nodul curent nu a fost colorat
                parc_ad(i,-c,a,culoare); //il coloram cu - culoarea nodului x si parcurgem si pt nodul i toti vecinii
            else
                if(culoare[x] == culoare[i]) //daca gasim 2 noduri alaturate, care au muchie intre ele adica, de
                    //aceeasi culoare, cautarea s-a terminat=> nu putem colora in doar 2 culori graful
                    gata=0;
        }
}

int main()
{
    int a[101][101], culoare[101];
    citire(a);
    int verif=1; //presupunem ca graful este bipartit
    for(int i=1;i<=n;i++) //parcurgem nodurile grafului
    {
        verif=1;
        if(culoare[i] == 0) //daca nodul curent nu este colorat
        {
            gata=1; //presupunem ca este colorat diferit fata de nodurile cu care are muchii
            parc_ad(i,1,a,culoare); //ii parcugem vecinii
            verif=(verif && gata); //daca ambele sunt true => true
        }
    }
    if(verif) //daca graful chiar este bipartit
    {
        cout<<"true"<<endl; //afisam mesaj corespunzator si pt ex 1b afisam si cele 2 grupe de noduri formate
        for(int i=1;i<=n;i++)
            if(culoare[i]==1)
                cout<<i<<" ";
        cout<<endl;
        for(int i=1;i<=n;i++)
            if(culoare[i]==-1)
                cout<<i<<" ";
    }
    else
        cout<<"false"<<endl; //altfel afisam mesaj corespunzator
    return 0;
}
//complexitatea algoritmului:
//preprocesare: O(n)
//procesare; O(n+m)