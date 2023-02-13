#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n;
  cin >> n;

  vector<int> a(n);
  for (int &i : a) cin >> i;

  vector<int> b;
  for (int i = 0; i < n; i++) {
    if (i == 0 or (a[i] != a[i - 1])) b.push_back(a[i]);
  }
  int v = n;
  a = b;
  n = a.size();

  a.push_back(v + 1);
  vector<int> pos_dp(n + 1);
  pos_dp[n] = 0;
  vector<int> val_dp(v + 1, n + 1);

  for (int i = n - 1; i >= 0; i--) {
    pos_dp[i] = 1 + val_dp[a[i]];
    if (a[i + 1] > a[i]) {
      pos_dp[i] = min(pos_dp[i], pos_dp[i + 1]);
      val_dp[a[i]] = min(val_dp[a[i]], pos_dp[i + 1]);
    }
    pos_dp[i] = min(pos_dp[i], n + 1);
  }

  cout << (pos_dp[0] <= n ? pos_dp[0] : -1) << "\n";
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