#include <bits/stdc++.h>
using namespace std;

typedef unsigned long long ull;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, l, r;
  cin >> n >> l >> r;

  if (n == 1) {
    cout << (r - (l - 1)) << "\n";
    return 0;
  }

  vector<int> roots(r + 1);
  roots[0] = 0;
  for (int root = 1, at = 1; at <= r; root++) {
    int nxt = root + 1;
    for (int i = 0; i < n - 2; i++) {
      nxt = min((long long)r + 1, 1ll * nxt * (root + 1));
    }
    while (at < nxt) {
      roots[at++] = root;
    }
  }

  vector<ull> dp(r + 1, 0);

  for (int a = 1; a <= r; a++) {
    int L = roots[(l - 1) / a] + 1;
    int R = roots[r / a];
    if (L > R) continue;

    for (int g = 1; g <= R; g++) {
      ull len = R / g - (L - 1) / g;
      dp[g] += len * (len - 1) / 2;
    }
  }

  for (int g = r; g >= 1; g--) {
    for (int mul = 2 * g; mul <= r; mul += g) {
      dp[g] -= dp[mul];
    }
  }

  cout << dp[1] * 2 << "\n";

  return 0;
}