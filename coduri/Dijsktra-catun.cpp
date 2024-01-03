#include <fstream>
#include <queue>
#define INF 99999999

using namespace std;

ifstream fin("date.in");
ofstream fout("date.out");

int main() {
    int N,M,K;
    vector<pair<int, int>>distances;
    vector<vector<pair<int, int>>> graph;
    vector<int>fortress;
    queue<pair<int, int>>q;

    fin>>N>>M>>K;

    distances.resize(N+1, make_pair(INF, INF));
    graph.resize(N+1);

    for(int i = 1; i <= K; ++i) {
        int x;
        fin>>x;
        distances[x] = make_pair(0, x);
        fortress.push_back(x);
        q.push(make_pair(0, x));
    }

    for(int i = 1; i <= M; ++i) {
        int x,y,length;
        fin>>x>>y>>length;
        graph[x].push_back(make_pair(y, length));
        graph[y].push_back(make_pair(x, length));
    }

    while(!q.empty()) {
        int node = q.front().second;
        q.pop();

        for (auto el: graph[node]) {
            if (distances[el.first].first > distances[node].first + el.second ||
                distances[el.first].first == distances[node].first + el.second &&
                distances[node].second < distances[el.first].second) {
                distances[el.first].first = distances[node].first + el.second;
                distances[el.first].second = distances[node].second;
            }
        }
    }

    // resetam distanta pentru toate fortaretele la 0
    for(int fort:fortress) {
        distances[fort].second = 0;
    }

    for (int i = 1; i < distances.size(); i++) {
        if (distances[i].second == INF)
            fout << 0 << " ";
        else
            fout << distances[i].second << " ";
    }

    return 0;
}

// Complexitate: O(m log n)