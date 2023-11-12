#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 1e5 + 5;
const int LOGN = 19;

int n;
int low, up;
int a[N];
ll pref[N];
ll mn_pref[LOGN][N], mx_pref[LOGN][N];
int nxt[2 * N];
int lift[LOGN][2 * N];

void init_sparse_table() {
  for (int i = 0; i <= n; i++) {
    mn_pref[0][i] = pref[i];
    mx_pref[0][i] = pref[i];
  }
  for (int j = 1; j < LOGN; j++) {
    for (int i = 0; i <= (n + 1) - (1 << j); i++) {
      mn_pref[j][i] = min(mn_pref[j - 1][i], mn_pref[j - 1][i + (1 << (j - 1))]);
      mx_pref[j][i] = max(mx_pref[j - 1][i], mx_pref[j - 1][i + (1 << (j - 1))]);
    }
  }
}

pair<ll, ll> query_sparse_table(int from, int to) {
  assert(0 <= from && from <= to && to <= n);
  int lg = 32 - __builtin_clz(to - from + 1) - 1;
  ll mn = min(mn_pref[lg][from], mn_pref[lg][to - (1 << lg) + 1]);
  ll mx = max(mx_pref[lg][from], mx_pref[lg][to - (1 << lg) + 1]);
  return {mn, mx};
}

int calc_nxt(int at, int val) {
  // val + pref[i] - pref[at] < low
  ll low_pref = pref[at] + low - val;
  // val + pref[i] - pref[at] > up
  ll up_pref = pref[at] + up - val;

  int L = at, R = n + 1;
  while (R - L > 1) {
    int mid = (L + R) / 2;
    auto [mn, mx] = query_sparse_table(at + 1, mid);
    if (low_pref <= mn and mx <= up_pref) L = mid;
    else R = mid;
  }

  if (R == n + 1) return 2 * (n + 1);
  else if (pref[R] < low_pref) return R * 2;
  else return R * 2 + 1;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> n >> low >> up;
  for (int i = 0; i < n; i++) cin >> a[i];

  for (int i = 0; i < n; i++) {
    pref[i + 1] = pref[i] + a[i];
  }

  init_sparse_table();

  for (int i = 0; i < n; i++) {
    nxt[2 * i] = calc_nxt(i, low);
    nxt[2 * i + 1] = calc_nxt(i, up);
    // debug(i, nxt[2 * i]);
    // debug(i, nxt[2 * i + 1]);
  }
  nxt[2 * n] = nxt[2 * n + 1] = 2 * (n + 1);

  for (int i = 0; i < 2 * (n + 1); i++) {
    lift[0][i] = nxt[i];
  }

  for (int j = 1; j < LOGN; j++) {
    for (int i = 0; i < 2 * (n + 1); i++) {
      if (lift[j - 1][i] == 2 * (n + 1)) lift[j][i] = 2 * (n + 1);
      else lift[j][i] = lift[j - 1][lift[j - 1][i]];
    }
  }

  int q;
  cin >> q;

  while (q--) {
    int b, e, x;
    cin >> b >> e >> x;
    b--, e--, x;
    e++;

    if (calc_nxt(b, x) / 2 <= e) {
      b = calc_nxt(b, x);
      for (int j = LOGN - 1; j >= 0; j--) {
        if (lift[j][b] < 2 * (e + 1)) b = lift[j][b];
      }
      x = b % 2 == 0 ? low : up;
      b = b / 2;
    }

    x += pref[e] - pref[b];
    cout << x << "\n";
  }

  return 0;
}