#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, k;
  cin >> n >> k;

  vector<int> a(n);
  for (int &i : a) cin >> i;

  vector<ll> all_pref(n + 1);
  vector<ll> positive_pref(n + 1);

  all_pref[0] = positive_pref[0] = 0;
  for (int i = 1; i <= n; i++) {
    all_pref[i] = all_pref[i - 1] + a[i - 1];
    positive_pref[i] = positive_pref[i - 1] + max(0, a[i - 1]);
  }

  ll ans = 0;
  for (int i = 1; i + k - 1 <= n; i++) {
    ans = max(ans, positive_pref[i - 1] + max(0ll, all_pref[i + k - 1] - all_pref[i - 1]) + positive_pref[n] - positive_pref[i + k - 1]);
  }

  cout << ans << "\n";

  return 0;
}