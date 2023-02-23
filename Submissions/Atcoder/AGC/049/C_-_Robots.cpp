#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;

  vector<int> a(n), b(n);
  for (int &i : a) cin >> i;
  for (int &i : b) cin >> i;

  int till = a.back() + 1;
  int ans = INT_MAX;
  int cnt = 0;

  for (int i = n - 1; i >= 0; i--) {
    int pos = a[i] - b[i];
    if (pos > 0) {
      till = min(till, pos);
    }
    else {
      int moves = 1 - pos;
      ans = min(ans, moves + max(0, cnt - moves));

      if (a[i] < till) {
        cnt++;
      }
    }
  }

  ans = min(ans, cnt);
  cout << ans << "\n";

  return 0;
}