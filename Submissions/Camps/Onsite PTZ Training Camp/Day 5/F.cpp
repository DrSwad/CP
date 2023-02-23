#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int MOD = 1e9 + 7;
const int INV2 = (MOD + 1) / 2;
const int INV6 = (MOD + 1) / 6;

ll sum1(ll n) {
  n %= MOD;
  return n * (n + 1) % MOD * INV2 % MOD;
}

ll sum2(ll n) {
  n %= MOD;
  return n * (n + 1) % MOD * (2 * n + 1) % MOD * INV6 % MOD;
}

ll sum3(ll n) {
  n %= MOD;
  return sum1(n) * sum1(n) % MOD;
}

ll func(ll c0, ll c1, ll c2, ll c3, ll m) {
  if (m < 0) return 0;
  m %= MOD;
  ll ans = 0;
  (ans += c0 * (m + 1) % MOD) %= MOD;
  (ans += c1 * sum1(m) % MOD) %= MOD;
  (ans += c2 * sum2(m) % MOD) %= MOD;
  (ans += c3 * sum3(m) % MOD) %= MOD;
  return ans;
}

ll solve(int n, ll pos_i, ll pos_j, ll val, ll a, ll b) {
  if (pos_i > pos_j) swap(pos_i, pos_j);
  if (pos_j > b) return 0;

  ll m1 = max(0ll, ((a - pos_i) + (n - 1)) / n);
  ll m2 = (b - pos_j) / n;
  if (m2 < m1) return 0;

  ll x = val % MOD;
  ll y = ((ll)pos_i - a + 1 + MOD) % MOD;
  ll z = ((ll)b - pos_j + 1 + MOD) % MOD;

  ll c0 = x * y % MOD * z % MOD;
  ll c1 = (x * z % MOD + y * z % MOD - x * y % MOD + MOD) % MOD;
  (c1 *= n) %= MOD;
  ll c2 = (z - x - y + 2ll * MOD) % MOD;
  (c2 *= n) %= MOD;
  (c2 *= n) %= MOD;
  ll c3 = (MOD - (ll)n * n % MOD * n % MOD) % MOD;

  // debug(m1, m2);
  // debug(x, y, z);
  // debug(c0, c1, c2, c3);

  ll ret = (func(c0, c1, c2, c3, m2) - func(c0, c1, c2, c3, m1 - 1) + MOD) % MOD;
  // ll ret = 0;
  // for (ll m = m1; m <= m2; m++) {
  // (ret += (c0 + c1 * m % MOD + c2 * m % MOD * m % MOD + c3 * m % MOD * m % MOD * m % MOD) % MOD) %= MOD;
  // (ret += (x + n * m) * (y + n * m) % MOD * (z - n * m)) %= MOD;
  // ll new_pos_i = pos_i + m * n;
  // ll new_pos_j = pos_j + m * n;
  // ll new_val = val + m * n;
  // if (a <= new_pos_i and new_pos_j <= b) {
  //   ret += new_val * (new_pos_i - a + 1) * (b - new_pos_j + 1);
  // }
  // }

  return ret;
}

void test_case() {
  int n;
  ll a, b;
  cin >> n >> a >> b;

  vector<int> s(n);
  for (int &i : s) cin >> i;

  ll ans = 0;

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (s[i] % n != s[j] % n) continue;

      ll pos_i = i, pos_j = j;
      ll val_i = s[i], val_j = s[j];
      if (val_i < val_j) pos_i += val_j - val_i, val_i = val_j;
      if (val_j < val_i) pos_j += val_i - val_j, val_j = val_i;
      assert(val_i == val_j);

      (ans += solve(n, pos_i, pos_j, val_i, a, b)) %= MOD;
    }
  }

  cout << ans << "\n";
}

int main() {
  int t;
  cin >> t;

  while (t--) {
    test_case();
  }

  return 0;
}