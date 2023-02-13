#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

ll solve(int sdx, int sdy, ll lx, ll ly, int edx, int edy) {
  assert(lx > 0);
  assert(ly >= 0);

  ll ret = 0;

  // start
  ret += sdx != 1;

  // end
  if (lx > ly) {
    ret += edx != 0;
  }
  else {
    ret += edy != 0;
  }

  // middle
  ll rem;
  if (lx >= ly) {
    ret += ly * 2;
    rem = lx - ly;
  }
  else {
    ret += lx * 2 - 1;
    rem = ly - (lx - 1);
  }

  if (rem > 0) ret++, rem--;
  ret += 2 * rem;

  return ret;
}

void test_case() {
  ll ax, ay, bx, by, cx, cy;
  cin >> ax >> ay >> bx >> by >> cx >> cy;

  int sdx = 0, sdy = 0;
  int sx = 0, sy = 0;

  int edx, edy;
  int ex, ey;

  // Make b the center
  if (abs(ax - bx) + abs(ay - by) == 2) swap(bx, cx), swap(by, cy);
  if (abs(cx - bx) + abs(cy - by) == 2) swap(bx, ax), swap(by, ay);

  edx = min(ax, cx) < bx;
  edy = min(ay, cy) < by;

  ex = bx - edx;
  ey = by - edy;

  ll lx = ex - sx;
  ll ly = ey - sy;

  if (lx < 0) lx = -lx, sdx ^= 1, edx ^= 1;
  if (ly < 0) ly = -ly, sdy ^= 1, edy ^= 1;

  ll ans = LLONG_MAX;
  if (lx == 0 and ly == 0) ans = min(ans, (ll)(sdx != edx or sdy != edy));
  if (lx > 0) ans = min(ans, solve(sdx, sdy, lx, ly, edx, edy));
  if (ly > 0) ans = min(ans, solve(sdy, sdx, ly, lx, edy, edx));

  cout << ans << "\n";
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