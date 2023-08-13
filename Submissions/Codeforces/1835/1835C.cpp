#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

void test_case() {
  int k;
  cin >> k;
  int n = 1 << (k + 1);

  vector g(n, array<int, 2>());
  for (auto & [low, high] : g) {
    ll val;
    cin >> val;
    low = val & (1 << k) - 1;
    high = val >> k;
  }

  if (k == 0) {
    cout << "1 1 2 2\n";
    return;
  }

  vector pref(n + 1, array<int, 2>());
  for (int it = 0; it < 2; it++) {
    for (int i = 1; i <= n; i++) {
      pref[i][it] = pref[i - 1][it] ^ g[i - 1][it];
    }
  }

  vector<int> last(1 << k, -1);
  vector<pair<int, int>> ranges;
  for (int r = 0; r <= n; r++) {
    int cur_pref = pref[r][0];
    if (last[cur_pref] != -1) {
      ranges.emplace_back(last[cur_pref] + 1, r);
    }
    last[cur_pref] = r;
  }

  fill(last.begin(), last.end(), -1);
  int l1, r1, l2, r2;
  bool found = false;
  for (int at = 0; at < ranges.size(); at++) {
    auto [l, r] = ranges[at];
    int cur_xor = pref[r][1] ^ pref[l - 1][1];
    if (last[cur_xor] != -1) {
      l1 = ranges[last[cur_xor]].first, r1 = ranges[last[cur_xor]].second;
      l2 = l, r2 = r;
      if (l1 > l2) swap(l1, l2), swap(r1, r2);
      assert(l1 != l2);
      assert(r1 != r2);
      found = true;
      break;
    }
    last[cur_xor] = at;
  }
  assert(found);

  if (r2 < r1) {
    int nr1 = l2 - 1;
    int nl2 = r2 + 1;
    r2 = r1;
    r1 = nr1;
    l2 = nl2;
  }
  else if (l2 <= r1) {
    int nr1 = l2 - 1;
    int nl2 = r1 + 1;
    r1 = nr1;
    l2 = nl2;
  }

  cout << l1 << " " << r1 << " " << l2 << " " << r2 << "\n";
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