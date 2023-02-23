#include <bits/stdc++.h>
using namespace std;

const int N = 102;
const int S = N * (N / 2) * (N / 2 + 1) / 2;

int n, k, m;
int dp[N][S];

void init() {
  dp[0][0] = 1;
  for (int i = 1; i <= n; i++) {
    vector<vector<int>> pref(i);
    for (int s = 0; s < S; s++) {
      int r = s % i;
      pref[r].push_back(dp[i - 1][s] + (!pref[r].empty() ? pref[r].back() : 0));
      if (pref[r].back() >= m) pref[r].back() -= m;

      dp[i][s] = pref[r].back();
      int sz = pref[r].size();
      if (sz >= k + 2) {
        dp[i][s] -= pref[r][sz - (k + 2)];
        if (dp[i][s] < 0) dp[i][s] += m;
      }
    }
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> n >> k >> m;
  init();

  for (int i = 1; i <= n; i++) {
    int ln = i - 1, rn = n - i;
    int tot = 0;
    for (int s = 0; s < S; s++) {
      tot += (long long)dp[ln][s] * dp[rn][s] % m;
      if (tot >= m) tot -= m;
    }
    tot = (long long)tot * (k + 1) % m;
    (tot += m - 1) %= m;
    cout << tot << "\n";
  }

  return 0;
}