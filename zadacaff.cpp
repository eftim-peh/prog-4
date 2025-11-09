#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> adj;
vector<int> parent;
int n, start, finish;

int dfs(int a) {
    if (a == finish) return INT_MAX;
    for (int i = 0; i < n; i++) {
        if (adj[a][i] > 0 && parent[i] == -1) {
            parent[i] = a;
            int t = dfs(i);
            if (t > 0) return min(t, adj[a][i]);
        }
    }
    return 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int m, a, b, c;
    cin >> n >> m;
    cin >> start >> finish;

    adj.assign(n, vector<int>(n, 0));
    parent.assign(n, -1);

    vector<pair<pair<int, int>, int>> edges;
    for (int i = 0; i < m; i++) {
        cin >> a >> b >> c;
        edges.push_back({{a, b}, c});
        adj[a][b] = c;
    }

    int best_flow = INT_MAX;
    int res = -1;

    for (int j = 0; j < m; j++) {
        for (int i = 0; i < n; i++)
            fill(adj[i].begin(), adj[i].end(), 0);
        for (int i = 0; i < m; i++) {
            adj[edges[i].first.first][edges[i].first.second] = edges[i].second;
        }
        adj[edges[j].first.first][edges[j].first.second] = 0;
        int max_flow = 0;
        while (true) {
            fill(parent.begin(), parent.end(), -1);
            parent[start] = -2;
            int min_flow = dfs(start);
            if (min_flow == 0) break;

            int k = finish;
            while (k != start) {
                int p = parent[k];
                adj[p][k] -= min_flow;
                adj[k][p] += min_flow;
                k = p;
            }
            max_flow += min_flow;
        }

        if (max_flow < best_flow) {
            best_flow = max_flow;
            res = j;
        }
    }

    cout << best_flow << " " << res << "\n";
}