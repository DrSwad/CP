#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;

  vector<int> a(n);
  for (int &i : a) cin >> i;
  sort(a.begin(), a.end());

  int msb = 31 - __builtin_clz(n);
  vector<vector<int>> jump(msb + 1, vector<int>(2 * n));

  for (int i = 0; i < n; i++) jump[0][i] = i - 1;
  for (int i = n; i < 2 * n; i++) {
    jump[0][i] = max(jump[0][i - 1], i - a[i - n]);
  }

  for (int e = 1; e <= msb; e++) {
    for (int i = 0; i < 2 * n; i++) {
      int j = jump[e - 1][i];
      jump[e][i] = j <= -1 ? -2 : jump[e - 1][j];
    }
  }

  vector<int> ans(n + 1, 0);

  for (int st = n - 1; st < 2 * n; st++) {
    int en = st - n;
    
    int at = st - (st < n ? 1 : a[st - n]);
    int jumps = 1;

    for (int e = msb; e >= 0 and at > en; e--) {
      if (jump[e][at] >= en) {
        at = jump[e][at];
        jumps += 1 << e;
      }
    }

    ans[jumps] = st - (n - 1);
  }

  for (int d = n - 1; d >= 0; d--) {
    ans[d] = max(ans[d], ans[d + 1]);
  }

  int q;
  cin >> q;

  while (q--) {
    int d;
    cin >> d;
    cout << ans[d] << "\n";
  }

  return 0;
}
