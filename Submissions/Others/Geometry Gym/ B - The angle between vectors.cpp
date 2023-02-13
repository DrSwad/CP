#include <bits/stdc++.h>
using namespace std;

#define PI acos(-1)
typedef long long ll;
typedef long double ld;
#define point pair<int, int>
#define x first
#define y second
point operator-(point &a, point &b) { return point(a.x - b.x, a.y - b.y); }

ll dot(point a, point b) { return (ll)a.x * b.x + (ll)a.y * b.y; }
ll cross(point a, point b) { return (ll)a.x * b.y - (ll)a.y * b.x; }
ld abs(point a) { return sqrtl((ll)a.x * a.x + (ll)a.y * a.y); }
ld angle(point a, point b) { return acos(clamp(dot(a, b) / abs(a) / abs(b), -1.0L, 1.0L)); }
ld orient(point a, point b, point c) { return cross(b - a, c - a); }
ld polar_angle(point a, point b) {
  if (orient({0, 0}, a, b) >= 0) return angle(a, b);
  else return 2 * PI - angle(a, b);
}

int main() {
  freopen("angle2.in", "r", stdin);
  freopen("angle2.out", "w", stdout);
  cout << fixed << setprecision(10);

  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  point pa, pb;
  cin >> pa.x >> pa.y >> pb.x >> pb.y;
  cout << angle(pa, pb) << "\n";

  return 0;
}