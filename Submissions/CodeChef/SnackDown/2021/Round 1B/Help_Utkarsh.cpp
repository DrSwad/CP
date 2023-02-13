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

void test_case() {}

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