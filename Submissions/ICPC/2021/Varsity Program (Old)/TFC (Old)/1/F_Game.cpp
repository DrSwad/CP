#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;

  vector<double> dp(n + 1);
  dp[n] = 0;

  vector<double> pref(60);
  pref[0] = 0;
  for (int i = 1; i < 60; i++) {
    pref[i] = pref[i - 1] + (double)i / (1ll << i);
  }

  for (int i = n - 1; i >= 0; i--) {
    int msb = 63 - __builtin_clzll((long long)n + i);
    int turns = msb + 1;
    double fail_probability = 1.0 / (1 << turns);
    dp[i] = pref[turns] + dp[i + 1] * (1 - fail_probability) + turns * fail_probability;
  }

  cout << fixed << setprecision(15) << dp[0] << "\n";

  return 0;
}