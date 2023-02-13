#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

void test_case() {
  ll n, k;
  cin >> n >> k;
  ll ans = ((k - 1) / 2 + (n - k)) * 2;
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