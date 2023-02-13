#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int MOD = 998244353;
const int N = 1e3 + 5;
const int C = 17;

int n;
string s;
int qcnt;
int need[N][N];
int flex[N][N];
int contrib[C + 1][1 << C];
int p[C + 1][N];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  for (int a = 1; a <= C; a++) {
    p[a][0] = 1;
    for (int e = 1; e < N; e++) {
      p[a][e] = (ll)p[a][e - 1] * a % MOD;
    }
  }

  cin >> n >> s;
  qcnt = count(s.begin(), s.end(), '?');
  s = "0" + s;

  for (int i = 1; i <= n; i++) {
    flex[i + 1][i - 1] = qcnt;
    flex[i + 1][i] = qcnt;
  }

  for (int len = 1; len <= n; len++) {
    for (int i = 1; i + len - 1 <= n; i++) {
      int j = i + len - 1;
      if (need[i + 1][j - 1] == -1 or
          (s[i] != '?' and s[j] != '?' and s[i] != s[j])
          ) {
        need[i][j] = -1;
      }
      else {
        need[i][j] = need[i + 1][j - 1];
        flex[i][j] = flex[i + 1][j - 1];
        if ((s[i] == '?') != (s[j] == '?')) {
          need[i][j] |= 1 << ((s[i] != '?' ? s[i] : s[j]) - 'a');
        }
        if (i != j and (s[i] == '?' or s[j] == '?')) {
          flex[i][j]--;
        }

        for (int sz = 1; sz <= C; sz++) {
          (contrib[sz][need[i][j]] += p[sz][flex[i][j]]) %= MOD;
        }
      }
    }
  }

  for (int sz = 1; sz <= C; sz++) {
    for (int i = 0; i < C; i++) {
      for (int mask = 0; mask < (1 << C); mask++) {
        if (mask & 1 << i) {
          (contrib[sz][mask] += contrib[sz][mask ^ 1 << i]) %= MOD;
        }
      }
    }
  }

  int q;
  cin >> q;
  while (q--) {
    string t;
    cin >> t;

    int mask = 0;
    for (char c : t) {
      mask |= 1 << (c - 'a');
    }

    cout << contrib[__builtin_popcount(mask)][mask] << "\n";
  }

  return 0;
}