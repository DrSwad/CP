#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;

  vector<int> a(n);
  for (int &i: a) cin >> i;
  a.insert(a.begin(), 0);

  vector<long long> ans(n + 1, 0);
  vector<int> order(n + 1);
  iota(order.begin(), order.end(), 0);
  sort(
    order.begin(),
    order.end(),
    [&](int i, int j) {
    return a[i] < a[j];
  }
    );

  for (int oi = n, mn = n; oi > 0; ) {
    int v = a[order[oi]];
    int noi = oi;
    while (noi and a[order[noi]] == v) {
      mn = min(mn, order[noi]);
      noi--;
    }

    ans[mn] += 1ll * (v - a[order[noi]]) * (n - noi);

    oi = noi;
  }

  for (int i = 1; i <= n; i++) {
    cout << ans[i] << "\n";
  }

  return 0;
}