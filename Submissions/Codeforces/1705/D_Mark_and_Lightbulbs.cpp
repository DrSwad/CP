#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n;
  cin >> n;

  string s[2];
  vector<int> v[2];

  for (int it = 0; it < 2; it++) {
    cin >> s[it];
    int len = s[it].length();
    for (int l = 0, r = 1; r <= len; r++) {
      if (r == len or s[it][r] != s[it][l]) {
        v[it].push_back(r - l);
        l = r;
      }
    }
  }

  if (s[0][0] != s[1][0] or v[0].size() != v[1].size()) {
    cout << "-1\n";
    return;
  }

  long long carry = 0, ans = 0;
  for (int i = 0; i < v[0].size(); i++) {
    ans += abs(carry);
    carry += v[0][i] - v[1][i];
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