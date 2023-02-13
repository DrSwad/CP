#include <bits/stdc++.h>
using namespace std;

const int MOD = 998244353;
const int TRIALS = 4;

seed_seq seq{
  (uint64_t)chrono::duration_cast<chrono::nanoseconds>(
    chrono::high_resolution_clock::now().time_since_epoch())
  .count(),
  (uint64_t)__builtin_ia32_rdtsc(),
  (uint64_t)(uintptr_t)make_unique<char>().get()};
mt19937 rng(seq);
uniform_int_distribution<int> uid(1, MOD - 1);
auto gen = bind(uid, rng);

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

void test_case() {
  int m;
  cin >> m;
  vector<int> c(m);
  for (int &i : c) cin >> i;

  int n;
  cin >> n;
  matrix A(n, row(n));
  for (row &r : A) {
    for (int &i : r) cin >> i;
  }

  bool possible = true;
  for (int trial = 0; trial < TRIALS and possible; trial++) {
    matrix R(1, row(n));
    for (int &i : R[0]) i = gen();

    matrix res(1, row(n, 0));
    for (int i = 0; i < m; i++, R = R * A) {
      res = res + R * c[i];
    }

    for (int i : res[0]) possible = possible and i == 0;
  }

  cout << (possible ? "YES" : "NO") << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int t = 1;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    // cout << "Case " << cs << ": ";
    test_case();
  }

  return 0;
}