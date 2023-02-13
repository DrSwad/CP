#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> point;
const int MOD = 1e9 + 7, INV2 = (MOD + 1) / 2;

#define x first
#define y second

inline ll area(point a, point b, point c) {
  ll ret = (b.x % MOD - a.x % MOD) * (c.y % MOD - a.y % MOD) % MOD - (b.y % MOD - a.y % MOD) * (c.x % MOD - a.x % MOD) % MOD;
  if (ret < 0) ret += MOD;
  return ret;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;

  vector<point> p(n);
  for (auto & [x, y] : p) cin >> x >> y;
  sort(
    p.begin(),
    p.end(),
    [&](const auto&p1, const auto&p2) {
    return p1.y * p2.x < p1.x * p2.y;
  }
    );

  vector<point> hull;
  hull.push_back({0, 0});
  for (int i = 0; i < n; i++) {
    auto [hx, hy] = hull.back();
    auto [px, py] = p[i];
    hull.push_back({hx + px, hy + py});
  }
  for (int i = 0; i < n - 1; i++) {
    auto [hx, hy] = hull.back();
    auto [px, py] = p[i];
    hull.push_back({hx - px, hy - py});
  }
  n = hull.size();

  // Pick: A = i + b / 2 - 1
  // => 2 * A = 2 * i + b - 2
  // => i = (2 * A - b + 2) / 2

  ll A = 0;
  for (int i = 1; i < n - 1; i++) {
    A += area(hull[0], hull[i], hull[i + 1]);
    A %= MOD;
  }

  ll B = 0;
  for (int i = 0; i < n; i++) {
    int j = (i + 1) % n;
    ll add = gcd(abs(hull[j].x - hull[i].x), abs(hull[j].y - hull[i].y));
    B += add;
    B %= MOD;
  }

  ll I = (A - B + 2) * INV2 % MOD;

  cout << (n == 2 ? gcd(hull[1].x, hull[1].y) : (B + I + MOD - 1) % MOD) << "\n";

  return 0;
}