#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

__int128 gcd(__int128 a, __int128 b) {
  if (a < b) swap(a, b);
  if (b == 0) return a;
  return gcd(b, a % b);
}

struct Fraction {
  __int128 up, down;
  Fraction() : up(0), down(1) {}
  Fraction(ll up) : up(up), down(1) {}
  Fraction(ll up, ll down) : up(up), down(down) {
    normalize();
  }
  void normalize() {
    if (down < 0) down = -down, up = -up;
    if (up == 0) down = 1;
    __int128 g = gcd(up >= 0 ? up : -up, down);
    up /= g, down /= g;
  }
  Fraction operator+(Fraction r) {
    Fraction ret(up * r.down + down * r.up, down * r.down);
    ret.normalize();
    return ret;
  }
  Fraction operator-(Fraction r) {
    r.up = -r.up;
    return *this + r;
  }
  Fraction operator*(Fraction r) {
    Fraction ret(up * r.up, down * r.down);
    ret.normalize();
    return ret;
  }
  Fraction operator/(Fraction r) {
    swap(r.up, r.down);
    return *this * r;
  }
  bool operator<(Fraction r) {
    return up * r.down < r.up * down;
  }
};

Fraction max(Fraction r1, Fraction r2) {
  return r1 < r2 ? r2 : r1;
}

// Returns min time needed when car1 is overtaken first
double solve(int l1, int s1, int d1, int l2, int s2, int d2, int l0, int s0) {
  // Go to lane2, in order to overtake car1
  Fraction lane_fix_time = Fraction(max(0, l2 - d2), s2);

  // Min time to overtake car1
  Fraction overtake1_time;
  // If car1 is not slower than car0, then car0 would never be able to overtake
  if (s1 >= s0) return -1;
  overtake1_time = lane_fix_time + (Fraction(d1) + lane_fix_time * s1 + l0) / (s0 - s1);
  // If car2 is faster than car1, then car0 needs to wait for car2 to give it enough space to overtake car1
  if (s2 > s1) {
    overtake1_time = max(overtake1_time, Fraction(max(0, (l0 + l2) - (d2 - d1)), s2 - s1));
  }
  // But if car2 is not faster than car1, then car0 must be able to overtake car1 before car2 comes too close
  else {
    if ((Fraction(d2) + overtake1_time * s2) - (Fraction(d1) + overtake1_time * s1) < (l0 + l2)) {
      return -1;
    }
  }

  // After overtaking car1, car0 should go at full speed to overtake car2 as soon as possible
  Fraction pos0 = (Fraction(d1) + overtake1_time * s1) + l0;
  Fraction pos2 = (Fraction(d2) + overtake1_time * s2);
  if (s2 >= s0) return -1;
  Fraction overtake2_time = overtake1_time + max(Fraction(0), Fraction(l0) - (pos0 - pos2)) / (s0 - s2);

  return (double)overtake2_time.up / overtake2_time.down;
}

void test_case() {
  int l1, s1, d1;
  cin >> l1 >> s1 >> d1;

  int l2, s2, d2;
  cin >> l2 >> s2 >> d2;

  int l0, s0;
  cin >> l0 >> s0;

  double ans;
  bool possible = false;

  for (int it = 0; it < 2; it++) {
    double cur = solve(l1, s1, d1, l2, s2, d2, l0, s0);
    if (cur > 0) {
      if (possible) ans = min(ans, cur);
      else ans = cur, possible = true;
    }

    swap(l1, l2);
    swap(s1, s2);
    swap(d1, d2);
  }

  if (possible) cout << ans << "\n";
  else cout << "-1\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cout << fixed << setprecision(4);

  int t = 1;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    cout << "Case " << cs << ": ";
    test_case();
  }

  return 0;
}
