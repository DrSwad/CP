#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;

  string s;
  cin >> s;

  int cur = 0, mx = 0;
  for (int l = 0, r = -1; r < 2 * n - 1; ) {
    cur += s[++r] == 'W';
    if (r - l + 1 > n) cur -= s[l++] == 'W';
    mx = max(mx, cur);
  }

  cout << mx << "\n";

  return 0;
}
