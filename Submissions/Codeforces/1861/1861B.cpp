#include <bits/stdc++.h>
using namespace std;

void test_case() {
  string a, b;
  cin >> a >> b;

  int n = a.length();
  assert(b.length() == n);

  for (int i = 0; i < n - 1; i++) {
    if (a[i] == '0' and b[i] == '0' and a[i + 1] == '1' and b[i + 1] == '1') {
      cout << "YES\n";
      return;
    }
  }

  cout << "NO\n";
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