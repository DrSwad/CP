#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;

  vector<int> a(n);
  for (int &i : a) cin >> i;
  sort(a.begin(), a.end());

  if (n == 1) cout << a[0] << "\n";
  else {
    ll ans = 0;
    for (int i = 0; i < n; i++) {
      ans += 1ll * a[i] * (i + 2);
    }
    ans -= a[n - 1];
    cout << ans << "\n";
  }

  return 0;
}