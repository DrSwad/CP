#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, m;
  cin >> n >> m;

  vector<pair<int, int>> edges;
  vector<vector<int>> edges_from_node(n); // Stores the edge ids of edges coming out of a particular node

  for (int i = 0; i < m; i++) {
    int from, to;
    cin >> from >> to;
    from--, to--;
    edges.emplace_back(from, to);
    edges_from_node[from].push_back(edges.size() - 1);
  }

  int best_cycle_node_sum = INT_MAX; // Sum of node ides
  vector<int> best_cycle;

  for (int banned_edge = 0; banned_edge < m; banned_edge++) {
    auto [cycle_end, cycle_start] = edges[banned_edge];

    vector<int> dist(n, INT_MAX), from(n, -1);
    priority_queue<pair<int, int>> pq;
    dist[cycle_start] = cycle_start + 1;
    pq.emplace(-dist[cycle_start], cycle_start);

    while (!pq.empty()) {
      auto [d, at] = pq.top();
      pq.pop();
      d = -d;
      if (d > dist[at]) continue;

      for (int edge_id : edges_from_node[at]) {
        if (edge_id != banned_edge) {
          int to = edges[edge_id].second;
          if (dist[to] > dist[at] + (to + 1)) {
            from[to] = at;
            dist[to] = dist[at] + (to + 1);
            pq.emplace(-dist[to], to);
          }
        }
      }
    }

    if (dist[cycle_end] < best_cycle_node_sum) {
      best_cycle_node_sum = dist[cycle_end];

      best_cycle.clear();
      int at = cycle_end;
      while (at != -1) {
        best_cycle.push_back(at);
        at = from[at];
      }
    }
  }

  sort(best_cycle.begin(), best_cycle.end());
  for (int i = 0; i < best_cycle.size(); i++) {
    if (i) cout << " ";
    cout << best_cycle[i] + 1;
  }
  cout << "\n";

  return 0;
}