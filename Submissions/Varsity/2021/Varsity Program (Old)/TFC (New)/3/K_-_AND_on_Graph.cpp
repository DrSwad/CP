#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;

int n, m;
vector<tuple<int, int, int, int>> e;
vector<vector<int>> adj;
vector<bool> is_edge_active;
int k;
int s, t;

int dijkstra() {
  vector<long long> dist(n + 1, -1);
  vector<bool> visited(n + 1, false);
  dist[s] = 0;
  priority_queue<pair<long long, int>> pq;
  pq.push({0, s});

  while (!pq.empty()) {
    auto top = pq.top();
    long long curr_dist = top.first;
    int at = top.second;
    pq.pop();
    curr_dist = -curr_dist;
    if (visited[at]) continue;
    visited[at] = true;

    for (int ei : adj[at]) {
      if (!is_edge_active[ei]) continue;
      int a = get<0>(e[ei]), b = get<1>(e[ei]), c = get<2>(e[ei]), v = get<3>(e[ei]);
      int to = a ^ b ^ at;
      if (dist[to] == -1 or dist[to] > curr_dist + c) {
        dist[to] = curr_dist + c;
        pq.push({-dist[to], to});
      }
    }
  }

  return dist[t];
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> n >> m;

  e.resize(m + 1);
  adj.resize(n + 1);
  for (int ei = 1; ei <= m; ei++) {
    int &a = get<0>(e[ei]), &b = get<1>(e[ei]), &c = get<2>(e[ei]), &v = get<3>(e[ei]);
    cin >> a >> b >> c >> v;
    adj[a].push_back(ei);
    adj[b].push_back(ei);
  }

  cin >> s >> t >> k;

  long long ans = -1;
  int num = 0;
  is_edge_active.resize(m + 1);

  for (int b = 29; b >= 0; b--) {
    fill(is_edge_active.begin(), is_edge_active.end(), false);

    int mask = k >> (b + 1);
    for (int ei = 1; ei <= m; ei++) {
      int a = get<0>(e[ei]), bb = get<1>(e[ei]), c = get<2>(e[ei]), v = get<3>(e[ei]);
      if ((v >> b & 1) and ((v >> (b + 1)) & mask) == mask) {
        is_edge_active[ei] = true;
      }
    }

    long long curr = dijkstra();
    if (k >> b & 1) {
      num |= 1 << b;
      if (num == k) {
        if (curr != -1) ans = ans == -1 ? curr : min(ans, curr);
      }
    }
    else {
      if (curr != -1) ans = ans == -1 ? curr : min(ans, curr);
    }
  }

  cout << ans << "\n";

  return 0;
}