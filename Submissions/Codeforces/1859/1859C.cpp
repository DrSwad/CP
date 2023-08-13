#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n;
  cin >> n;

  int ans = 0;

  for (int mx = 1; mx <= n * n; mx++) {
    set<int> available;
    for (int i = 1; i <= n; i++) available.insert(i);

    int cur = -mx;
    for (int i = n; i >= 1; i--) {
      int best = mx / i;
      auto it = available.upper_bound(best);
      if (it != available.begin()) {
        it--;
        cur += i * (*it);
        available.erase(it);
      }
    }

    ans = max(ans, cur);
  }

  cout << ans << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    test_case();
  }

  return 0;
}