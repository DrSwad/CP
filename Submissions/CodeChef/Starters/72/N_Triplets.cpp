#include <bits/stdc++.h>
using namespace std;

const int N = 1e5;

void test_case() {
  int n;
  cin >> n;

  int d;
  for (d = 2; d < min(N, n); d++) {
    if (n % d == 0) break;
  }

  if (d < n and d * d != n and n % d == 0) {
    cout << "1 " << d << " " << n / d << "\n";
  }
  else cout << "-1\n";
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