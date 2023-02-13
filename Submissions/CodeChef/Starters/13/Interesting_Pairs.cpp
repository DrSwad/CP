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

void test_case() {
  int n;
  cin >> n;

  vector<int> a(n);
  for (int &i : a) cin >> i;

  vector<pair<int, int>> c;
  for (int i = 1; i <= n; i++) {
    int j = a[i - 1];
    int g = gcd(i, j);
    c.push_back({i / g, j / g});
  }

  long long ans = 0;

  gp_hash_table<int, int, chash> dp[n + 1];
  for (auto [div, mul] : c) {
    vector<int> divs;
    for (int i = 1; i * i <= mul; i++) {
      if (mul % i == 0) divs.push_back(i);
    }
    for (int i = 0; i < (int)divs.size(); i++) {
      int d = divs[i];
      if ((long long)d * d < mul) {
        divs.push_back(mul / d);
      }
    }

    for (int i : divs) {
      ans += dp[div][i];
    }

    for (int i : divs) {
      if (i <= n) {
        dp[i][div]++;
      }
    }
  }

  cout << ans << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int t = 1;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    // cout << "Case " << cs << ": ";
    test_case();
  }

  return 0;
}