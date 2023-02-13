#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n;
  cin >> n;

  vector<vector<int>> a(n, vector<int>(5));
  for (auto &v : a) for (int &i : v) cin >> i;

  for (int i = 0; i < 5; i++) {
    for (int j = i + 1; j < 5; j++) {
      vector<int> cnt(4, 0);
      for (int k = 0; k < n; k++) {
        int id = (a[k][i] << 1) + (a[k][j]);
        cnt[id]++;
      }

      if (cnt[1] + cnt[2] + cnt[3] < n) continue;
      if (cnt[1] > n / 2) continue;
      if (cnt[2] > n / 2) continue;
      cout << "YES\n";
      return;
    }
  }

  cout << "NO\n";
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