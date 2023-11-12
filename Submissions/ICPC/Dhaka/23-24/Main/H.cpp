#include <bits/stdc++.h>

using namespace std;

typedef long double T;
typedef complex<T> point;

#define x real()
#define y imag()

inline T dot(point A, point B) {return (conj(A) * B).x;}
inline T cross(point A, point B) {return (conj(A) * B).y;}

const T INF = 2e9;
const T EPS = 1e-12;
const int MAGIC_B = 70;
const int MAGIC_T = 100;

void normalize(vector<point> &poly) {
  int pos = 0;
  for (int i = 0; i < poly.size(); ++i) {
    point P = poly[i];
    if (P.y < poly[pos].y or (P.y == poly[pos].y and P.x < poly[pos].x)) pos = i;
  }
  rotate(poly.begin(), poly.begin() + pos, poly.end());
}

inline int isUpper(point P) {
  return P.y > 0 or (P.y == 0 and P.x > 0);
}

vector<point> minkowskiSum(vector<point> polyA, vector<point> polyB) {
  normalize(polyA), normalize(polyB);
  vector<point> ord;
  for (int i = 0; i < polyA.size(); ++i) {
    int j = i + 1 < polyA.size() ? i + 1 : 0;
    ord.emplace_back(polyA[j] - polyA[i]);
  }
  for (int i = 0; i < polyB.size(); ++i) {
    int j = i + 1 < polyB.size() ? i + 1 : 0;
    ord.emplace_back(polyB[j] - polyB[i]);
  }
  sort(
    ord.begin(),
    ord.end(),
    [](auto A, auto B) {
      return (isUpper(A) == isUpper(B)) ? (cross(A, B) > 0) : (isUpper(A) > isUpper(B));
    }
  );
  point starting = polyA[0] + polyB[0];
  vector<point> res{starting};
  for (auto vec : ord) res.emplace_back(res.back() + vec);
  assert(res.back() == starting);
  res.pop_back(); return res;
}

inline bool isLeft(point A, point B, point P) {
  return cross(B - A, P - A) + EPS > 0;
}

inline T pointToSegment(point P, point A, point B) {
  if (dot(B - A, P - A) < 0) return abs(P - A);
  if (dot(A - B, P - B) < 0) return abs(P - B);
  return abs(cross(B - A, P - A)) / abs(A - B);
}

T distBS(vector<point> &poly, point P, int lo, int hi) {
  --hi; int n = poly.size();
  while (lo < hi) {
    int mid = lo + hi >> 1;
    if (pointToSegment(P, poly[mid], poly[(mid + 1) % n]) < pointToSegment(P, poly[(mid + 1) % n], poly[(mid + 2) % n])) hi = mid;
    else lo = mid + 1;
  }
  return pointToSegment(P, poly[lo], poly[(lo + 1) % n]);
}

T pointToPolygon(vector<point> &poly, point P) {
  int n = poly.size();
  if (isLeft(poly[0], poly[1], P) and !isLeft(poly[0], poly[n - 1], P)) {
    int lo = 0, hi = n - 2;
    while (lo < hi) {
      int mid = lo + hi + 1 >> 1;
      if (isLeft(poly[0], poly[mid], P)) lo = mid;
      else hi = mid - 1;
    }
    if (isLeft(poly[lo], poly[lo + 1], P)) return 0;
  }
  return min({distBS(poly, P, 0, n / 2), distBS(poly, P, n / 2, n), distBS(poly, P, 0, n)});
}

int main() {
  int t;
  cin >> t;
  while (t--) {
    int n, m, q;
    scanf("%d %d", &n, &m);
    vector<point> polyA(n), polyB(m);
    for (auto &P : polyA) {
      int inp_x, inp_y;
      scanf("%d %d", &inp_x, &inp_y);
      P = point(inp_x, inp_y);
    }
    for (auto &P : polyB) {
      int inp_x, inp_y;
      scanf("%d %d", &inp_x, &inp_y);
      P = point(inp_x, inp_y);
    }
    for (auto &P : polyA) P *= point(-1, 0);
    auto cover = minkowskiSum(polyA, polyB);
    scanf("%d", &q);
    while (q--) {
      int inp_x, inp_y, inp_s;
      scanf("%d %d %d", &inp_x, &inp_y, &inp_s);
      point dir(inp_x, inp_y);
      T lo = 0, hi = INF, s = inp_s;
      for (int it = 0; it < MAGIC_T; ++it) {
        T l = (lo + lo + hi) / 3, r = (lo + hi + hi) / 3;
        if (pointToPolygon(cover, l * dir) - l * s < pointToPolygon(cover, r * dir) - r * s) hi = r;
        else lo = l;
      }
      if (pointToPolygon(cover, lo * dir) - lo * s > EPS) {
        puts("-1");
        continue;
      }
      lo = 0;
      for (int it = 0; it < MAGIC_B; ++it) {
        T mid = 0.5 * (lo + hi);
        if (pointToPolygon(cover, mid * dir) - mid * s < 0) hi = mid;
        else lo = mid;
      }
      printf("%0.12f\n", (double) lo);
    }
  }
  return 0;
}