#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n;
  cin >> n;

  vector<int> s(n);
  for (int &i : s) cin >> i;

  string v;
  cin >> v;

  int ans = INT_MAX;
  for (int i = 0; i < n; i++) {
    if (v[i] == '0') ans = min(ans, s[i]);
  }

  cout << ans << "\n";
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