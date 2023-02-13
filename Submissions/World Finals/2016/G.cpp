#include <bits/stdc++.h>
using namespace std;

pair<int, int> normalize(int n, int d) {
  assert(d != 0);
  int g = gcd(n, d);
  n /= g;
  d /= g;
  if (d < 0) {
    n = -n;
    d = -d;
  }
  return make_pair(n, d);
}

bool compare(const pair<int, int> &f1, const pair<int, int> &f2) {
  auto [n1, d1] = f1;
  auto [n2, d2] = f2;
  return (long long)n1 * d2 < (long long)n2 * d1;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int n;
  cin >> n;

  vector<tuple<int, int, int>> p(n);
  for (auto &t : p) {
    cin >> get<0>(t) >> get<1>(t) >> get<2>(t);
  }

  long long ans = 0;

  for (int i = 0; i < n; i++) {
    for (int it = 0; it < 2; it++) {
      auto [ixs, ixe, iy] = p[i];
      int ix = it == 0 ? ixs : ixe;

      vector<tuple<int, int, int>> slopes;

      for (int j = 0; j < n; j++) {
        auto [jxs, jxe, jy] = p[j];

        if (iy != jy) {
          auto ss = normalize(jxs - ix, jy - iy);
          auto se = normalize(jxe - ix, jy - iy);

          int sign = compare(ss, se) ? -1 : 1;
          slopes.push_back(make_tuple(ss.first, ss.second, sign * (j + 1)));
          sign = -sign;
          slopes.push_back(make_tuple(se.first, se.second, sign * (j + 1)));
        }
      }

      sort(slopes.begin(), slopes.end(), [&](const auto &s1, const auto &s2) {
        auto [n1, d1, i1] = s1;
        auto [n2, d2, i2] = s2;

        pair<int, int> f1(n1, d1);
        pair<int, int> f2(n2, d2);

        bool c1 = compare(f1, f2);
        bool c2 = compare(f2, f1);

        return !c1 and !c2 ? i1 < i2 : c1;
      });

      long long curr = abs(ixs - ixe);

      for (int j = 0; j < (int)slopes.size(); j++) {
        auto [sx, sy, si] = slopes[j];

        int id = abs(si) - 1;
        auto [xs, xe, y] = p[id];
        int sign = si < 0 ? 1 : -1;

        curr += abs(xe - xs) * sign;
        ans = max(ans, curr);
      }
    }
  }

  cout << ans << "\n";

  return 0;
}