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

  vector<int> p2(n + 1);
  p2[0] = 1;
  for (int exp = 1; exp <= n; exp++) {
    p2[exp] = mul(p2[exp - 1], 2);
  }

  int max_a = *max_element(a.begin(), a.end());
  vector<int> freq(max_a + 1, 0);
  for (int i : a) freq[i]++;

  vector<int> dp(max_a + 1, 0);
  for (int d = max_a; d >= 1; d--) {
    int cnt = 0;
    for (int mul = d; mul <= max_a; mul += d) {
      cnt += freq[mul];
      if (mul > d) dp[d] = add(dp[d], mod - dp[mul]);
    }
    dp[d] = add(dp[d], add(p2[cnt], mod - 1));
  }

  cout << dp[1] << "\n";

  return 0;
}