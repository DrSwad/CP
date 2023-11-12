#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 5;
const int A = 1e6 + 5;
const int mod = 1e9 + 7;

int n;
int a[N];
int freq[A];
int dp[A];
int p2[N];
int ans;

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

  cin >> n;
  for (int i = 0; i < n; i++) {
    cin >> a[i];
    freq[a[i]]++;
  }

  p2[0] = 1;
  for (int i = 1; i < N; i++) {
    p2[i] = mul(2, p2[i - 1]);
  }

  for (int g = A - 1; g > 1; g--) {
    int cnt = 0;

    for (int mul = g; mul < A; mul += g) {
      cnt += freq[mul];
      dp[g] = add(dp[g], mod - dp[mul]);
    }

    if (cnt) dp[g] = add(dp[g], mul(cnt, p2[cnt - 1]));

    ans = add(ans, mul(g, dp[g]));
  }

  cout << ans << "\n";

  return 0;
}