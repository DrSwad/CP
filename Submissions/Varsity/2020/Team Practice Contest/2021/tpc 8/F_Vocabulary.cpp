#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 1e6 + 5;
const int MOD = 1e9 + 9;

int nn;
int n[3];
char s[3][N];
int suff_fill[3][N];
int pref_eq[3][N];
int suff_lex[3][N];

void solve() {
  nn = 0;
  for (int it = 0; it < 3; it++) {
    scanf("%s", s[it] + 1);
    n[it] = strlen(s[it] + 1);
    nn = max(nn, n[it]);
  }

  for (int it = 0; it < 3; it++) {
    for (int i = n[it] + 1; i <= nn; i++) {
      s[it][i] = 0;
    }
  }

  for (int it = 0; it < 3; it++) {
    suff_fill[it][nn + 1] = 1;
    for (int i = n[it]; ~i; i--) {
      suff_fill[it][i] = (ll)suff_fill[it][i + 1] * (s[it][i] == '?' ? 26 : 1) % MOD;
    }
  }

  pref_eq[0][0] = 1;
  for (int i = 1; i <= nn; i++) {
    if (s[0][i] != '?') {
      if (s[1][i] != '?') pref_eq[0][i] = s[0][i] != '?' ? s[0][i] == s[1][i] ? pref_eq[0][i - 1] : 0 : 1;
      else;
    }
  }
}

int main() {
  int t;
  cin >> t;

  while (t--) {
    solve();
  }

  return 0;
}