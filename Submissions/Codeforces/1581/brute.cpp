#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 5;

int n, m;
int x[N], y[N];
int added[N];
int pref[N];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    cin >> x[i] >> y[i];
  }

  int psum = 0;
  for (int qq = 1; qq <= m; qq++) {
    int op, k;
    cin >> op >> k ;

    int from = op == 2 ? added[k] : qq;
    int xx = x[k];
    int yy = y[k];
    int period = xx + yy;
    int add = op == 1 ? 1 : -1;

    if (op == 1) added[k] = qq;

    for (int at = from; at < N; at += period) {
      int st = at + xx;
      int en = at + period;
      if (st < N) pref[st] += add;
      if (en < N) pref[en] -= add;
      if (st < qq and qq <= en) pref[qq] += add;
    }

    psum += pref[qq];
    int ans = psum;

    cout << ans << "\n";
  }

  return 0;
}