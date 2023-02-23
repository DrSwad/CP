#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int n;
  cin >> n;

  vector<int> a(n), b(n);
  for (int i = 0; i < n; i++) {
    cin >> a[i] >> b[i];
  }

  vector<int> order(n);
  iota(order.begin(), order.end(), 0);

  int ans = 1e9;

  do {
    int mx = 0, cur = 0;
    for (int i : order) {
      cur += a[i];
      mx = max(mx, cur);
      cur -= b[i];
    }
    ans = min(ans, mx);
  } while (next_permutation(order.begin(), order.end()));

  cout << ans << "\n";

  return 0;
}