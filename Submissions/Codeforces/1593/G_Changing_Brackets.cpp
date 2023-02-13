#include <bits/stdc++.h>
using namespace std;

const int N = 1e6 + 5;

string s;
int n;
int dp[N][2][2];
int q;

void test_case() {
  cin >> s; s = " " + s;
  n = s.size();

  for (int i = 1; i <= n; i++) {
    if (s[i] == ')') s[i] = '(';
    if (s[i] == ']') s[i] = '[';
  }

  for (int i = 1; i < n; i++) {
    if (s[i] != s[i + 1]) {
      dp[i][i & 1][s[i] == '(']++;
    }
  }

  for (int i = 1; i <= n; i++) {
    for (int l = 0; l < 2; l++) {
      for (int f = 0; f < 2; f++) {
        dp[i][l][f] += dp[i - 1][l][f];
      }
    }
  }

  cin >> q;
  while (q--) {
    int l, r;
    cin >> l >> r;
    int cnt0 = dp[r - 1][l & 1][0] - dp[l - 1][l & 1][0];
    int cnt1 = dp[r - 1][l & 1][1] - dp[l - 1][l & 1][1];
    cout << abs(cnt0 - cnt1) << "\n";
  }

  for (int i = 1; i <= n; i++) {
    for (int l = 0; l < 2; l++) {
      for (int f = 0; f < 2; f++) {
        dp[i][l][f] = 0;
      }
    }
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int t = 1;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    // cout << "Case " << cs << ": ";
    test_case();
  }

  return 0;
}