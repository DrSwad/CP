#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;

int dp[N];

void init() {
  dp[0] = 0;
  for (int i = 1, r = 1, sq = 1; i <= sq and i < N; i++) {
    dp[i] = sq - i;
    assert(dp[i] <= i);
    if (i == sq) {
      sq += 2 * r + 1;
      r++;
    }
  }
}

void test_case() {
  int n;
  cin >> n;

  vector<int> ans(n);
  int at = n - 1;
  while (at >= 0) {
    int nxt = dp[at];
    int sq = at + nxt;
    for (int i = nxt; i <= at; i++) {
      ans[i] = sq - i;
    }
    at = nxt - 1;
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

  init();

  int t = 1;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    // cout << "Case " << cs << ": ";
    test_case();
  }

  return 0;
}