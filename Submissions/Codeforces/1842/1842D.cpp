#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll MX_T = ll(1e18) + 1ll;

void test_case() {
  int n, m;
  cin >> n >> m;

  vector<tuple<int, int, ll>> conds(m);
  for (auto & [x, y, t] : conds) cin >> x >> y >> t, x--, y--;

  ll tot_t = 0;
  vector<pair<string, ll>> ans;

  string s(n, '0');
  s[0] = '1';

  while (true) {
    ll nxt_t = MX_T;
    for (auto [x, y, t] : conds) {
      if (s[x] != s[y]) {
        nxt_t = min(nxt_t, t);
      }
    }

    if (nxt_t == MX_T) {
      cout << "inf\n";
      return;
    }

    tot_t += nxt_t;

    if (nxt_t) {
      ans.emplace_back(s, nxt_t);
    }

    bool stop = false;
    vector<int> move_group;
    for (auto [x, y, t] : conds) {
      if (s[x] != s[y] and t == nxt_t) {
        if (s[y] == '0') swap(x, y);
        if (x == n - 1) {
          stop = true;
          break;
        }
        move_group.push_back(x);
      }
    }

    if (stop) break;
    for (auto &x : move_group) s[x] = '1';
  }

  cout << tot_t << " " << ans.size() << "\n";

  for (auto [s, t] : ans) {
    cout << s << " " << t << "\n";
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t = 1;
  // cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    // cout << "Case " << cs << ": ";
    test_case();
  }

  return 0;
}