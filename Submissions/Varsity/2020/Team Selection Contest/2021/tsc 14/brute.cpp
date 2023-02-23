#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<ll, ll> pairll;
typedef vector<ll> vll;
typedef vector<pairll> vpair;

long long readInt() {
  long long in;
  scanf("%lld", &in);
  return in;
}

struct Point {
  ll x, y;

  bool operator<(const Point b) {
    if (x == b.x) { return y < b.y; }
    return x < b.x;
  }
};

bool comp(Point a, Point b) {
  if (a.y == b.y) { return a.x < b.x; }
  return a.y < b.y;
}

bool compi(Point a, Point b) {
  if (a.y == b.y) { return a.x > b.x; }
  return a.y > b.y;
}
ll fac[100069];

const ll mod = 1000000007LL;
int main() {
  ll T = readInt();
  fac[0] = 1;
  for (ll i = 1; i < 100069; i++) { fac[i] = (i * fac[i - 1]) % mod; }
  while (T--) {
    vector<Point> points, part1, part2;
    ll N = readInt(), ans = 0;
    for (ll i = 0; i < 2 * N; i++) {
      ll x = readInt(), y = readInt();
      points.push_back({x, y});
    }

    sort(points.begin(), points.end());
    for (ll i = 0; i < N; i++) { part1.push_back(points[i]); }
    for (ll i = N; i < 2 * N; i++) { part2.push_back(points[i]); }
    if (part1[N - 1].x >= part2[0].x) {
      ans = 0;
    } else {
      sort(part1.begin(), part1.end(), comp);
      sort(part2.begin(), part2.end(), compi);

      debug() << "part1";
      for (auto p : part1) { debug() << name(p.x) name(p.y); }
      debug() << "part2";
      for (auto p : part2) { debug() << name(p.x) name(p.y); }

      ans = 1;
      ll cnt = 0;
      for (ll i = 0; i < N; i++) {
        debug() << name(part1[i].y) name(part2[i].y);
        if (part1[i].y == part2[i].y) {
          ans = 0;
          break;
        } else if (part1[i].y > part2[i].y) {
          ans = 1;
          break;
        } else
          cnt++;
      }
      if (ans) {

        ans = (ans * fac[cnt]) % mod;
        ans = (ans * fac[N - cnt]) % mod;
      }
    }

    printf("%lld\n", ans);
  }
}
