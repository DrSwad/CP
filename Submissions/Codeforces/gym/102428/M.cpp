#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, x;
  cin >> n >> x;

  vector<int> a(n);
  for (int &i : a) cin >> i;

  vector<int> dp(n);
  dp[n - 1] = 1;
  for (int i = n - 2; i >= 0; i--) {
    dp[i] = 1;
    if (a[i] + x >= a[i + 1]) dp[i] = 1 + dp[i + 1];
  }

  cout << *max_element(dp.begin(), dp.end()) << "\n";

  return 0;
}