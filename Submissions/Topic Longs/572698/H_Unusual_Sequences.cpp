#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int mod = 1e9 + 7;

ll binExp(ll a, ll e, ll m = mod) {
  if (e == -1) e = m - 2;
  ll ret = 1;
  while (e) {
    if (e & 1) ret = ret * a % m;
    a = a * a % m, e >>= 1;
  }
  return ret;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int x, y;
  cin >> x >> y;
  if (y % x != 0) {
    cout << "0\n";
    return 0;
  }

  vector<int> divs;
  for (int d = 1; d * d <= y; d++) {
    if (y % d == 0) {
      divs.push_back(d);
      if (d * d != y) divs.push_back(y / d);
    }
  }
  sort(divs.begin(), divs.end());

  int sz = divs.size();
  vector<int> dp(sz);

  for (int i = sz - 1; i >= 0; i--) {
    dp[i] = binExp(2, (y / divs[i]) - 1);
    for (int j = i + 1; j < sz; j++) {
      if (divs[j] % divs[i] == 0) {
        (dp[i] += mod - dp[j]) %= mod;
      }
    }
    if (divs[i] == x) {
      cout << dp[i] << "\n";
      return 0;
    }
  }

  return 0;
}