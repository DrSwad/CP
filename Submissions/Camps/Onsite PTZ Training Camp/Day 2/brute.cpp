#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

ll nC2(int n) {
  return 1ll * n * (n - 1) / 2;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  ll k;
  cin >> n >> k;

  vector<int> vp;
  for (int p = 0; p <= n; p++) {
    ll sum = nC2(p);
    ll L = 0, R = 1ll * p * (n - p);
    if (sum + L <= k and k <= sum + R) {
      vp.push_back(p);
    }
  }

  ll ans = -1;
  // debug(vp);
  for (int p : vp) {
    int m = n - p;
    ans = max(ans, nC2(p) + nC2(m));
  }

  cout << ans << "\n";

  return 0;
}