#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int B = 63;
const int MOD = int(1e9) + 7;
const int INV2 = (MOD + 1) / 2;

ll total_terms(ll last_term) {
  ll ret = 0;
  for (int b = 0; b < B; b++) {
    ret += last_term >> b;
  }
  return ret;
}

ll total_sum(ll last_term) {
  ll ret = 0;
  for (int b = 0; b < B; b++) {
    ll cnt = last_term >> b;
    cnt %= MOD;
    (ret += (1ll << b) % MOD * cnt % MOD * (cnt + 1) % MOD * INV2 % MOD) %= MOD;
  }
  return ret;
}

ll solve(ll n) {
  if (n == 1) return 1;
  n--;

  ll last_term;
  ll L = 1, R = n + 1;
  while (R > L + 1) {
    ll mid = (L + R) / 2;
    if (total_terms(mid - 1) <= n) L = mid;
    else R = mid;
  }
  last_term = L;

  ll ans = total_sum(last_term - 1);
  (ans += last_term * (n - total_terms(last_term - 1)) % MOD) %= MOD;
  (ans += 1) %= MOD;
  return ans;
}

int main() {
  int t;
  cin >> t;

  while (t--) {
    ll n;
    cin >> n;
    cout << solve(n) << "\n";
  }

  return 0;
}