#include <bits/stdc++.h>
using namespace std;

// Returns number of multiples of at least one of the given primes in [1, n]
int prime_multiples(int n, vector<int> primes) {
  int sz = primes.size();
  int ret = 0;
  for (int mask = 1; mask < 1 << sz; mask++) {
    int mul = 1;
    for (int i = 0; i < sz; i++) {
      if (mask >> i & 1) {
        mul *= primes[i];
      }
    }
    ret += n / mul * (__builtin_popcount(mask) & 1 ? 1 : -1);
  }
  return ret;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int d;
  cin >> d;

  int l_x, r_x;
  cin >> l_x >> r_x;

  int l_y, r_y;
  cin >> l_y >> r_y;

  vector<int> divs, primes;
  {
    int D = d;
    for (int div = 1; div * div <= d; div++) {
      if (d % div == 0) {
        divs.push_back(div);
        if (div * div != d) divs.push_back(d / div);
      }
      if (div > 1 and D % div == 0) {
        primes.push_back(div);
        while (D % div == 0) D /= div;
      }
    }
    if (D > 1) primes.push_back(D);
  }

  long long ans = 0;

  for (int gx : divs) {
    int dx = gx, dy = d / gx;

    int cnt_x = r_x / dx - (l_x - 1) / dx, cnt_y = r_y / dy - (l_y - 1) / dy;

    vector<int> nprimes;
    for (int p : primes) {
      if (d / dx % p == 0) nprimes.push_back(p);
    }

    cnt_x -= prime_multiples(r_x / dx, nprimes) - prime_multiples((l_x - 1) / dx, nprimes);

    ans += 1ll * cnt_x * cnt_y;
  }

  cout << ans << "\n";

  return 0;
}