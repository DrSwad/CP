#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n, k;
  cin >> n >> k;

  string s;
  cin >> s;

  string ans(n, '0');
  vector<int> pref(n + 1, 0);

  for (int i = 0; i < n; i++) {
    if (i) pref[i] ^= pref[i - 1];
    char c = s[i] ^ pref[i];
    if (i + k <= n and c == '1') {
      c = '0';
      pref[i] ^= 1;
      pref[i + k] ^= 1;
    }
    ans[i] = c;
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