#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;

  vector<int> a(n);
  for (int &i : a) cin >> i;

  set<pair<int, int>> st;
  for (int i = 0; i < n; i++) {
    st.insert({a[i], i});
  }

  vector<vector<int>> ans;
  for (int low = 1 << 20; low; low /= 2) {
    auto it = st.lower_bound(make_pair(low, 0));
    if (it == st.end()) continue;

    ans.push_back({});
    int sub = it->first;

    while (it != st.end()) {
      auto [aa, i] = *it;
      ans.back().push_back(i);
      it = st.erase(it);
      a[i] -= sub;
    }
    for (int i : ans.back()) {
      st.insert(make_pair(a[i], i));
    }
  }

  cout << ans.size() << "\n";
  for (auto &v : ans) {
    cout << v.size() << "\n";
    for (int i = 0; i < v.size(); i++) {
      if (i) cout << " ";
      cout << v[i] + 1;
    }
    cout << "\n";
    cout << "- " << v[0] + 1 << "\n";
  }

  return 0;
}