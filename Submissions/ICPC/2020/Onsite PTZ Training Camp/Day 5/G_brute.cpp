#include <bits/stdc++.h>

using namespace std;

int main() {
  int n;
  cin >> n;
  vector<int> f(n);

  f[1] = f[2] = 1;
  for (int i = 3; i < n; i++) f[i] = f[i - f[i - 1]] + f[i - 1 - f[i - 2]];

  vector<int> freq(2000, 0), ans(2000, 0);

  for (int i = 1; i < n; i++) {
    freq[f[i]]++;
    ans[f[i]] = __builtin_ctz(f[i]) + 1;
  }

  for (int i = 2; i < 50; i++) {
    cout << i << ' ' << freq[i] << ' ' << ans[i] << endl;
    assert(freq[i] == ans[i]);
  }

  return 0;
}