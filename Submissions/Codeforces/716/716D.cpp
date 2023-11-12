#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const ll INF = 1e18;
const int N = 1e3;
const int M = 1e4;

int nodes, edges;
ll need_dist;
int source, target;
vector<tuple<int, int, ll>> edge;
vector<int> adj[N];
ll min_cost[N][N];
int from_edge[N][N];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> nodes >> edges >> need_dist >> source >> target;
  int max_empty_edges = 0;
  for (int i = 0; i < edges; i++) {
    int u, v, w;
    cin >> u >> v >> w;
    max_empty_edges += w == 0;
    int edge_id = edge.size();
    edge.emplace_back(u, v, w);
    adj[u].push_back(edge_id);
    adj[v].push_back(edge_id);
  }
  max_empty_edges = min(max_empty_edges, nodes - 1);

  for (int empty_edges = 0; empty_edges <= max_empty_edges; empty_edges++) {
    for (int at_node = 0; at_node < nodes; at_node++) {
      min_cost[at_node][empty_edges] = INF;
      from_edge[at_node][empty_edges] = -1;
    }
  }

  min_cost[source][0] = 0;

  for (int empty_edges = 0; empty_edges <= max_empty_edges; empty_edges++) {
    for (int at_node = 0; at_node < nodes; at_node++) {
      if (empty_edges != 0) {
        for (int edge_id : adj[at_node]) {
          auto [u, v, w] = edge[edge_id];
          int from_node = u + v - at_node;
          if (w == 0 and
              min_cost[at_node][empty_edges] > min_cost[from_node][empty_edges - 1]
          ) {
            min_cost[at_node][empty_edges] = min_cost[from_node][empty_edges - 1];
            from_edge[at_node][empty_edges] = edge_id;
          }
        }
      }
    }

    priority_queue<pair<ll, int>> pq;
    for (int i = 0; i < nodes; i++) {
      pq.emplace(-min_cost[i][empty_edges], i);
    }

    while (!pq.empty()) {
      auto [cost, at_node] = pq.top();
      pq.pop();
      cost = -cost;
      if (cost > min_cost[at_node][empty_edges]) continue;

      for (int edge_id : adj[at_node]) {
        auto [u, v, w] = edge[edge_id];
        int to_node = u + v - at_node;
        if (w > 0 and
            min_cost[to_node][empty_edges] > min_cost[at_node][empty_edges] + w
        ) {
          min_cost[to_node][empty_edges] = min_cost[at_node][empty_edges] + w;
          from_edge[to_node][empty_edges] = edge_id;
          pq.emplace(-min_cost[to_node][empty_edges], to_node);
        }
      }
    }
  }

  int empty_edges;
  for (empty_edges = 0; empty_edges <= max_empty_edges; empty_edges++) {
    if (min_cost[target][empty_edges] + empty_edges <= need_dist) break;
  }

  if (empty_edges > max_empty_edges) cout << "NO\n";
  else if (empty_edges == 0 and min_cost[target][0] < need_dist) cout << "NO\n";
  else {
    vector<int> edge_ids;
    int at_node = target;
    int remaining_empty_edges = empty_edges;

    while (at_node != source) {
      assert(empty_edges >= 0);
      int edge_id = from_edge[at_node][remaining_empty_edges];

      assert(edge_id != -1);
      auto [u, v, w] = edge[edge_id];

      if (w == 0) {
        remaining_empty_edges--;
        edge_ids.push_back(edge_id);
      }

      at_node = u + v - at_node;
    }

    ll remaining_dist = need_dist - min_cost[target][empty_edges];
    for (int edge_id : edge_ids) {
      get<2>(edge[edge_id]) = 1;
      remaining_dist--;
    }
    if (!edge_ids.empty()) {
      get<2>(edge[edge_ids.back()]) += remaining_dist;
    }

    for (int edge_id = 0; edge_id < edges; edge_id++) {
      auto & [u, v, w] = edge[edge_id];
      if (w == 0) w = INF;
    }

    cout << "YES\n";
    for (auto [u, v, w] : edge) cout << u << " " << v << " " << w << "\n";
  }

  return 0;
}