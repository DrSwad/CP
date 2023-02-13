#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n;
  cin >> n;

  vector<pair<int, int>> v(n);
  map<int, int> f[2];
  for (auto & [a, b] : v) {
    cin >> a >> b;
    f[0][a]++;
    f[1][b]++;
  }

  long long ans = (long long)n * (n - 1) * (n - 2) / 6;
  for (auto [a, b] : v) {
    ans -= (long long)(f[0][a] - 1) * (f[1][b] - 1);
  }

  cout << ans << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int t = 1;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    // cout << "Case " << cs << ": ";
    test_case();
  }

  return 0;
}