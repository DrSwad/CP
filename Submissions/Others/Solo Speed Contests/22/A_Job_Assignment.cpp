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

  int ans = INT_MAX;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      int curr = i == j ? a[i] + b[i] : max(a[i], b[j]);
      ans = min(ans, curr);
    }
  }

  cout << ans << endl;

  return 0;
}