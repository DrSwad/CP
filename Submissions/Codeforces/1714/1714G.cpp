#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int LOGN = 20;

void test_case() {
  int n;
  cin >> n;

  vector<vector<tuple<int, ll, ll>>> e(n);
  for (int i = 1; i <= n - 1; i++) {
    int j, a, b;
    cin >> j >> a >> b;
    j--;
    e[i].push_back({j, a, b});
    e[j].push_back({i, a, b});
  }

  vector<vector<int>> p(LOGN, vector<int>(n));
  vector<ll> a_pref(n, 0), b_pref(n, 0);
  vector<int> h(n, 0);
  vector<int> ans(n);

  function<void(int, int, int, int)> dfs = [&](int at, int from, int a, int b) {
    // DB();
    // debug(at, from, a, b);
    if (at != 0) {
      h[at] = h[from] + 1;
      a_pref[at] = a_pref[from] + a;
      b_pref[at] = b_pref[from] + b;
    }
    // debug(h[at], a_pref[at], b_pref[at]);

    p[0][at] = from;
    for (int i = 1; i < LOGN; i++) {
      if (p[i - 1][at] != -1) {
        p[i][at] = p[i - 1][p[i - 1][at]];
      }
    }

    if (b_pref[at] <= a_pref[at]) ans[at] = h[at];
    else {
      int u = at;
      for (int i = LOGN - 1; i >= 0; i--) {
        if (p[i][u] != -1 and b_pref[p[i][u]] > a_pref[at]) {
          u = p[i][u];
        }
      }
      ans[at] = h[p[0][u]];
    }
    // debug(ans[at]);

    for (auto [to, a, b] : e[at]) {
      if (to != from) dfs(to, at, a, b);
    }
  };

  dfs(0, -1, 0, 0);

  for (int i = 1; i < n; i++) {
    if (i > 1) cout << " ";
    cout << ans[i];
  }
  cout << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t = 1;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    // cout << "Case " << cs << ": ";
    test_case();
  }

  return 0;
}