#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 60;

ll div_mask[N];
ll mul_mask[N];

bool verify(int n, ll mask) {
  for (int i = 1; i <= n; i++) {
    if (!(mask >> (i - 1) & 1)) continue;
    for (int j = 2 * i; j <= n; j += i) {
      if (!(mask >> (j - 1) & 1)) continue;
      for (int k = 2 * j; k <= n; k += j) {
        if (mask >> (k - 1) & 1) return false;
      }
    }
  }
  return true;
}

ll brute(int n) {
  ll ans = 0;
  for (ll mask = 0; mask < 1ll << n; mask++) {
    ans += verify(n, mask);
  }
  return ans;
}

void init() {
  for (int d = 1; d <= N; d++) {
    for (int m = 2 * d; m <= N; m += d) {
      div_mask[m - 1] |= 1ll << (d - 1);
      mul_mask[d - 1] |= 1ll << (m - 1);
    }
  }
}

ll solve(int n) {
  int nn = n / 2;
  ll big_full = (1ll << n) - (1ll << nn);
  ll ans = 0;

  for (ll mask = 0; mask < (1ll << nn); mask++) {
    ll nmask = mask;
    ll big_mask = 0;

    while (nmask) {
      int lsb = __builtin_ctz(nmask);
      nmask &= (nmask - 1);

      if (mask & div_mask[lsb]) {
        big_mask |= mul_mask[lsb];
        if (big_mask & mask) break;
      }
    }

    if (big_mask & mask) continue;
    int bad = __builtin_popcountll(big_full & big_mask);
    ans += 1ll << (n - nn - bad);
  }

  return ans;
}

int main() {
  // ios::sync_with_stdio(false);
  // cin.tie(nullptr);

  init();

  for (int n = 1; n <= N; n++) {
    cerr << n << endl;
    // cout << brute(n) << " " << solve(n) << "\n";
    cout << solve(n) << "\n";
  }

  return 0;
}