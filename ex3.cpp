#include <fstream>
#include <iostream>

using namespace std;

ifstream f("graf.in");

int n;

void citire(int a[101][101]) //citim muchiile si le salvam pe invers in matricea de adiacenta
{
    int x,y;
    f>>n;
    while(f>>x>>y)
        a[y][x]=1;
}
void parc_ad(int x,int a[101][101], int viz[101], int &length, int rez[101])
{//parcurgem in adancime graful (DFS) si salvam nodurile vizitate intr-un vector
    rez[length++]=x;
    viz[x]=1; //marcam nodul curent ca l-am vizitat o data, ca sa nu-l mai vizitam si a doua oara
    for(int i=1;i<=n;i++) //parcurgem graful si daca exista muchie de la nodul x la nodul i si i nu a fost vizitat,
        //il vom parcurge si pe i
        if(a[x][i]==1 && viz[i]==0)
            parc_ad(i,a,viz,length,rez);
}
int main()
{

    int a[101][101],viz[101], length=0, gata=0, rez[101];
    citire(a);

    for(int i=1;i<=n;i++) //parcurgem graful si pt fiecare nod facem o parcurgere in adancime
    {
        parc_ad(i,a,viz,length,rez);
        if(length==n) //daca am gasit un circuit hamiltonian, inseamna ca cerinta exercitiului este satisfacuta
            //in acest caz, afisam nodurile in ordinea in care le-am parcurs cu DFS si iesim din for, deoarece
            //am terminat exercitiul
        {
            for(int j=0;j<length;j++)
            {
                cout<<rez[j]<<" "; gata=1;
            }
        break;
        }

    }
    if(gata==0) //daca insa nu am gast circuitul hamiltonian, afisam vectorul vid si rezolvam si ex 3b,
        //care ne cere sa afisam totusi circuitul gasits
    {
        cout<<"[]"<<endl<<"ex 3b:"<<endl;
        for(int i=0;i<length;i++)
            cout<<rez[i]<<" ";
    }

    return 0;
}
//preprocesare: O(m)
//procesare: O(n+m)
