#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;

  vector<int> a(n);
  for (int &i : a) cin >> i;

  vector<int> divs;
  for (int i = 1; i * i <= n; i++) {
    if (n % i == 0) {
      divs.push_back(i);
      if (n / i != i) {
        divs.push_back(n / i);
      }
    }
  }

  long long ans = 0;

  for (int div : divs) {
    vector<int> mx(div, 0);
    for (int i = 0; i < n; i++) {
      int rem = i % div;
      mx[rem] = max(mx[rem], a[i]);
    }

    vector<bool> good(n);
    for (int i = 0; i < n; i++) {
      int rem = i % div;
      good[i] = a[i] == mx[rem];
    }

    vector<int> right(n);

    if (!good[n - 1]) right[n - 1] = 0;
    else {
      right[n - 1] = 1;
      while (right[n - 1] < n and good[(n - 1 + right[n - 1]) % n]) right[n - 1]++;
    }

    for (int i = n - 2; i >= 0; i--) {
      right[i] = !good[i] ? 0 : min(n, 1 + right[i + 1]);
    }

    int inv_div = n / div;

    vector<int> coprime(inv_div + 1);
    coprime[0] = 0;
    for (int i = 1; i <= inv_div; i++) {
      coprime[i] = coprime[i - 1] + (gcd(i, inv_div) == 1);
    }

    for (int i = 0; i < n; i++) {
      ans += coprime[right[i] / div];
    }
  }

  cout << ans - n << "\n";

  return 0;
}