#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

template<class T>
class BIT {
public:
  int n;
  vector<T> f;
  BIT(int n) : n(n) {
    f.resize(n + 1, (T)0);
  }
  BIT(const vector<T> &a) { // O(n)
    n = a.size();
    f.assign(n + 1, (T)0);
    for (int i = 1; i <= n; i++) {
      f[i] += a[i - 1];
      if (i + (i & -i) <= n) {
        f[i + (i & -i)] += f[i];
      }
    }
  }
  void update(int p, T v) {
    while (p <= n) f[p] += v, p += p & -p;
  }
  T pref(int p) {
    T ret = 0;
    while (p) ret += f[p], p -= p & -p;
    return ret;
  }
  T range(int l, int r) {
    return pref(r) - pref(l - 1);
  }
};

void test_case() {
  int len;
  cin >> len;

  string s;
  cin >> s;

  int n = len + 1;
  vector<int> p(n);
  p[0] = 0;
  for (int i = 1; i < n; i++) {
    p[i] = p[i - 1] + (s[i - 1] == '(' ? 1 : -1);
  }

  vector<int> r(n);
  r[n - 1] = n;
  for (int i = n - 2; i >= 0; i--) {
    r[i] = i + 1;
    while (r[i] < n and p[r[i]] >= p[i]) r[i] = r[r[i]];
  }

  ll ans = 0;
  ll c = 0;
  for (int i = 0, mn = 0; i < n; i++) {
    mn = min(mn, p[i]);
    c += max(p[0], p[i]) - mn;
  }

  ans = c;
  BIT<int> bit(2 * len + 1);
  int offset = len + 1;
  for (int i = 0; i < n; i++) {
    bit.update(p[i] + offset, 1);
  }

  for (int i = 0; i < n - 1; i++) {
    bit.update(p[i] + offset, -1);
    if (p[i + 1] < p[i]) {
      c = c - bit.pref(p[i] + offset - 1);
    }
    else {
      c = c - (r[i + 1] - (i + 1)) + bit.pref(p[i + 1] + offset - 1);
    }
    ans += c;
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