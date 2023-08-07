#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;

  vector<int> coins(6, 0);
  for (int i = 1; i <= 5; i++) {
    cin >> coins[i];
  }

  int ans = 0;
  function<void(int, int)> go =
    [&](int at, int sum) {
      if (at == 7) {
        ans += sum == n;
        return;
      }
      for (int i = 1; i <= 5; i++) {
        if (coins[i] and sum + i <= n) {
          coins[i]--;
          go(at + 1, sum + i);
          coins[i]++;
        }
      }
    };

  go(1, 0);

  cout << ans << "\n";

  return 0;
}