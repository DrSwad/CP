#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> point;
#define x first
#define y second

double dist(point p1, point p2) {
  int dx = p1.x - p2.x;
  int dy = p1.y - p2.y;
  return sqrt(1ll * dx * dx + 1ll * dy * dy);
}

void test_case() {
  point o(0, 0), p, a, b;
  cin >> p.x >> p.y;
  cin >> a.x >> a.y;
  cin >> b.x >> b.y;

  double ans = HUGE_VAL;
  ans = min(ans, max(dist(a, o), dist(a, p)));
  ans = min(ans, max(dist(b, o), dist(b, p)));
  ans = min(ans, max(dist(a, b) / 2, max(dist(a, o), dist(b, p))));
  ans = min(ans, max(dist(a, b) / 2, max(dist(a, p), dist(b, o))));

  cout << ans << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout << fixed << setprecision(10);

  int t = 1;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    // cout << "Case " << cs << ": ";
    test_case();
  }

  return 0;
}