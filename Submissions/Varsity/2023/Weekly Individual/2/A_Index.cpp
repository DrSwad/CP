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
  return (ll)a * b % MOD;
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
  cin >> n;

  ll k;
  cin >> k;

  vector<int> a(n);
  for (int &i : a) cin >> i;

  vector<int> c(n);
  for (int &i : c) cin >> i;

  int p, q, r;
  cin >> p >> q >> r;

  if (k < n) {
    cout << a[k] << "\n";
    return 0;
  }

  matrix base(n + 3, row(1));
  for (int i = 0; i < n; i++) base[i][0] = a[i];
  base[n + 0][0] = 1;
  base[n + 1][0] = n;
  base[n + 2][0] = n * n;

  matrix A(n + 3, row(n + 3, 0));
  for (int i = 0; i < n - 1; i++) {
    A[i][i + 1] = 1;
  }
  for (int j = 0; j < n; j++) {
    A[n - 1][j] = c[n - 1 - j];
  }
  A[n - 1][n + 0] = p;
  A[n - 1][n + 1] = q;
  A[n - 1][n + 2] = r;

  A[n + 0][n + 0] = 1;

  A[n + 1][n + 0] = 1;
  A[n + 1][n + 1] = 1;

  A[n + 2][n + 0] = 1;
  A[n + 2][n + 1] = 2;
  A[n + 2][n + 2] = 1;

  base = (A ^ (k - (n - 1))) * base;
  cout << base[n - 1][0] << "\n";

  return 0;
}