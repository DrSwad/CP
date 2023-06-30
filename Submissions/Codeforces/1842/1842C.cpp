#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n;
  cin >> n;

  vector<int> a(n);
  for (int &i : a) cin >> i, i--;

  vector<int> color_dp(n, -1);
  vector<int> pos_dp(n);

  pos_dp[n - 1] = 0;
  color_dp[a[n - 1]] = n;

  for (int i = n - 2; i >= 0; i--) {
    pos_dp[i] = pos_dp[i + 1];
    if (color_dp[a[i]] != -1) {
      pos_dp[i] = max(pos_dp[i], color_dp[a[i]] - i);
    }

    color_dp[a[i]] = max(color_dp[a[i]], (i + 1) + pos_dp[i + 1]);
  }

  cout << pos_dp[0] << "\n";
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