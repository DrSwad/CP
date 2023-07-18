#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, m;
  cin >> n >> m;

  vector<int> a(n);
  for (int &i : a) cin >> i;

  long long ans = 0;
  for (int i : a) ans += i;

  set<pair<int, int>> st;
  for (int i = 0; i < n; i++) {
    st.insert({a[i], i});
  }

  while (m--) {
    auto [val, i] = *prev(st.end()); st.erase(prev(st.end()));
    int nval = val / 2;
    ans -= val - nval;
    st.insert({nval, i});
  }

  cout << ans << "\n";

  return 0;
}