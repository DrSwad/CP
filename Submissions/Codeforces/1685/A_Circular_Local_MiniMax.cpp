#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n;
  cin >> n;

  vector<int> v(n);
  for (int &i : v) cin >> i;
  sort(v.begin(), v.end());

  if (n & 1) {
    cout << "NO\n";
    return;
  }

  int m = n / 2;
  vector<int> ans(n);
  for (int i = 0; i < m; i++) {
    ans[2 * i] = v[i];
    ans[2 * i + 1] = v[i + m];
  }

  for (int i = 0; i < n; i++) {
    int j = (i + 1) % n;
    if (ans[i] == ans[j]) {
      cout << "NO\n";
      return;
    }
  }

  cout << "YES\n";
  for (int i = 0; i < n; i++) {
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