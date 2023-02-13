#include <bits/stdc++.h>
using namespace std;

const int N = 1e6 + 2;
int f[2 * N];

void test_case() {
  int n;
  cin >> n;

  vector<int> a(n);
  for (int &i : a) cin >> i;

  int ans = 0;

  for (int i : a) {
    int same = 0;
    vector<int> divs;

    for (int j : a) {
      if (i == j) {
        same++;
        continue;
      }

      int k = abs(i - j);
      for (int d = 1; d * d <= k; d++) {
        if (k % d != 0) continue;
        divs.push_back(d), f[d]++;
        int dd = k / d;
        if (d != dd) divs.push_back(dd), f[dd]++;
      }
    }

    if (same >= n / 2) {
      cout << "-1\n";
      for (int d : divs) f[d] = 0;
      return;
    }

    for (int d : divs) {
      if (same + f[d] >= n / 2) {
        ans = max(ans, d);
      }
    }

    for (int d : divs) f[d] = 0;
  }

  cout << ans << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int t = 1;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    // cout << "Case " << cs << ": ";
    test_case();
  }

  return 0;
}