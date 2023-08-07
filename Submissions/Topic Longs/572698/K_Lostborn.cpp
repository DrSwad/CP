#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int K = 100;
const int N = 7e6;

ll n;
int k;
int a[K];
ll divs[N], dp[N], dp2[N];
ll ans;

void go(int at, bool parity, ll mul) {
  if (at >= k or mul * a[at] > n) {
    ll contrib = (mul >= N ? dp[n / mul] : dp2[mul]) - n / mul;
    if (parity) ans += contrib;
    else ans -= contrib;
    return;
  }

  go(at + 1, !parity, mul * a[at]);
  go(at + 1, parity, mul);
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> n >> k;
  for (int i = 0; i < k; i++) {
    cin >> a[i];
  }
  sort(a, a + k);

  int sz = 0;
  for (ll l = 1; l <= n; ) {
    ll d = n / l;
    divs[sz++] = d;
    l = n / d + 1;
  }
  divs[sz++] = 0;
  reverse(divs, divs + sz);

  int k1 = min(k, 12);

  for (int i = 0; i < k1; i++) {
    for (int j = sz - 1, ptr = sz - 1; j >= 0; j--) {
      // while (ptr >= 0 and divs[ptr] * a[i] > divs[j]) ptr--;
      dp[j] += divs[ptr] - dp[ptr];
    }
  }

  for (int i = 0; i < sz; i++) {
    if (divs[i] >= N) {
      dp2[n / divs[i]] = dp[i];
    }
  }
  for (int i = sz - 1; i >= 0; i--) {
    if (divs[i] < N) dp[divs[i]] = dp[i];
  }

  go(k1, 0, 1);

  cout << ans << "\n";

  return 0;
}