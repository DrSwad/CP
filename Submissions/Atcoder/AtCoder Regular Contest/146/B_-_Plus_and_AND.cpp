#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int B = 30;

void test_case() {
  int n, m, k;
  cin >> n >> m >> k;

  vector<int> a(n);
  for (int &i : a) cin >> i;

  sort(a.begin(), a.end());
  vector<ll> pref(n + 1);
  pref[0] = 0;
  for (int i = 0; i < n; i++) {
    pref[i + 1] = pref[i] + a[i];
  }

  function<bool(int, int)> check = [&](int b, int ans) {
    int up = lower_bound(a.begin(), a.end(), ans + (1 << b)) - a.begin();
    int low = lower_bound(a.begin(), a.end(), ans) - a.begin();
    if (up < k) return false;

    int need = max(0, k - (up - low));
    ll moves = 1ll * need * ans - (pref[low] - pref[low - need]);
    return moves <= m;
  };

  int ans = 0;
  for (int b = B - 1; b >= 0; b--) {
    int nans = ans | 1 << b;
    if (check(b, nans)) ans = nans;
  }

  cout << ans << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t = 1;
  // cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    // cout << "Case " << cs << ": ";
    test_case();
  }

  return 0;
}