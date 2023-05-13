#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n, q;
  cin >> n >> q;

  vector<pair<int, int>> queries(q);
  for (auto & [x, y] : queries) {
    cin >> x >> y;
    x--, y--;
  }

  vector<bool> good_mask(1 << n);
  for (int mask = 0; mask < 1 << n; mask++) {
    int _mask = mask;
    for (auto [x, y] : queries) {
      if ((_mask >> x & 1) > (_mask >> y & 1)) {
        _mask -= 1 << x;
        _mask += 1 << y;
      }
    }
    int cnt1 = mask == 0 ? 0 : __builtin_popcount(mask);
    int cnt0 = n - cnt1;
    good_mask[mask] = _mask == ((1 << cnt1) - 1) << cnt0;
  }

  vector<long long> dp(1 << n, 0);
  dp[0] = 1;
  for (int mask = 1; mask < 1 << n; mask++) {
    int rest = ((1 << n) - 1) - mask;
    for (int i = 0; i < n; i++) {
      if (mask >> i & 1) {
        if (good_mask[rest + (1 << i)]) {
          dp[mask] += dp[mask - (1 << i)];
        }
      }
    }
  }

  cout << dp[(1 << n) - 1] << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    cout << "Case " << cs << ": ";
    test_case();
  }

  return 0;
}