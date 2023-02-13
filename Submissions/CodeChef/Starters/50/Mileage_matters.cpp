#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n, x, y, a, b;
  cin >> n >> x >> y >> a >> b;

  if (x * b < y * a) cout << "PETROL\n";
  else if (x * b > y * a) cout << "DIESEL\n";
  else cout << "ANY\n";
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