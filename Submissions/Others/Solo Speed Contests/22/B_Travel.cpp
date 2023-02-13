#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, k;
  cin >> n >> k;

  vector<vector<int>> t(n, vector<int>(n));
  for (auto &row : t) {
    for (auto &i : row) {
      cin >> i;
    }
  }

  vector<int> p(n);
  iota(p.begin(), p.end(), 0);
  int ans = 0;

  do {
    if (p[0] != 0) continue;
    int curr = 0;
    for (int i = 1; i < n; i++) {
      curr += t[p[i - 1]][p[i]];
    }
    curr += t[p.back()][p[0]];
    ans += curr == k;
  } while (next_permutation(p.begin(), p.end()));

  cout << ans << endl;

  return 0;
}