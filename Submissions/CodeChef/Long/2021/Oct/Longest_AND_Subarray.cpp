#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n;
  cin >> n;

  int ans = 0;
  for (int i = 0; i < 30; i++) {
    int st = 1 << i;
    int en = min(1 << (i + 1), n + 1);
    ans = max(ans, en - st);
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