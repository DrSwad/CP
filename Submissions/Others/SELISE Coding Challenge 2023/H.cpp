#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, k;
  cin >> n >> k;

  vector<ll> a(n);
  for (ll &i : a) cin >> i;

  int l = -1, r = n;
  while (r - l > 1) {
    int m = (r + l) / 2;
    int cnt = 0;
    for (int i = m; i < n; i++) {
      cnt += a[m] % a[i] == 0;
    }
    if (cnt >= k) l = m;
    else r = m;
  }

  cout << (l == -1 ? -1 : l + 1) << "\n";

  return 0;
}
