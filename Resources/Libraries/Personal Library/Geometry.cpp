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

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  return 0;
}