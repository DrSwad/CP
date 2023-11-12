#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;

  vector<int> a(n + 1);
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }

  vector<int> freq(n + 1, 0);
  vector<ll> suffix_sum(n + 1, 0);

  ll ans = 0;
  for (int i = 1; i <= n; i++) {
    ans += suffix_sum[a[i]] - 1ll * freq[a[i]] * (n - i + 1);
    freq[a[i]]++;
    suffix_sum[a[i]] += n - i;
  }
  for (int i = 1; i <= n; i++) {
    ans -= 1ll * freq[i] * (freq[i] - 1) * (freq[i] - 2) / 6;
  }

  cout << ans << "\n";

  return 0;
}