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

typedef long long ll;

ll arithmetic_sum(ll first_term, ll d, ll terms) {
  return (2ll * first_term + (terms - 1) * d) * terms / 2ll;
}

ll arithmetic_terms(ll first_term, ll d, ll max_term) {
  if (max_term < first_term) return 0;
  return (max_term - first_term) / d + 1;
}

ll arithmetic(ll first_term1, ll d1, ll first_term2, ll d2, ll need) {
  ll L = -1, R = 1e18;
  while (R > L + 1) {
    ll max_term = (L + R) / 2;
    ll got1 = arithmetic_terms(first_term1, d1, max_term);
    ll got2 = arithmetic_terms(first_term2, d2, max_term);
    if (got1 + got2 >= need) R = max_term;
    else L = max_term;
  }

  ll max_term = R;
  ll terms1 = arithmetic_terms(first_term1, d1, max_term);
  ll terms2 = arithmetic_terms(first_term2, d2, max_term);
  ll ret = 0;
  ret += arithmetic_sum(first_term1, d1, terms1);
  ret += arithmetic_sum(first_term2, d2, terms2);
  if (terms1 + terms2 > need) ret -= max_term;

  // while (need--) {
  //   if (first_term1 <= first_term2) {
  //     ret += first_term1;
  //     first_term1 += d1;
  //   }
  //   else {
  //     ret += first_term2;
  //     first_term2 += d2;
  //   }
  // }

  return ret;
}

ll solve(ll d1, ll d2, ll up_cost, ll down_cost) {
  // debug(d1, d2, up_cost, down_cost);

  ll ans = LLONG_MAX;
  // debug(arithmetic_sum(up_cost, up_cost, d1));
  ans = min(ans, arithmetic_sum(up_cost, up_cost, d1) + arithmetic(down_cost * (d1 + 1), down_cost, up_cost, up_cost, d2));
  ans = min(ans, arithmetic_sum(up_cost, up_cost, d2) + arithmetic(up_cost, up_cost, down_cost * (d2 + 1), down_cost, d1));

  return ans;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;

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

  while (q--) {
    int root, up_cost, down_cost, u, v;
    cin >> root >> up_cost >> down_cost >> u >> v;
    root--, u--, v--;
    // DB();
    // debug(root, up_cost, down_cost, u, v);

    vector<int> candidates{lca.query(u, v), lca.query(u, root), lca.query(v, root)};
    int max_depth = INT_MIN, q_lca = -1;

    for (int cur_lca : candidates) {
      if (lca.dist(root, u) != lca.dist(root, cur_lca) + lca.dist(cur_lca, u)) continue;
      if (lca.dist(root, v) != lca.dist(root, cur_lca) + lca.dist(cur_lca, v)) continue;
      int cur_depth = lca.depth[cur_lca];
      if (cur_depth > max_depth) {
        max_depth = cur_depth;
        q_lca = cur_lca;
      }
    }

    // debug(q_lca);

    int du = lca.dist(q_lca, u);
    int dv = lca.dist(q_lca, v);

    cout << solve(du, dv, up_cost, down_cost) << "\n";
  }

  return 0;
}