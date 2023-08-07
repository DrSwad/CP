#include <bits/stdc++.h>
using namespace std;

const int K = 40;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, m;
  cin >> n >> m;

  vector<vector<int>> seq(n);
  vector<unordered_map<int, int>> seq_val(n);
  for (int i = 0; i < n; i++) {
    int sz;
    cin >> sz;
    seq[i].resize(sz);
    for (int j = 0; j < sz; j++) {
      cin >> seq[i][j];
      seq_val[i][seq[i][j]] = j;
    }
  }

  vector<vector<int>> prime_powers;
  {
    vector<bool> is_prime(K + 1, true);
    for (int p = 2; p <= K; p++) {
      if (is_prime[p]) {
        for (int q = 2 * p; q <= K; q += p) {
          is_prime[q] = false;
        }

        prime_powers.push_back({p});
        while (prime_powers.back().back() * p <= K) {
          prime_powers.back().push_back(prime_powers.back().back() * p);
        }
      }
    }
  }

  vector<vector<vector<int>>> pp_next(n);
  for (int i = n - 1; i >= 0; i--) {
    for (int j = 0; j < prime_powers.size(); j++) {
      const auto &pp = prime_powers[j];
      pp_next[i].push_back({});
      for (int k = 0; k < pp.size(); k++) {
        int p = pp[k];
        if ((int)seq[i].size() % p == 0) pp_next[i][j].push_back(i);
        else pp_next[i][j].push_back(i < n - 1 ? pp_next[i + 1][j][k] : n);
      }
    }
  }

  vector<vector<int>> dp(n);
  vector<int> ans(m + 1, 0);
  for (int i = n - 1; i >= 0; i--) {
    dp[i].resize(seq[i].size());
    for (int j = 0; j < seq[i].size(); j++) {
      int a = seq[i][j];

      if (i < n - 1 and seq_val[i + 1].find(a) != seq_val[i + 1].end()) {
        dp[i][j] = dp[i + 1][seq_val[i + 1][a]];
      }
      else dp[i][j] = i;

      if (i < n - 1) {
        for (int k = 0; k < prime_powers.size(); k++) {
          const auto &pp = prime_powers[k];
          for (int l = 0; l < pp.size(); l++) {
            int p = pp[l];
            if ((int)seq[i].size() % p != 0) break;
            int ii = pp_next[i + 1][k][l];
            if (ii >= n or seq_val[ii].find(a) == seq_val[ii].end()) break;
            int jj = seq_val[ii][a];
            if (j % p != jj % p) {
              dp[i][j] = min(dp[i][j], ii - 1);
              break;
            }
          }
        }
      }

      ans[a] = max(ans[a], dp[i][j] - (i - 1));
    }
  }

  for (int i = 1; i <= m; i++) {
    cout << ans[i] << "\n";
  }

  return 0;
}