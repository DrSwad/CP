#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;

  vector<int> a(n);
  for (int &i : a) cin >> i;

  int mx = *max_element(a.begin(), a.end());
  int logn = 32 - __builtin_clz(mx);

  vector<int> dp(1 << logn, 0);
  for (int i : a) dp[i] = i;

  for (int i = 0; i < logn; i++) {
    for (int mask = (1 << logn) - 1; mask >= 0; mask--) {
      if (mask >> i & 1) dp[mask] = max(dp[mask], dp[mask ^ 1 << i]);
    }
  }

  for (int i = 0; i < n; i++) {
    if (i) cout << " ";
    int ia = ((1 << logn) - 1) ^ a[i];
    cout << (dp[ia] ? dp[ia] : -1);
  }
  cout << "\n";

  return 0;
}