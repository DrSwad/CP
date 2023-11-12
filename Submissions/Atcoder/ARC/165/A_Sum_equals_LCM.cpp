#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n;
  cin >> n;

  int p = -1;
  for (int i = 2; i * i <= n; i++) {
    if (n % i == 0) {
      p = i;
      break;
    }
  }
  if (p == -1) p = n;

  while (n % p == 0) n /= p;

  if (n == 1) cout << "No\n";
  else cout << "Yes\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    test_case();
  }

  return 0;
}