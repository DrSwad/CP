#include <bits/stdc++.h>
using namespace std;

const int N = 1e6 + 5;

int freq[N];

void test_case(int n) {
  vector<vector<int>> st(n);
  vector<unordered_map<int, int>> st_freq(n);
  for (int i = 0; i < n; i++) {
    auto &s = st[i];
    int h;
    cin >> h;
    s.resize(h);
    for (int &v : s) cin >> v, st_freq[i][v]++, freq[v]++;
    s.resize(unique(s.begin(), s.end()) - s.begin());
    reverse(s.begin(), s.end());
  }

  vector<int> all;
  for (auto &s : st) {
    for (int i : s) {
      all.push_back(i);
    }
  }

  sort(all.begin(), all.end());
  all.resize(unique(all.begin(), all.end()) - all.begin());
  reverse(all.begin(), all.end());

  int tot = all.size();
  vector<vector<int>> dp(tot, vector<int>(n + 1, 0));

  if (tot > 1) {
    vector<vector<bool>> can_save(n + 1, vector<bool>(tot - 1, false));
    vector<vector<bool>> can_continue(n + 1, vector<bool>(tot - 1, false));

    for (int i = 0; i < n; i++) {
      for (int j = 0; j < tot - 1; j++) {
        bool found1 = st_freq[i].find(all[j]) != st_freq[i].end();
        bool found2 = st_freq[i].find(all[j + 1]) != st_freq[i].end();
        if (found1 and found2) {
          can_save[i][j] = true;
          int cnt = st_freq[i][all[j + 1]];
          can_continue[i][j] = cnt == freq[all[j + 1]];
        }
      }
    }

    for (int i = tot - 2; i >= 0; i--) {
      for (int j = 0; j <= n; j++) {
        dp[i][j] = dp[i + 1][n];
        for (int k = 0; k < n; k++) {
          if (k != j and can_save[k][i]) {
            int nj = can_continue[k][i] ? n : k;
            dp[i][j] = 1 + dp[i + 1][nj];
          }
        }
      }
    }
  }

  int ans = n - 1;
  for (auto &s : st) ans += 2 * ((int)s.size() - 1);
  ans -= 2 * dp[0][n];
  cout << ans << "\n";

  for (auto &s : st) {
    for (int i : s) {
      freq[i] = 0;
    }
  }
}

int main() {
  int n;
  for (int cs = 1; cin >> n; cs++) {
    cout << "Case " << cs << ": ";
    test_case(n);
  }

  return 0;
}