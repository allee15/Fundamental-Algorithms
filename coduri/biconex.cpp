#include <bits/stdc++.h>
#include <vector>
#include <set>

using namespace std;

struct VertexInfo {
    int depth;
    int min_depth;
};

vector<vector<int>>graph;
bool isOriented = false;
vector<VertexInfo> vertexInfo(graph.size());
vector<bool> visited(graph.size());
set<int> criticalNodes;
vector<std::pair<int, int>> criticalEdges;

void dfs(int parent, int currentNode, int depth) {
    visited[currentNode] = true;

    int dfsChildren = 0;

    int minDepth = depth;
    //Set this in the nodeInfo so that nodes further down can see this info
    vertexInfo[currentNode] = {depth,minDepth};
    for (auto const &rightEdge: graph[currentNode]) {
        if (!visited[rightEdge]) {
            dfsChildren++;
            dfs(rightEdge, currentNode, depth + 1);
            if (minDepth > vertexInfo[rightEdge].min_depth) {
                minDepth = vertexInfo[rightEdge].min_depth;
            }
            if (depth < vertexInfo[rightEdge].min_depth) {
                criticalEdges.push_back({currentNode, rightEdge});
            }
            //Root treated separately
            if (depth <= vertexInfo[rightEdge].min_depth && parent != 0) {
                criticalNodes.insert(currentNode);
            }
        } else if (rightEdge != parent && vertexInfo[rightEdge].depth < minDepth) {
            minDepth = vertexInfo[rightEdge].depth;
        }
    }
    vertexInfo[currentNode] = {depth, minDepth};

    if(parent == 0 && dfsChildren > 1){
        criticalNodes.insert(currentNode);

    }
}

int main() {
    int edges, vertexes;
    cin >> vertexes >> edges;
    graph.resize(vertexes + 1);
    for (int i = 0; i < edges; i++) {
        int a, b;
        cin >> a >> b;
        graph[a].push_back(b);
        if (!isOriented) {
            graph[b].push_back(a);
        }

    }

    dfs(0, 1, 1);
    cout << "Noduri critice:\n";
    for (auto const &node: criticalNodes) {
        cout << node << " ";
    }
    cout << "\n Muchii critice:\n";
    for (auto const&[left, right]: criticalEdges) {
        cout << left << " " << right << "\n";
    }
    return 0;
}