#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;
const int mod = 1e9 + 7;

int add(int a, int b) {
  int c = a + b;
  return c < mod ? c : c - mod;
}

int mul(int a, int b) {
  return 1ll * a * b % mod;
}

int n;
int a[N];
int fact[N];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  fact[0] = 1;
  for (int i = 1; i < N; i++) fact[i] = 1ll * fact[i - 1] * i % mod;

  cin >> n;
  vector<int> freq1(n, 0), freq2(n, 0);
  for (int i = 0; i < n; i++) cin >> a[i], freq1[a[i]]++;
  for (int i = 1; i <= n; i++) {
    freq2[abs((i - 1) - (n - i))]++;
  }

  if (freq1 != freq2) cout << "0\n";
  else {
    int ans = 1;
    for (int i : freq1) {
      ans = mul(ans, fact[i]);
    }
    cout << ans << "\n";
  }

  return 0;
}