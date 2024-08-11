#include <bits/stdc++.h>
using namespace std;

const int mod = 998244353;

int add(int a, int b) {
  int c = a + b;
  return c < mod ? c : c - mod;
}

template<class T>
class BIT {
public:
  int n;
  vector<T> f;
  BIT(int n) : n(n) {
    f.resize(n + 1, (T)0);
  }
  void update(int p, T v) {
    while (p <= n) f[p] = add(f[p], v), p += p & -p;
  }
  T pref(int p) {
    T ret = 0;
    while (p) ret = add(ret, f[p]), p -= p & -p;
    return ret;
  }
  T range(int l, int r) {
    return pref(r) - pref(l - 1);
  }
};

void test_case() {
  int n;
  cin >> n;

  vector<int> a(n + 1);
  for (int i = 1; i <= n; i++) cin >> a[i];

  vector<int> left_small(n + 1), right_small(n + 1);
  for (int i = 1; i <= n; i++) {
    left_small[i] = i - 1;
    while (left_small[i] and a[left_small[i]] > a[i]) {
      left_small[i] = left_small[left_small[i]];
    }
  }
  for (int i = n; i >= 1; i--) {
    right_small[i] = i + 1;
    while (right_small[i] <= n and a[right_small[i]] > a[i]) {
      right_small[i] = right_small[right_small[i]];
    }
  }

  vector<int> dp(n + 1, 0);
  BIT<int> bit(n + 1);
  bit.update(1, 1);

  for (int i = 1; i <= n; i++) {
    dp[i] = add(bit.pref(n + 1), mod - bit.pref(left_small[i]));
    bit.update(right_small[i], dp[i]);
  }

  int ans = 0;
  for (int i = n, mn = a[i]; i >= 1; i--) {
    mn = min(mn, a[i]);
    if (mn == a[i]) {
      ans = add(ans, dp[i]);
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