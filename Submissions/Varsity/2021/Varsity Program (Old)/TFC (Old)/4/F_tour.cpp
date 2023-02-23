#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

void test_case() {
  int n, m, s, t;
  cin >> n >> m >> s >> t;
  s--, t--;

  vector<vector<vector<pair<int, int>>>> e(n, vector<vector<pair<int, int>>>(26));
  vector<tuple<int, int, int>> edges;

  while (m--) {
    int u, v, w, c;
    char ch;
    cin >> u >> v >> w >> ch;
    u--, v--;
    c = ch - 'a';

    e[u][c].push_back({v, w});
    e[v][c].push_back({u, w});
    edges.push_back({u, v, w});
  }

  vector<vector<ll>> dist(n, vector<ll>(n, -1));
  priority_queue<pair<ll, pair<int, int>>> pq;
  pq.push({0, {s, t}});

  while (!pq.empty()) {
    ll d;
    int u, v;
    d = -pq.top().first;
    u = pq.top().second.first;
    v = pq.top().second.second;
    pq.pop();
    if (dist[u][v] != -1) continue;
    dist[u][v] = d;

    for (int c = 0; c < 26; c++) {
      for (int i = 0; i < e[u][c].size(); i++) {
        int nu = e[u][c][i].first;
        int wu = e[u][c][i].second;
        for (int j = 0; j < e[v][c].size(); j++) {
          int nv = e[v][c][j].first;
          int wv = e[v][c][j].second;
          pq.push({-(d + wu + wv), {nu, nv}});
        }
      }
    }
  }

  ll ans = -1;
  for (int i = 0; i < n; i++) {
    ll cur = dist[i][i];
    if (cur != -1) ans = ans == -1 ? cur : min(cur, ans);
  }
  for (int i = 0; i < edges.size(); i++) {
    int u, v, w;
    u = get<0>(edges[i]);
    v = get<1>(edges[i]);
    w = get<2>(edges[i]);
    for (int it = 0; it < 2; it++) {
      ll cur = dist[u][v];
      if (cur != -1) {
        cur += w;
        ans = ans == -1 ? cur : min(cur, ans);
      }
      swap(u, v);
    }
  }

  cout << ans << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t = 1;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    // cout << "Case " << cs << ": ";
    test_case();
  }

  return 0;
}