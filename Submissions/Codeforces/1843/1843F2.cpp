#include <bits/stdc++.h>
using namespace std;

function<int(int, int)> f[2]{
  [](int a, int b) { return min(a, b); },
  [](int a, int b) { return max(a, b); },
};

void test_case() {
  int events;
  cin >> events;

  int n = 1;
  vector<vector<int>> adj(2);
  vector<int> val{0, 1};
  vector<tuple<int, int, int>> queries;

  while (events--) {
    char type;
    cin >> type;

    if (type == '+') {
      int id = ++n, parent, value;
      cin >> parent >> value;
      adj.push_back({parent});
      adj[parent].emplace_back(id);
      val.emplace_back(value);
    }
    else if (type == '?') {
      int u, v, k;
      cin >> u >> v >> k;
      queries.emplace_back(u, v, k);
    }
    else assert(false);
  }

  int logn = 32 - __builtin_clz(n);
  vector<int> depth(n + 1, 0);
  vector<int> sum_to_root(n + 1, 0);
  vector parent(n + 1, vector(logn, -1));
  vector st(n + 1, vector(logn, vector(2, vector(2, 0))));
  vector seg(n + 1, vector(logn, vector(2, 0)));

  function<void(int, int)> dfs =
    [&](int at, int from) {
      depth[at] = depth[from] + 1;
      sum_to_root[at] = val[at] + sum_to_root[from];
      parent[at][0] = from;
      for (int it = 0; it < 2; it++) {
        for (int dir = 0; dir < 2; dir++) {
          st[at][0][it][dir] = f[it](val[at], 0);
        }
        seg[at][0][it] = f[it](val[at], 0);
      }

      for (int i = 1; i < logn; i++) {
        int to = parent[at][i - 1];
        if (to >= 0 and parent[to][i - 1] >= 0) {
          parent[at][i] = parent[to][i - 1];
          for (int it = 0; it < 2; it++) {
            int sum[2] = {sum_to_root[at] - sum_to_root[to], sum_to_root[to] - sum_to_root[parent[to][i - 1]]};
            st[at][i][it][0] = f[it](st[at][i - 1][it][0], sum[0] + st[to][i - 1][it][0]);
            st[at][i][it][1] = f[it](st[to][i - 1][it][1], sum[1] + st[at][i - 1][it][1]);
            seg[at][i][it] = f[it](
              f[it](seg[at][i - 1][it], seg[to][i - 1][it]),
              st[at][i - 1][it][1] + st[to][i - 1][it][0]
            );
          }
        }
      }

      for (int to : adj[at]) {
        if (to != from) {
          dfs(to, at);
        }
      }
    };

  dfs(1, 0);

  auto under_lca =
    [&](int u, int v) {
      if (depth[u] < depth[v]) swap(u, v);
      for (int i = logn - 1; i >= 0; i--) {
        if (parent[u][i] >= 0 and depth[parent[u][i]] >= depth[v]) {
          u = parent[u][i];
        }
      }
      if (u == v) return u;
      for (int i = logn - 1; i >= 0; i--) {
        if (parent[u][i] != parent[v][i]) {
          u = parent[u][i];
          v = parent[v][i];
        }
      }
      return u;
    };

  auto query =
    [&](int mode, int at, int ancestor) {
      int st_ans = 0, seg_ans = 0;
      for (int i = logn - 1; i >= 0; i--) {
        int to = parent[at][i];
        if (to >= 0 and depth[to] >= depth[ancestor] - 1) {
          seg_ans = f[mode](seg_ans, f[mode](seg[at][i][mode], st_ans + st[at][i][mode][0]));
          st_ans = f[mode](st[at][i][mode][1], sum_to_root[at] - sum_to_root[to] + st_ans);
          at = to;
        }
      }
      return make_pair(st_ans, seg_ans);
    };

  for (auto [u, v, k] : queries) {
    if (depth[u] < depth[v]) swap(u, v);
    int U = under_lca(u, v);

    vector res(2, 0);
    if (U == v) {
      for (int it = 0; it < 2; it++) {
        auto [st, seg] = query(it, u, U);
        res[it] = seg;
      }
    }
    else {
      int V = parent[U][0];
      for (int it = 0; it < 2; it++) {
        auto [l_st, l_seg] = query(it, u, U);
        auto [r_st, r_seg] = query(it, v, V);
        res[it] = f[it](f[it](l_seg, r_seg), l_st + r_st);
      }
    }

    if (res[0] <= k and k <= res[1]) cout << "YES\n";
    else cout << "NO\n";
  }
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