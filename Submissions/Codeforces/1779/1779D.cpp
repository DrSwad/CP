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
  int n;
  cin >> n;

  vector<int> a(n);
  for (int &i : a) cin >> i;

  vector<int> b(n);
  for (int &i : b) cin >> i;

  int m;
  cin >> m;

  map<int, int> sz_freq;
  while (m--) {
    int sz;
    cin >> sz;
    sz_freq[sz]++;
  }

  map<int, vector<int>> sz_cut_at_pos;
  BIT<int> bit(n);

  for (int i = 0; i < n; i++) {
    if (b[i] > a[i]) {
      cout << "NO\n";
      return;
    }
    else {
      sz_cut_at_pos[-b[i]].push_back(i);
    }
  }

  for (auto [_sz, pos_v] : sz_cut_at_pos) {
    int sz = -_sz;
    int prv = -1;
    for (int pos : pos_v) {
      if (a[pos] > b[pos]) {
        if (prv == -1 or bit.range(prv + 2, pos + 1) > 0) {
          if (sz_freq[sz] == 0) {
            cout << "NO\n";
            return;
          }
          sz_freq[sz]--;
        }
        prv = pos;
      }
    }
    for (int pos : pos_v) {
      bit.update(pos + 1, 1);
    }
  }

  cout << "YES\n";
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