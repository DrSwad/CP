#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n, m;
  cin >> n >> m;

  vector<int> a_freq(m + 1, 0);
  for (int i = 0; i < n; i++) {
    int a;
    cin >> a;
    a_freq[a]++;
  }

  int ans = m;
  vector<int> dp(m + 1, m + 1);
  vector<int> dp_freq(m + 2, 0);
  dp_freq[m + 1] = n;

  for (int mn = m, mx = m + 1; mn >= 1; mn--) {
    for (int a = mn; a <= m; a += mn) {
      int ndp = a == mn ? mn : a / mn >= mn ? dp[a / mn] : m + 1;
      if (ndp < dp[a]) {
        dp_freq[dp[a]] -= a_freq[a];
        dp[a] = ndp;
        dp_freq[dp[a]] += a_freq[a];
      }
    }

    while (dp_freq[mx] == 0) mx--;

    if (mx <= m) ans = min(ans, mx - mn);
  }

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