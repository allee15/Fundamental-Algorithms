#include <vector>
#include <iostream>

using namespace std;

void printCycle(vector<int> const &parrentTree, int current, int endNode) {
    if (current == endNode) {
        cout << current << " ";
    } else {
        printCycle(parrentTree, parrentTree[current], endNode);
        cout << current << " ";
    }
}

bool findCycle(vector<vector<int>> const &graph, int currentElement, vector<int> &checked) {
    for (auto const &vertex: graph[currentElement]) {
        //Check so that we don't go back into the parentIndex
        if (vertex != checked[currentElement]) {
            if (!checked[vertex]) {
                checked[vertex] = currentElement;
                auto res = findCycle(graph, vertex, checked);
                if (res) {
                    // Don't iterate further
                    return true;
                }
            } else {
                printCycle(checked, currentElement, vertex);
                cout << vertex;
                return true;
            }
        }
    }
    return false;
}

bool isOriented = false;

int main() {
    int edges, vertexes;
    cin >> vertexes >> edges;
    vector<vector<int>> graph(vertexes + 1);
    for (int i = 0; i < edges; i++) {
        int a, b;
        cin >> a >> b;
        graph[a].push_back(b);
        if (!isOriented) {
            graph[b].push_back(a);
        }
    }
    vector<int> checked(graph.size());
    findCycle(graph, 1, checked);
    return 0;
}