#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  const int A = 24;

  vector<int> dp(1 << A, 0);

  int n;
  cin >> n;
  while (n--) {
    string s;
    cin >> s;

    sort(s.begin(), s.end());
    s.resize(unique(s.begin(), s.end()) - s.begin());

    int a = s.length() >= 1 ? 1 << (s[0] - 'a') : -1;
    int b = s.length() >= 2 ? 1 << (s[1] - 'a') : -1;
    int c = s.length() >= 3 ? 1 << (s[2] - 'a') : -1;

    if (a != -1) dp[a] += 1;
    if (b != -1) dp[b] += 1;
    if (c != -1) dp[c] += 1;
    if (b != -1) dp[a + b] -= 1;
    if (c != -1) dp[b + c] -= 1;
    if (c != -1) dp[c + a] -= 1;
    if (c != -1) dp[a + b + c] += 1;
  }

  for (int i = 0; i < A; i++) {
    for (int mask = (1 << A) - 1; mask >= 0; mask--) {
      if (mask >> i & 1) dp[mask] += dp[mask ^ 1 << i];
    }
  }

  int ans = 0;
  for (int mask = 0; mask < 1 << A; mask++) {
    ans ^= dp[mask] * dp[mask];
  }

  cout << ans << "\n";

  return 0;
}