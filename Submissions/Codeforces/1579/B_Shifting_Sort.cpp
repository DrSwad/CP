#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n;
  cin >> n;

  vector<int> a(n);
  for (int &i : a) cin >> i, i--;

  vector<int> sa = a;
  sort(sa.begin(), sa.end());

  vector<tuple<int, int, int>> ans;
  for (int i = 0; i < n; i++) {
    if (a[i] == sa[i]) continue;

    int d = find(a.begin() + i, a.begin() + n, sa[i]) - (a.begin() + i);
    ans.push_back({i + 1, n, d});

    vector<int> b = a;
    for (int j = 0, len = n - i; j < len; j++) {
      b[i + j] = a[i + (j + d) % len];
    }
    swap(a, b);
  }

  cout << ans.size() << "\n";
  for (auto [l, r, d] : ans) cout << l << " " << r << " " << d << "\n";
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