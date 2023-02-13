#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, m;
  cin >> n >> m;

  vector<vector<pair<int, int>>> e(2 * n);
  while (m--) {
    int from, to, w;
    cin >> from >> to >> w;
    from--, to--;
    e[from << 1].push_back({to << 1, w});
    e[to << 1].push_back({from << 1 | 1, w});
    e[to << 1 | 1].push_back({from << 1 | 1, w});
  }

  priority_queue<pair<ll, int>> pq;
  vector<ll> dist(2 * n, LLONG_MAX);
  dist[0] = dist[1] = 0;
  pq.push({0, 0});
  pq.push({0, 1});

  while (!pq.empty()) {
    auto [d, at] = pq.top(); pq.pop();
    d = -d;
    if (d > dist[at]) continue;

    for (auto [to, w] : e[at]) {
      if (dist[to] > d + w) {
        dist[to] = d + w;
        pq.push({-dist[to], to});
      }
    }
  }

  for (int i = 1; i < n; i++) {
    if (i > 1) cout << " ";
    ll ans = min(dist[i << 1], dist[i << 1 | 1]);
    cout << (ans < LLONG_MAX ? ans : -1);
  }
  cout << "\n";

  return 0;
}