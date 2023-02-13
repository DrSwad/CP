#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int MOD = 998244353;

ll binExp(ll a, ll e, ll m = MOD) {
  if (e == -1) e = m - 2;
  ll ret = 1;
  while (e) {
    if (e & 1) ret = ret * a % m;
    a = a * a % m, e >>= 1;
  }
  return ret;
}

void test_case() {
  string p, q;
  cin >> p >> q;
  int np = p.length(), nq = q.length();

  ll ans = 0;
  for (int lp = 1; lp <= np; lp++) {
    string pref = p.substr(0, lp);
    for (int ls = 1; ls <= np; ls++) {
      string suff = p.substr(np - ls);

      string pattern = pref + suff;
      int len = pattern.length();
      for (int i = 0; i <= nq - len; i++) {
        if (q.substr(i, len) == pattern) {
          (ans += 1) %= MOD;
          break;
        }
      }
    }
  }
  (ans *= binExp((ll)np * np % MOD, -1)) %= MOD;

  cout << ans << "\n";
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