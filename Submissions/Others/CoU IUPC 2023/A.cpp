#include <bits/stdc++.h>
using namespace std;

const int mod = 1e9 + 7;

int add(int a, int b) {
  int c = a + b;
  return c < mod ? c : c - mod;
}

int mul(int a, int b) {
  return 1ll * a * b % mod;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;

  vector<int> a(n);
  for (int &i : a) cin >> i;

  int L = 1;
  for (int i = 1; i <= 9; i++) {
    L = lcm(i, L);
  }

  vector<int> divL;
  for (int i = 1; i <= L; i++) {
    if (L % i == 0) divL.push_back(i);
  }

  int sz = divL.size();
  vector<int> dp(sz, 0);
  dp[0] = 1;

  for (int i = 0; i < n; i++) {
    vector<int> ndp = dp;

    for (int j = 0; j < sz; j++) {
      int g = gcd(divL[j] * a[i], L);
      int at = find(divL.begin(), divL.end(), g) - divL.begin();
      ndp[at] = add(ndp[at], dp[j]);
    }

    swap(dp, ndp);
  }

  cout << dp.back() << "\n";

  return 0;
}