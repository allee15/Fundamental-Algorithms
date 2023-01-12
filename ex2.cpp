#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

int n, m, drum, contor;

int verificare(int x, int y, vector<int>&a) //in acest subprogram vrem sa vedem daca nodurile x si y abia citite de
//la tastatura apar in sirul primit in input, unul dupa altul
//in caz ca apar, returnam 1
{
	for (int i = 1; i <= n ; i++)
		if (x == a[i])
		{
			if (y == a[i + 1])
				return 1;
			else
				if (i>1 && y == a[i - 1])
					return 1;
		}
	return 0;

}

int main()
{
	ifstream f("graf.in");
	f >> n >> m;
	vector<int> a(n + 1);
	for (int i = 1; i <= n; i++) //citim sirul dat in input
	{
		int x; f >> x; a[i] = x;
	}
	for (int i = 1; i <= m; i++) //citim muchiile grafului
	{
		int x, y;
		f >> x >> y;
		if (x == 1 || y==1) contor++;
		if (verificare(x, y,a) ==1 ) //daca x si y apar unul dupa altul in sirul dat in input,
            //crestem contorul numit drum (cu acesta vedem la final daca am reusit sa formam acel sir dat in input
		{
			drum++;
		}
	}//la final afisam mesaj corespunzator in functie de deznodamantul programului
	if (contor+1 == n) cout << "1";
	else
	{
		if (drum+1 == n) cout << "1";
		else cout << "0";
	}
	return 0;

}
//preprocesare: O(n)
//procesare: O(n*m)