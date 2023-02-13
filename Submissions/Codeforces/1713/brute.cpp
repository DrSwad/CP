#include <bits/stdc++.h>
using namespace std;

struct TwoSat {
  int N;
  vector<vector<int>> gr;
  vector<int> values; // 0 = false, 1 = true

  TwoSat(int n = 0) : N(n), gr(2 * n) {}

  int add_var() { // (optional)
    gr.emplace_back();
    gr.emplace_back();
    return N++;
  }

  void either(int f, int j) {
    f = max(2 * f, -1 - 2 * f);
    j = max(2 * j, -1 - 2 * j);
    gr[f].push_back(j ^ 1);
    gr[j].push_back(f ^ 1);
  }
  void set_value(int x) { either(x, x); }

  void at_most_one(const vector<int> &li) { // (optional)
    if ((int)li.size() <= 1) return;
    int cur = ~li[0];
    for (int i = 2; i < (int)li.size(); i++) {
      int next = add_var();
      either(cur, ~li[i]);
      either(cur, next);
      either(~li[i], next);
      cur = ~next;
    }
    either(cur, ~li[1]);
  }

  vector<int> val, comp, z;
  int time = 0;
  int dfs(int i) {
    int low = val[i] = ++time, x;
    z.push_back(i);
    for (auto &e : gr[i])
      if (!comp[e]) low = min(low, val[e] ?: dfs(e));
    if (low == val[i]) do {
        x = z.back();
        z.pop_back();
        comp[x] = low;
        if (values[x >> 1] == -1) values[x >> 1] = x & 1;
      } while (x != i);
    return val[i] = low;
  }

  bool solve() {
    values.assign(N, -1);
    val.assign(2 * N, 0);
    comp = val;
    for (int i = 0; i < 2 * N; i++) {
      if (!comp[i]) dfs(i);
    }
    for (int i = 0; i < N; i++) {
      if (comp[2 * i] == comp[2 * i + 1]) return 0;
    }
    return 1;
  }
};

vector<vector<int>> solve(int n, vector<vector<int>> mat) {
  vector<tuple<int, int, bool>> v;

  for (int i = 0; i < n; i++) {
    for (int j = i + 1; j < n; j++) {
      if (mat[i][j] != mat[j][i]) {
        v.push_back({i, j, mat[i][j] > mat[j][i]});
      }
    }
  }

  auto check = [&](int m) {
    TwoSat ts(n);
    for (int i = 0; i < m; i++) {
      auto [x, y, b] = v[i];
      if (b) ts.either(x, y), ts.either(~x, ~y); // different
      else ts.either(x, ~y), ts.either(~x, y); // same
    }
    return ts.solve();
  };

  int L = 0, R = v.size() + 1;
  while (R - L > 1) {
    int M = (L + R) / 2;
    if (check(M)) L = M;
    else R = M;
  }

  vector<int> ts_sol;
  {
    TwoSat ts(n);
    for (int i = 0; i < L; i++) {
      auto [x, y, b] = v[i];
      if (b) ts.either(x, y), ts.either(~x, ~y);
      else ts.either(x, ~y), ts.either(~x, y);
    }
    ts.solve();
    ts_sol = ts.values;
  }

  for (int i = 0; i < n; i++) {
    for (int j = i + 1; j < n; j++) {
      if ((ts_sol[i] + ts_sol[j]) & 1) {
        swap(mat[i][j], mat[j][i]);
      }
    }
  }

  return mat;
}

vector<vector<int>> brute(int n, vector<vector<int>> mat) {
  auto ans = mat;
  for (int mask = 1; mask < 1 << n; mask++) {
    auto curr = mat;

    for (int i = 0; i < n; i++) {
      for (int j = i + 1; j < n; j++) {
        int ti = mask >> i & 1;
        int tj = mask >> j & 1;
        if ((ti + tj) & 1) {
          swap(curr[i][j], curr[j][i]);
        }
      }
    }

    ans = min(ans, curr);
  }

  return ans;
}

void test_case() {
  int n;
  cin >> n;

  vector<vector<int>> mat(n, vector<int>(n));
  for (auto &row : mat) {
    for (int &cell : row) cin >> cell;
  }

  mat = brute(n, mat);

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (j) cout << " ";
      cout << mat[i][j];
    }
    cout << "\n";
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t = 1;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    // cout << "Case " << cs << ": ";
    test_case();
  }

  return 0;
}