#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

ll binExp(ll a, ll e, ll m) {
  if (e == -1) e = m - 2;
  ll ret = 1;
  while (e) {
    if (e & 1) ret = ret * a % m;
    a = a * a % m, e >>= 1;
  }
  return ret;
}

bool solve(ll mod, ll n, ll m, vector<vector<pair<ll, ll>>> e) {
  for (int u = 0; u < n; u++) {
    for (auto & [v, w] : e[u]) {
      if (w < 0) w = binExp((-w) % mod, -1, mod);
      else w %= mod;
    }
  }

  // DB();
  // debug(mod);
  // debug(n, m, e);
  vector<ll> val(n, -1);

  function<void(ll)> dfs = [&](ll at) {
    // debug(at, val[at]);

    for (auto [to, w] : e[at]) {
      if (val[to] < 0) {
        val[to] = 1ll * val[at] * w % mod;
        dfs(to);
      }
    }
  };

  for (ll i = 0; i < n; i++) {
    if (val[i] < 0) {
      val[i] = 1;
      dfs(i);
    }
  }

  for (ll u = 0; u < n; u++) {
    for (auto [v, w] : e[u]) {
      if (1ll * val[u] * w % mod != val[v]) {
        return false;
      }
    }
  }

  return true;
}

void test_case() {
  ll n, m;
  cin >> n >> m;

  vector<vector<pair<ll, ll>>> e(n);
  for (ll i = 0; i < m; i++) {
    ll u, v, w;
    cin >> u >> v >> w;
    u--, v--;
    e[u].push_back({v, w});
    e[v].push_back({u, -w});
  }

  if (solve((ll)1e9 + 7, n, m, e) and solve((ll)9999991, n, m, e)) {
    cout << "Yes\n";
  }
  else {
    cout << "No\n";
  }
}

void init() {
  const int n = 1e7;
  vector<bool> vis(n, false);
  int last_prime;
  for (int i = 2; i < n; i++) {
    if (!vis[i]) {
      last_prime = i;
      for (int j = i; j < n; j += i) {
        vis[j] = true;
      }
    }
  }
  cerr << last_prime << endl;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  // init();

  int t = 1;
  // cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    // cout << "Case " << cs << ": ";
    test_case();
  }

  return 0;
}