#include <bits/stdc++.h>
using namespace std;

// 1 1 2 3 5 8
// 1 1 2 3 5

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
matrix operator^(const matrix &m, const int &e) {
  if (e == 0) return one(m.size());
  matrix sqrtm = m ^ (e / 2);
  matrix ret = sqrtm * sqrtm;
  if (e & 1) ret = ret * m;
  return ret;
}

void test_case() {
  int n, m;
  cin >> n >> m;

  matrix mat(m, row(m, 0));
  for (int i = 0; i < m; i++) mat[0][i] = 1;
  for (int i = 1; i < m; i++) mat[i][i - 1] = 1;

  matrix base(m, row(1, 0));
  base[0][0] = 1;

  cout << (mat ^ (n + 1))[0][0] << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t = 1;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    cout << "Case #" << cs << ": ";
    test_case();
  }

  return 0;
}