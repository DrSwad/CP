#include <bits/stdc++.h>
using namespace std;

class SCC {
public:
  vector<int> comp;
  int ncomps;
  vector<vector<int>> comps, G;

private:
  vector<int> disc, st;
  int Time;

  int dfs(int at, const vector<vector<int>> &g) {
    int low = disc[at] = ++Time;
    st.push_back(at);
    for (auto e : g[at]) {
      if (comp[e] < 0) {
        low = min(low, disc[e] ? disc[e] : dfs(e, g));
      }
    }

    if (low == disc[at]) {
      comps.push_back({});
      int v;
      do {
        v = st.back();
        st.pop_back();
        comp[v] = ncomps;
        comps.back().push_back(v);
      } while (v != at);
      ncomps++;
    }
    return disc[at] = low;
  }

public:
  SCC(const vector<vector<int>> &g) {
    int n = (int)g.size();
    disc.assign(n, 0);
    comp.assign(n, -1);
    Time = ncomps = 0;
    for (int i = 0; i < n; i++) {
      if (comp[i] < 0) dfs(i, g);
    }

    vector<bool> vis(ncomps, false);
    for (int i = 0; i < ncomps; i++) {
      G.push_back({});
      for (int u : comps[i]) {
        for (int v : g[u]) {
          if (!vis[comp[v]]) G.back().push_back(comp[v]);
          vis[comp[v]] = true;
        }
      }
      for (int u : comps[i]) {
        for (int v : g[u]) vis[comp[v]] = false;
      }
    }
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, m;
  cin >> n >> m;

  vector<vector<int>> e(n);
  vector<bool> useful(n, false);
  while (m--) {
    int u, v;
    cin >> u >> v;
    u--, v--;
    e[u].push_back(v);
    useful[u] = useful[v] = true;
  }

  SCC scc(e);
  int ans = 2 * n - scc.ncomps - count(useful.begin(), useful.end(), false);
  cout << ans << "\n";

  return 0;
}