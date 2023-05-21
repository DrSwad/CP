#include <bits/stdc++.h>
using namespace std;

template<class T>
class BIT {
public:
  int n;
  vector<T> f;
  BIT(int n) : n(n) {
    f.resize(n + 1, (T)0);
  }
  void update(int p, T v) {
    p++;
    while (p <= n) f[p] += v, p += p & -p;
  }
  T pref(int p) {
    p++;
    T ret = 0;
    while (p) ret += f[p], p -= p & -p;
    return ret;
  }
  T range(int l, int r) {
    return pref(r) - pref(l - 1);
  }
};

void test_case() {
  int n;
  cin >> n;

  vector<int> a(n);
  for (int &i : a) cin >> i;

  {
    vector<int> sa = a;
    sort(sa.begin(), sa.end());
    for (int &i : a) {
      i = lower_bound(sa.begin(), sa.end(), i) - sa.begin();
    }
  }

  vector<int> ia(n);
  for (int i = 0; i < n; i++) {
    ia[a[i]] = i;
  }

  BIT<int> bit(n);

  auto equal_range = [&](int at) {
    assert(0 <= at and at < n);
    int val = bit.range(at, at);
    int pref_at = bit.pref(at);

    int l = -1;
    if (pref_at != val * (at + 1)) {
      l = 0;
      int pref_l = 0;
      for (int i = 19; i >= 0; i--) {
        int nl = l + (1 << i);
        if (nl >= at) continue;
        int pref_nl = pref_l + bit.f[nl];
        if (pref_at - pref_nl != val * (at + 1 - nl)) l = nl, pref_l = pref_nl;
      }
    }
    l += 2;

    int r = 0, pref_r = 0;
    for (int i = 19; i >= 0; i--) {
      int nr = r + (1 << i);
      if (nr > n) continue;
      int pref_nr = pref_r + bit.f[nr];
      if (nr < at + 1 or pref_nr - pref_at == val * (nr - at - 1)) r = nr, pref_r = pref_nr;
    }

    return make_pair(l - 1, r - 1);
  };

  long long ans = 0;
  for (int l = 1, r = n - 1; l <= n - 1; l++, r--) {
    ans += 1ll * l * r;
  }

  for (int i = 0; i < n; i++) {
    int at = ia[i];
    bit.update(at, 1);
    auto [l0, r0] = equal_range(at);
    if (r0 == n - 1) continue;
    auto [l1, r1] = equal_range(r0 + 1);
    ans -= 1ll * (at - l0 + 1) * (r1 - l1 + 1);
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

// 2 1 4 3
// [2 1] -> 1
// [1 4] -> 0
// [4 3] -> 1
// [2 1 4] -> 1
// [1 4 3] -> 1
// [2 1 4 3] -> 2