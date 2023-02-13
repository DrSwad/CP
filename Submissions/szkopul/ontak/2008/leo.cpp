#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;
const int MOD = 1e9;
const int K = 13;

int C[K + 1][K + 1];
void initC() {
  for (int n = 0; n <= K; n++) {
    C[n][0] = C[n][n] = 1;
    for (int k = 1; k < n; k++) {
      C[n][k] = C[n - 1][k] + C[n - 1][k - 1];
    }
  }
}

typedef vector<int> row;
typedef vector<row> matrix;
inline int add(const int &a, const int &b) {
  int c = a + b;
  if (c < MOD) return c;
  return c - MOD;
}
inline int mult(const int &a, const int &b) {
  ll c = (ll)a * b % MOD;
  if (c < MOD) return c;
  return c % MOD;
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

matrix geometric_sum(matrix m, ull n) {
  int dim = m.size();
  matrix sum = one(dim);
  matrix offset = one(dim);
  matrix ret(dim, row(dim, 0));

  for (int p = 0; n; p++) {
    if (n >> p & 1) {
      ret = ret + sum * offset;
      offset = offset * m;
      n -= 1ull << p;
    }
    sum = sum + sum * m;
    m = m * m;
  }

  return ret;
}

matrix construct_coefficient(int k) {
  int dim = (k + 1) * (k + 2) / 2;
  matrix ret(dim, row(dim, 0));

  for (int r1 = 0, e1 = k, e2 = 0; r1 < dim; r1++) {
    int nk = e1;

    for (int r2 = 0, e3 = k, e4 = 0; r2 < dim; r2++) {
      if (e3 >= e2) {
        int ne3 = e3 - e2;
        if (ne3 + e4 <= e1) {
          ret[r1][r2] = mult(C[e1][ne3], C[e1 - ne3][e4]);
        }
      }

      e4++;
      if (e3 + e4 > k) {
        e3--;
        e4 = 0;
      }
    }

    e2++;
    if (e1 + e2 > k) {
      e1--;
      e2 = 0;
    }
  }

  return ret;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  initC();

  ull n;
  int k;
  cin >> n >> k;

  if (n == 0) {
    cout << "1\n";
    return 0;
  }
  if (n == 1) {
    cout << "2\n";
    return 0;
  }
  if (k == 0) {
    cout << n + 1 << "\n";
    return 0;
  }

  matrix a = construct_coefficient(k);

  string ans = to_string(((geometric_sum(a, n) * matrix((k + 1) * (k + 2) / 2, row(1, 1)))[0][0] + 1) % MOD);
  while (ans.length() < 9) ans = "0" + ans;
  cout << ans << "\n";

  return 0;
}