#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, m, k;
  cin >> n >> m >> k;

  vector<int> c(n);
  for (int &i : c) cin >> i;

  int nn = 2 * n;
  vector<vector<int>> dist(nn, vector<int>(nn, nn));
  for (int i = 0; i < n; i++) {
    int u = i << 1, v = i << 1 | 1;
    dist[u][u] = 0;
    dist[v][v] = 0;
  }

  while (m--) {
    int s, t;
    cin >> s >> t;
    s--, t--;

    int xr = c[s] != c[t];
    s <<= 1;
    t <<= 1;

    dist[s][t ^ xr] = 1;
    dist[t][s ^ xr] = 1;
    dist[(s ^ 1)][(t ^ 1) ^ xr] = 1;
    dist[(t ^ 1)][(s ^ 1) ^ xr] = 1;
  }

  for (int k = 0; k < nn; k++) {
    for (int i = 0; i < nn; i++) {
      for (int j = 0; j < nn; j++) {
        dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
      }
    }
  }

  int ans = 0;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      int d0 = dist[i << 1][j << 1], d1 = dist[i << 1][j << 1 | 1];
      if (d0 > d1) swap(d0, d1);

      int have = k;
      int take = min(d1 - d0, have);
      have -= take;
      d0 += take;

      if (d1 < nn) d0 += have / 2;
      else d0 += have;

      ans = max(ans, d0);
    }
  }

  cout << ans << "\n";

  return 0;
}
