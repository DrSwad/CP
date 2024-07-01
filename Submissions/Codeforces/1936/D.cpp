#include <bits/stdc++.h>
using namespace std;

const int max_a = 1e9;
const int bits = 30;

template<typename T, typename AssociativeOperation>
struct segment_tree {
  int SZ;
  T identity;
  AssociativeOperation TT;
  std::vector<T> data;

  segment_tree() {}

  segment_tree(int _SZ, T _identity, AssociativeOperation _TT)
    : SZ(_SZ), identity(_identity), TT(_TT) {
    data.resize(2 * SZ, identity);
  }

  // Returns the value at index i
  const T&operator[](int i) const {
    assert(0 <= i && i < SZ);
    return data[SZ + i];
  }

  // Assigns fn(i) at index i for each i in [0, SZ)
  template<typename Function>
  void assign(Function fn) {
    for (int i = 0; i < SZ; i++) data[SZ + i] = fn(i);
    for (int i = SZ - 1; i; i--) data[i] = TT(data[2 * i], data[2 * i + 1]);
  }

  // Assigns v at index i
  void assign(int i, T v) {
    assert(0 <= i && i < SZ);
    data[i += SZ] = v;
    for (i /= 2; i; i /= 2) data[i] = TT(data[2 * i], data[2 * i + 1]);
  }

  // Returns the result of a left fold of the elements at indices in [first, last) over TT
  T accumulate(int first, int last) const {
    assert(0 <= first && last <= SZ);
    T left = identity, right = identity;
    for (first += SZ, last += SZ; first < last; first /= 2, last /= 2) {
      if (first & 1) left  = TT(left, data[first++]);
      if (last  & 1) right = TT(data[--last], right);
    }
    return TT(left, right);
  }
};

void test_case() {
  int n, v;
  cin >> n >> v;

  vector<int> a(n), b(n);
  for (int &i : a) cin >> i;
  for (int &i : b) cin >> i;

  int q;
  cin >> q;

  vector st(
    bits,
    segment_tree{n, max_a + 1, [&](int i, int j) { return min(i, j); }});

  for (int i = 0; i < bits; i++) {
    for (int j = 0; j < n; j++) {
      if (b[j] >> i & 1) {
        st[i].assign(j, a[j]);
      }
    }
  }

  while (q--) {
    int type;
    cin >> type;

    if (type == 1) {
      int i, x;
      cin >> i >> x;
      i--;

      for (int j = 0; j < bits; j++) {
        if (b[i] >> j & 1) {
          st[j].assign(i, max_a + 1);
        }
      }

      b[i] = x;

      for (int j = 0; j < bits; j++) {
        if (b[i] >> j & 1) {
          st[j].assign(i, a[i]);
        }
      }
    }
    else {
      int l, r;
      cin >> l >> r;
      l--;

      int pref = 0;
      int ans = max_a + 1;

      for (int i = bits - 1; i >= 0; i--) {
        int cur = st[i].accumulate(l, r);
        debug(i, cur);
        if (v >> i & 1) pref = max(pref, cur);
        else ans = min(ans, max(pref, cur));
      }

      ans = min(ans, pref);

      cout << (ans <= max_a ? ans : -1);
      if (q) cout << " ";
    }
  }

  cout << "\n";
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