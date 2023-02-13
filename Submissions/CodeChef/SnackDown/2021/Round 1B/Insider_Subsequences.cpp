#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt") // use avx for older judges
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
    for (int i = 0, sz = con.size(); i < sz; i++) {
      cout << (i ? " " : "") << con[i];
    }
    return os;
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

const int BLOCK = 1000;

#define up 0
#define down 1

class Block {
private:
  int n;
  vector<int> a, na;
  vector<pair<int, int>> ans[2];
public:
  Block(vector<int> a) : a(a), n(a.size()) {
    na.reserve(2 * n + 1);
    na.push_back(1);
    for (int i : a) {
      na.push_back(i);
      na.push_back(i + 1);
    }
    sort(na.begin(), na.end());
    na.resize(unique(na.begin(), na.end()) - na.begin());
    int nn = na.size();

    for (int dir = 0; dir < 2; dir++) {
      ans[dir].resize(nn);
      for (int i = 0; i < nn; i++) {
        int cdir = dir;
        int val = na[i];
        int took = 0;
        for (int j = 0; j < n; j++) {
          if ((a[j] > val and cdir == up) or (a[j] < val and cdir == down)) {
            took++;
            cdir ^= 1;
          }
        }
        ans[dir][i] = make_pair(took, cdir);
      }
    }
  }
  pair<int, int> query(int val, int dir) const {
    int low = upper_bound(na.begin(), na.end(), val) - na.begin();
    low--;
    assert(low >= 0);
    return ans[dir][low];
  }
};

void test_case() {
  int n;
  cin >> n;
  vector<int> a(n);
  cin >> a;

  vector<Block> blocks;
  for (int i = 0; i < n; i += BLOCK) {
    blocks.push_back({vector<int>(a.begin() + i, a.begin() + min(i + BLOCK, n))});
  }

  vector<int> na;
  na.reserve(2 * n);
  for (int i : a) {
    na.push_back(i);
    na.push_back(i + 1);
  }
  sort(na.begin(), na.end());
  na.resize(unique(na.begin(), na.end()) - na.begin());

  vector<vector<int>> ans(2, vector<int>(n - 1, -1));
  for (int i = 0; i < na.size(); i++) {
    int val = na[i];
    int mx_took = 0;

    for (int dir = 0; dir < 2; dir++) {
      int took = 0;
      int cdir = dir;
      for (const Block&block : blocks) {
        auto [ntook, ndir] = block.query(val, cdir);
        took += ntook;
        cdir = ndir;
      }
      mx_took = max(mx_took, took);
    }

    if (mx_took > 1) {
      assert(mx_took <= n);

      int cans = val;
      int &ans0 = ans[0][mx_took - 2];
      ans0 = ans0 == -1 ? cans : min(ans0, cans);

      assert(i < (int)na.size() - 1);
      cans = na[i + 1] - 1;
      int &ans1 = ans[1][mx_took - 2];
      ans1 = ans1 == -1 ? cans : max(ans1, cans);
    }
  }

  for (int i = n - 2, mx = -1, mn = -1; i >= 0; i--) {
    if (ans[1][i] != -1) mx = mx == -1 ? ans[1][i] : max(mx, ans[1][i]);
    if (ans[0][i] != -1) mn = mn == -1 ? ans[0][i] : min(mn, ans[0][i]);
    ans[1][i] = mx;
    ans[0][i] = mn;
  }

  cout << ans[0] << "\n" << ans[1] << "\n";
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