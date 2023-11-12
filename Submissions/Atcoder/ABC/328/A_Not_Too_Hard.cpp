#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, x;
  cin >> n >> x;

  int ans = 0;
  while (n--) {
    int s;
    cin >> s;
    if (s <= x) ans += s;
  }

  cout << ans << "\n";

  return 0;
}