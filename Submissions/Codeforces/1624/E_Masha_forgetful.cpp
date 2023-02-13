#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n, m;
  cin >> n >> m;

  map<string, pair<int, int>> mp;
  for (int i = 1; i <= n; i++) {
    string s;
    cin >> s;

    for (int j = 0; j < m; j++) {
      string ss;
      ss += s[j];
      if (j + 2 <= m) {
        ss += s[j + 1];
        mp[ss] = {i, j + 1};
      }
      if (j + 3 <= m) {
        ss += s[j + 2];
        mp[ss] = {i, j + 1};
      }
    }
  }

  string s;
  cin >> s;

  vector<tuple<int, int, int>> from(m + 1, {-1, -1, -1});

  for (int i = 0; i < m; i++) {
    if (i != 0 and get<0>(from[i]) == -1) continue;

    string ss;
    ss += s[i];
    if (i + 2 <= m) {
      ss += s[i + 1];
      if (mp.find(ss) != mp.end()) {
        from[i + 2] = {i, mp[ss].first, mp[ss].second};
      }
    }
    if (i + 3 <= m) {
      ss += s[i + 2];
      if (mp.find(ss) != mp.end()) {
        from[i + 3] = {i, mp[ss].first, mp[ss].second};
      }
    }
  }

  if (get<0>(from[m]) == -1) {
    cout << "-1\n";
    return;
  }

  vector<tuple<int, int, int>> ans;
  int at = m;
  while (at) {
    auto [prv, i, l] = from[at];
    int r = l + (at - prv - 1);
    ans.push_back({i, l, r});
    at = prv;
  }

  reverse(ans.begin(), ans.end());
  cout << ans.size() << "\n";
  for (auto [i, l, r] : ans) {
    cout << l << " " << r << " " << i << "\n";
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