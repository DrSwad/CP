#include <bits/stdc++.h>
using namespace std;

void test_case() {
  long long n;
  cin >> n;

  if (n == 1 or
      n == 2 or
      n == 3 or
      n == 5 or
      n == 6 or
      n == 9 or
      n == 10 or
      n == 13 or
      n == 17
  ) {
    cout << "No\n";
  }
  else {
    cout << "Yes\n";
  }
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