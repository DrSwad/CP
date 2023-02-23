#include <bits/stdc++.h>
using namespace std;

int n;
vector<vector<int>> e;
vector<int> centroid;

int dfs1(int at, int from) {
  bool flag = true;
  int subTot = 1;

  for (int to : e[at]) {
    if (to != from) {
      int sub = dfs1(to, at);
      if (sub > n / 2) {
        flag = false;
      }
      subTot += sub;
    }
  }

  if (n - subTot > n / 2) {
    flag = false;
  }

  if (flag) {
    centroid.push_back(at);
  }

  return subTot;
}

void dfs2(int at, int from, vector<int> &dist) {
  dist[at] = dist[from] + 1;
  for (int to : e[at]) {
    if (to != from) {
      dfs2(to, at, dist);
    }
  }
}

int main() {
  int t;
  cin >> t;

  while (t--) {
    scanf("%d", &n);

    e.assign(n, vector<int>());
    centroid.clear();

    for (int i = 1; i < n; i++) {
      int v;
      scanf("%d", &v);
      v--;

      e[i].push_back(v);
      e[v].push_back(i);
    }

    dfs1(0, -1);

    if (centroid.size() == 1) {
      int c = centroid[0];

      vector<int> dist(n, -1);
      dfs2(c, c, dist);
      vector<int> distFreq(n, 0);
      for (int i = 0; i < n; i++) {
        distFreq[dist[i]]++;
      }

      long long ans = n * 1ll * (n - 1) / 2;
      for (int i = 0; i < n; i++) {
        ans += distFreq[i] * 1ll * (distFreq[i] - 1) / 2;
      }

      printf("%lld\n", ans);
    } else {
      vector<vector<int>> dist(2, vector<int>(n, -1));
      vector<vector<int>> distFreq(2, vector<int>(n, 0));

      for (int it = 0; it < 2; it++) {
        dfs2(centroid[it], centroid[it ^ 1], dist[it]);
        for (int i = 0; i < n; i++) {
          if (~dist[it][i]) {
            distFreq[it][dist[it][i]]++;
          }
        }
      }

      long long ans = n * 1ll * (n - 1) / 2;
      for (int i = 0; i < n; i++) {
        ans += distFreq[0][i] * 1ll * (distFreq[0][i] - 1) / 2;
        ans += distFreq[1][i] * 1ll * (distFreq[1][i] - 1) / 2;
        ans -= distFreq[0][i] * 1ll * distFreq[1][i];
      }

      printf("%lld\n", ans);
    }
  }

  return 0;
}