#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n, q;
  cin >> n >> q;

  string s;
  cin >> s;

  vector<vector<int>> freq(26, vector<int>(n + 1, 0));
  for (int c = 0; c < 26; c++) {
    for (int i = 1; i <= n; i++) {
      freq[c][i] = freq[c][i - 1] + (s[i - 1] == 'a' + c);
    }
  }

  while (q--) {
    int l, r, c;
    char ch;
    cin >> l >> r >> ch;
    l--, r--;
    c = ch - 'a';

    int li = l / n, ri = r / n;
    long long ans = 0;

    if (li == ri) ans = freq[c][r % n + 1] - freq[c][l % n];
    else {
      ans += freq[c][n] - freq[c][l % n];
      ans += freq[c][r % n + 1];
      ans += (long long)freq[c][n] * (ri - li - 1);
    }

    cout << ans << "\n";
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