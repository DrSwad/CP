#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int MOD = 1e9 + 7;
const int INV2 = (MOD + 1) / 2;
const int INV3 = (MOD + 1) / 3;
const int INV6 = INV2 * 1ll * INV3 % MOD;

int add(int a, int b) {
  return (a + b) % MOD;
}

int mul(int a, int b) {
  return 1ll * a * b % MOD;
}

void test_case() {
  int n;
  cin >> n;

  ll ans = 0;
  ans = add(ans, mul(2, mul(n, mul(n + 1, mul(2 * n + 1, INV6)))));
  ans = add(ans, MOD - mul(n, mul(n + 1, INV2)));
  ans = mul(ans, 2022);

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