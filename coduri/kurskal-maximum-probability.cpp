class Solution {
public:
    double maxProbability(int n, vector<vector<int>>& edges, vector<double>& succProb, int start, int end) {
        vector<vector<pair<int, double>>> graph;
        graph.resize(n);

        vector<bool> visited;
        visited.resize(n, 0);

        priority_queue<pair<int, double>> maxDistances;
        maxDistances.emplace(start,1.0);

        // ne construim listele de adiacenta
        for(int i = 0; i < edges.size(); ++i) {
            graph[edges[i][0]].push_back(edges[i][1], succProb[i]);
            graph[edges[i][1]].push_back(edges[i][0], succProb[i]);
        }

        // iteram pana cand vizitam toate nodurile
        while(!maxDistances.empty()) {
            pair<int, double> x = maxDistances.top();
            maxDistances.pop();

            // daca ajungem la final, afisam probabilitatea
            if(x.first == end) {
                return x.second;
            }
            // daca nodul a fost deja vizitat, mergem mai departe
            if(visited[x.first]) {
                continue;
            }
            visited[x.first] = true;

            // parcurgem vecinii nodului
            for(auto it: graph[x.first]) {
                if(!visited[it.first]) {
                    maxDistances.emplace(it.first, x.second * it.second);
                }
            }
        }
        return 0;
    }
};

// Complexitate: O(m log n)