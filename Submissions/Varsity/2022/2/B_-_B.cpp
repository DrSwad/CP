#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

void test_case() {
  int n, m;
  cin >> n >> m;

  vector<ll> p(m);
  for (ll &i : p) cin >> i;
  sort(p.begin(), p.end());

  vector<vector<pair<int, int>>> e(n);
  for (int i = 0; i < n - 1; i++) {
    int u, v, k;
    cin >> u >> v >> k;
    u--, v--;
    e[u].emplace_back(v, k);
    e[v].emplace_back(u, k);
  }

  vector<ll> leaves;
  function<void(int, int, int, ll)> dfs = [&](int at, int from, int depth, ll carry) {
    int children = 0;
    for (auto [to, w] : e[at]) {
      if (to != from) {
        dfs(to, at, depth + 1, carry + 1ll * w * (depth + 1));
        children++;
      }
    }
    if (children == 0) leaves.push_back(carry);
  };
  dfs(0, -1, 0, 0ll);
  sort(leaves.begin(), leaves.end());

  int ans = 0;
  for (int i = (int)leaves.size() - 1, j = m - 1; i >= 0 and j >= 0; i--) {
    if (leaves[i] <= p[j]) j--, ans++;
  }

  cout << ans << "\n";
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