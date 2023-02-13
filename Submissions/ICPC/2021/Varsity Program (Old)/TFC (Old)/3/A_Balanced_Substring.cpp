#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;

  string s;
  cin >> s;

  vector<int> pref(n + 1);
  pref[0] = 0;
  for (int i = 1; i <= n; i++) {
    pref[i] = pref[i - 1] + (s[i - 1] == '0' ? -1 : 1);
  }

  int ans = 0;
  map<int, int> mp;
  mp[0] = 0;

  for (int i = 1; i <= n; i++) {
    if (mp.find(pref[i]) == mp.end()) {
      mp[pref[i]] = i;
    }
    ans = max(ans, i - mp[pref[i]]);
  }

  cout << ans << "\n";

  return 0;
}