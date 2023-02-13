#include <bits/stdc++.h>
using namespace std;

#define x first
#define y second

typedef long long ll;
typedef pair<ll, ll> point; // (x, y)
typedef tuple<ll, ll, ll> line; // a * x + b * y + c = 0

line line_from_points(point p1, point p2) {
  ll a = p2.y - p1.y;
  ll b = p1.x - p2.x;
  assert(a or b);
  if (a < 0 or (a == 0 and b < 0)) a = -a, b = -b;
  ll c = -(p1.x * a + p1.y * b);
  ll g = gcd(a, b);
  a /= g, b /= g, c /= g;
  return line(a, b, c);
}

bool is_point_on_line(point p, line l) {
  auto [x, y] = p;
  auto [a, b, c] = l;
  return a * x + b * y + c == 0;
}

line perpendicular(point p, line l) {
  assert(is_point_on_line(p, l));
  auto [x, y] = p;
  auto [a, b, c] = l;
  swap(a, b); b = -b;
  if (a < 0 or (a == 0 and b < 0)) a = -a, b = -b;
  c = -(x * a + y * b);
  return line(a, b, c);
}

const int N = 1e3 + 5;

int n;
point P[N];
ll w[N];
map<line, map<pair<ll, ll>, ll>> mp;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> P[i].x >> P[i].y >> w[i];
    P[i].x *= 2, P[i].y *= 2;
  }

  for (int i = 1; i <= n; i++) {
    for (int j = i + 1; j <= n; j++) {
      point M((P[i].x + P[j].x) / 2, (P[i].y + P[j].y) / 2);
      line l = line_from_points(P[i], P[j]);
      line p = perpendicular(M, l);
      ll &W = mp[p][M];
      W = max(W, w[i] + w[j]);
    }
  }

  ll ans = -1;

  for (const auto & [l, mp2] : mp) {
    ll mx1 = -1, mx2 = -1;
    for (const auto & [P, w] : mp2) {
      if (w > mx1) mx2 = mx1, mx1 = w;
      else if (w > mx2) mx2 = w;
    }
    if (~mx1 and ~mx2) ans = max(ans, mx1 + mx2);
  }

  cout << ans << "\n";

  return 0;
}