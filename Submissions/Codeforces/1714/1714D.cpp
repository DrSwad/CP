#include <bits/stdc++.h>
using namespace std;

void test_case() {
  string t;
  cin >> t;

  int n;
  cin >> n;

  vector<string> vs(n);
  for (string &s : vs) cin >> s;

  int sz = t.length();
  vector<bool> vis(sz, false);
  vector<pair<int, int>> ans;
  int curr_r = 0;
  int nxt_i, nxt_r = 0;

  for (int i = 0; i < sz; i++) {
    for (int si = 0; si < n; si++) {
      if (t.substr(i, vs[si].length()) == vs[si] and i + vs[si].length() > nxt_r) {
        nxt_i = si;
        nxt_r = i + vs[si].length();
      }
    }

    for (int j = nxt_r - 1; j >= 0 and !vis[j]; j--) vis[j] = true;

    if (!vis[i]) {
      cout << "-1\n";
      return;
    }

    if (i == curr_r) {
      ans.push_back({nxt_i, nxt_r - vs[nxt_i].length()});
      curr_r = nxt_r;
    }
  }

  cout << ans.size() << "\n";
  for (auto [si, pos] : ans) {
    cout << si + 1 << " " << pos + 1 << "\n";
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