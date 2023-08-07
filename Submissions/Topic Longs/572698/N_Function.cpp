#include <bits/stdc++.h>
using namespace std;

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

const int mod = 998244353;
const int max_mul = 20210926;

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

  int n;
  cin >> n;

  gp_hash_table<int, int, chash> dp;

  function<int(int)> DP =
    [&](int n) {
      if (dp.find(n) != dp.end()) return dp[n];
      for (int l = 2; l <= min(n, max_mul); ) {
        int d = n / l;
        int r = min(n / d, max_mul);
        dp[n] = add(dp[n], mul(r - (l - 1), DP(d)));
        l = r + 1;
      }
      return ++dp[n];
    };

  cout << DP(n) << "\n";

  return 0;
}