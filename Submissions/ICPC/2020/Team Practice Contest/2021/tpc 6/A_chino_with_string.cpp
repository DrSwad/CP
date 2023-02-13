#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<ll> row;
typedef vector<row> matrix;
const ll INF = 1e18;

struct AC {
  int N, P;
  const int A = 26;
  vector<vector<int>> next;
  vector<int> link, out_link;
  vector<ll> out;

  AC() : N(0), P(0) {
    node();
  }

  int node() {
    next.emplace_back(A, 0);
    link.emplace_back(0);
    out_link.emplace_back(0);
    out.emplace_back(0);
    return N++;
  }

  inline int get(char c) {
    return c - 'a';
  }

  int add_pattern(const string T, int score) {
    int u = 0;
    for (auto c : T) {
      if (!next[u][get(c)]) next[u][get(c)] = node();
      u = next[u][get(c)];
    }
    out[u] += score;
    return P++;
  }

  void compute() {
    queue<int> q;
    for (q.push(0); !q.empty(); ) {
      int u = q.front();
      q.pop();
      for (int c = 0; c < A; ++c) {
        int v = next[u][c];
        if (!v) {next[u][c] = next[link[u]][c];}
        else {
          link[v] = u ? next[link[u]][c] : 0;
          out[v] += out[link[v]];
          q.push(v);
        }
      }
    }
  }

  int advance(int u, char c) {
    while (u && !next[u][get(c)]) u = link[u];
    u = next[u][get(c)];
    return u;
  }

  matrix base_matrix() {
    matrix base = matrix(N, row(N, -INF));
    for (int u = 0; u < N; u++) {
      for (int c = 0; c < A; c++) {
        int v = next[u][c];
        base[u][v] = max(base[u][v], out[v]);
      }
    }
    return base;
  }
};

matrix operator*(const matrix &m1, const matrix &m2) {
  int r = m1.size();
  int m = m1.back().size();
  int c = m2.back().size();
  matrix ret(r, row(c, -INF));
  for (int i = 0; i < r; i++) {
    for (int k = 0; k < m; k++) {
      for (int j = 0; j < c; j++) {
        ret[i][j] = max(ret[i][j], m1[i][k] + m2[k][j]);
      }
    }
  }
  return ret;
}
matrix one(int dim) {
  matrix ret(dim, row(dim, -INF));
  for (int i = 0; i < dim; i++) {
    ret[i][i] = 0;
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

int main() {
  int n, m;
  scanf("%d %d", &n, &m);

  AC aho;

  while (m--) {
    string s;
    int score;
    cin >> s >> score;
    aho.add_pattern(s, score);
  }

  aho.compute();

  matrix mat = aho.base_matrix();
  mat = mat ^ n;

  ll ans = LLONG_MIN;
  for (int c = 0; c < mat[0].size(); c++) {
    ans = max(ans, mat[0][c]);
  }

  printf("%lld\n", ans);

  return 0;
}