class Solution {
public:
    vector<vector<int>> validArrangement(vector<vector<int>>& pairs) {
        unordered_map<int, vector<int>> graph;
        unordered_map<int, int> degree;

        int start = 0;
        for (auto& edge : pairs) {
            graph[edge[0]].push_back(edge[1]);
            ++degree[edge[0]];
            --degree[edge[1]];
            start = edge[0];
        }

        for (auto& [k, v] : degree)
            if (v == 1) start = k;

        vector<int> path;
        stack<int> stk; stk.push(start);
        while (stk.size()) {
            while (graph[stk.top()].size()) {
                int x = stk.top();
                stk.push(graph[x].back());
                graph[x].pop_back();
            }
            path.push_back(stk.top()); stk.pop();
        }
        reverse(path.begin(), path.end());
        vector<vector<int>> ans;
        for (int i = 0; i < path.size()-1; ++i) ans.push_back({path[i], path[i+1]});
        return ans;
    }
};

// Complexitate: O(M+N)