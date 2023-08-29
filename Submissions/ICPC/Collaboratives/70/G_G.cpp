#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int D, M;
  cin >> D >> M;

  vector<int> d(M);
  for (int &i : d) cin >> i;

  int ans = 0;
  int w = 2;
  for (int m = 1; m <= M; m++) {
    for (int i = 1; i <= d[m - 1]; i++) {
      if (w == 0 and i == 13) ans++;
      w = (w + 1) % 7;
    }
  }

  cout << ans << "\n";
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