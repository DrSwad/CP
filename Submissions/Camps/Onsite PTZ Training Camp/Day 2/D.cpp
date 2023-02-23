#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

ll nC2(int n) {
  return 1ll * n * (n - 1) / 2;
}

ll f(int n, int p) {
  return 1ll * p * (2 * n - 1 - p) / 2;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  ll k;
  cin >> n >> k;

  int pL = 0, pR = n;
  // debug(pL, pR);

  {
    int l = 0, r = n + 1;
    while (l + 1 < r) {
      int m = (l + r) / 2;
      if (nC2(m) > k) r = m;
      else l = m;
    }
    pR = min(pR, r - 1);
  }
  // debug(pL, pR);

  {
    int l = -1, r = n + 1;
    while (l + 1 < r) {
      int m = (l + r) / 2;
      if (f(n, m) < k) l = m;
      else r = m;
    }
    pL = max(pL, l + 1);
  }
  // debug(pL, pR);
  // debug(f(n, 4));

  ll ans = -1;
  if (pL <= pR) {
    {
      int p = pL;
      int m = n - p;
      ans = max(ans, nC2(p) + nC2(m));
    }
    {
      int p = pR;
      int m = n - p;
      ans = max(ans, nC2(p) + nC2(m));
    }
  }

  cout << ans << "\n";

  return 0;
}