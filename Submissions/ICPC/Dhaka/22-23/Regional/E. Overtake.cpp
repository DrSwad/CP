#include <bits/stdc++.h>
using namespace std;

double eps = 1e-5;

// Returns min time needed when car1 is overtaken first
double solve(int l1, int s1, int d1, int l2, int s2, int d2, int l0, int s0) {
  // Go to lane2, in order to overtake car1
  double lane_fix_time = (double)max(0, l2 - d2) / s2;

  // Min time to overtake car1
  double overtake1_time;
  // If car1 is not slower than car0, then car0 would never be able to overtake
  if (s1 >= s0) return -1;
  overtake1_time = lane_fix_time + (double)(d1 + lane_fix_time * s1 + l0) / (s0 - s1);
  // If car2 is faster than car1, then car0 needs to wait for car2 to give it enough space to overtake car1
  if (s2 > s1) {
    overtake1_time = max(overtake1_time, (double)max(0, (l0 + l2) - (d2 - d1)) / (s2 - s1));
  }
  // But if car2 is not faster than car1, then car0 must be able to overtake car1 before car2 comes too close
  else {
    if ((d2 + overtake1_time * s2) - (d1 + overtake1_time * s1) + eps < (l0 + l2)) {
      return -1;
    }
  }

  // After overtaking car1, car0 should go at full speed to overtake car2 as soon as possible
  double pos0 = (d1 + overtake1_time * s1) + l0;
  double pos2 = (d2 + overtake1_time * s2);
  if (s2 >= s0) return -1;
  double overtake2_time = overtake1_time + max((double)0, l0 - (pos0 - pos2)) / (s0 - s2);

  return overtake2_time;
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
