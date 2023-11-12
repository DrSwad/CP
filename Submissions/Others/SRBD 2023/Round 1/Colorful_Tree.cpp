#include <bits/stdc++.h>
using namespace std;

template<class T>
struct RMQ { // 0-based
  vector<vector<T>> rmq;
  T kInf = numeric_limits<T>::max();
  void build(const vector<T>&V) {
    int n = V.size(), on = 1, dep = 1;
    while (on < n) on *= 2, ++dep;
    rmq.assign(dep, V);

    for (int i = 0; i < dep - 1; ++i)
      for (int j = 0; j < n; ++j) {
        rmq[i + 1][j] = min(rmq[i][j], rmq[i][min(n - 1, j + (1 << i))]);
      }
  }
  T query(int a, int b) { // [a, b)
    if (b <= a) return kInf;
    int dep = 31 - __builtin_clz(b - a); // log(b - a)
    return min(rmq[dep][a], rmq[dep][b - (1 << dep)]);
  }
};

struct LCA { // 0-based
  vector<int> enter, depth, exxit;
  vector<vector<int>> G;
  vector<pair<int, int>> linear;
  RMQ<pair<int, int>> rmq;
  int timer = 0;
  LCA() {}
  LCA(int n) : enter(n, -1), exxit(n, -1), depth(n), G(n), linear(2 * n) {}
  void dfs(int node, int dep) {
    linear[timer] = {dep, node};
    enter[node] = timer++;
    depth[node] = dep;
    for (auto vec : G[node])
      if (enter[vec] == -1) {
        dfs(vec, dep + 1);
        linear[timer++] = {dep, node};
      }
    exxit[node] = timer;
  }
  void add_edge(int a, int b) {
    G[a].push_back(b);
    G[b].push_back(a);
  }
  void build(int root) {
    dfs(root, 0);
    rmq.build(linear);
  }
  int query(int a, int b) {
    a = enter[a], b = enter[b];
    return rmq.query(min(a, b), max(a, b) + 1).second;
  }
  int dist(int a, int b) {
    return depth[a] + depth[b] - 2 * depth[query(a, b)];
  }
};

void test_case() {
  int n, q;
  cin >> n >> q;

  LCA lca(n);

  for (int i = 1; i < n; i++) {
    int j;
    cin >> j;
    j--;
    lca.add_edge(i, j);
  }

  string s;
  cin >> s;

  vector<int> dp(n, 0);

  function<void(int, int)> dfs =
    [&](int at, int from) {
      dp[at] = s[at] - '0';
      if (from != -1) dp[at] += dp[from];

      for (int to : lca.G[at]) {
        if (to != from) {
          dfs(to, at);
        }
      }
    };

  dfs(0, -1);

  lca.build(0);

  while (q--) {
    int u, v;
    cin >> u >> v;
    u--, v--;

    cout << dp[u] + dp[v] - 2 * dp[lca.query(u, v)] + 1 << "\n";
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