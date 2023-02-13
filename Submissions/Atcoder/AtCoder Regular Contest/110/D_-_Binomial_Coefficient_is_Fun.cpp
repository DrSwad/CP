#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, m;
  cin >> n >> m;
  m += n;

  int s = n;
  while (n--) {
    int a;
    cin >> a;
    s += a;
  }

  if (m < s) cout << "0\n";
  else {
    long long ans = 1;
    vector<long long> inv(s + 1);
    inv[1] = 1;
    for (int i = 1; i <= s; i++) {
      if (i > 1) inv[i] = 1ll * (MOD - MOD / i) * inv[MOD % i] % MOD;
      (ans *= inv[i]) %= MOD;
      (ans *= m - (i - 1)) %= MOD;
    }
    cout << ans << "\n";
  }

  return 0;
}