#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n;
  cin >> n;

  vector<vector<int>> a(2, vector<int>(n));
  for (int &i : a[0]) cin >> i;
  for (int &i : a[1]) cin >> i;

  vector<pair<int, int>> ans;
  auto custom_sort = [&](int index, int l, int r) {
    while (r > l) {
      for (int i = l; i < r - 1; i++) {
        if (a[index][i] > a[index][i + 1]) {
          ans.push_back({i, i + 1});
          swap(a[0][i], a[0][i + 1]);
          swap(a[1][i], a[1][i + 1]);
        }
      }
      r--;
    }
  };

  custom_sort(0, 0, n);

  for (int l = 0; l < n; ) {
    int r = l;
    while (r < n and a[0][r] == a[0][l]) r++;
    custom_sort(1, l, r);
    l = r;
  }

  if (!is_sorted(a[0].begin(), a[0].end()) or !is_sorted(a[1].begin(), a[1].end())) {
    cout << "-1\n";
  }
  else {
    cout << ans.size() << "\n";
    for (auto [l, r] : ans) {
      cout << l + 1 << " " << r + 1 << "\n";
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