#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;

  long long ans = 1;
  for (int i = 1; i <= n; i++) {
    (ans *= i) %= MOD;
  }

  cout << ans << "\n";

  return 0;
}