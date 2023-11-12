#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
int mod;

int add(int a, int b) {
  int c = a + b;
  return c < mod ? c : c - mod;
}

int mul(int a, int b) {
  return 1ll * a * b % mod;
}

ll binExp(ll a, ll e, ll m = mod) {
  if (e == -1) e = m - 2;
  ll ret = 1;
  while (e) {
    if (e & 1) ret = ret * a % m;
    a = a * a % m, e >>= 1;
  }
  return ret;
}

void test_case() {
  int n, q;
  cin >> n >> mod >> q;

  vector<int> pref(n + 2), suff(n + 2);
  pref[0] = 1;
  for (int i = 1; i <= n; i++) {
    pref[i] = mul(pref[i - 1], binExp(i, i - 1));
  }
  suff[n + 1] = 1;
  for (int i = n; i >= 1; i--) {
    suff[i] = mul(suff[i + 1], binExp(i, n + 1 - i));
  }

  vector<int> middle(n + 1);
  middle[n / 2] = n % 2 == 0 ? 1 : (n + 1) / 2;
  for (int i = n / 2 - 1; i >= 1; i--) {
    middle[i] = mul(middle[i + 1], mul(i + 1, (n + 1) - (i + 1)));
  }

  while (q--) {
    int r;
    cin >> r;
    r = min(r, n - r);

    int ans = mul(pref[r], mul(suff[n - r + 1], binExp(middle[r], r)));
    cout << ans << "\n";
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    test_case();
  }

  return 0;
}