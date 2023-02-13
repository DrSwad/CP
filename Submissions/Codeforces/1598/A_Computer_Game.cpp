#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n;
  cin >> n;

  string r[2];
  cin >> r[0] >> r[1];

  for (int i = 0; i < n; i++) {
    if (r[0][i] == '1' and r[1][i] == '1') {
      cout << "NO\n";
      return;
    }
  }

  cout << "YES\n";
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