#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int sz = 1005;

int n; ll k;
char s[sz][sz];

ll upcum[sz];
ll rcum[sz][sz];

ll up_prefix(ll row) {
  int i = row / k;
  ll res = i ? upcum[i - 1] * k : 0;

  ll cnt = row % k + 1;
  res += rcum[i][0] * cnt;

  return res * k;
}

ll right_suffix(int i, ll col) {
  int j = col / k;
  ll res = rcum[i][j + 1] * k;

  ll cnt = k - col % k;
  res += cnt * (s[i][j] == '1');

  return res;
}

void solve() {
  scanf("%d %lld", &n, &k);
  for (int i = 0; i < n; i++) scanf("%s", s[i]);

  for (int i = 0; i < n; i++) {
    upcum[i] = 0;
    for (int j = 0; j < n; j++) upcum[i] += s[i][j] == '1';
    if (i) upcum[i] += upcum[i - 1];
  }

  for (int i = 0; i < n; i++) {
    rcum[i][n] = 0;
    for (int j = n - 1; j >= 0; j--) rcum[i][j] = rcum[i][j + 1] + (s[i][j] == '1');
  }

  int q;
  scanf("%d", &q);
  while (q--) {
    ll l, r;
    scanf("%lld %lld", &l, &r);

    ll row_l = l / (n * k);
    ll row_r = r / (n * k);
    ll ans = up_prefix(row_r) - up_prefix(row_l);

    l %= n * k;
    r %= n * k;

    ans += right_suffix(row_l / k, l);
    ans -= right_suffix(row_r / k, r);

    ans += s[row_r / k][r / k] == '1';

    printf("%lld\n", ans);
  }
}

int main() {
  int t, cs = 0;
  cin >> t;
  while (t--) {
    printf("Case %d:\n", ++cs);
    solve();
  }
}