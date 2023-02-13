#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;

  vector<char> d(n);
  vector<int> l(n);
  for (int i = 0; i < n; i++) {
    cin >> d[i] >> l[i];
  }

  vector<int> cnt_l, cnt_r;
  for (int i = 0; i < n; i++) {
    if (d[i] == 'y') {
      cnt_l.push_back(0);
      for (int j = i - 1, mx = -1; j >= 0; j--) {
        if (d[j] == 'n' and l[j] >= l[i]) break;
        if (d[j] == 'n') mx = max(mx, l[j]);
        if (d[j] == 'y' and l[j] < l[i] and l[j] > mx) cnt_l.back()++;
      }

      cnt_r.push_back(0);
      for (int j = i + 1, mx = -1; j < n; j++) {
        if (d[j] == 'n' and l[j] >= l[i]) break;
        if (d[j] == 'n') mx = max(mx, l[j]);
        if (d[j] == 'y' and l[j] <= l[i] and l[j] > mx) cnt_r.back()++;
      }
    }
  }

  // debug(cnt_l, cnt_r);

  int nn = cnt_l.size();
  assert(cnt_r.size() == nn);
  int ans = 0;

  for (int i = 0; i < nn; i++) {
    ans += cnt_l[i] == 0 and cnt_r[i] == 0;
  }

  cout << ans << "\n";

  return 0;
}