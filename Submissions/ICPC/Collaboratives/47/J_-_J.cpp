#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;

  vector<int> a(n);
  for (int &i : a) cin >> i;

  int ans = 0;
  for (int g = 1; g <= 100; g++) {
    bool flag = false;
    for (int l = 0; l < n and !flag; ) {
      if (a[l] % g != 0) {
        l++;
        continue;
      }

      int gg = a[l];
      int r = l + 1;
      while (!flag and r < n and a[r] % g == 0) gg = __gcd(gg, a[r]), r++;

      if (gg == g) flag = true;

      l = r;
    }
    ans += flag;
  }

  cout << ans << "\n";

  return 0;
}