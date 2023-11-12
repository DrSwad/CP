#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, q;
  cin >> n >> q;

  vector<int> h(n);
  for (int &i : h) cin >> i;

  set<pair<int, int>> st[2];
  for (int it = 0; it < 2; it++) {
    st[it].emplace(0, h[0]);
    for (int i = 1; i < n; i++) {
      if (st[it].rbegin()->second < h[i]) {
        st[it].emplace(i, h[i]);
      }
    }
    reverse(h.begin(), h.end());
  }

  while (q--) {
    char type;
    cin >> type;

    if (type == 'U') {
      int i;
      cin >> i;
      i--;
      cin >> h[i];

      int at_h = h[i];

      for (int it = 0; it < 2; it++) {
        auto iter = st[it].lower_bound({i, 0});
        while (iter != st[it].end() and iter->second < at_h) {
          iter = st[it].erase(iter);
        }

        if (iter == st[it].begin() or prev(iter)->second < at_h) {
          st[it].emplace(i, at_h);
        }

        i = (n - 1) - i;
      }
    }
    else {
      int i;
      cin >> i;
      i--;

      int at[2];
      for (int it = 0; it < 2; it++) {
        auto iter = st[it].lower_bound({i + ((it == 0) == (type == 'R')), 0});
        at[it] = iter == st[it].end() ? -1 : iter->first;
        if (at[it] != -1 and it == 1) at[it] = (n - 1) - at[it];
        i = (n - 1) - i;
      }

      int ans;
      if (at[0] == -1) ans = at[1];
      else if (at[1] == -1) ans = at[0];
      else if (h[at[0]] > h[at[1]]) ans = at[0];
      else ans = at[1];

      cout << ans + 1 << "\n";
    }
  }

  return 0;
}