#include <bits/stdc++.h>
using namespace std;

void test_case() {
  long long k;
  cin >> k;
  k--;

  int n;
  cin >> n;

  if (k >= (1ll << (n + 2))) {
    cout << "-1\n";
    return;
  }

  long long carry = 1;
  for (int i = n + 1; i >= 2; i--) {
    if (k >> i & 1) carry *= 2;
  }
  k %= 4;

  long long ans = carry * (k == 0 ? 1 : k == 3 ? 4 : 2);
  cout << ans << "\n";
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
