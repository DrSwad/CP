#include <bits/stdc++.h>
using namespace std;

void test_case() {
  long long n;
  cin >> n;

  if (n % 2 == 1) {
    cout << "-1\n";
    return;
  }

  n /= 2;

  if (n <= 1) {
    cout << "-1\n";
    return;
  }

  long long x = n / 6 * 2 + ((n % 6 + 2) / 3);
  long long y = n / 6 * 3 + (n % 6 / 2);

  cout << x << " " << y << "\n";
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