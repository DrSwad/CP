#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  vector<pair<int, int>> queries;
  {
    int n;
    int q = 0;
    while (cin >> n, n != 0) {
      queries.emplace_back(n, q++);
    }
  }

  if (queries.empty()) return 0;
  sort(queries.begin(), queries.end());

  int mx_n = queries.rbegin()->first;
  vector<bool> is_prime(mx_n + 1, true);
  vector<int> ans(queries.size(), 1);
  vector<int> fact_exp(mx_n + 1, 0);
  const int mod = 1e8 + 7;

  for (int p = 2; p <= mx_n; p++) {
    if (is_prime[p]) {
      int exp = 0;
      int at_query = 0;

      for (int q = p; q <= mx_n; q += p) {
        is_prime[q] = false;

        exp += 1ll * p * fact_exp[q - p] % mod;
        if (exp >= mod) exp -= mod;

        fact_exp[q] = (q / p) + fact_exp[(q / p) / p * p];

        while (at_query < queries.size() and queries[at_query].first < q + p) {
          auto [n, qi] = queries[at_query++];
          if (n < q) continue;
          int cur_exp = (exp + 1ll * fact_exp[q] * (n - q + 1) % mod) % mod;
          ans[qi] = 1ll * ans[qi] * (cur_exp + 1) % mod;
        }
      }
    }
  }

  for (int i = 0; i < ans.size(); i++) {
    cout << ans[i] << "\n";
  }

  return 0;
}