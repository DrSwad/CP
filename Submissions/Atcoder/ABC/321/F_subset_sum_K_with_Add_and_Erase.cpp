#include <bits/stdc++.h>
using namespace std;

const int mod = 998244353;

int add(int a, int b) {
  int c = a + b;
  return c < mod ? c : c - mod;
}

int mul(int a, int b) {
  return 1ll * a * b % mod;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int q, k;
  cin >> q >> k;

  vector<int> dp(k + 1, 0);
  dp[0] = 1;

  while (q--) {
    char type;
    cin >> type;

    int x;
    cin >> x;

    if (type == '+') {
      for (int i = k; i >= x; i--) {
        dp[i] = add(dp[i], dp[i - x]);
      }
    }
    else {
      for (int i = x; i <= k; i++) {
        dp[i] = add(dp[i], mod - dp[i - x]);
      }
    }

    cout << dp[k] << "\n";
  }

  return 0;
}