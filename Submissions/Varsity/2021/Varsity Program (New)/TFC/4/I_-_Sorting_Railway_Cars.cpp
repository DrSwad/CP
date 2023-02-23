#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;

  vector<int> a(n), p(n);
  for (int i = 0; i < n; i++) {
    cin >> a[i], a[i]--;
    p[a[i]] = i;
  }

  vector<int> dp(n, 1);
  for (int i = n - 2; i >= 0; i--) {
    if (p[i + 1] > p[i]) dp[i] += dp[i + 1];
  }

  cout << n - *max_element(dp.begin(), dp.end()) << "\n";

  return 0;
}