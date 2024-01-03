#include <iostream>
#include <fstream>
#include <queue>
#include <vector>
#include <climits>
using namespace std;

ifstream fin("cuplaj.in");
ofstream fout("cuplaj.out");

vector<int> viz, tata;
vector<vector < int>> graf;
struct muchie
{
    int x, y, cap, poz;
};

//Ford-Fulkerson

vector<muchie> edges;

int n, capacity, src, dest, l_unit, r_unit;

int bfs()
{
    tata.clear();
    tata.resize(n);
    fill(viz.begin(), viz.end(), 0);
    queue<int> que;
    que.push(src);
    viz[src] = 1;

    while (!que.empty())
    {
        int nod = que.front();
        que.pop();
        if (nod == dest)
            continue;
        for (int i : graf[nod])
        {
            muchie m_curent = edges[i];
            if (!viz[m_curent.y] and m_curent.cap != 0)
            {
                viz[m_curent.y] = 1;
                tata[m_curent.y] = i;
                que.push(m_curent.y);
            }
        }
    }

    return viz[dest];
}

int maxflow()
{
    int flux_maxim = 0;

    while (bfs())
    {
        for (auto i : graf[dest])
        {
            if (viz[edges[i].y] and edges[edges[i].poz].cap != 0)
            {
                int flux_curr = INT_MAX;
                muchie m_curr = edges[i];
                tata[dest] = m_curr.poz;
                int nod = dest;
                while (nod != src)
                {
                    flux_curr = min(flux_curr, edges[tata[nod]].cap);
                    nod = edges[tata[nod]].x;
                }

                nod = dest;
                while (nod != src)
                {
                    edges[tata[nod]].cap -= flux_curr;
                    edges[edges[tata[nod]].poz].cap += flux_curr;
                    nod = edges[tata[nod]].x;
                }

                flux_maxim += flux_curr;
            }
        }
    }

    return flux_maxim;
}

int main()
{
    fin >> l_unit >> r_unit >> capacity;
    n = l_unit + r_unit + 2;
    src = 0;
    dest = n - 1;
    viz.resize(n);
    tata.resize(n);
    graf.resize(n);
    for (int i = 1; i <= capacity; i++)
    {
        int x, y;
        fin >> x >> y;
        edges.push_back({ x, y + l_unit, 1, 2 * i - 1 });
        edges.push_back({ y + l_unit, x, 0, 2 * i - 2 });
        graf[y + l_unit].push_back(2 * i - 1);
        graf[x].push_back(2 * i - 2);
    }

    int e_size = int(edges.size());
    for (int i = 1; i <= l_unit; i++)
    {
        e_size += 2;
        edges.push_back({ src, i, 1, e_size - 1 });
        graf[i].push_back(e_size - 1);
        edges.push_back({ i, src, 0, e_size - 2 });
        graf[src].push_back(e_size - 2);
    }

    for (int i = l_unit + 1; i < n - 1; i++)
    {
        e_size += 2;
        edges.push_back({ i, dest, 1, e_size - 1 });
        graf[dest].push_back(e_size - 1);
        edges.push_back({ dest, i, 0, e_size - 2 });
        graf[i].push_back(e_size - 2);
    }

    fout << maxflow() << endl;

    for (auto& it : edges)
    {
        if (it.cap == 0 && it.x != src && it.y != dest && it.x < it.y)
        {
            fout << it.x << " " << it.y - l_unit << "\n";
        }
    }


    return 0;

}