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

int solve(const vector<pair<int, int>> &ranges) {
  vector<int> coords;
  for (auto [l, r] : ranges) {
    coords.push_back(l);
    coords.push_back(r);
  }
  sort(coords.begin(), coords.end());
  coords.resize(unique(coords.begin(), coords.end()) - coords.begin());

  int sz = coords.size();

  vector<int> pref(sz, 0), suff(sz, 0);

  for (auto [l, r] : ranges) {
    int ll = lower_bound(coords.begin(), coords.end(), l) - coords.begin();
    int rr = lower_bound(coords.begin(), coords.end(), r) - coords.begin();
    pref[ll]++;
    suff[rr]++;
  }

  for (int i = 1; i < sz; i++) {
    pref[i] += pref[i - 1];
  }
  for (int i = sz - 2; i >= 0; i--) {
    suff[i] += suff[i + 1];
  }

  int mx = 0;
  for (int i = 0; i < sz; i++) {
    mx = max(mx, pref[i] + suff[i]);
  }

  return mx;
}

void test_case() {
  int n;
  cin >> n;

  vector<int> a(n);
  for (int &i : a) cin >> i;

  LCA lca(n);

  for (int i = 0; i < n - 1; i++) {
    int u, v;
    cin >> u >> v;
    u--, v--;
    lca.add_edge(u, v);
  }

  lca.build(0);

  int q;
  cin >> q;

  vector<pair<int, int>> queries(q);
  vector queries_at(n, vector<int>());
  for (int qi = 0; qi < q; qi++) {
    auto & [u, v] = queries[qi];
    cin >> u >> v;
    u--, v--;
    queries_at[u].push_back(qi);
    queries_at[v].push_back(qi);
  }

  const int log_a = 30;

  vector pos(log_a, vector<int>());
  vector ranges(q, vector(log_a, make_pair(-1, -1)));

  function<void(int, int)> dfs =
    [&](int at, int from) {
      for (int bit = 0; bit < log_a; bit++) {
        if (a[at] >> bit & 1) {
          pos[bit].push_back(lca.depth[at]);
        }
      }

      for (int qi : queries_at[at]) {
        auto [u, v] = queries[qi];
        int l = lca.query(u, v);
        int du = lca.depth[u];
        int dv = lca.depth[v];
        int dl = lca.depth[l];

        for (int bit = 0; bit < log_a; bit++) {
          if (pos[bit].empty() or pos[bit].back() < dl) continue;
          int d1 = lca.depth[at] - pos[bit].back();
          int d2 = lca.depth[at] - *lower_bound(pos[bit].begin(), pos[bit].end(), dl);

          if (at != u) {
            int tot_d = du + dv - 2 * dl;
            d1 = tot_d - d1;
            d2 = tot_d - d2;
            swap(d1, d2);
          }

          if (ranges[qi][bit].first == -1 or ranges[qi][bit].first > d1) {
            ranges[qi][bit].first = d1;
          }
          if (ranges[qi][bit].second == -1 or ranges[qi][bit].second < d2) {
            ranges[qi][bit].second = d2;
          }
        }
      }

      for (int to : lca.G[at]) {
        if (to != from) {
          dfs(to, at);
        }
      }

      for (int bit = 0; bit < log_a; bit++) {
        if (a[at] >> bit & 1) {
          pos[bit].pop_back();
        }
      }
    };

  dfs(0, -1);

  for (int qi = 0; qi < q; qi++) {
    vector<pair<int, int>> nranges;
    for (int bit = 0; bit < log_a; bit++) {
      if (ranges[qi][bit].first == -1 and ranges[qi][bit].second != -1) {
        ranges[qi][bit].first = ranges[qi][bit].second;
      }
      if (ranges[qi][bit].second == -1 and ranges[qi][bit].first != -1) {
        ranges[qi][bit].second = ranges[qi][bit].first;
      }
      if (ranges[qi][bit].first != -1) {
        assert(ranges[qi][bit].second != -1);
        nranges.emplace_back(ranges[qi][bit]);
      }
    }

    if (qi) cout << " ";
    cout << solve(nranges);
  }
  cout << "\n";
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