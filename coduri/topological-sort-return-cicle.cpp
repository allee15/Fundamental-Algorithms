#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <unordered_map>

using namespace std;

ifstream fin("date.in");
ofstream fout("date.out");

vector<int> cycle;
void DFS(int first, int node, vector<vector<int>> graph, vector<bool>& visited, stack<int>& stack) {
    visited[node] = true;
    stack.push(node);
    for(auto vecin: graph[node]) {
        if(!visited[vecin]) {
            DFS(first, vecin, graph, visited, stack);
        } else if(visited[vecin] && vecin == first && cycle.empty()) {
            // Ne cream noul vector ce va tine minte primul ciclu format
            stack.push(first);
            while(!stack.empty()) {
                cycle.push_back(stack.top());
                stack.pop();
            }
        }
    }
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
            DFS(i, i, graph, visited, stack);
        }
    }

    // daca vectorul nu e gol, afisam elementele lui, altfel, nu afisam nimic
    if(!cycle.empty()) {
        for(auto el: cycle) {
            fout<<el<<" ";
        }
    }
    fout<<endl;
    return 0;
}
// Complexitate: O(n+m)