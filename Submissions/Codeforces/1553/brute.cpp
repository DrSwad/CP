#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int n;
  cin >> n;

  vector<int> a(n);
  for (int &i : a) cin >> i;

  for (int i = 1; i <= n; i++) {
    long long ans = 0;
    for (int j = 0; j < i; j++) {
      for (int k = 0; k < i; k++) {
        ans += a[j] % a[k];
      }
    }
    if (i > 1) cout << " ";
    cout << ans;
  }
  cout << "\n";

  return 0;
}