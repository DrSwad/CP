#include <bits/stdc++.h>

using namespace std;

int main() {

  int n;
  cin >> n;
  vector<int> a(n), b(n);
  long long ans = 0;
  for (int i = 0; i < n; i++) {
    cin >> a[i] >> b[i];
    if (i) {
      ans += abs(a[i] - a[i - 1]);
      ans += abs(b[i] - b[i - 1]);
    }
  }
  cout << ans << '\n';

  return 0;
}