#include <bits/stdc++.h>
using namespace std;

class VirtualTree {
private:
  int n, log_n;
  vector<vector<int>> e;
  vector<int> h, st, en;
  vector<vector<int>> P;

  int lca_dfs(int v = 0, int p = 0, int t = 0) {
    st[v] = t;
    h[v] = h[p] + 1;
    P[v][0] = p;
    for (int i = 1; i < log_n; i++) P[v][i] = P[P[v][i - 1]][i - 1];
    for (int u : e[v]) if (u != p) t = lca_dfs(u, v, t + 1);
    return en[v] = t;
  }
  bool contains(int u, int v) {
    return st[u] <= st[v] and en[v] <= en[u];
  }
  int lca(int u, int v) {
    if (contains(u, v)) return u;
    if (contains(v, u)) return v;
    for (int i = log_n - 1; i >= 0; i--)
      if (!contains(P[u][i], v)) u = P[u][i];
    return P[u][0];
  }
public:
  VirtualTree(vector<vector<int>> e) {
    n = e.size(), log_n = 32 - __builtin_clz(n), this->e = e;
    h.resize(n), st.resize(n), en.resize(n);
    P.resize(n, vector<int>(log_n));
    lca_dfs();
  }
  pair<vector<vector<pair<int, int>>>, vector<int>> get_tree(vector<int> V) {
    int k = V.size();
    auto cmp = [&](int u, int v) { return st[u] < st[v]; };
    sort(V.begin(), V.end(), cmp);
    for (int i = 0; i < k - 1; i++) V.push_back(lca(V[i], V[i + 1]));
    sort(V.begin(), V.end(), cmp);
    V.resize(unique(V.begin(), V.end()) - V.begin());
    k = V.size();

    vector<vector<pair<int, int>>> E(k);
    stack<int> st;
    st.push(0);
    for (int i = 1; i < k; i++) {
      while (!contains(V[st.top()], V[i])) st.pop(), assert(!st.empty());
      E[st.top()].push_back({i, h[V[i]] - h[V[st.top()]]});
      st.push(i);
    }

    return {E, V};
  }
};
/* Usage
 * All the nodes are 0-indexed
 *
 * e = adjacency list
 * VirtualTree vt(e); // O(Nlog(N))
 *
 * auto [E, V] = vt.get_tree(vert); // O(Klog(K))
 * E = compressed adjacency list
 * V = original ids of the nodes in E
 */

void test_case() {
  int n;
  cin >> n;

  vector<vector<int>> e(n);
  for (int i = 0; i < n - 1; i++) {
    int u, v;
    cin >> u >> v;
    u--, v--;
    e[u].push_back(v), e[v].push_back(u);
  }

  int q;
  cin >> q;

  VirtualTree vt(e);

  while (q--) {
    int k;
    cin >> k;
    vector<int> vert(k);
    for (int &i : vert) cin >> i, i--;

    auto [E, V] = vt.get_tree(vert);
    for (int i = 0; i < V.size(); i++) {
      if (i) cout << " ";
      cout << V[i] + 1;
    }
    cout << "\n";
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t;
  cin >> t;

  while (t--) {
    test_case();
  }

  return 0;
}