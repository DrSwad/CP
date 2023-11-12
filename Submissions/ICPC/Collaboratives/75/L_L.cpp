#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n, q;
  cin >> n >> q;

  string s;
  cin >> s;

  vector<int> pref(n + 1);
  pref[0] = 0;

  for (int i = 0; i + 3 <= n; i++) {
    if (s[i] == s[i + 1] or s[i] == s[i + 2] or s[i + 1] == s[i + 2]) {
      pref[i + 1] = 1;
    }
  }

  for (int i = 1; i <= n; i++) {
    pref[i] += pref[i - 1];
  }

  while (q--) {
    int l, r;
    cin >> l >> r;

    if (r - l + 1 >= 3 and pref[r - 2] - pref[l - 1]) cout << "YES\n";
    else cout << "NO\n";
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    test_case();
  }

  return 0;
}