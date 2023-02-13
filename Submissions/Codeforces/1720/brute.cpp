#include <bits/stdc++.h>
using namespace std;

const int A = 260;

void test_case() {
  int n;
  cin >> n;

  vector<int> a(n);
  for (int &i : a) cin >> i;

  vector<int> dp(n, 1);
  for (int i = 0; i < n; i++) {
    for (int j = max(i - A, 0); j < i; j++) {
      if ((a[j] ^ i) < (a[i] ^ j)) {
        dp[i] = max(dp[i], 1 + dp[j]);
      }
    }
  }

  cout << *max_element(dp.begin(), dp.end()) << "\n";
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