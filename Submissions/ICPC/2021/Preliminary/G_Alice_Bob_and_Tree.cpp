#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

void test_case() {
  int n;
  cin >> n;

  vector<ll> w(n);
  for (ll &i : w) cin >> i;

  vector<vector<int>> e(n);
  for (int i = 0; i < n - 1; i++) {
    int u, v;
    cin >> u >> v;
    u--, v--;
    e[u].push_back(v);
    e[v].push_back(u);
  }

  vector<vector<ll>> dp(2, vector<ll>(n));
  vector<vector<ll>> ww(2, vector<ll>(n));
  fill(ww[0].begin(), ww[0].end(), 1);
  ww[1] = w;

  for (int it = 0; it < 2; it++) {
    vector<ll> sub(n);
    function<void(int, int)> dfs1 = [&](int at, int from) {
      sub[at] = ww[it][at];
      for (int to : e[at]) {
        if (to != from) {
          dfs1(to, at);
          sub[at] -= sub[to];
        }
      }
    };
    dfs1(0, -1);

    dp[it][0] = sub[0];
    function<void(int, int)> dfs2 = [&](int at, int from) {
      for (int to : e[at]) {
        if (to != from) {
          dp[it][to] = sub[to] - (dp[it][at] + sub[to]);
          dfs2(to, at);
        }
      }
    };
    dfs2(0, -1);
  }

  ll ans_val = LLONG_MIN;
  int ans_i;

  for (int i = 0; i < n; i++) {
    ll curr_val = w[i] * dp[0][i] - dp[1][i];
    if (curr_val > ans_val) {
      ans_val = curr_val;
      ans_i = i;
    }
  }

  cout << ans_i + 1 << "\n";
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