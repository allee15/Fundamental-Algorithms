#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

ifstream fin("date.in");
ofstream fout("date.out");

int tests;

int DFS(int node, int initialSum, int maxSum, vector<vector<int>> graph, vector<bool>& visited, vector<int> values) {
    visited[node] = true;
    for(auto it: graph[node]) {
        if(!visited[it]) {
            // verific daca ajung intr-un punct in care suma creata este mai mare decat suma maxima pe care o avem pana in acel punct
            if(values[it] + initialSum > maxSum) {
                maxSum = values[it] + initialSum;
            }
            initialSum += values[it];
            maxSum = max(maxSum ,DFS(it, initialSum, maxSum, graph, visited, values));
            initialSum -= values[it];
        }
    }
    return maxSum;
}

int main() {
    fin>>tests;
    while(tests) {
        int N, M;
        fin>>N>>M;
        vector<int> values(N+1);
        vector<vector<int>> graph(N+1);
        int max = -1, nodeStart = 1;
        for(int i = 1 ; i <= N; ++i) {
            int value;
            fin>>value;
            if(value > max) {
                max = value;
                nodeStart = i;
            }
            values[i] = value;
        }
        for(int i = 0; i < M; ++i) {
            int x, y;
            fin>>x>>y;
            graph[x].push_back(y);
            graph[y].push_back(x);
        }

        vector<bool> visited(N+1);

        fout<<DFS(nodeStart, values[nodeStart], values[nodeStart], graph, visited, values)<<endl;
        --tests;
    }
    return 0;
}

// Complexity: O(N + M)