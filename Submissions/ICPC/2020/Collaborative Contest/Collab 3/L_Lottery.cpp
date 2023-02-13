#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int MOD = 1e9 + 7;

int main() {
  int t;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    int n;
    scanf("%d", &n);

    map<ll, int> mp;
    for (int i = 0; i < n; i++) {
      int a, x;
      scanf("%d %d", &a, &x);

      mp[a] += x;
    }

    for (auto [a, x] : mp) {
      if (x > 2) {
        if (x & 1) {
          mp[a] = 1;
          mp[a + 1] += x / 2;
        } else {
          mp[a] = 2;
          mp[a + 1] += x / 2 - 1;
        }
      }
    }

    ll dp1 = 1, dp2 = 1;
    for (auto it = mp.rbegin(); it != mp.rend(); it++) {
      auto [a, x] = *it;

      ll _a = -1;
      if (it != mp.rbegin()) {
        it--;
        _a = it->first;
        it++;
      }
      if (_a != a + 1) { dp2 = dp1; }

      ll ndp1, ndp2;
      if (x == 0) {
        ndp1 = ndp2 = dp1;
      } else if (x == 1) {
        ndp1 = (dp1 * 2) % MOD;
        ndp2 = dp2;
      } else if (x == 2) {
        ndp1 = (dp1 * 2 + dp2) % MOD;
        ndp2 = dp2;
      }

      dp1 = ndp1;
      dp2 = ndp2;
    }

    printf("Case #%d: %lld\n", cs, dp1);
  }

  return 0;
}