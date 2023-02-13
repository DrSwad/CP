#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int MOD = 1e9 + 7;
const int N = 1e6 + 5;

int fact[N], ifact[N], inv[N];

void init() {
  inv[1] = fact[0] = ifact[0] = 1;
  for (int i = 2; i < N; i++) inv[i] = (ll)inv[MOD % i] * (MOD - MOD / i) % MOD;
  for (int i = 1; i < N; i++) fact[i] = (ll)fact[i - 1] * i % MOD;
  for (int i = 1; i < N; i++) ifact[i] = (ll)ifact[i - 1] * inv[i] % MOD;
}

int nCr(int n, int r) {
  if (r<0 or r> n) return 0;
  return 1ll * fact[n] * ifact[r] % MOD * ifact[n - r] % MOD;
}

int count(int left, int right, int mid) {
  assert(left > 0);
  assert(mid >= 2);
  int ret = 0;
  for (int mi = 1; mi < mid; mi++) {
    int l = left - 1;
    int r = right + mi;
    (ret += nCr(l + r, l)) %= MOD;
  }
  return ret;
}

void test_case() {
  int n;
  cin >> n;

  vector<int> a(n);
  for (int &i : a) cin >> i;

  if (count(a.begin(), a.end(), a[0]) == n) {
    cout << "1\n";
    return;
  }

  sort(a.begin(), a.end());
  int ans = 0;

  for (int l = 0; l < n; ) {
    int r = l;
    while (r < n and a[r] == a[l]) r++;

    int left = l;
    int right = n - r;

    (ans += nCr(left + right, left)) %= MOD;
    if (r - l > 1) {
      if (left > 0) {
        (ans += count(left, right, r - l)) %= MOD;
      }
      if (right > 0) {
        (ans += count(right, left, r - l)) %= MOD;
      }
    }

    l = r;
  }

  cout << ans << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  init();

  int t = 1;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    // cout << "Case " << cs << ": ";
    test_case();
  }

  return 0;
}