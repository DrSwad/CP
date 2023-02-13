#include <bits/stdc++.h>
using namespace std;

class SCC {
private:
  int Time;
  vector<int> disc, st;

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
  int ncomps;
  vector<int> comp;
  vector<vector<int>> comps, G;

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

void test_case() {
  int n, m;
  cin >> n >> m;

  vector<vector<int>> g(n);
  while (m--) {
    int from, to;
    cin >> from >> to;
    g[from - 1].push_back(to - 1);
  }

  SCC scc(g);
  auto comp = scc.comp;
  auto comps = scc.comps;
  vector<int> cans(scc.ncomps, 0);

  auto f = [&](int ci) {
    if (comps[ci].size() > 1) return -1;
  };

  cans[comp[0]] = 0;

  for (int ci = scc.comp[0]; ~ci; ci--) {
    if (ci) {}
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int t = 1;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    // cout << "Case " << cs << ": ";
    test_case();
  }

  return 0;
}