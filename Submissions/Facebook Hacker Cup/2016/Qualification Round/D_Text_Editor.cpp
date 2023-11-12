#include <bits/stdc++.h>
using namespace std;

struct Trie {
  const int A = 26;
  int N;
  vector<vector<int>> next;
  vector<int> cnt;

  Trie() : N(0) {
    node();
  }

  int node() {
    next.emplace_back(A, -1);
    cnt.emplace_back(0);
    return N++;
  }

  inline int get(char c) {
    return c - 'a';
  }

  inline void insert(string s) {
    int cur = 0;
    for (char c : s) {
      int to = get(c);
      if (next[cur][to] == -1) next[cur][to] = node();
      cur = next[cur][to];
    }
    cnt[cur]++;
  }
};

void test_case() {
  int n, k;
  cin >> n >> k;

  Trie trie;
  while (n--) {
    string s;
    cin >> s;
    trie.insert(s);
  }

  n = trie.N;
  vector dp(n, vector(k + 1, n + 1));

  for (int at = n - 1; at >= 0; at--) {
    vector<int> tot_dp;
    for (int c = 0; c < 26; c++) {
      int to = trie.next[at][c];
      if (to == -1) continue;
      if (tot_dp.empty()) tot_dp = dp[to];
      else {
        vector<int> new_tot_dp(k + 1, n + 1);
        new_tot_dp[0] = 0;
        for (int k0 = 0; k0 <= k; k0++) {
          for (int k1 = 0; k0 + k1 <= k; k1++) {
            new_tot_dp[k0 + k1] = min(new_tot_dp[k0 + k1], tot_dp[k0] + dp[to][k1]);
          }
        }
        swap(tot_dp, new_tot_dp);
      }
    }

    if (!tot_dp.empty()) dp[at] = tot_dp;
    else dp[at] = vector<int>(k + 1, n + 1), dp[at][0] = 0;

    for (int kk = 0; kk <= k; kk++) {
      dp[at][kk]++;
    }

    if (trie.cnt[at]) {
      for (int kk = k; kk >= 1; kk--) {
        dp[at][kk] = dp[at][kk - 1];
      }
    }

    dp[at][0] = 0;
  }

  cout << (dp[0][k] - 1) * 2 + k << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    cout << "Case #" << cs << ": ";
    test_case();
  }

  return 0;
}