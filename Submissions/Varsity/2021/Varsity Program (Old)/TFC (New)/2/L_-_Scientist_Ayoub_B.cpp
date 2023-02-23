#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n;
  cin >> n;

  const int st = 1e8;
  for (int i = 0; i < n; i++) {
    if (i) cout << " ";
    cout << st + i;
  }
  cout << "\n";
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