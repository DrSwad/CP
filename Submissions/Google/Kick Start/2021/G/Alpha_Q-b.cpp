#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N = 100010;

int t, cs, n;
ll x[N][2], y[N][2];

ll getX (ll at) {
  ll ret = 0;
  for (int i = 0; i < n; ++i) {
    if (x[i][1] < at) ret += at - x[i][1];
    else if (at < x[i][0]) ret += x[i][0] - at;
  }
  return ret;
}

ll getY (ll at) {
  ll ret = 0;
  for (int i = 0; i < n; ++i) {
    if (y[i][1] < at) ret += at - y[i][1];
    else if (at < y[i][0]) ret += y[i][0] - at;
  }
  return ret;
}

int main() {
  cin >> t;
  while (t--) {
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
      scanf("%lld %lld %lld %lld", x[i], y[i], x[i] + 1, y[i] + 1);
    }
    ll lo = INT_MIN, hi = INT_MAX;
    while (lo < hi) {
      ll mid = lo + hi >> 1;
      if (getX(mid) > getX(mid + 1)) lo = mid + 1;
      else hi = mid;
    }
    ll best_x = lo;
    lo = INT_MIN, hi = INT_MAX;
    while (lo < hi) {
      ll mid = lo + hi >> 1;
      if (getY(mid) > getY(mid + 1)) lo = mid + 1;
      else hi = mid;
    }
    ll best_y = lo;
    printf("Case #%d: %lld %lld\n", ++cs, best_x, best_y);
  }
  return 0;
}

