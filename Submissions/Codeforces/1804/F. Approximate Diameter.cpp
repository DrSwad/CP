#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, m, q;
  cin >> n >> m >> q;

  vector<vector<pair<int, int>>> adj(n);
  while (m--) {
    int u, v;
    cin >> u >> v;
    u--, v--;

    adj[u].emplace_back(v, 0);
    adj[v].emplace_back(u, 0);
  }

  for (int query = 1; query <= q; query++) {
    int u, v;
    cin >> u >> v;
    u--, v--;
    adj[u].emplace_back(v, query);
    adj[v].emplace_back(u, query);
  }

  auto max_dist = [&](int query) {
    vector<int> dist(n, n);
    queue<int> q;
    dist[0] = 0;
    q.push(0);
    int mx_dist = 0;

    while (!q.empty()) {
      int at = q.front();
      q.pop();
      mx_dist = max(mx_dist, dist[at]);

      for (auto [to, _query] : adj[at]) {
        if (_query <= query and dist[to] > dist[at] + 1) {
          dist[to] = dist[at] + 1;
          q.push(to);
        }
      }
    }

    return mx_dist;
  };

  vector<int> ans(q + 1);

  for (int ql = 0; ql <= q; ) {
    int d = max_dist(ql);

    int _ql = ql, qr = q + 1;
    while (qr > _ql + 1){
      int mid = (_ql + qr) / 2;
      int _d = max_dist(mid);
      if (2 * _d >= d) _ql = mid;
      else qr = mid;
    }

    for (int query = ql; query < qr; query++) {
      ans[query] = d;
    }

    ql = qr;
  }

  for (int query = 0; query <= q; query++) {
    if (query) cout << " ";
    cout << ans[query];
  }
  cout << "\n";

  return 0;
}
