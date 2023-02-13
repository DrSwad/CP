#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

struct pt {
  long double x, y;
  pt() {}
  pt(long double x, long double y) : x(x), y(y) {}
  pt(const pt &p) : x(p.x), y(p.y) {}

  pt operator +(const pt &p) const { return pt(x + p.x, y + p.y); }
  pt operator -(const pt &p) const { return pt(x - p.x, y - p.y); }
  pt operator *(long double c) const { return pt(x * c, y * c); }
};

inline long double dot(pt u, pt v) { return u.x * v.x + u.y * v.y; }
inline long double cross(pt u, pt v) {return u.x * v.y - u.y * v.x;}
inline long double triArea2(pt a, pt b, pt c) { return cross(b - a, c - a); }

inline bool inDisk(pt a, pt b, pt p) { return dot(a - p, b - p) <= 0; }
inline bool onSegment(pt a, pt b, pt p) { return triArea2(a, b, p) == 0 && inDisk(a, b, p); }

// points of the polygon has to be in ccw order
// if strict, returns false when a is on the boundary
inline bool insideConvexPoly(const vector<pt> &C, pt p, bool strict) {
  int nc = C.size();
  int st = 1, en = nc - 1, mid;
  while (en - st > 1) {
    mid = (st + en) >> 1;
    if (triArea2(C[0], C[mid], p) < 0) en = mid;
    else st = mid;
  }
  if (strict) {
    if (st == 1) if (onSegment(C[0], C[st], p)) return false;
    if (en == nc - 1) if (onSegment(C[0], C[en], p)) return false;
    if (onSegment(C[st], C[en], p)) return false;
  }
  if (triArea2(C[0], C[st], p) < 0) return false;
  if (triArea2(C[st], C[en], p) < 0) return false;
  if (triArea2(C[en], C[0], p) < 0) return false;
  return true;
}

void test_case() {
  int n;
  cin >> n;
  vector<pair<ll, ll>> p(n);
  for (int i = 0; i < n; i++) cin >> p[i].first >> p[i].second;

  auto mn_it = min_element(p.begin(), p.end());
  auto mx_it = max_element(p.begin(), p.end());

  vector<pair<ll, ll>> hull[2];
  for (int _ = 0; _ < 2; _++) {
    for (auto it = mn_it; ; it++) {
      if (it == p.end()) it = p.begin();
      hull[_].push_back(*it);
      if (it == mx_it) break;
    }
    swap(mn_it, mx_it);
    assert(hull[_].size() >= 2);
    if (hull[_][0].first == hull[_][1].first) hull[_].erase(hull[_].begin());
    int sz = hull[_].size();
    assert(hull[_].size() >= 2);
    if (hull[_][sz - 1].first == hull[_][sz - 2].first) hull[_].pop_back();
    assert(hull[_].size() >= 2);
  }
  reverse(hull[1].begin(), hull[1].end());

  ll need = n / 10;
  vector<pair<ll, ll>> ans;

  // (y - y1) / (x - x1) = (y2 - y1) / (x2 - x1)
  // y = (y2 - y1) * (x - x1) / (x2 - x1) + y1
  for (ll i[2]{0, 0}, x = mn_it->first + 1; need and x < mx_it->first; ) {
    for (int _ = 0; _ < 2; _++) {
      while (i[_] < hull[_].size() - 1 and hull[_][i[_] + 1].first <= x) {
        i[_]++;
      }
      assert(i[_] < hull[_].size() - 1);
    }

    auto largest_y = [&](int hi, ll x, bool strict) {
      ll x1 = hull[hi][i[hi]].first;
      ll y1 = hull[hi][i[hi]].second;
      ll x2 = hull[hi][i[hi] + 1].first;
      ll y2 = hull[hi][i[hi] + 1].second;
      ll num = (y2 - y1) * (x - x1), den = x2 - x1;
      assert(den > 0);
      ll y = y1 + (num - (num < 0 ? den - 1 : 0)) / den;
      if (strict and num % den == 0) y--;
      return y;
    };

    ll nx = min(hull[0][i[0] + 1].first, hull[1][i[1] + 1].first);

    auto go = [&]() {
      while (x < nx and need) {
        ll y[2]{largest_y(0, x, false), largest_y(1, x, true)};
        assert(y[1] - y[0] >= -1);
        if (y[1] - y[0] == 0) break;
        for (ll yy = y[0] + 1; yy <= y[1] and need; yy++) {
          ans.push_back({x, yy});
          need--;
        }
        x++;
      }
    };

    go();

    ll L = x, R = nx;
    while (L != R) {
      ll tot = L + R;
      ll m = (tot - (tot < 0)) / 2;
      ll y[2]{largest_y(0, x, false), largest_y(1, x, true)};
      assert(y[1] - y[0] >= -1);
      if (y[1] - y[0] > 0) R = m;
      else L = m + 1;
    }
    x = L;

    go();
    assert(!need or x == nx);
    x = nx;
  }

  if (need) cout << "-1\n";
  else {
    sort(ans.begin(), ans.end());
    ans.resize(unique(ans.begin(), ans.end()) - ans.begin());
    assert(ans.size() == n / 10);

    vector<pt> poly(n);
    for (int j = 0; j < n; j++) poly[j].x = p[j].first, poly[j].y = p[j].second;
    for (int i = 0; i < ans.size(); i++) {
      assert(insideConvexPoly(poly, pt{(long double)ans[i].first, (long double)ans[i].second}, true));
      cout << ans[i].first << " " << ans[i].second << "\n";
    }
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t = 1;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    // cout << "Case " << cs << ": ";
    test_case();
  }

  return 0;
}