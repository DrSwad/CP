#include <bits/stdc++.h>
using namespace std;

namespace IO {
  #define output_op(...) ostream &operator<<(ostream &os, const __VA_ARGS__&u)
  #define input_op(...) istream &operator>>(istream & is, __VA_ARGS__ & u)

  // Pairs
  template<class U, class V> output_op(pair<U, V>) {
    return os << u.first << " " << u.second;
  }
  template<class U, class V> input_op(pair<U, V>) {
    return is >> u.first >> u.second;
  }

  // Vectors, sets, maps, etc
  #define iterable(stream) \
  template<class Con, class = decltype(begin(declval<Con>()))> \
  typename enable_if<!is_same<Con, string>::value, stream&>::type
  iterable(ostream) operator<<(ostream & os, const Con&con) {
    char s = 0; for (auto &x : con) os << s << x, s = ' '; return os;
  }
  iterable(istream) operator>>(istream & is, Con & con) {
    for (auto &x : con) is >> x; return is;
  }

  // Tuples
  template<size_t i, class T> ostream&output_tuple_utils(ostream&os, const T&tup) {
    if constexpr (i == tuple_size<T>::value) return os;
    else return output_tuple_utils<i + 1, T>(os << (i ? " " : "") << get<i>(tup), tup);
  }
  template<class ... U> output_op(tuple<U...>) {
    return output_tuple_utils<0, tuple<U...>>(os, u);
  }
  template<size_t i, class T> istream&input_tuple_utils(istream&is, T&tup) {
    if constexpr (i == tuple_size<T>::value) return is;
    else return input_tuple_utils<i + 1, T>(is >> get<i>(tup), tup);
  }
  template<class ... U> input_op(tuple<U...>) {
    return input_tuple_utils<0, tuple<U...>>(is, u);
  }

  void setup_io() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(15);
    cerr << fixed << setprecision(7);
  }

  #undef output_op
  #undef input_op
  #undef iterable
}
using namespace IO;

template<typename T>
int compress(vector<T> &a) {
  int n = a.size();
  vector<pair<T, int>> pairs(n);
  for (int i = 0; i < n; ++i) {
    pairs[i] = {a[i], i};
  }
  sort(pairs.begin(), pairs.end());
  int nxt = 0;
  for (int i = 0; i < n; ++i) {
    if (i > 0 && pairs[i - 1].first != pairs[i].first) nxt++;
    a[pairs[i].second] = nxt;
  }
  return nxt + 1;
}

void test_case() {
  int n;
  cin >> n;
  vector<int> a(1 << n);
  cin >> a;

  int mn = *min_element(a.begin(), a.end());
  int mx = *max_element(a.begin(), a.end());
  int sz = compress(a);
  cout << (sz <= 2 and mx - mn <= 1 ? "YES" : "NO") << "\n";
}

int main() {
  setup_io();

  int t = 1;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    // cout << "Case " << cs << ": ";
    test_case();
  }

  return 0;
}