#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n;
  cin >> n;

  vector<int> a(n);
  for (int &i : a) cin >> i;

  int mx_a = *max_element(a.begin(), a.end());

  vector<vector<int>> pos(mx_a + 1);
  for (int i = 0; i < n; i++) {
    pos[a[i]].push_back(i);
  }

  vector<vector<int>> pf(n);

  vector<bool> is_prime(mx_a + 1, true);
  for (int p = 2; p <= mx_a; p++) {
    if (is_prime[p]) {
      for (int mul = p; mul <= mx_a; mul += p) {
        for (int i : pos[mul]) {
          pf[i].push_back(p);
        }
        is_prime[mul] = false;
      }
    }
  }

  vector<int> dp(n, 0);
  unordered_map<int, int> last;
  int ans = 1;

  for (int i = 0; i < n; i++) {
    if (i) dp[i] = max(dp[i], dp[i - 1]);
    for (int p : pf[i]) {
      if (last.find(p) == last.end()) last[p] = -1;
      dp[i] = max(dp[i], last[p] + 1);
      last[p] = i;
    }
    ans = max(ans, i - dp[i] + 1);
  }

  cout << (ans == 1 ? -1 : ans) << "\n";
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