#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int a, b;
  cin >> a >> b;
  cout << a + b << endl;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t = 1;

  for (int cs = 1; cs <= t; cs++) {
    // cout << "Case " << cs << ": ";
    test_case();
  }

  return 0;
}