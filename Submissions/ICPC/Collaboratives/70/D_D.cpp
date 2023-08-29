#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;

  vector<int> h(n);
  for (int &i : h) cin >> i;

  int mx_h = *max_element(h.begin(), h.end());

  set<int> rem;
  vector<set<int>> h_pos(mx_h + 1);

  for (int i = 0; i < n; i++) {
    rem.insert(i);
    h_pos[h[i]].insert(i);
  }

  int ans = 0;
  while (!rem.empty()) {
    ans++;
    int at = *rem.begin();
    while (true) {
      rem.erase(at);
      h_pos[h[at]].erase(at);

      int nxt_h = h[at] - 1;
      auto it = h_pos[nxt_h].upper_bound(at);
      if (it != h_pos[nxt_h].end()) at = *it;
      else break;
    }
  }

  cout << ans << "\n";

  return 0;
}