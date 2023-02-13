#include <bits/stdc++.h>
using namespace std;

struct DSU {
  int n, sz;
  vector<int> p; // root: -1 * component size, otherwise: parent
  DSU(int n) : n(n), sz(n), p(n, -1) {}
  bool same(int a, int b) { return root(a) == root(b); }
  int root(int a) { return p[a] < 0 ? a : (p[a] = root(p[a])); }
  int size(int a) { return -p[root(a)]; }
  int size() { return sz; }
  bool merge(int a, int b, bool rank = true) {
    int x = root(a), y = root(b);
    if (x == y) return false;
    sz--;
    if (rank and - p[x] < -p[y]) swap(x, y);
    p[x] += p[y];
    p[y] = x;
    return true;
  }
  vector<vector<int>> groups() {
    vector<int> _root(n), sz(n);
    for (int i = 0; i < n; i++) _root[i] = root(i), sz[_root[i]]++;
    vector<vector<int>> g(n);
    for (int i = 0; i < n; i++) g[i].reserve(sz[i]);
    for (int i = 0; i < n; i++) g[_root[i]].push_back(i);
    auto empty = [&](const vector<int>&v) { return v.empty(); };
    g.erase(remove_if(g.begin(), g.end(), empty), g.end());
    return g;
  }
};

int MOD;

int add(int a, int b) {
  int c = a + b;
  return c < MOD ? c : c - MOD;
}

int mul(int a, int b) {
  return 1ll * a * b % MOD;
}

int solve(int n, vector<vector<int>> adj, int k) {
  vector<int> is_bad(n, false);
  vector<int> bad_nodes;
  vector<vector<int>> bad_adj(n);

  vector<bool> bad_dfs_vis(n, false);
  function<void(int, int)> bad_dfs = [&](int at, int from) {
    bad_dfs_vis[at] = true;
    bool curr_bad = false;
    for (int to : adj[at]) {
      if (to != from) {
        if (bad_dfs_vis[to]) {
          curr_bad = true;
          bad_adj[at].push_back(to);
        }
        else bad_dfs(to, at);
      }
      if (curr_bad) {
        is_bad[at] = true;
        bad_nodes.push_back(at);
      }
    }
  };
  bad_dfs(0, -1);

  vector<int> colors(n, -1);
  vector<vector<int>> dp(n);
  int ans = 0;

  vector<bool> solve_dfs_vis(n, false);
  function<void(int, int, int)> solve_dfs = [&](int at, int from, int colors_used) {
    solve_dfs_vis[at] = true;
    vector<int> ret(colors_used + 1, 0);

    for (int at_color = 0; at_color <= colors_used; at_color++) {
      if (is_bad[at] and at_color != colors[at]) continue;
      ret[at_color] = 1 % MOD;
    }

    for (int to : adj[at]) {
      if (to != from and !solve_dfs_vis[to]) {
        solve_dfs(to, at, colors_used);

        vector<int> nret(colors_used + 1);

        for (int at_color = 0; at_color <= colors_used; at_color++) {
          if (is_bad[at] and at_color != colors[at]) continue;
          for (int to_color = 0; to_color <= colors_used; to_color++) {
            if (is_bad[to] and to_color != colors[to]) continue;
            if (at_color == to_color) continue;

            int to_mul = to_color < colors_used ? 1 : at_color < colors_used ? (k - colors_used) : (k - colors_used - 1);
            if (to_mul <= 0) continue;
            to_mul %= MOD;

            nret[at_color] = add(nret[at_color], mul(ret[at_color], mul(dp[to][to_color], to_mul)));
          }
        }

        swap(ret, nret);
      }
    }

    dp[at] = ret;
  };

  function<void(int, int, int)> color_bads = [&](int at, int colors_used, int ans_mul) {
    if (colors_used > k) return;
    if (at == bad_nodes.size()) {
      fill(solve_dfs_vis.begin(), solve_dfs_vis.end(), false);
      solve_dfs(0, -1, colors_used);
      vector<int> root_dp = dp[0];
      int nans = 0;
      for (int color = 0; color < colors_used; color++) {
        nans = add(nans, root_dp[color]);
      }
      nans = add(nans, mul(root_dp[colors_used], (k - colors_used) % MOD));
      nans = mul(nans, ans_mul);
      ans = add(ans, nans);
      return;
    }

    for (int curr_color = 0; curr_color < colors_used; curr_color++) {
      bool valid = true;
      for (int to : bad_adj[bad_nodes[at]]) {
        if (colors[to] == curr_color) {
          valid = false;
          break;
        }
      }

      if (valid) {
        colors[bad_nodes[at]] = curr_color;
        color_bads(at + 1, colors_used, ans_mul);
      }
    }

    colors[bad_nodes[at]] = colors_used;
    color_bads(at + 1, colors_used + 1, mul(ans_mul, (k - colors_used) % MOD));
  };

  color_bads(0, 0, 1 % MOD);

  return ans;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, m, k;
  cin >> n >> m >> k >> MOD;

  DSU dsu(n);
  vector<vector<int>> adj(n);
  while (m--) {
    int u, v;
    cin >> u >> v;
    u--, v--;
    adj[u].push_back(v);
    adj[v].push_back(u);
    dsu.merge(u, v);
  }

  vector<vector<int>> groups = dsu.groups();
  int ans = 1 % MOD;

  for (auto group : groups) {
    auto comp_group = group;
    sort(comp_group.begin(), comp_group.end());
    comp_group.resize(unique(comp_group.begin(), comp_group.end()) - comp_group.begin());

    int nn = group.size();
    vector<vector<int>> nadj(nn);

    for (int u : group) {
      int comp_u = lower_bound(comp_group.begin(), comp_group.end(), u) - comp_group.begin();
      for (int v : adj[u]) {
        int comp_v = lower_bound(comp_group.begin(), comp_group.end(), v) - comp_group.begin();
        nadj[comp_u].push_back(comp_v);
      }
    }

    ans = mul(ans, solve(nn, nadj, k));
  }

  cout << ans % MOD << "\n";

  return 0;
}