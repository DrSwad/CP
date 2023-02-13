#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n;
  cin >> n;

  string a, b;
  cin >> a >> b;

  string xr;
  for (int i = 0; i < n; i++) {
    xr.push_back('0' + (a[i] ^ b[i]));
  }

  if (count(xr.begin(), xr.end(), '0') != n and count(xr.begin(), xr.end(), '1') != n) {
    cout << "NO\n";
    return;
  }

  cout << "YES\n";

  bool same = count(xr.begin(), xr.end(), '0') == n;
  vector<pair<int, int>> ans;
  for (int i = 0; i < n; i++) {
    if (a[i] == '1') {
      ans.emplace_back(i + 1, i + 1);
      same ^= 1;
    }
  }

  if (!same) {
    ans.emplace_back(n - 1, n);
    ans.emplace_back(n - 1, n - 1);
    ans.emplace_back(n, n);
  }

  cout << ans.size() << "\n";
  for (auto [l, r] : ans) {
    cout << l << " " << r << "\n";
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