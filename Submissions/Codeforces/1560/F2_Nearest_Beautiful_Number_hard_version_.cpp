#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int D = 10, N = 10;

void test_case() {
  ll nv;
  cin >> nv;
  string ns = to_string(nv);

  int k;
  cin >> k;

  vector<ll> p(N), pref(N);
  p[0] = pref[0] = 1;
  for (int i = 1; i < N; i++) {
    p[i] = p[i - 1] * D;
    pref[i] = pref[i - 1] + p[i];
  }

  ll ans = LLONG_MAX;

  for (int mask = 0; mask < 1 << D; mask++) {
    if (__builtin_popcount(mask) != k) continue;

    ll curr = LLONG_MAX;
    ll prv = 0;
    int len = ns.length();

    for (int i = 0; i <= len; i++) {
      if (i == len) {
        curr = nv;
        break;
      }

      ll d = ns[i] - '0';
      int exp = (len - 1) - i;

      if (mask >> (d + 1) > 0) {
        ll nd = __builtin_ctz(mask >> (d + 1)) + (d + 1);
        ll sm = __builtin_ctz(mask);

        curr = prv + nd * p[exp] + (exp == 0 ? 0 : sm * pref[exp - 1]);
      }

      if ((mask >> d & 1) == 0) break;
      prv += d * p[exp];
    }

    ans = min(ans, curr);
  }

  cout << ans << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int t;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    // cout << "Case " << cs << ": ";
    test_case();
  }

  return 0;
}