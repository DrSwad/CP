#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n;
  cin >> n;

  vector<int> a(n);
  for (int &i : a) cin >> i, i = (i == 1 ? 1 : -1);

  vector<int> p(n + 1);
  p[0] = 0;
  int mn_p = 0, mn_i = 0;
  int mx_d = 0;
  int l = -1, r = -1;
  for (int i = 0; i < n; i++) {
    p[i + 1] = p[i] + a[i];
    if (p[i + 1] < mn_p) {
      mn_p = p[i + 1];
      mn_i = i + 1;
    }

    if (p[i + 1] - mn_p > mx_d) {
      mx_d = p[i + 1] - mn_p;
      l = mn_i;
      r = i;
    }
  }

  if (mx_d == 0) cout << "1\n1\n";
  else {
    vector<int> ans;
    ans.push_back(l);
    for (int i = l, s = 0; i <= r; i++) {
      s += a[i];
      if (s == 1) {
        ans.push_back(i + 1);
        s = 0;
      }
    }

    cout << ans.size() << "\n";
    for (int i = 0; i < ans.size(); i++) {
      if (i) cout << " ";
      cout << ans[i] + 1;
    }
    cout << "\n";
  }
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