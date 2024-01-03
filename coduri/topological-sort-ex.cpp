#include <iostream>
#include <fstream>
#include <vector>
#include <stack>

using namespace std;

ifstream fin("date.in");
ofstream fout("date.out");

void DFS(int node, vector<vector<int>> graph, vector<bool>& visited, stack<int>& stack) {
    visited[node] = true;

    for(auto vecin: graph[node]) {
        if(!visited[vecin]) {
            DFS(vecin, graph, visited, stack);
        }
    }
    stack.push(node);
}

int main() {
    vector<bool> visited;
    vector<vector<int>> graph;
    stack<int> stack;
    int numCourses, x, y;

    fin>>numCourses;

    visited.resize(numCourses, false);
    graph.resize(numCourses);

    while(fin>>x>>y) {
        graph[y].push_back(x);
    }

    for(int i = 0; i < numCourses; ++i) {
        if(!visited[i]) {
            DFS(i, graph, visited, stack);
        }
    }

    while(!stack.empty()) {
        fout<<stack.top()<<" ";
        stack.pop();
    }
    fout<<endl;

    return 0;
}
// Complexitate: O(n+m)