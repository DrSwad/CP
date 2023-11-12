#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n;
  cin >> n;

  vector<int> c(n);
  for (int &i : c) cin >> i;

  int k;
  cin >> k;

  vector<int> suffix_min(n);
  suffix_min[n - 1] = n - 1;
  for (int i = n - 2; i >= 0; i--) {
    if (c[i] < c[suffix_min[i + 1]]) suffix_min[i] = i;
    else suffix_min[i] = suffix_min[i + 1];
  }

  vector<int> op(n, 0);
  for (int l = 0, last = -1; l < n; ) {
    int at = suffix_min[l];

    int cost_per_move = c[at] - (last == -1 ? 0 : c[last]);
    int moves = min(last == -1 ? INT_MAX : op[last], k / cost_per_move);
    if (moves == 0) break;
    if (last != -1) op[last] -= moves;
    op[at] += moves;
    k -= moves * cost_per_move;

    last = at;
    l = at + 1;
  }

  vector<int> ans(n);
  for (int i = n - 1; i >= 0; i--) {
    ans[i] = i == n - 1 ? 0 : ans[i + 1];
    ans[i] += op[i];
  }

  for (int i = 0; i < n; i++) {
    if (i) cout << " ";
    cout << ans[i];
  }
  cout << "\n";
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