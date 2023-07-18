#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, m;
  cin >> n >> m;

  vector<int> a(m);
  for (int &i : a) cin >> i, i--;

  vector<bool> a_vis(n, false);
  for (int i : a) a_vis[i] = true;

  int ans = n;
  for (int x = 1; x <= n; x++) {
    int cur_ans = 0;
    int remaining = m;
    int at = 0;
    vector<bool> cur_vis(n, false);

    while (!cur_vis[at] and remaining) {
      cur_vis[at] = true;
      cur_ans++;
      if (a_vis[at]) remaining--;
      at += x;
      if (at >= n) at -= n;
    }

    if (remaining == 0) {
      ans = min(ans, cur_ans);
    }
  }

  cout << ans << "\n";

  return 0;
}