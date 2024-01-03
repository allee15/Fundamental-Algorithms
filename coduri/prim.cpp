#include <iostream>
#include <vector>
#include <queue>

using namespace std;

void prim(vector<vector<pair<int, int>>> &lists, int start_node) {

    const int inf = 1 << 25;

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    vector<bool> visited(lists.size());
    vector<int> dist(lists.size(), inf), dad(lists.size(), 0);

    pq.push({0, start_node});
    dist[start_node] = 0;
    dad[start_node] = 0;

    while (!pq.empty()) {

        while (!pq.empty() && visited[pq.top().second]) {
            pq.pop();
        } // asta e pentru ca avem dubluri

        if (pq.empty())
            continue;
        auto p = pq.top();
        pq.pop();

        int u = p.second;
        visited[u] = true;

        for (auto &neighbour : lists[u]) {
            if (!visited[neighbour.first] && dist[neighbour.first] > neighbour.second) {
                //daca nu e viiztat si distanta pana la el e mai mare decat muchia u->neighbour
                dist[neighbour.first] = neighbour.second;
                //daca aveam heap-ul nostru, dadeam repair, nu bagam, direct
                dad[neighbour.first] = u;
                pq.push({dist[neighbour.first], neighbour.first});
            }
        }

    }
    for (int i = 1; i < dad.size(); i++) {
        if (dist[i] != 0)
            cout << i << " " << dad[i] << " -> " << dist[i] << endl;
    }
}

int main() {
    vector<vector<pair<int, int>>> neighbours;
    int n, m;
    cin >> n >> m;
    neighbours.resize(n + 1);
    int x, y, cost;
    for (int i = 1; i <= m; i++) {
        cin >> x >> y >> cost;
        neighbours[x].push_back({y, cost});
        neighbours[y].push_back({x, cost});
    }
    prim(neighbours, 1);
}