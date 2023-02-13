#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int MOD = 1e9 + 7;
typedef vector<int> row;
typedef vector<row> matrix;
inline int add(const int &a, const int &b) {
  int c = a + b;
  if (c >= MOD) c -= MOD;
  return c;
}
inline int mult(const int &a, const int &b) {
  return (long long)a * b % MOD;
}
matrix operator+(const matrix &m1, const matrix &m2) {
  int r = m1.size();
  int c = m1.back().size();
  matrix ret(r, row(c));
  for (int i = 0; i < r; i++) {
    for (int j = 0; j < c; j++) {
      ret[i][j] = add(m1[i][j], m2[i][j]);
    }
  }
  return ret;
}
matrix operator*(const matrix &m1, const int m2) {
  int r = m1.size();
  int c = m1.back().size();
  matrix ret(r, row(c));
  for (int i = 0; i < r; i++) {
    for (int j = 0; j < c; j++) {
      ret[i][j] = mult(m1[i][j], m2);
    }
  }
  return ret;
}
matrix operator*(const matrix &m1, const matrix &m2) {
  int r = m1.size();
  int m = m1.back().size();
  int c = m2.back().size();
  matrix ret(r, row(c, 0));
  for (int i = 0; i < r; i++) {
    for (int k = 0; k < m; k++) {
      for (int j = 0; j < c; j++) {
        ret[i][j] = add(ret[i][j], mult(m1[i][k], m2[k][j]));
      }
    }
  }
  return ret;
}
matrix one(int dim) {
  matrix ret(dim, row(dim, 0));
  for (int i = 0; i < dim; i++) {
    ret[i][i] = 1;
  }
  return ret;
}
matrix operator^(const matrix &m, const ll &e) {
  if (e == 0) return one(m.size());
  matrix sqrtm = m ^ (e / 2);
  matrix ret = sqrtm * sqrtm;
  if (e & 1) ret = ret * m;
  return ret;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  ll k;
  cin >> n >> k;

  vector<int> a(n);
  for (int &i : a) cin >> i;

  matrix mul(3, row(3, 0));
  for (int rem = 0; rem < 3; rem++) {
    for (int i = 0; i < n; i++) {
      if (a[i] ^ rem % 3 == 0) {
        mul[__builtin_popcount(a[i]) % 3][rem]++;
      }
    }
  }

  matrix base(3, row(1, 0));
  for (int i = 0; i < n; i++) {
    base[__builtin_popcount(a[i]) % 3][0]++;
  }
  debug(base);

  matrix res = (mul ^ (k - 1)) * base;
  debug(res);
  ll ans = 0;
  for (int i = 0; i < 3; i++) {
    (ans += res[i][0]) %= MOD;
  }

  cout << ans << "\n";

  return 0;
}