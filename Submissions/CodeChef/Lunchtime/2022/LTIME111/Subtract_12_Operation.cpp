#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

void test_case() {
  int n;
  cin >> n;

  vector<ll> a(n);
  for (ll &i : a) cin >> i;

  for (int i = n - 1; i > 0; i--) {
    if (a[i] <= 0) continue;
    a[i - 1] -= a[i] / 2;
    a[i] -= a[i] / 2 * 2;
    if (a[i] == 1 and (a[i - 1] % 2 == 1 or (i == 1 and a[i - 1] > 0))) a[i] -= 2, a[i - 1]--;
  }

  ll ans = 0;
  for (ll i : a) ans += abs(i);

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