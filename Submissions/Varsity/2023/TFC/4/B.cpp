#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, q;
  cin >> n >> q;

  vector<int> a(n + 1);
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }
  a[0] = INT_MAX;

  set<int> st;
  for (int i = 1; i <= n; i++) {
    if (a[i] % a[i - 1] != 0) {
      st.insert(i);
    }
  }

  while (q--) {
    int type;
    cin >> type;

    if (type == 1) {
      int i, x;
      cin >> i >> x;

      st.erase(i);
      st.erase(i + 1);

      a[i] = x;
      if (a[i] % a[i - 1] != 0) st.insert(i);
      if (i + 1 <= n and a[i + 1] % a[i] != 0) st.insert(i + 1);
    }
    else {
      int i;
      cin >> i;

      cout << *prev(st.upper_bound(i)) << "\n";
    }
  }

  return 0;
}