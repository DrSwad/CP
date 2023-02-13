#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

void test_case() {
  int n, m, s, t;
  cin >> n >> m >> s >> t;
  s--, t--;

  vector<vector<vector<pair<int, int>>>> e(n, vector<vector<pair<int, int>>>(26));

  vector<vector<ll>> dist(n, vector<ll>(n, -1));
  vector<vector<bool>> vis(n, vector<bool>(n, false));
  priority_queue<tuple<ll, int, int>> pq;

  for (int i = 0; i < n; i++) {
    dist[i][i] = 0;
    pq.push({0, i, i});
  }

  while (m--) {
    int u, v, w;
    char c;
    cin >> u >> v >> w >> c;
    u--, v--;
    e[u][c - 'a'].push_back({v, w});
    e[v][c - 'a'].push_back({u, w});

    if (u > v) swap(u, v);
    if (dist[u][v] == -1 or dist[u][v] > w) {
      dist[u][v] = w;
      pq.push({-w, u, v});
    }
  }

  while (!pq.empty()) {
    auto top = pq.top();
    ll W = get<0>(top);
    int u = get<1>(top);
    int v = get<2>(top);
    pq.pop();
    if (vis[u][v]) continue;
    vis[u][v] = true;
    W = -W;

    for (int c = 0; c < 26; c++) {
      for (auto e1 : e[u][c]) {
        for (auto e2 : e[v][c]) {
          int u1 = e1.first;
          int w1 = e1.second;
          int u2 = e2.first;
          int w2 = e2.second;
          ll W2 = W + w1 + w2;
          if (u1 > u2) swap(u1, u2);
          if (dist[u1][u2] == -1 or dist[u1][u2] > W2) {
            dist[u1][u2] = W2;
            pq.push({-W2, u1, u2});
          }
        }
      }
    }
  }

  if (s > t) swap(s, t);
  cout << dist[s][t] << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    test_case();
  }

  return 0;
}