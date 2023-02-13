#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  long long n;
  cin >> n;

  auto f = [&](long long a, long long b) {
    return a * a * a + a * a * b + a * b * b + b * b * b;
  };

  long long ans = 1e18;

  for (long long a = 0; a <= 1e6; a++) {
    long long bL = 0, bR = 1e6;
    while (bL != bR) {
      long long b = (bL + bR) / 2;
      if (f(a, b) >= n) bR = b;
      else bL = b + 1;
    }
    ans = min(ans, f(a, bL));
  }

  cout << ans << "\n";

  return 0;
}