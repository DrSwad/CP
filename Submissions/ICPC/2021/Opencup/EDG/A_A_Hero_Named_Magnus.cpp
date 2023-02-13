#include <bits/stdc++.h>
using namespace std;

void test_case() {
  long long n;
  cin >> n;
  cout << 2 * (n - 1) + 1 << "\n";
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