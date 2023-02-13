#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n;
  cin >> n;

  int a, b, c;

  c = 1;
  n--;

  if (n % 2 == 0) {
    a = n / 2 - 1;
    b = n / 2 + 1;

    if (a % 2 == 0) a--, b++;
  }
  else {
    a = n / 2;
    b = n / 2 + 1;
  }

  cout << a << " " << b << " " << c << "\n";
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