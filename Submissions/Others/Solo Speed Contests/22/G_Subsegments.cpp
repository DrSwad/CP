#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, k;
  cin >> n >> k;

  vector<int> a(n);
  for (int &i : a) cin >> i;

  map<int, int> f;
  for (int i = 0; i < k - 1; i++) f[a[i]]++;

  set<int> st;
  for (auto [v, cnt] : f) {
    if (cnt == 1) st.insert(v);
  }

  for (int i = k - 1; i < n; i++) {
    if (i >= k) {
      if (f[a[i - k]] == 1) st.erase(a[i - k]);
      if (f[a[i - k]] == 2) st.insert(a[i - k]);
      f[a[i - k]]--;
    }

    if (f[a[i]] == 0) st.insert(a[i]);
    if (f[a[i]] == 1) st.erase(a[i]);
    f[a[i]]++;

    if (st.empty()) cout << "Nothing\n";
    else cout << (*st.rbegin()) << "\n";
  }

  return 0;
}