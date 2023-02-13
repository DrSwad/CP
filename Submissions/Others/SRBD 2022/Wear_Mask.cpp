#include <bits/stdc++.h>
using namespace std;

void test_case() {
  long long W, H;
  cin >> W >> H;

  cout << ((W + 2) / 3) * ((H + 2) / 3) << "\n";
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