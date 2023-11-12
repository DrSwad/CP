#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n, k;
  cin >> n >> k;

  vector<int> a(n);
  for (int &i : a) cin >> i, i--;

  vector<int> inc, dec;
  for (int i = 0; i < n; i++) {
    if (inc.empty() or a[i] > a[inc.back()]) inc.push_back(i);
  }
  for (int i = n - 1; i >= 0; i--) {
    if (dec.empty() or a[i] > a[dec.back()]) dec.push_back(i);
  }

  vector<int> vis(k, -1);
  for (int i = 0; i < n; i++) {
    vis[a[i]] = i;
  }

  for (int i = 0; i < k; i++) {
    if (i) cout << " ";
    if (vis[i] == -1) cout << "0";
    else {
      int l = *lower_bound(
        inc.begin(),
        inc.end(),
        vis[i],
        [&](int i, int j) {
          return a[i] < a[j];
        }
      );
      int r = *lower_bound(
        dec.begin(),
        dec.end(),
        vis[i],
        [&](int i, int j) {
          return a[i] < a[j];
        }
      );

      cout << 2 * (r - l + 1);
    }
  }
  cout << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    test_case();
  }

  return 0;
}