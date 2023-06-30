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

  gp_hash_table<int, int, chash> freq;
  for (int i : a) freq[i]++;

  long long ans = 0;
  const int MX_A = 1e6;
  int mx_a = *max_element(a.begin(), a.end());

  auto check = [&](int j, int b) {
    if (b > 1 and
        a[j] % b == 0 and
        freq.find(a[j] / b) != freq.end() and
        1ll * a[j] * b <= mx_a and
        freq.find(a[j] * b) != freq.end()
        ) {
      int ai = a[j] / b;
      int ak = a[j] * b;
      ans += 1ll * freq[ai] * freq[ak];
    }
  };

  for (int j = 0; j < n; j++) {
    ans += 1ll * (freq[a[j]] - 1) * (freq[a[j]] - 2);

    if (a[j] > MX_A) {
      for (int b = 2; a[j] * b <= mx_a; b++) {
        check(j, b);
      }
    }
    else {
      for (int b = 1; b * b <= a[j]; b++) {
        if (a[j] % b == 0) {
          check(j, b);
          if (b * b != a[j]) check(j, a[j] / b);
        }
      }
    }
  }

  cout << ans << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    test_case();
  }

  return 0;
}