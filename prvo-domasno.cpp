#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll INF = (1LL<<60);

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

   

    int n, m;
    if (!(cin >> n >> m)) return 0;

    vector<vector<pair<int,ll>>> adj(n+1); 
    for (int i = 0; i < m; ++i) {
        int u, v;
        ll w;
        cin >> u >> v >> w;
        
        adj[u].push_back({v,w});
    }

    int start, target;
    cin >> start >> target;

    
    vector<ll> dist(n+1, INF);
    vector<int> parent(n+1, -1);
    dist[start] = 0;

    
    priority_queue<pair<ll,int>, vector<pair<ll,int>>, greater<>> pq;
    pq.push({0, start});

    while (!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();
        if (d != dist[u]) continue; 
        if (u == target) break;     

        for (auto &edge : adj[u]) {
            int v = edge.first;
            ll w = edge.second;
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                parent[v] = u;
                pq.push({dist[v], v});
            }
        }
    }

    if (dist[target] == INF) {
        cout << "No path from " << start << " to " << target << "\n";
        return 0;
    }

    
    vector<int> path;
    for (int v = target; v != -1; v = parent[v]) path.push_back(v);
    reverse(path.begin(), path.end());

    cout << "Distance: " << dist[target] << "\n";
    cout << "Path (" << path.size() << " nodes):";
    for (int v : path) cout << ' ' << v;
    cout << '\n';

    return 0;
}
