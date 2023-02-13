#include <bits/stdc++.h>
using namespace std;

void test_case() {
  string s;
  cin >> s;

  int n = s.length();
  vector<int> pref(1, 0);
  for (char c : s) {
    pref.push_back(pref.back() + (c == '0'));
  }
  int cnt0 = pref.back();

  int ans = n;
  for (int len = 0; len <= n; len++) {
    int cnt = pref[len] - pref[max(0, len - cnt0)];
    int rem = max(0, cnt0 - len);
    cnt += pref[len + rem] - pref[len];
    ans = min(ans, cnt0 - cnt);
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