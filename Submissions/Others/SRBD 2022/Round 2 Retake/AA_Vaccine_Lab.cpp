#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

void test_case() {
  int n, m;
  cin >> n >> m;

  vector<ll> h(n), c(m);
  for (ll &i : h) cin >> i;
  for (ll &i : c) cin >> i;

  vector<vector<ll>> p(m, vector<ll>(n));
  for (auto &v : p) for (ll & i : v) cin >> i;

  ll min_val = LLONG_MAX, min_cost = LLONG_MAX;
  vector<ll> rem_h = h;

  function<void(int, ll)> dfs =
    [&](int i, ll cur_cost) {
      if (i == m) {
        ll cur_val = 0;
        for (ll i : rem_h) cur_val += max(i, 0ll);
        if (cur_val < min_val) {
          min_val = cur_val;
          min_cost = cur_cost;
        }
        else if (cur_val == min_val) {
          min_cost = min(min_cost, cur_cost);
        }
        return;
      }

      dfs(i + 1, cur_cost);

      for (int it = 0; it < 2; it++) {
        for (int j = 0; j < n; j++) {
          rem_h[j] -= p[i][j];
        }
        cur_cost += c[i];
        dfs(i + 1, cur_cost);
      }
      for (int j = 0; j < n; j++) {
        rem_h[j] += 2ll * p[i][j];
      }
    };

  dfs(0, 0);

  cout << min_cost << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t = 1;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    cout << "Case " << cs << ": ";
    test_case();
  }

  return 0;
}