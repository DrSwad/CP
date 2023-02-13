#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<int> row;
typedef vector<row> matrix;
const int MOD = 1e9 + 7;
const int K = 10;
const int C = 10;
const int LOGN = 54;

int choose[K + 1][K + 1];
void init() {
  for (int n = 0; n <= K; n++) {
    choose[n][0] = choose[n][n] = 1;
    for (int k = 1; k < n; k++) {
      choose[n][k] = (choose[n - 1][k] + choose[n - 1][k - 1]) % MOD;
    }
  }
}

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

matrix A[K + 1][LOGN], b[K + 1];

void init_matrix() {
  for (int k = 1; k <= K; k++) {
    int dim = (k + 1) * (k + 1) + C * C;
    b[k] = matrix(dim, row(1, 0));
    matrix &M = A[k][0];
    M = matrix(dim, row(dim, 0));
    for (int x = 0; x <= k; x++) {
      for (int y = 0; y <= k - x; y++) {
        int row = x * (k + 1) + y;
        for (int i = 0; i <= x; i++) {
          int col = (i + y) * (k + 1) + (x - i);
          M[row][col] = choose[x][i];
        }
        b[k][row][0] = y == 0;
      }
    }

    int OFFSET = (k + 1) * (k + 1);

    for (int c = 1; c <= C; c++) {
      for (int x = 0; x < C; x++) {
        int row = (c - 1) * C + x;

        if (x != 0) {
          int col = (c - 1) * C + (x - 1);
          M[OFFSET + row][OFFSET + col] = 1;
        }
        else {
          int col = (c - 1) * C + (c - 1);
          M[OFFSET + row][OFFSET + col] = 1;

          {
            int x = k;
            int y = 0;
            for (int i = 0; i <= x; i++) {
              int col = (i + y) * (k + 1) + (x - i);
              M[OFFSET + row][col] = choose[x][i];
            }
          }
        }

        b[k][OFFSET + row][0] = x == 0;
      }
    }

    for (int b = 1; b < LOGN; b++) {
      A[k][b] = A[k][b - 1] * A[k][b - 1];
    }
  }
}

void test_case() {
  ll n;
  int c, k;
  cin >> n >> c >> k;
  if (n == 0) {
    cout << "0\n";
    return;
  }

  ll e = n * c - 1;
  matrix R = b[k];
  for (int b = 0; b < LOGN; b++) {
    if (e >> b & 1) {
      R = A[k][b] * R;
    }
  }
  int OFFSET = (k + 1) * (k + 1);
  cout << R[OFFSET + (c - 1) * C][0] << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  init();
  init_matrix();

  int t = 1;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    cout << "Case " << cs << ": ";
    test_case();
  }

  return 0;
}