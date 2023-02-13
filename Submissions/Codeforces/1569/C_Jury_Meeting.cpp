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
  int n;
  cin >> n;

  vector<int> a(n);
  for (int &i : a) cin >> i;

  sort(a.begin(), a.end());

  if (a[n - 1] > a[n - 2] + 1) cout << "0\n";
  else {
    ll ans = 1;
    for (int i = 1; i <= n; i++) {
      (ans *= i) %= MOD;
    }

    if (a[n - 1] > a[n - 2]) {
      int f = count(a.begin(), a.end(), a[n - 2]);
      (ans *= binExp(f + 1, -1)) %= MOD;
      (ans *= f) %= MOD;
    }

    cout << ans << "\n";
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int t;
  cin >> t;

  while (t--) {
    test_case();
  }

  return 0;
}