#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;

  vector<vector<int>> v(n);

  for (int i = 0; i < n; i++) {
    int f, s;
    cin >> f >> s;
    f--;
    v[f].push_back(s);
  }

  int ans = 0;
  int mx1 = 0, mx2 = 0;

  for (int i = 0; i < n; i++) {
    sort(v[i].begin(), v[i].end());
    int sz = v[i].size();
    if (sz >= 2) {
      ans = max(ans, v[i][sz - 1] + v[i][sz - 2] / 2);
    }
    if (sz >= 1) {
      if (v[i][sz - 1] >= mx1) mx2 = mx1, mx1 = v[i][sz - 1];
      else if (v[i][sz - 1] >= mx2) mx2 = v[i][sz - 1];
    }
  }

  ans = max(ans, mx1 + mx2);

  cout << ans << "\n";

  return 0;
}