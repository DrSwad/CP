#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int MOD = 998244353;

void test_case() {
  int n, k;
  cin >> n >> k;

  vector<int> a(n);
  for (int &i : a) cin >> i;

  ll ans = 1;
  for (int b = 0; b < k; b++) {
    int tot_zero = 0;
    for (int i = 0; i < n; i++) {
      tot_zero += (a[i] >> b & 1) == 0;
    }

    ll curr = tot_zero + 1;
    for (int i = 0; i < n; i++) {
      if (a[i] >> b & 1) {
        curr += tot_zero + 1;
      }
      else {
        tot_zero -= 1;
      }
    }

    (ans *= curr % MOD) %= MOD;
  }

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