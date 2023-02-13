#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, inc, dec;
  cin >> n >> inc >> dec;

  if (1ll * inc * dec<n or inc + dec - 1> n) {
    cout << "-1\n";
    return 0;
  }

  int rem = n - inc;
  int l = 1;
  vector<int> ans;

  for (int seg = 0; seg < inc; seg++) {
    int take = min(rem, dec - 1);
    rem -= take;
    int len = 1 + take;
    int r = l + len - 1;

    for (int i = r; i >= l; i--) ans.push_back(i);

    l = r + 1;
  }

  for (int i = 0; i < n; i++) {
    if (i) cout << " ";
    cout << ans[i];
  }
  cout << "\n";

  return 0;
}