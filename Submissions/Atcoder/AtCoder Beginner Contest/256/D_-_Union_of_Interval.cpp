#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;

  set<pair<int, int>> st;

  while (n--) {
    int l, r;
    cin >> l >> r;

    auto it = st.lower_bound({l, 0});
    if (it != st.begin()) it--;

    int L = l, R = r;
    while (it != st.end() and it->first <= r) {
      if (l <= it->second) {
        L = min(L, it->first);
        R = max(R, it->second);
        it = st.erase(it);
      }
      else it++;
    }
    st.insert({L, R});
  }

  for (auto [l, r] : st) {
    cout << l << " " << r << "\n";
  }

  return 0;
}