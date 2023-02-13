#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 1e5 + 5;
const int B = 45;

int n;
ll k;
ll a[N];
ll dp[B];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> n >> k;
  for (int i = 0; i < n; i++) cin >> a[i];

  for (int b = 0; b < B; b++) {
    int cnt = 0;
    for (int i = 0; i < n; i++) {
      cnt += (a[i] >> b & 1);
    }

    dp[b] = (b > 0 ? dp[b - 1] : 0) + (1ll << b) * max(cnt, n - cnt);
  }

  ll ans = 0;
  for (int i = 0; i < n; i++) {
    ans += a[i] ^ k;
  }

  ll cnum = 0;
  for (int b = B - 1; b >= 0; b--) {
    if (k >> b & 1) {
      ll cans = (b > 0 ? dp[b - 1] : 0);
      ll mask = ((1ll << B) - 1) - ((1ll << b) - 1);
      for (int i = 0; i < n; i++) {
        cans += (a[i] & mask) ^ cnum;
      }
      ans = max(ans, cans);

      cnum += 1ll << b;
    }
  }

  cout << ans << "\n";

  return 0;
}