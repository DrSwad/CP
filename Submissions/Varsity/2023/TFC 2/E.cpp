#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, k;
  cin >> n >> k;

  vector<int> a(n);
  for (int &i : a) cin >> i;

  vector<vector<int>> v(k);
  for (int i = 0; i < n; i++) {
    v[i % k].push_back(a[i]);
  }

  vector<long long> ans(2, 0);
  for (int i = 0; i < k; i++) {
    sort(v[i].begin(), v[i].end(), greater<int>());
    vector<long long> mx(2, 0);

    mx[0] = 0;
    for (int j = 0; j + 1 < v[i].size(); j += 2) {
      if (v[i][j] + v[i][j + 1] < 0) break;
      mx[0] += v[i][j] + v[i][j + 1];
    }

    mx[1] = v[i][0];
    for (int j = 1; j + 1 < v[i].size(); j += 2) {
      if (v[i][j] + v[i][j + 1] < 0) break;
      mx[1] += v[i][j] + v[i][j + 1];
    }

    ans[0] += mx[0];
    ans[1] += mx[1];
  }

  cout << max(ans[0], ans[1]) << "\n";

  return 0;
}