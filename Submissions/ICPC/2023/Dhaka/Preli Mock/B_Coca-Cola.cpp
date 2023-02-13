#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int m, n, k;
  cin >> m >> n >> k;

  cout << ((n * k <= m) ? "Yes\n" : "No\n");
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