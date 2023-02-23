#include <bits/stdc++.h>
using namespace std;

const int LOGK = 30;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, k;
  cin >> n >> k;
  cin.ignore();

  vector<bool> a(n);
  for (int i = 0; i < n; i++) {
    char c;
    cin >> c;
    a[i] = c - '0';
  }

  vector<int> dp(n, 0);

  for (int i = 0; i < n; i++) {
    if (a[i]) dp[i] ^= 1;
    for (int j = 0; j < LOGK; j++) {
      if (dp[i] >> j & 1) dp[i] ^= 1 << (j + 1);
      if ((k >> j & 1) and (i - (1 << j) >= 0) and (dp[i - (1 << j)] >> j & 1)) {
        dp[i] ^= 1 << (j + 1);
      }
    }
  }

  for (int i = 0; i < n; i++) {
    cout << (dp[i] >> LOGK & 1);
  }
  cout << "\n";

  return 0;
}