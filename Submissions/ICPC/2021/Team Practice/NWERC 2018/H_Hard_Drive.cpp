#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, c, b;
  cin >> n >> c >> b;

  vector<bool> broken(n, false);
  for (int i = 0; i < n; i++) {
    int pos;
    cin >> pos;
    broken[pos - 1] = true;
  }

  string ans(n, '0');
  for (int i = n - 1; i > 0; ) {
    if (broken[i] or c < 2) i--;
    else ans[i] = '1', c -= 2, i -= 2;
  }

  if (c) ans[0] = '1';

  cout << ans << "\n";

  return 0;
}