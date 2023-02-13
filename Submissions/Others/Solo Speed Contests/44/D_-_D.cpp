#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

void test_case() {
  ll n, m;
  cin >> n >> m;

  if (n == 1) {
    if (m == 1) {
      cout << "1\n";
    }
    else {
      cout << m - 2 << "\n";
    }
  }
  else if (m == 1) {
    cout << n - 2 << "\n";
  }
  else {
    ll ans = (n - 2) * (m - 2);
    cout << ans << "\n";
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t = 1;
  // cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    // cout << "Case " << cs << ": ";
    test_case();
  }

  return 0;
}