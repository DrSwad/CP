#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> point;
#define x first
#define y second

ll cross(point a, point b) {
  return a.x * b.y - a.y * b.x;
}

ll area2(point a, point b) {
  return cross(a, b);
}

const ll X = 2000;

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);

  int n;
  cin >> n;

  ll mn_x = X, mx_x = -X;
  vector<point> poly(n);
  for (auto &p : poly) {
    cin >> p.x >> p.y;
    if (p.y == 0) {
      mn_x = min(mn_x, p.x);
      mx_x = max(mx_x, p.x);
    }
  }

  ll A2 = 0;
  ll gx_6A = 0;
  for (int i = 0; i < n; i++) {
    ll T2 = area2(poly[i], poly[(i + 1) % n]);
    A2 += T2;
    gx_6A += (poly[i].x + poly[(i + 1) % n].x) * T2;
  }
  if (A2 < 0) A2 = -A2, gx_6A = -gx_6A;

  if (poly[0].x * 3 * A2 < gx_6A) {
    gx_6A = -gx_6A;
    poly[0].x = -poly[0].x;
    mn_x = -mn_x;
    mx_x = -mx_x;
    swap(mn_x, mx_x);
  }

  if (poly[0].x<mn_x or gx_6A> mx_x * 3 * A2) {
    cout << "unstable\n";
    return 0;
  }

  if (poly[0].x == mn_x) {
    if (gx_6A != poly[0].x * 3 * A2) cout << "unstable\n";
    else cout << "0 .. inf\n";
    return 0;
  }
  else if (gx_6A == mx_x * 3 * A2) {
    if (gx_6A != poly[0].x * 3 * A2) cout << "0 .. 0\n";
    else cout << "0 .. inf\n";
    return 0;
  }

  auto fl = [&](ll a, ll b) { return a / b; };
  auto cl = [&](ll a, ll b) { return (a + b - 1) / b; };

  ll mn_w, mx_w;

  if (gx_6A >= mn_x * 3 * A2) mn_w = 0;
  else mn_w = fl(mn_x * 3 * A2 - gx_6A, 6 * (poly[0].x - mn_x));

  if (poly[0].x <= mx_x) mx_w = -1;
  else mx_w = cl(mx_x * 3 * A2 - gx_6A, 6 * (poly[0].x - mx_x));

  cout << mn_w << " .. ";
  if (mx_w == -1) cout << "inf\n";
  else cout << mx_w << "\n";

  return 0;
}