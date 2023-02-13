#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n, m;
  cin >> n >> m;
  int tot = n * m;

  vector<int> v(tot);
  for (int &i : v) cin >> i;

  sort(v.begin(), v.end());

  bool rev = false;
  if (m > n) rev = true, swap(n, m);

  vector<vector<int>> ans(n, vector<int>(m));
  int need_smaller = (m - 1 + 1) / 2, need_bigger = (m - 1) / 2;
  int moves = n + m - 1;
  int st, min_diff = INT_MAX;
  for (int l = need_smaller; l < tot - need_bigger - moves + 1; l++) {
    if (v[l + moves - 1] - v[l] < min_diff) {
      min_diff = v[l + moves - 1] - v[l];
      st = l;
    }
  }

  ans[0][0] = v[st];
  vector<bool> vis(tot, false);
  vis[st] = true;

  auto use_val = [&](int i, int j, int index) {
    ans[i][j] = v[index];
    vis[index] = true;
  };

  for (int j = 1, l = 0, r = tot - 1; j < m; j++) {
    if (j & 1) {
      use_val(0, j, st + j);
      use_val(1, j - 1, l++);
    }
    else {
      use_val(0, j, st + j);
      use_val(1, j - 1, r--);
    }
  }
  for (int i = 1; i < n; i++) {
    use_val(i, m - 1, st + m - 1 + i);
  }

  for (int i = 0, ptr = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (ans[i][j]) continue;
      while (vis[ptr]) ptr++;
      use_val(i, j, ptr);
    }
  }

  if (!rev) {
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        if (j) cout << " ";
        cout << ans[i][j];
      }
      cout << "\n";
    }
  }
  else {
    for (int j = 0; j < m; j++) {
      for (int i = 0; i < n; i++) {
        if (i) cout << " ";
        cout << ans[i][j];
      }
      cout << "\n";
    }
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