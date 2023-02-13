#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int k, s;
  cin >> k >> s;

  long long ans = 0;
  for (int i = 0; i <= min(s, k); i++) {
    int rem = s - i;
    if (rem > 2 * k) continue;
    int min_z = max(0, rem - k);
    int max_z = min(k, rem);
    ans += max_z - min_z + 1;
  }

  cout << ans << "\n";

  return 0;
}