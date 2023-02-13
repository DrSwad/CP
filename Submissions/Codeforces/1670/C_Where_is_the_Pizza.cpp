#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;

void test_case() {
  int n;
  cin >> n;

  vector<int> a(n), b(n), d(n);
  for (int &i : a) cin >> i, i--;
  for (int &i : b) cin >> i, i--;
  for (int &i : d) cin >> i;

  vector<int> b_val_at(n);
  for (int i = 0; i < n; i++) {
    b_val_at[b[i]] = i;
  }

  vector<bool> vis(n, false);
  int ans = 1;
  for (int i = 0; i < n; i++) {
    if (!vis[i]) {
      vector<int> cycle;
      int at = i;
      while (!vis[at]) {
        cycle.push_back(at);
        vis[at] = true;
        at = b_val_at[a[at]];
      }

      bool fixed = false;
      for (int i : cycle) {
        if (d[i] != 0) {
          fixed = true;
          break;
        }
      }

      if (!fixed and cycle.size() > 1) {
        (ans *= 2) %= MOD;
      }
    }
  }

  cout << ans << "\n";
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