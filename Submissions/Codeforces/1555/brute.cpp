#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;

void test_case() {
  int n, m;
  cin >> n >> m;

  vector<tuple<int, int, int>> segs(n);
  for (auto & [l, r, w] : segs) {
    cin >> l >> r >> w;
  }

  sort(segs.begin(), segs.end());

  int ans = INF;

  for (int mask = 1; mask < 1 << n; mask++) {
    vector<int> ids;
    for (int i = 0; i < n; i++) {
      if (mask >> i & 1) {
        ids.push_back(i);
      }
    }

    int mn = INF, mx = 0;
    int R = 1;
    bool possible = true;

    for (int id : ids) {
      auto [l, r, w] = segs[id];
      if (l > R) {
        possible = false;
        break;
      }
      R = max(R, r);
      mn = min(mn, w);
      mx = max(mx, w);
    }

    if (possible and R == m) {
      int curr = mx - mn;
      ans = min(ans, curr);
    }
  }

  cout << ans << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int t = 1;
  // cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    // cout << "Case " << cs << ": ";
    test_case();
  }

  return 0;
}