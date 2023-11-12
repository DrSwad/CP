#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int s, d, k;
  cin >> s >> d >> k;

  int buns = 2 * (s + d);
  int mids = s + 2 * d;

  if (buns >= k + 1 and mids >= k) cout << "YES\n";
  else cout << "NO\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    cout << "Case #" << cs << ": ";
    test_case();
  }

  return 0;
}