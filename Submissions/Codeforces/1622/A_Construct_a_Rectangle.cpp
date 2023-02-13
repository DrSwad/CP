#include <bits/stdc++.h>
using namespace std;

bool solve(int l1, int l2, int l3) {
  return l1 == l2 + l3 or l1 % 2 == 0 and l2 == l3;
}

void test_case() {
  int l1, l2, l3;
  cin >> l1 >> l2 >> l3;

  if (solve(l1, l2, l3) or solve(l2, l1, l3) or solve(l3, l1, l2)) {
    cout << "YES\n";
  }
  else cout << "NO\n";
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