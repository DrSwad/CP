#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

void test_case() {
  int n, k;
  cin >> n >> k;

  vector<ll> a(n);
  for (ll &i : a) cin >> i;

  vector<ll> b(n);
  for (int i = 0; i < n; i++) {
    b[i] = a[i] + (i + 1);
  }

  sort(b.begin(), b.end(), greater<ll>());
  ll mx_sum = 0;
  for (int i = 0; i < k; i++) {
    mx_sum += b[i];
  }

  ll ans = 0;
  for (int i = 0; i < n; i++) {
    ans += a[i] + k;
  }
  ans -= mx_sum;
  ans -= (ll)k * (k - 1) / 2;

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