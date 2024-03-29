#include <vector>
#include<iostream>
#include <utility>
#include <algorithm>
#include <vector>

using namespace std;

struct ConnectedComponentVertex {
    int parentIndex;
    int componentDepth;
};

// First is the vertex, second is the depth
pair<int, int> getRootVertex(vector<ConnectedComponentVertex> const &componentVertex, int vertex) {
    int current = vertex;
    int parent = componentVertex[vertex].parentIndex;
    while (parent != -1) {
        current = parent;
        parent = componentVertex[current].parentIndex;
    }

    return {current, componentVertex[current].componentDepth};

}

struct Edge {
    int leftVertex;
    int rightVertex;
    int cost;
};


// Return the parentIndex array and the connected components
// A -1 will mean a node is not in the tree, a 0 means that is the root, anything else is the parentIndex
pair<vector<Edge>, vector<ConnectedComponentVertex>> kruskal(vector<Edge> const &edges, int vertexCount,
                                                                  vector<ConnectedComponentVertex> const &initialComponentVertex = {},vector<Edge> const& initialSelectedEdges = {}) {
    // A vector that tells us another vertex from the same connected component with a given vertex
    vector<ConnectedComponentVertex> componentVertex = initialComponentVertex.empty()
                                                       ? vector<ConnectedComponentVertex>(vertexCount + 1, {-1, 1})
                                                       : vector<ConnectedComponentVertex>(
                    initialComponentVertex);
    vector<Edge> selectedEdges = initialSelectedEdges.empty() ? vector<Edge>():vector<Edge>(initialSelectedEdges);
    if (vertexCount == 0) {
        return {selectedEdges, componentVertex};
    }
    for (auto const &edge: edges) {
        if (selectedEdges.size() == vertexCount - 1) {
            return {selectedEdges, componentVertex};
        }
        auto[leftVertexConnectedRoot, leftDepth] = getRootVertex(componentVertex, edge.leftVertex);
        auto[rightVertexConnectedRoot, rightDepth] = getRootVertex(componentVertex, edge.rightVertex);
        if (leftVertexConnectedRoot != rightVertexConnectedRoot) {


            //Add this edge to the tree
            selectedEdges.push_back(edge);

            //Merge the connected components
            if (leftDepth < rightDepth) {
                componentVertex[leftVertexConnectedRoot] = {rightVertexConnectedRoot, rightDepth};
            } else if (leftDepth > rightDepth) {
                componentVertex[rightVertexConnectedRoot] = {leftVertexConnectedRoot, leftDepth};
            } else {
                // The depth of the connected component increased
                componentVertex[rightVertexConnectedRoot] = {leftVertexConnectedRoot, leftDepth + 1};
                componentVertex[leftVertexConnectedRoot] = {-1, leftDepth + 1};
            }
        }

    }
    return {selectedEdges, componentVertex};
}

int main() {
    vector<Edge> graph;
    int vertex, edgeCount;
    cin >> vertex >> edgeCount;
    for (int i = 0; i < edgeCount; i++) {
        Edge edge;
        cin >> edge.leftVertex >> edge.rightVertex >> edge.cost;
        graph.push_back(edge);
    }

    int k;
    cin >> k;
    vector<Edge> setEdges;
    for (int i = 0; i < k; i++) {
        Edge edge;
        cin >> edge.leftVertex >> edge.rightVertex >> edge.cost;
        setEdges.push_back(edge);
    }

    auto[initialTree, initialComponent] = kruskal(setEdges, vertex);
    std::sort(graph.begin(), graph.end(), [](Edge a, Edge b) {
        return a.cost < b.cost;
    });
    auto[apm, _] = kruskal(graph, vertex, initialComponent,initialTree);
    for (auto const &[left, right, _]: apm) {
        cout << left << ' ' << right << "\n";
    }
    return 0;
}