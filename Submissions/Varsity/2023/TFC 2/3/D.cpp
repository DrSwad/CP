#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int D = 20;

ll dp[D][2][2][16][3][5][7][9];

string num;
ll DP(int at, bool nonzero, bool under, int mask, int r3, int r5, int r7, int r9) {
  // DB();
  // debug(at, nonzero, under, mask, r3, r5, r7, r9);
  if (at == D) {
    if ((mask >> 0 & 1) and r3 == 0) return 0;
    if ((mask >> 1 & 1) and r5 == 0) return 0;
    if ((mask >> 2 & 1) and r7 == 0) return 0;
    if ((mask >> 3 & 1) and r9 == 0) return 0;
    return 1;
  }

  ll &cdp = dp[at][nonzero][under][mask][r3][r5][r7][r9];
  if (cdp != -1) return cdp;
  cdp = 0;

  int min_d = 0, max_d = under ? 9 : num[at] - '0';
  for (int d = min_d; d <= max_d; d++) {
    if ((nonzero or d != 0) and d != 3 and d != 5 and d != 7 and d != 9) continue;
    int nr3 = (r3 * 10 + d) % 3;
    int nr5 = (r5 * 10 + d) % 5;
    int nr7 = (r7 * 10 + d) % 7;
    int nr9 = (r9 * 10 + d) % 9;
    // debug(d);
    int di = d == 3 ? 0 : d == 5 ? 1 : d == 7 ? 2 : d == 9 ? 3 : -1;
    cdp += DP(at + 1, nonzero or d != 0, under or d < num[at] - '0', di == -1 ? mask : mask | 1 << di, nr3, nr5, nr7, nr9);
  }

  return cdp;
}

ll count(ll n) {
  memset(dp, -1, sizeof dp);
  num = to_string(n);
  while (num.length() < 20) num = '0' + num;
  // DB();
  // debug(n, num);
  ll ret = DP(0, false, false, 0, 0, 0, 0, 0);
  // debug(ret);
  return ret;
}

void test_case() {
  ll a, b, k;
  cin >> a >> b >> k;

  ll sub = count(a - 1);
  // debug(sub);

  ll L = a - 1, R = b + 1;
  while (R - L > 1) {
    ll mid = (L + R) / 2;
    ll add = count(mid);
    // debug(mid, add);
    if (add - sub >= k) R = mid;
    else L = mid;
  }

  cout << (R > b ? -1 : R) << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  // cerr << count(59) << "\n";

  int t;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    test_case();
  }

  return 0;
}