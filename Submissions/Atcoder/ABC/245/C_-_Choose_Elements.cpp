#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, k;
  cin >> n >> k;

  vector<int> a(n), b(n);
  for (int &i : a) cin >> i;
  for (int &i : b) cin >> i;

  bool dp_a = true, dp_b = true;
  for (int i = 1; i < n; i++) {
    bool ndp_a = (dp_a and abs(a[i] - a[i - 1]) <= k) or (dp_b and abs(a[i] - b[i - 1]) <= k);
    bool ndp_b = (dp_a and abs(b[i] - a[i - 1]) <= k) or (dp_b and abs(b[i] - b[i - 1]) <= k);
    dp_a = ndp_a;
    dp_b = ndp_b;
  }

  cout << (dp_a or dp_b ? "Yes" : "No") << "\n";

  return 0;
}