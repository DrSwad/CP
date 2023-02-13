// Test if a point is inside a convex polygon in O(lg n) time
// Solves SPOJ INOROUT

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair <ll, ll> point;

#define x first
#define y second

struct segment {
  point P1, P2;

  segment () {}
  segment (point P1, point P2) : P1(P1), P2(P2) {}
};

inline ll ccw (point A, point B, point C) {
  return (B.x - A.x) * (C.y - A.y) - (C.x - A.x) * (B.y - A.y);
}

inline bool pointOnSegment (segment S, point P) {
  ll x = P.x, y = P.y, x1 = S.P1.x, y1 = S.P1.y, x2 = S.P2.x, y2 = S.P2.y;
  ll a = x - x1, b = y - y1, c = x2 - x1, d = y2 - y1, dot = a * c + b * d, len = c * c + d * d;
  if (x1 == x2 and y1 == y2) return x1 == x and y1 == y;
  if (dot < 0 or dot > len) return 0;
  return x1 * len + dot * c == x * len and y1 * len + dot * d == y * len;
}

const int M = 17;
const int N = 10010;

struct polygon {
  int n; // n > 1
  point p[N]; // clockwise order

  polygon () {}
  polygon (int _n, point *T) {
    n = _n;
    for (int i = 0; i < n; ++i) p[i] = T[i];
  }

  bool contains (point P, bool strictlyInside) {
    int lo = 1, hi = n - 1;
    while (lo < hi){
      int mid = lo + hi >> 1;
      if (ccw(p[0], P, p[mid]) > 0) lo = mid + 1;
      else hi = mid;
    }
    if (ccw(p[0], P, p[lo]) > 0) lo = 1;
    if (!strictlyInside and pointOnSegment(segment(p[0], p[n - 1]), P)) return 1;
    if (!strictlyInside and pointOnSegment(segment(p[lo], p[lo - 1]), P)) return 1;
    if (lo == 1 or ccw(p[0], P, p[n - 1]) == 0) return 0;
    return ccw(p[lo], P, p[lo - 1]) < 0;
  }
};

int q;
point P;
polygon p;

int main() {
  cin >> p.n >> q;
  for (int i = p.n - 1; i >= 0; --i) {
    scanf("%lld %lld", &p.p[i].x, &p.p[i].y);
  }
  while (q--) {
    scanf("%lld %lld", &P.x, &P.y);
    puts(p.contains(P, 0) ? "D" : "F");
  }
  return 0;
}

