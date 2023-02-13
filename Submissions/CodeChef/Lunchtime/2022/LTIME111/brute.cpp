#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n;
  cin >> n;

  vector<int> a(n);
  for (int &i : a) cin >> i;

  map<vector<int>, int> dp;
  function<int(vector<int>&)> DP = [&](vector<int> &v) {
    if (dp.find(v) != dp.end()) return dp[v];

    int ans = 0;
    for (int i : a) ans += abs(i);

    for (int i = 0; i < n - 1; i++) {
      if (v[i] > 0 or v[i + 1] > 0) {
        v[i]--, v[i + 1] -= 2;
        ans = min(ans, DP(v));
        v[i]++, v[i + 1] += 2;
      }
    }

    return dp[v] = ans;
  };

  cout << DP(a) << "\n";
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