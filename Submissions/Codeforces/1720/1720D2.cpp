#include <bits/stdc++.h>
using namespace std;

const int BITS = 30;
typedef long long ll;

#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
struct chash {
  const int RANDOM = (long long)(make_unique<char>().get())
                     ^ chrono::high_resolution_clock::now()
                     .time_since_epoch()
                     .count();
  static unsigned long long hash_f(unsigned long long x) {
    x += 0x9e3779b97f4a7c15;
    x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
    x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
    return x ^ (x >> 31);
  }
  static unsigned hash_combine(unsigned a, unsigned b) {
    return a * 31 + b;
  }
  int operator()(int x) const { return hash_f(x) ^ RANDOM; }
  int operator()(pair<int, int> x) const {
    return hash_combine(x.first, x.second) ^ RANDOM;
  }
};

void test_case() {
  int n;
  cin >> n;

  vector<int> a(n);
  for (int &i : a) cin >> i;

  gp_hash_table<int, ll, chash> dp[BITS];
  int ans = 0;
  int full = (1 << 30) - 1;
  int nbits = 30;

  for (int i = 0; i < n; i++) {
    int curr = 1;
    for (int j = BITS - 1; j >= 0; j--) {
      int xr = (a[i] >> j) ^ (i >> j);
      int need_xr = xr ^ 1;
      int need_pb = ((a[i] >> j) & 1) ^ 1;

      if (dp[j].find(need_xr) == dp[j].end()) continue;
      ll got = dp[j][need_xr];

      int prv_dp;
      if (need_pb == 0) prv_dp = got & full;
      else prv_dp = got >> nbits;

      curr = max(curr, prv_dp + 1);
    }

    ans = max(ans, curr);

    for (int j = BITS - 1; j >= 0; j--) {
      int xr = (a[i] >> j) ^ (i >> j);
      int pb = (i >> j) & 1;
      if (dp[j].find(xr) == dp[j].end()) dp[j][xr] = 0;

      ll dp_val = dp[j][xr];
      int big = dp_val >> nbits;
      int small = dp_val & full;
      if (pb == 0) small = max(small, curr);
      else big = max(big, curr);
      dp_val = ((ll)big << nbits) + small;
      dp[j][xr] = dp_val;
    }
  }

  cout << ans << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t = 1;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    // cout << "Case " << cs << ": ";
    test_case();
  }

  return 0;
}