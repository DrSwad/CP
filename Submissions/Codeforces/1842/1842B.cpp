#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n, x;
  cin >> n >> x;

  int knowledge = 0;
  for (int it = 0; it < 3; it++) {
    bool flag = true;
    for (int i = 0; i < n; i++) {
      int a;
      cin >> a;

      if ((x & a) == a and flag) {
        knowledge |= a;
      }
      else {
        flag = false;
      }
    }
  }

  if (knowledge == x) cout << "Yes\n";
  else cout << "No\n";
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