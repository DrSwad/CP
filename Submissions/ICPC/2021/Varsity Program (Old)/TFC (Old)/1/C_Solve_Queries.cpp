#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int A = 26;
const int K = 120;
const ll M = 1e15;

string s;
string t[A];
ll k;
ll dp[A][K];

void init_dp() {
  for (int kk = 0; kk < K; kk++) {
    for (int i = 0; i < A; i++) {
      if (kk == 0) dp[i][kk] = 1;
      else {
        for (char c : t[i]) {
          dp[i][kk] += dp[c - 'a'][kk - 1];
          if (dp[i][kk] > M) {
            dp[i][kk] = M + 1;
            break;
          }
        }
      }
    }
  }
}

char solve(int c, int k, ll m) {
  if (k == 0) {
    assert(m <= t[c].length());
    return t[c][m - 1];
  }

  int nc;
  for (char _nc : t[c]) {
    nc = _nc - 'a';
    if (dp[nc][k] >= m) break;
    m -= dp[nc][k];
  }

  return solve(nc, k - 1, m);
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> s;
  for (int i = 0; i < A; i++) cin >> t[i];
  cin >> k;
  if (k > 60) k = 60 + k % 60;

  init_dp();

  int q;
  cin >> q;

  while (q--) {
    ll m;
    cin >> m;

    int c;
    for (char _c : s) {
      c = _c - 'a';
      if (dp[c][k] >= m) break;
      m -= dp[c][k];
    }

    cout << solve(c, k - 1, m) << "\n";
  }

  return 0;
}