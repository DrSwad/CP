#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n;
  cin >> n;

  vector<int> a(n);
  for (int &i : a) cin >> i;

  vector<pair<int, int>> ans;

  {
    int max_i = 0;
    for (int i = 1; i < n; i++) {
      if (abs(a[i]) > abs(a[max_i])) max_i = i;
    }

    for (int i = 0; i < n; i++) {
      ans.emplace_back(i + 1, max_i + 1);
      a[i] += a[max_i];
    }
  }

  if (a[0] >= 0) {
    for (int i = 1; i < n; i++) {
      ans.emplace_back(i + 1, i);
      a[i] += a[i - 1];
    }
  }
  else {
    for (int i = n - 2; i >= 0; i--) {
      ans.emplace_back(i + 1, i + 2);
      a[i] += a[i + 1];
    }
  }

  cout << ans.size() << "\n";
  for (auto [i, j] : ans) cout << i << " " << j << "\n";
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