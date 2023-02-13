#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n;
  cin >> n;

  set<int> st;
  for (int i = 1; i <= n; i++) st.insert(i);

  vector<int> a(n);
  for (int i = 0, xr = 0; i < n; i++) {
    int nxr = *st.begin();
    a[i] = xr ^ nxr;
    xr = nxr;
    st.erase(nxr);
  }

  for (int i = 0; i < n; i++) {
    if (i) cout << " ";
    cout << a[i];
  }
  cout << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t = 1;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    // cout << "Case " << cs << ": ";
    test_case();
  }

  return 0;
}