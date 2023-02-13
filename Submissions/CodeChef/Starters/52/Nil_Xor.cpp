#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n, x;
  cin >> n >> x;

  int overall = 1, ans = 0;
  for (int i = 0; i < 30; i++) {
    int noverall = 0, nans = 0;
    for (int kb = 0; kb < 2; kb++) {
      int nb = n >> i & 1;
      int nnb = nb ^ kb;
      int xb = x >> i & 1;
      if ((nnb & xb) == 0) {
        noverall += overall;
        if (kb < nb) nans += overall;
        if (kb == nb) nans += ans;
      }
    }

    swap(overall, noverall);
    swap(ans, nans);
  }

  cout << ans << "\n";
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