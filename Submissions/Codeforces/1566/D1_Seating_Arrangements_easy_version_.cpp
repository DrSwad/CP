#include <bits/stdc++.h>
using namespace std;

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
typedef tree<int, null_type, less<int>, rb_tree_tag,
             tree_order_statistics_node_update>
  ordered_set;

void test_case() {
  int n, m;
  cin >> n >> m;

  int tot = n * m;

  vector<pair<int, int>> a(tot);
  for (int i = 0; i < tot; i++) {
    cin >> a[i].first;
    a[i].second = i;
  }

  sort(a.begin(), a.end());

  vector<vector<int>> b;
  for (int i = 0; i < tot; i++) {
    if (i == 0 or a[i].first > a[b.back().back()].first) {
      b.push_back({i});
    } else {
      b.back().push_back(i);
    }
  }

  vector<vector<int>> g(n, vector<int>(m));

  int x = 0, y = 0;
  int bi = 0, bj = 0;

  while (x < n) {
    int bsz = b[bi].size() - bj;
    int gsz = m - y;
    int take = min(bsz, gsz);

    reverse(b[bi].begin() + bj, b[bi].begin() + bj + take);

    for (int i = 0; i < take; i++) {
      g[x][y++] = a[b[bi][bj++]].second;
    }

    if (bj == b[bi].size()) bi++, bj = 0;
    if (y == m) x++, y = 0;
  }

  long long ans = 0;

  for (int i = 0; i < n; i++) {
    ordered_set os;
    for (int j = 0; j < m; j++) {
      ans += os.order_of_key(g[i][j]);
      os.insert(g[i][j]);
    }
  }

  cout << ans << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int t;
  cin >> t;

  while (t--) {
    test_case();
  }

  return 0;
}