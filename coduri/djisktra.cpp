#include <fstream>
#include <vector>
#include <utility>
#include <set>
#include <queue>
#include <iostream>
#include <vector>

using namespace std;

struct Vertex {
    int node;
    int duration;
};


struct DistanceNode {
    int distance;
    int parent;
};

struct SearchNode {
    int currentNode;
    int distance;
};

int getDistance(vector<vector<Vertex>> graph, int startNode, int endNode) {
    vector<DistanceNode> distances(graph.size(), {INT8_MAX, -1});
    distances[startNode] = {0, 0};
    auto compare = [](SearchNode const &a, SearchNode const &b) { return a.distance > b.distance; };
    std::priority_queue<SearchNode, vector<SearchNode>, decltype(compare)> searchQueue(compare);
    searchQueue.push({1, 0});
    while (!searchQueue.empty()) {
        auto[currentNode, distance] = searchQueue.top();
        searchQueue.pop();
        if (currentNode == endNode) {
            return distance;
        }
        for (auto[rightEdge, cost]: graph[currentNode]) {
            if (distance + cost < distances[rightEdge].distance) {
                distances[rightEdge] = {distance + cost, currentNode};
                searchQueue.push({rightEdge, distance + cost});
            }
        }
    }
    return -1;
}

int edges, vertexes;
bool isOriented = false;

int main() {

    cin >> vertexes >> edges;
    vector<vector<Vertex>> graph(vertexes + 1);
    for (int i = 0; i < edges; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        graph[a].push_back({b, c});
        if (!isOriented) {
            graph[b].push_back({a, c});
        }

    }
    int start, end;
    cin >> start >> end;
    cout << getDistance(graph, start, end);
    return 0;
}