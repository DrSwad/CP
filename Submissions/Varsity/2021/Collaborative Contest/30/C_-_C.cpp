#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int B = 40;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;

  vector<ll> a(n);
  for (ll &i : a) cin >> i;

  vector<ll> dp(n, 0);
  vector<int> last_at(B, n);
  for (int i = n - 1; i >= 0; i--) {
    for (int b = 0; b < B; b++) {
      if (last_at[b] == n) continue;
      int j = last_at[b];
      dp[i] = max(dp[i], dp[j] + (a[i] & a[j]));
    }
    for (int b = 0; b < B; b++) {
      if (a[i] >> b & 1) {
        last_at[b] = i;
      }
    }
  }

  cout << dp[0] << "\n";

  return 0;
}