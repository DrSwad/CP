#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n, k;
  cin >> n >> k;

  string s;
  cin >> s;

  int segments = 1;
  for (int i = 1; i <= k - 1; i++) {
    if (s[i] != s[i - 1]) segments++;
  }

  int ans = segments - (s[k - 1] == '1');
  for (int i = k; i < n; i++) {
    if (s[i] != s[i - 1]) segments++;
    if (s[i - k] != s[i - k + 1]) segments--;
    ans = min(ans, segments - (s[i] == '1'));
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