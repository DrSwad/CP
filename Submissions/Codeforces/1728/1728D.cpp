#include <bits/stdc++.h>
using namespace std;

void test_case() {
  string s;
  cin >> s;
  int n = s.length();

  vector<vector<int>> dp(n + 2, vector<int>(n + 2, -2));
  for (int i = 1; i <= n + 1; i++) {
    dp[i][i - 1] = 0;
  }

  function<int(int, int)> alice_result;
  function<int(int, int, char c)> bob_result;

  alice_result = [&](int l, int r) {
    if (dp[l][r] != -2) return dp[l][r];
    vector<int> res_freq(3, 0);
    res_freq[bob_result(l + 1, r, s[l - 1]) + 1]++;
    res_freq[bob_result(l, r - 1, s[r - 1]) + 1]++;
    if (res_freq[0]) return dp[l][r] = 1;
    else if (res_freq[1]) return dp[l][r] = 0;
    else return dp[l][r] = -1;
  };

  bob_result = [&](int l, int r, char c) {
    vector<int> res_freq(3, 0);

    int res1 = alice_result(l + 1, r);
    int res2 = alice_result(l, r - 1);
    if (res1 == -1 or res2 == -1) return 1;
    if ((res1 == 0 and s[l - 1] > c) or (res2 == 0 and s[r - 1] > c)) return 1;
    if ((res1 == 0 and s[l - 1] == c) or (res2 == 0 and s[r - 1] == c)) return 0;
    return -1;
  };

  int res = alice_result(1, n);
  if (res == 1) cout << "Alice\n";
  else if (res == -1) cout << "Bob\n";
  else cout << "Draw\n";
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