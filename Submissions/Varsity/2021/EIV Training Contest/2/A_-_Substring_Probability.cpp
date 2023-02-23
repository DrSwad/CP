#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int MOD = 998244353;

ll binExp(ll a, ll e, ll m = MOD) {
  if (e == -1) e = m - 2;
  ll ret = 1;
  while (e) {
    if (e & 1) ret = ret * a % m;
    a = a * a % m, e >>= 1;
  }
  return ret;
}

template<typename T>
vector<int> prefix_function(int n, const T &s) {
  vector<int> p(n, 0);
  int k = 0;
  for (int i = 1; i < n; i++) {
    while (k > 0 && !(s[i] == s[k])) {
      k = p[k - 1];
    }
    if (s[i] == s[k]) {
      k++;
    }
    p[i] = k;
  }
  return p;
}
template<typename T>
vector<int> prefix_function(const T &s) {
  return prefix_function((int) s.size(), s);
}

pair<vector<int>, vector<vector<int>>> construct_edges(string p, string q) {
  int np = p.length(), nq = q.length();
  string r = p + '#' + q;
  int nr = r.length();

  vector<vector<int>> e(np + 1);
  vector<int> with;

  vector<int> pf = prefix_function(r);
  for (int i = 0; i < np; i++) {
    e[pf[i]].push_back(i + 1);
  }

  for (int i = np + 1; i < nr; i++) {
    with.push_back(pf[i]);
  }

  return {with, e};
}

void test_case() {
  string p, q;
  cin >> p >> q;
  int np = p.length(), nq = q.length();

  auto [with0, e0] = construct_edges(p, q);

  reverse(p.begin(), p.end());
  reverse(q.begin(), q.end());
  auto [with1, e1] = construct_edges(p, q);
  reverse(with1.begin(), with1.end());

  // debug(with0, e0);
  // debug(with1, e1);

  int n = np + 1;

  vector<int> h(n);
  h[0] = 0;
  function<void(int)> h_dfs = [&](int v) {
    for (int u : e0[v]) {
      h[u] = h[v] + 1;
      h_dfs(u);
    }
  };
  h_dfs(0);
  // debug(h);

  vector<vector<int>> ids(n);
  for (int i = 0; i < nq - 1; i++) {
    if (with0[i]) ids[with1[i + 1]].push_back(with0[i]);
  }
  // debug(ids);

  vector<bool> vis(n, false);
  vector<ll> sum(n, 0);
  ll ans = 0;

  vector<int> sz(n);
  function<void(int)> sz_dfs = [&](int v) {
    sz[v] = ids[v].size();
    for (int u : e1[v]) {
      sz_dfs(u);
      sz[v] += sz[u];
    }
  };
  sz_dfs(0);
  // debug(sz);

  function<void(int, bool)> dsu = [&](int v, bool keep) {
    // DB();
    // debug(v, keep);
    int big_sz = 0, big_child = -1;
    for (int u : e1[v]) {
      if (sz[u] > big_sz) {
        big_sz = sz[u];
        big_child = u;
      }
    }

    for (int u : e1[v]) {
      if (u != big_child) {
        dsu(u, false);
      }
    }

    if (big_child != -1) {
      dsu(big_child, true);
      for (int id : ids[v]) {
        if (!vis[id]) {
          ids[big_child].push_back(id);
          vis[id] = true;
          sum[big_child] += id;
        }
      }
      swap(ids[big_child], ids[v]);
      swap(sum[big_child], sum[v]);
    }
    else {
      for (int id : ids[v]) {
        vis[id] = true;
        sum[v] += h[id];
      }
    }

    for (int u : e1[v]) {
      if (u != big_child) {
        for (int id : ids[u]) {
          if (!vis[id]) {
            ids[v].push_back(id);
            vis[id] = true;
            sum[v] += h[id];
          }
        }
      }
    }

    if (v) (ans += sum[v]) %= MOD;

    if (!keep) {
      for (int id : ids[v]) {
        vis[id] = false;
      }
    }

    // debug(v, ids[v], sum[v]);
  };
  dsu(0, true);

  (ans *= binExp((ll)np * np % MOD, -1)) %= MOD;
  cout << ans << "\n";
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