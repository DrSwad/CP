#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n, m;
  cin >> n >> m;

  int pdivs = 0;
  for (int p = 2; p <= 1e5; p++) {
    if (m % p == 0) {
      pdivs++;
      while (m % p == 0) {
        m /= p;
      }
    }
  }
  if (m > 1) pdivs++;

  vector<int> divs;
  for (int d = 1; (long long)d * d <= n; d++) {
    if (n % d == 0) {
      divs.push_back(d);
      if (d != n / d) divs.push_back(n / d);
    }
  }

  int ans;
  if (pdivs == 0) ans = 0;
  else {
    ans = 1;
    for (int d : divs) {
      if (d <= pdivs) {
        ans = max(ans, d);
      }
    }
  }

  cout << ans << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t = 1;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    // cout << "Case " << cs << ": ";
    test_case();
  }

  return 0;
}