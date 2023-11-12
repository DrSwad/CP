#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, d, p;
  cin >> n >> d >> p;

  vector<int> f(n);
  for (int &i : f) cin >> i;

  sort(f.begin(), f.end(), greater<int>());

  long long sum = accumulate(f.begin(), f.end(), 0ll);
  long long ans = sum;

  for (int i = 0; i < n; i++) {
    sum -= f[i];
    ans = min(ans, sum + 1ll * (i + 1 + d - 1) / d * p);
  }

  cout << ans << "\n";

  return 0;
}