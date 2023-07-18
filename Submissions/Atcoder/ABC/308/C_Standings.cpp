#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;

  vector<int> a(n), b(n);
  for (int i = 0; i < n; i++) {
    cin >> a[i] >> b[i];
  }

  vector<int> order(n);
  iota(order.begin(), order.end(), 0);
  sort(
    order.begin(),
    order.end(),
    [&](int i, int j) {
      long long res_i = 1ll * a[i] * (a[j] + b[j]);
      long long res_j = 1ll * a[j] * (a[i] + b[i]);
      if (res_i != res_j) return res_i > res_j;
      return i < j;
    }
  );

  for (int i = 0; i < n; i++) {
    if (i) cout << " ";
    cout << order[i] + 1;
  }
  cout << "\n";

  return 0;
}