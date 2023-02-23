#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

void test_case() {
  ll n2, n3, n4;
  cin >> n2 >> n3 >> n4;

  ll c = n3 / 2;
  ll ans = 0;

  ll take = min(n4, c);
  ans += take;
  n4 -= take;
  c -= take;

  take = min(n2 / 2, c);
  ans += take;
  n2 -= take * 2;
  c -= take;

  n4 = min(n4, 2 * n2);
  ans += (n2 + 2 * n4) / 5;

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