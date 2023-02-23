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
  gp_hash_table<int, long long, chash> mp;

  int n;
  cin >> n;

  long long ans = 0;

  while (n--) {
    int a;
    cin >> a;

    for (int i = 2; 1ll * i * i <= a; i++) {
      if (a % i == 0) {
        mp[i] += a;
        if (mp[i] > ans) ans = mp[i];
        int j = a / i;
        if (j != i and j != 1) {
          mp[j] += a;
          if (mp[j] > ans) ans = mp[j];
        }
      }
    }

    if (a != 1) {
      mp[a] += a;
      if (mp[a] > ans) ans = mp[a];
    }
  }

  cout << ans << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t = 1;
  // cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    // cout << "Case " << cs << ": ";
    test_case();
  }

  return 0;
}