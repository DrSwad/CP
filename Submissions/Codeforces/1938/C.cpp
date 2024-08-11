#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

void test_case() {
  int n;
  cin >> n;

  vector<int> a(n);
  for (int &i : a) cin >> i;

  if (n == 1) {
    cout << (1ll << a[0]) - 1 << "\n";
    return;
  }

  int fixed_bits = 0;
  ll fixed_val = 0;

  for (int i = 1; i < n; i++) {
    int d = a[i] - a[i - 1];

    if (fixed_val < (1ll << fixed_bits) - 1) {
      fixed_val++;
      if (__builtin_popcountll(fixed_val) - __builtin_popcountll(fixed_val - 1) != d) {
        cout << "-1\n";
        return;
      }
    }
    else {
      if (d > -fixed_bits + 1) {
        cout << "-1\n";
        return;
      }
      fixed_bits = 2 - d;
      fixed_val = 1ll << (fixed_bits - 1);
    }
  }

  ll fixed_a0 = fixed_val - (n - 1);
  if (__builtin_popcountll(fixed_a0) > a[0]) {
    cout << "-1\n";
    return;
  }

  while (__builtin_popcountll(fixed_a0) < a[0]) {
    int tot_bits = 64 - __builtin_clzll(fixed_a0);
    int set_bit = max(tot_bits, fixed_bits);
    fixed_a0 |= 1ll << set_bit;
  }

  cout << fixed_a0 << "\n";
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