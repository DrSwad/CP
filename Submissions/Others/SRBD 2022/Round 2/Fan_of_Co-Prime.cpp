#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int MOD = 1000000007;

ll binExp(ll a, ll e, ll m = MOD) {
  if (e == -1) e = m - 2;
  ll ret = 1;
  while (e) {
    if (e & 1) ret = ret * a % m;
    a = a * a % m, e >>= 1;
  }
  return ret;
}

void test_case() {
  int p, n;
  cin >> p >> n;
  cout << binExp(p, n - 1) * (p - 1) % MOD << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t = 1;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    cout << "Case " << cs << ": ";
    test_case();
  }

  return 0;
}