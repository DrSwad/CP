#include <bits/stdc++.h>
using namespace std;

vector<int> val, comp, z;
int Time, ncomps;
int dfs(int j, vector<vector<int>> &g) {
  int low = val[j] = ++Time, x;
  z.push_back(j);
  for (auto e : g[j]) {
    if (comp[e] < 0) {
      low = min(low, val[e] ?: dfs(e, g));
    }
  }

  if (low == val[j]) {
    do {
      x = z.back();
      z.pop_back();
      comp[x] = ncomps;
    } while (x != j);
    ncomps++;
  }
  return val[j] = low;
}
void scc(vector<vector<int>> &g) {
  int n = (int)g.size();
  val.assign(n, 0);
  comp.assign(n, -1);
  Time = ncomps = 0;
  for (int i = 0; i < n; i++) {
    if (comp[i] < 0) dfs(i, g);
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, m;
  cin >> n >> m;

  vector<tuple<int, int, int, int>> conditions(m);

  for (int i = 0; i < m; i++) {
    auto & [a, b, c, d] = conditions[i];
    cin >> a >> b >> c >> d;
    a--, b--, c--, d--;
  }

  vector<vector<int>> adj(n);
  vector<vector<bool>> adj_vis(n, vector<bool>(n, false));

  while (true) {
    for (auto [a, b, c, d] : conditions) {
      if (a <= b and c <= d) {
        if (!adj_vis[a][c]) {
          adj[a].push_back(c);
          adj_vis[a][c] = true;
        }
      }
    }

    scc(adj);

    bool rerun = false;
    for (auto & [a, b, c, d] : conditions) {
      if (a <= b and c <= d) {
        if (comp[a] == comp[c]) {
          rerun = true;
          a++, c++;
          if (c > d) {
            cout << "No\n";
            return 0;
          }
        }
      }
    }

    if (!rerun) break;
  }

  cout << "Yes\n";

  return 0;
}