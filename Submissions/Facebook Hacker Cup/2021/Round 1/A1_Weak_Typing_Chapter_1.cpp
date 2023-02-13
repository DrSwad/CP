#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n;
  cin >> n;

  string w;
  cin >> w;

  int ans = 0;
  for (int i = 0, prv = 0; i < n; i++) {
    if (w[i] != 'F') {
      if (prv != 0 and w[i] != prv) ans++;
      prv = w[i];
    }
  }

  cout << ans << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int t;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    cout << "Case #" << cs << ": ";
    test_case();
  }

  return 0;
}