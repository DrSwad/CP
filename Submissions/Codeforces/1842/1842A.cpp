#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n[2];
  cin >> n[0] >> n[1];

  long long sum[2] = {0};
  for (int it = 0; it < 2; it++) {
    for (int i = 0; i < n[it]; i++) {
      int x;
      cin >> x;
      sum[it] += x;
    }
  }

  if (sum[0] > sum[1]) cout << "Tsondu\n";
  else if (sum[1] > sum[0]) cout << "Tenzing\n";
  else cout << "Draw\n";
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