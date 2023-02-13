#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int K = 1e6 + 5;

ll dp[K];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;

  vector<int> a(n);
  for (int &i : a) cin >> i;

  vector<pair<int, int>> ranges;

  for (int i = 0; i < n; i++) {
    vector<pair<int, int>> nranges;
    for (auto item : ranges) {
      int g = item.first;
      int j = item.second;
      g = __gcd(g, a[i]);
      if (nranges.empty() or nranges.back().first != g) {
        nranges.push_back({g, j});
      }
    }
    if (nranges.empty() or nranges.back().first != a[i]) {
      nranges.push_back({a[i], i});
    }
    swap(ranges, nranges);

    for (int ri = 0; ri < ranges.size(); ri++) {
      int g = ranges[ri].first;
      int j = ranges[ri].second;
      int nxt = ri + 1 == ranges.size() ? i + 1 : ranges[ri + 1].second;
      if (g < K) dp[g] += nxt - j;
    }
  }

  int q;
  cin >> q;
  while (q--) {
    int k;
    cin >> k;

    ll ans = 0;
    for (int d = 1; d * d <= k; d++) {
      if (k % d == 0) {
        ans += dp[d];
        if (d * d != k) ans += dp[k / d];
      }
    }
    cout << ans << "\n";
  }

  return 0;
}