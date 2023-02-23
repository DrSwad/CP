#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int x;
  cin >> x;

  set<int> s{40, 70, 90};
  auto it = s.upper_bound(x);
  if (it == s.end()) cout << "expert\n";
  else cout << *it - x << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int t = 1;
  // cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    // cout << "Case " << cs << ": ";
    test_case();
  }

  return 0;
}