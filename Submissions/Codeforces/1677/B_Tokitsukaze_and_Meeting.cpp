#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n, m;
  cin >> n >> m;
  int tot = n * m;

  string s;
  cin >> s;

  vector<int> pref(tot + 1);
  pref[0] = 0;
  for (int i = 1; i <= tot; i++) {
    pref[i] = pref[i - 1] + (s[i - 1] - '0');
  }

  vector<int> row_cnt(m, 0);
  vector<bool> col_vis(m, false);
  int col_cnt = 0;
  vector<int> ans(tot, 0);

  for (int i = 0, col = 0; i < tot; i++) {
    if (pref[i + 1] - pref[max(0, i - (m - 1))] > 0) row_cnt[col]++;
    ans[i] += row_cnt[col];

    if (s[i] == '1' and !col_vis[col]) {
      col_cnt++;
      col_vis[col] = true;
    }

    ans[i] += col_cnt;

    col++;
    if (col >= m) col = 0;
  }

  for (int i = 0; i < tot; i++) {
    if (i) cout << " ";
    cout << ans[i];
  }
  cout << "\n";
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