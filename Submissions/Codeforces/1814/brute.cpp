#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int mx = 100;

void test_case() {
  int n, k;
  cin >> n >> k;

  vector<int> f(n), d(n);
  for (int &i : f) cin >> i;
  for (int &i : d) cin >> i;

  int ans = n;

  for (int l = 1; l <= mx; l++) {
    int r = l + k;

    bool possible = true;
    int got = 0;

    for (int i = 0; i < n; i++) {
      if (l <= f[i] * d[i] and f[i] * d[i] <= r) got++;
      else if (f[i] > k + 1) {
        int L = l % f[i];
        int R = r % f[i];

        if (0 < L and (k == 0 or L < R)) {
          possible = false;
        }
      }
    }

    if (possible) {
      ans = min(ans, n - got);
    }
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