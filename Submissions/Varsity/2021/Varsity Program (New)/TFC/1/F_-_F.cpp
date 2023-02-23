#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

void test_case() {
  int n;
  cin >> n;

  vector<ll> a(n);
  for (ll &i : a) cin >> i;

  ll ans = 0;
  for (int i = n - 1; i >= 1; i--) {
    if (a[i] == 1 and a[i - 1] >= 2) {
      a[i]--;
      a[i - 1] -= 2;
      ans++;
    }
  }

  for (int i = 0; i < n; i++) {
    if (a[i] >= 3 and a[i] % 2 == 1) {
      a[i] -= 3;
      ans++;
    }
  }

  for (int i = n - 1, j = 0; i >= 0 and j <= i; ) {
    if (i == j) {
      ans += a[i] / 3;
      break;
    }

    ll i_take = a[i] / 2;
    ll j_take = a[j];
    ll take = min(i_take, j_take);
    a[i] -= take * 2;
    a[j] -= take;
    ans += take;
    if (a[i] <= 1) i--;
    if (a[j] == 0) j++;
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