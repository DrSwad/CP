#include <bits/stdc++.h>
using namespace std;

const int B = 30;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;

  vector<map<int, int>> pref(B);
  for (int i = 0; i < n; i++) {
    int l, r;
    cin >> l >> r;

    for (int b = 0; b < B; b++) {
      int p = 1 << b;
      if (r - l + 1 >= p) {
        pref[b][0]++;
      }
      else {
        pref[b][l % p]++;
        pref[b][r % p + 1]--;
        if (l % p > r % p) {
          pref[b][0]++;
        }
      }
    }
  }

  vector<int> ans(B);
  for (int b = 0; b < B; b++) {
    ans[b] = 0;
    int sum = 0;
    for (auto [v, f] : pref[b]) {
      sum += f;
      ans[b] = max(ans[b], sum);
    }
  }

  int q;
  cin >> q;

  while (q--) {
    int w;
    cin >> w;
    int lsb = __builtin_ctz(w);
    cout << ans[lsb] << "\n";
  }

  return 0;
}