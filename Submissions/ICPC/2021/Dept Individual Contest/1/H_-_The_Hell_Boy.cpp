#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;

void test_case() {
  int n;
  cin >> n;

  vector<int> a(n);
  for (int &i : a) cin >> i;

  long long ans = 1;
  for (int i = 0; i < n; i++) {
    (ans *= (1 + a[i])) %= MOD;
  }

  cout << (ans + MOD - 1) % MOD << "\n";
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