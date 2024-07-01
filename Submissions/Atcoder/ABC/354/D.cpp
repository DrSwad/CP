#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int a, b, c, d;
  cin >> a >> b >> c >> d;

  // number of x in [l, r) s.t. x = rem (mod mod)
  auto remainder_occurrence_in_range =
    [&](int l, int r, int rem, int mod) {
      int ret = (r - l) / mod;
      while ((r + mod) % mod != (l + mod) % mod) {
        ret += (r - 1 + mod) % mod == rem;
        r--;
      }
      return ret;
    };

  int cell_areas[2][4] = {
    {2, 1, 0, 1},
    {1, 2, 1, 0}
  };

  long long ans = 0;
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 4; j++) {
      ans +=
        1ll
        * remainder_occurrence_in_range(a, c, j, 4)
        * remainder_occurrence_in_range(b, d, i, 2)
        * cell_areas[i][j];
    }
  }

  cout << ans << "\n";

  return 0;
}