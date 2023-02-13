#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll MOD = 998244353;
const ll INV2 = (MOD + 1) / 2;
const ll INV3 = (MOD + 1) / 3;
const ll INV4 = (3ll * MOD + 1) / 4;

ll mul(ll a, ll b) {
  a %= MOD;
  b %= MOD;
  return a * b % MOD;
}

ll nC4(ll n) {
  ll res = n;
  res = mul(res, n - 1);
  res = mul(res, n - 2);
  res = mul(res, n - 3);
  res = mul(res, INV2);
  res = mul(res, INV3);
  res = mul(res, INV4);
  return res;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, m;
  cin >> n >> m;

  ll tot_rects = mul(mul(nC4(n), nC4(m)), 18);
  ll bad_rects = mul(mul(nC4(n), nC4(m)), 4);
  ll nested_rects = mul(mul(nC4(n), nC4(m)), 1);
  ll ans = (tot_rects - bad_rects + nested_rects) % MOD;
  if (ans < 0) ans += MOD;
  cout << ans << "\n";

  return 0;
}