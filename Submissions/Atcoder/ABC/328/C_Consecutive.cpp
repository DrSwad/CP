#include <bits/stdc++.h>
using namespace std;

template<class T>
class BIT {
public:
  int n;
  vector<T> f;
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
  T pref(int p) {
    T ret = 0;
    while (p) ret += f[p], p -= p & -p;
    return ret;
  }
  T range(int l, int r) {
    return pref(r) - pref(l - 1);
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, q;
  cin >> n >> q;

  string s;
  cin >> s;

  vector<int> a(n - 1);
  for (int i = 0; i < n - 1; i++) {
    a[i] = s[i] == s[i + 1];
  }

  BIT bit(a);
  while (q--) {
    int l, r;
    cin >> l >> r;
    cout << bit.range(l, r - 1) << "\n";
  }

  return 0;
}